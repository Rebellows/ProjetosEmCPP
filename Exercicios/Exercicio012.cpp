//criando lista duplamente encadeada e imprimindo-a normalmente e ao contrário
#include <iostream>
using namespace std ;
struct Nodo {
    int num;
    Nodo * prox;
    Nodo * ante;
    Nodo ( char n) { num = n; prox = nullptr ; cout << " Nodo " << num << " criado ... " << endl ; }
    ~ Nodo () { cout << " Nodo " << num << " destruido ..." << endl ; }
};

int main () {
    Nodo * nodo1 = new Nodo (5);
    Nodo * nodo2 = new Nodo (7);
    Nodo * nodo3 = new Nodo (8);
    Nodo * nodo4 = new Nodo (1);
    Nodo * nodo5 = new Nodo (3);

    Nodo * primeiro = nodo1;
    nodo1 -> prox = nodo2;
    nodo2 -> prox = nodo3;
    nodo3 -> prox = nodo4;
    nodo4 -> prox = nodo5;

    Nodo * ultimo = nodo5;
    nodo5 -> ante = nodo4;
    nodo4 -> ante = nodo3;
    nodo3 -> ante = nodo2;
    nodo2 -> ante = nodo1;

    cout << "Padrão //" << endl;
    for ( Nodo * aux = primeiro ; aux != nullptr ; aux = aux -> prox )
        cout << aux -> num << endl ;
    
    cout << "Inverso //" << endl;
    for ( Nodo * aux = ultimo ; aux != nullptr ; aux = aux -> ante )
        cout << aux -> num << endl ;

    while ( primeiro != nullptr ) {
        Nodo * aux = primeiro ;
        primeiro = primeiro -> prox ;
        delete aux ;
    }
    return 0;
}
