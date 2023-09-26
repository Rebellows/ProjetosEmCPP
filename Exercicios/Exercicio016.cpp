#include <iostream>

using namespace std;

struct Node {
    char info;
    Node* next, * prev;

    Node(char i) {
        info = i;
        prev = next = nullptr;
    }
    ~Node () { 
        cout << "-" << endl; }
};

void pushFrente(Node*& head, Node*& tail, char c) {
    Node* node = new Node(c);
    if (head == nullptr) {
        head = tail = node;
    }
    else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void pushTras(Node*& head, Node*& tail, char c) {
    Node* node = new Node(c);
    if (tail == nullptr) {
        head = tail = node;
    }
    else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
}

void insereNoAlvo(Node*& head, char c, unsigned pos) {
    Node* aux = head;
    for (unsigned i = 0; i < pos && aux != nullptr; i++) {
        aux = aux->next;
    }
    if (aux == nullptr) {
        cout << "ERRO" << endl;
        return;
    }

    Node* node = new Node(c);
    node->prev = aux->prev;
    node->next = aux;
    if (aux->prev != nullptr) {
        aux->prev->next = node;
    }
    aux->prev = node;
    if (head == aux) {
        head = node;
    }
}

void popFrente(Node*& head, Node*& tail) {
    if (head != nullptr) {
        Node* aux = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        else {
            head->prev = nullptr;
        }
        delete aux;
    }
    else {
        cout << "ERRO" << endl;
    }
}

void popTras(Node*& head, Node*& tail) {
    if (tail != nullptr) {
        Node* aux = tail;
        tail = tail->prev;
        if (tail == nullptr) {
            head = nullptr;
        }
        else {
            tail->next = nullptr;
        }
        delete aux;
    }
    else {
        cout << "ERRO" << endl;
    }
}

void removeNoAlvo(Node*& head, Node*& tail, unsigned pos) {
    Node* aux = head;
    for (unsigned i = 0; i < pos && aux != nullptr; i++) {
        aux = aux->next;
    }
    if (aux == nullptr) {
        cout << "ERRO" << endl;
        return;
    }

    if (aux->prev != nullptr) {
        aux->prev->next = aux->next;
    }
    else {
        head = aux->next;
    }

    if (aux->next != nullptr) {
        aux->next->prev = aux->prev;
    }
    else {
        tail = aux->prev;
    }

    delete aux;
}

void imprimeLista(const Node* head) {
    const Node* aux = head;
    while (aux != nullptr) {
        cout << "|" << aux->info;
        aux = aux->next;
    }
    cout << "|" << endl;
}

void limpaLista(Node*& head) {
    while (head != nullptr) {
        Node* aux = head;
        head = head->next;
        delete aux;
    }
}

void inverteLista(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (tail != nullptr) {
        Node* temp = head;
        head = tail;
        tail = temp;
    }
}

int main() {
    Node* head = nullptr, * tail = nullptr;
    char op, c;
    unsigned pos;
    bool fim = false;
    while (!fim) {
        imprimeLista(head);
        cin >> op;
        switch (op) {
        case '<':
            cin >> c;
            cout << "+" << endl;
            pushFrente(head, tail, c);
            break;
        case '>':
            cin >> c;
            cout << "+" << endl;
            pushTras(head, tail, c);
            break;
        case '+':
            cin >> c >> pos;
            cout << "+" << endl;
            insereNoAlvo(head, c, pos);
            break;
        case '{':
            cout << "-" << endl;
            popFrente(head, tail);
            break;
        case '}':
            cout << "-" << endl;
            popTras(head, tail);
            break;
        case '-':
            cout << "-" << endl;
            cin >> pos;
            removeNoAlvo(head, tail, pos);
            break;
        case '.':
            fim = true;
            break;
        }
    }
    inverteLista(head, tail);
    imprimeLista(head);
    limpaLista(head);
    return 0;
}
