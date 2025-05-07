#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/list.h>
#include <linux/slab.h>

#define DEVICE_NAME "mq"
#define CLASS_NAME  "mq_class"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gabriel D. Rebello e Gustavo S. Silva");
MODULE_DESCRIPTION("Driver de kernel para troca de mensagens em fila circular entre processos");
MODULE_VERSION("7.7.7");

static int majorNumber;
static int number_opens = 0;
static struct class *charClass = NULL;
static struct device *charDevice = NULL;

// fixado mas pode ser parametrizado
static int max_processes = 20;
static int max_messages = 8;
static int max_message_size = 128;

// parametrizado aqui
module_param(max_processes, int, 0644);
module_param(max_messages, int, 0644);
module_param(max_message_size, int, 0644);

struct message_s {
	struct list_head link;
	char *message;
	short size;
};

struct process_s {
	struct list_head link;
	char *name;
	pid_t pid;
	struct list_head messages; // eh uma lista mas vai ser a fila de mensagens ja que nao tem queue_head
	int msg_count;
}

struct list_head process_list;
int process_count = 0;

static int	dev_open(struct inode *, struct file *);
static int	dev_release(struct inode *, struct file *);
static ssize_t	dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t	dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

struct process_s *find_process_by_pid(pid_t pid) {
	struct process_s *entry = NULL;
	
	list_for_each_entry(entry, &process_list, link) {
		if (entry->pid == pid) {
			return entry;
		}
	}
	
	return NULL;
}

struct process_s *find_process_by_name(char *name) {
	struct process_s *entry = NULL;
	
	list_for_each_entry(entry, &process_list, link) {
		if (strcmp(entry->name, name) == 0) {
			return entry;
		}
	}
	
	return NULL;
}

int register_process(char *name, pid_t pid) {
	struct process_s *entry = NULL;
	
	if (process_count >= max_processes) {
		printk(KERN_INFO "MQ Driver: Maximum number of processes reached: %d.\n", max_processes);
		return 1;
	}
	
	if (find_process_by_name(name) != NULL) {
		printk(KERN_INFO "MQ Driver: Process %s is already registered.\n", name);
		return 1;
	}

	if (find_process_by_pid(pid) != NULL) {
		printk(KERN_INFO "MQ Driver: Process with pid %d is already registered.\n", pid);
		return 1;
	}

	entry = kmalloc(sizeof(struct process_s), GFP_KERNEL);
	
	if (!entry) {
		printk(KERN_INFO "MQ Driver: Memory allocation failed, this should never fail due to GFP_KERNEL flag\n");
		return 1;
	}

	strcpy(entry->name, name);
	entry->pid = pid;
	entry->msg_count = 0;
	INIT_LIST_HEAD(&entry->messages);
	list_add_tail(&entry->link, &process_list);
	process_count++;
	
	printk(KERN_INFO "MQ Driver: Process %s registered with pid %d.\n", name, pid);

	return 0;
}

int remove_process(char *name, pid_t pid) {
	struct process_s *entry = NULL;
	strut message_s *msg = NULL, *tmp = NULL;
	
	entry = find_process_by_pid(pid);
	
	if (!entry) {
		printk(KERN_INFO "MQ Driver: Process with pid %d is not registered.\n", pid);
		return 1;
	}

	list_for_each_entry(msg, tmp, &entry->messages, link) {
		list_del(&msg->link);
		kfree(msg->message);
		kfree(msg);
	}
	
	list_del(&entry->link);
	kfree(entry->name);
	kfree(entry);
	process_count--;
	
	printk(KERN_INFO "MQ Driver: Process %s with pid %d removed.\n", name, pid);

	return 0;
}

int send_message(char *name, char *message, int message_size) {
	struct process_s *entry = NULL;
	struct message_s *msg = NULL;
	
	entry = find_process_by_name(name);
	
	if (!entry) {
		printk(KERN_INFO "MQ Driver: Process %s is not registered.\n", name);
		return 1;
	}

	if (message_size > max_message_size) {
		printk(KERN_INFO "MQ Driver: Message is too long, maximum size is %d. The message will be truncated.\n", max_message_size);
		message_size = max_message_size;
	}

	msg = kmalloc(sizeof(struct message_s), GFP_KERNEL);
	
	if (!msg) {
		printk(KERN_INFO "MQ Driver: Memory allocation failed, this should never fail due to GFP_KERNEL flag\n");
		return 1;
	}

	msg->message = kmalloc(message_size, GFP_KERNEL);
	
	if (!msg->message) {
		printk(KERN_INFO "MQ Driver: Memory allocation failed, this should never fail due to GFP_KERNEL flag\n");
		kfree(msg);
		return 1;
	}

	strcpy(msg->message, message);
	msg->message[message_size] = '\0';
	msg->size = message_size;
	
	if (entry->msg_count >= max_messages) {
		struct message_s *tmp = list_first_entry(&entry->messages, struct message_s, link);
		list_del(&tmp->link);
		kfree(tmp->message);
		kfree(tmp);
		entry->msg_count--;
		printk(KERN_INFO "MQ Driver: Removed old message.\n");
	}

	list_add_tail(&msg->link, &entry->messages);
	entry->msg_count++;
	
	printk(KERN_INFO "MQ Driver: Message added to process %s with pid %d.\n", name, entry->pid);

	return 0;
}

