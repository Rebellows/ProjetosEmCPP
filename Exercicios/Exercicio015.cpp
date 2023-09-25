#include <iostream>
using namespace std;

struct Node {
    char info;
    Node* next;

    Node(char i) {
        info = i;
        next = nullptr;
    }
};

void pushFront(Node*& head, char c) {
    Node* newNode = new Node(c);
    newNode->next = head;
    head = newNode;
}

void pushBack(Node*& head, char c) {
    Node* newNode = new Node(c);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void insertAtIndex(Node*& head, char c, unsigned pos) {
    if (pos == 0) {
        pushFront(head, c);
    } else {
        Node* newNode = new Node(c);
        Node* current = head;
        unsigned index = 0;

        while (current != nullptr && index < pos - 1) {
            current = current->next;
            index++;
        }

        if (current == nullptr) {
            cout << "ERRO" << endl;
            delete newNode;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

void popFront(Node*& head) {
    if (head == nullptr) {
        cout << "ERRO" << endl;
    } else {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void popBack(Node*& head) {
    if (head == nullptr) {
        cout << "ERRO" << endl;
    } else if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
}

void removeAtIndex(Node*& head, unsigned pos) {
    if (head == nullptr || pos == 0) {
        cout << "ERRO" << endl;
    } else {
        Node* current = head;
        unsigned index = 0;

        while (current->next != nullptr && index < pos - 1) {
            current = current->next;
            index++;
        }

        if (current->next == nullptr) {
            cout << "ERRO" << endl;
        } else {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
}

void printList(const Node* head) {
    const Node* current = head;
    while (current != nullptr) {
        cout << "|" << current->info;
        current = current->next;
    }
    cout << "|" << endl;
}

void clearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    char op, c;
    unsigned pos;
    bool fim = false;

    cout << "'<' = PUSH_FRONT / '>' = PUSH_BACK / '{' = POP_FRONT / '}' = POP_BACK '+' = INSERT / '-' = REMOVE / '.' = QUIT" << endl;

    while (!fim) {
        printList(head);
        cin >> op;
        switch (op) {
            case '<':
                cin >> c;
                pushFront(head, c);
                break;
            case '>':
                cin >> c;
                pushBack(head, c);
                break;
            case '+':
                cin >> c >> pos;
                insertAtIndex(head, c, pos);
                break;
            case '{':
                popFront(head);
                break;
            case '}':
                popBack(head);
                break;
            case '-':
                cin >> pos;
                removeAtIndex(head, pos);
                break;
            case '.':
                fim = true;
                break;
            default:
                cout << "Operacao invalida" << endl;
                break;
        }
    }

    clearList(head); // Libera a memória alocada
    return 0;
}
