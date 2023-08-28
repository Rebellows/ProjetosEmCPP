#include <fstream> // para usar file streams ( ifstream , ofstream )
#include <iostream> // para usar cin , cout
#include <string> // para usar string
#include <iomanip> // para usar manip . (setw , right , ...)
#include <cstdlib> // para usar srand () , rand () e exit ()
#include <ctime> // para usar time ()

#define TAM 10000 // total de dados a serem gravados

using namespace std;

int main () {
    ifstream arq ; // Cria input file stream ( ifstream )
    cout << " Abrindo arquivo texto ..." << endl ;
    arq . open ( "teste.txt" , ios :: in ) ; // Abre arquivo
    if (! arq . is_open () ) // Se houver erro , sai do programa
        return 1;
    // Le cabecalho
    string cabecalho ;
    getline ( arq , cabecalho ) ;
    // Exibe cabecalho na tela
    cout << cabecalho << endl ;
    do { // Le n registros numericos
        int num , valor ;
        arq >> num >> valor ;
        if (! arq . fail () )
            cout << num << " " << valor << endl ;
    } while ( arq . good () );
    if ( arq . bad () || ! arq . eof () ) {
        cerr << " Erro fatal !" << endl ;
        exit (1) ; // Aborta programa
    }
    cout << " Fechando o arquivo ..." << endl ;
    arq . close () ;
    return 0;
}