int send_message_to_all(char *message, int message_size) {
	struct process_s *entry = NULL;
	int count = 0;
	
	list_for_each_entry(entry, &process_list, link) {
		send_message(entry->name, message, message_size);
		count++;
	}
	
	printk(KERN_INFO "MQ Driver: Message sent to %d processes.\n", count);

	return 0;
}

struct message_s *read_message(pid_t pid) {
	struct process_s *entry = NULL;
	struct message_s *msg = NULL;
	
	entry = find_process_by_pid(pid);
	
	if (!entry) {
		printk(KERN_INFO "MQ Driver: Process with pid %d is not registered.\n", pid);
		return NULL;
	}

	if (entry->msg_count == 0) {
		printk(KERN_INFO "MQ Driver: Process %s with pid %d has no messages.\n", entry->name, pid);
		return NULL;
	}
	
	msg = list_first_entry(&entry->messages, struct message_s, link);
	
	list_del(&msg->link);
	entry->msg_count--;

	printk(KERN_INFO "MQ Driver: Message read from process %s with pid %d.\n", entry->name, pid);
	
	return msg;
}

// pra baixo eh codigo do sor

static int mq_init(void)
{
	printk(KERN_INFO "MQ Driver: Initializing the LKM\n");

	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	if (majorNumber < 0) {
		printk(KERN_ALERT "MQ Driver: failed to register a major number\n");
		return majorNumber;
	}
	
	printk(KERN_INFO "MQ Driver: registered correctly with major number %d\n", majorNumber);

	charClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(charClass)) {		
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "MQ Driver: failed to register device class\n");
		return PTR_ERR(charClass);	
	}
	
	printk(KERN_INFO "MQ Driver: device class registered correctly\n");

	charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(charDevice)) {		
		class_destroy(charClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "MQ Driver: failed to create the device\n");
		return PTR_ERR(charDevice);
	}
	
	printk(KERN_INFO "MQ Driver: device class created.\n");
	
	INIT_LIST_HEAD(&list);
		
	return 0;
}

static void mq_exit(void) {
	struct process_s *entry = NULL, *p_tmp = NULL;
	struct message_s *msg = NULL, *m_tmp = NULL;

	list_for_each_entry_safe(entry, p_tmp, &process_list, link) {
		list_for_each_entry_safe(msg, m_tmp, &entry->messages, link) {
			list_del(&msg->link);
			kfree(msg->message);
			kfree(msg);
		}
		list_del(&entry->link);
		kfree(entry->name);
		kfree(entry);
		process_count--;
	}

	device_destroy(charClass, MKDEV(majorNumber, 0));
	class_unregister(charClass);
	class_destroy(charClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	printk(KERN_INFO "MQ Driver: goodbye.\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
	number_opens++;
	printk(KERN_INFO "MQ Driver: device has been opened %d time(s)\n", number_opens);
	printk("Process id: %d, name: %s\n", (int) task_pid_nr(current), current->comm);

	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "MQ Driver: device successfully closed\n");

	return 0;
}

// falta atualizar esses dois do codigo do sor

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
	int error = 0;
	struct message_s *entry = list_first_entry(&list, struct message_s, link);
   
	if (list_empty(&list)) {
		printk(KERN_INFO "Simple Driver: no data.\n");
		
		return 0;
	}	
	
	// copy_to_user has the format ( * to, *from, size) and returns 0 on success
	error = copy_to_user(buffer, entry->message, entry->size);

	if (!error) {				// if true then have success
		printk(KERN_INFO "Simple Driver: sent %d characters to the user\n", entry->size);
		list_delete_head();
		
		return 0;
	} else {
		printk(KERN_INFO "Simple Driver: failed to send %d characters to the user\n", error);
		
		return -EFAULT;			// Failed -- return a bad address message (i.e. -14)
	}
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
	if (len < MSG_SIZE) {
		list_add_entry(buffer);
		list_show();

		printk(KERN_INFO "Simple Driver: received %zu characters from the user\n", len);
		
		return len;
	} else {
		printk(KERN_INFO "Simple Driver: too many characters to deal with (%d)\n", len);
		
		return 0;
	}
}

module_init(mq_init);
module_exit(mq_exit);
