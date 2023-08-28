#include <fstream> // para usar file streams ( ifstream , ofstream )
#include <iostream> // para usar cin , cout
#include <string> // para usar string
#include <iomanip> // para usar manip . (setw , right , ...)
#include <cstdlib> // para usar srand () , rand () e exit ()
#include <ctime> // para usar time ()

#define TAM 10000 // total de dados a serem gravados

using namespace std ;

int main () {
    ofstream arqsaida ; // Cria output file stream ( ofstream )
    arqsaida . open ("teste.txt", ios :: out ); // Cria e abre arquivo
    if (! arqsaida . is_open () ) // Se houver erro , sai do programa
        return 1;
    srand ( time ( NULL )) ; // Semente utilizando o tempo atual do sistema
    cout << " Gerando dados ..." << endl ;
    arqsaida << " Cabecalho do arquivo " << endl ; // Grava o cabecalho
    for ( int i = 0; i < TAM ; i ++) {
        int num = rand () % TAM ; // Grava formatando a maneira de escrita na saida
        arqsaida << i << setw (10) << num << endl ;
        if ( arqsaida . fail () ) {
            cerr << " Erro fatal !" << endl ;
            exit (1) ; // Aborta programa
        }
    }
    cout << " Fechando o arquivo ..." << endl ;
    arqsaida . close () ;
    return 0;
}
