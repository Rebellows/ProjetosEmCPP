#include <iostream>
#include <cstdlib>
#include <sys/time.h>

#define TAM 10000

using namespace std;

void quickSort(int* dados, int ini, int fim) // Hoare
{
	int i, j, pivo, aux;
	i = ini;
	j = fim;
	pivo = dados[(ini + fim) / 2];
	while(i <= j)
	{
		while(dados[i] < pivo)
		{
			i++;
		}
		while(dados[j] > pivo)
		{
			j--;
		}
		if(i <= j)
		{
			aux = dados[i];
			dados[i] = dados[j];
			dados[j] = aux;
			i++;
			j--;
		}
	}
	if(j > ini)
		quickSort(dados, ini, j);
	if(i < fim)
		quickSort(dados, i, fim);
}

int particiona(int* dados, int ini, int fim) 
{
    int pivot = dados[fim];
    int i = ini - 1;
    
    for (int j = ini; j <= fim - 1; j++) {
        if (dados[j] < pivot) {
            i++;
            swap(dados[i], dados[j]);
        }
    }
    
    if (pivot < dados[i + 1]) {
        swap(dados[i + 1], dados[fim]);
    }
    
    return i + 1;
}

void quickSort(int* dados, int ini, int fim) // Lomuto
{
    if (ini < fim) {
        int p = particiona(dados, ini, fim);
        quickSort(dados, ini, p - 1);
        quickSort(dados, p + 1, fim);
    }
}


int estaOrdenado (int* dados , int tam) {
    for (int i = 0; i < tam -1; ++ i ) if ( dados [i] > dados [i +1]) return 0;
    return 1;
}

int main () {
    int vetor [ TAM ];
    struct timeval antes , depois ;
    unsigned long microssegundos ;
    srand ( time (0));

    cout << "> Ordenado : ";
    for ( int i =0; i < TAM ; i ++) vetor [i] = i; // preenche o vetor ordenado
    gettimeofday (& antes , NULL ); quickSort ( vetor ,0 , TAM -1); gettimeofday (& depois , NULL );
    microssegundos = ( depois . tv_sec - antes . tv_sec ) * 1000000 + depois . tv_usec - antes . tv_usec ;
    if ( estaOrdenado ( vetor , TAM )) cout << microssegundos << " us" << endl ; else cout << " FALHOU " << endl ;
    
    cout << "> Invertido : ";
    for ( int i =0; i < TAM ; i ++) vetor [i] = TAM - i; // preenche o vetor invertido
    gettimeofday (& antes , NULL ); quickSort ( vetor ,0 , TAM -1); gettimeofday (& depois , NULL );
    microssegundos = ( depois . tv_sec - antes . tv_sec ) * 1000000 + depois . tv_usec - antes . tv_usec ;
    if ( estaOrdenado ( vetor , TAM )) cout << microssegundos << " us" << endl ; else cout << " FALHOU " << endl ;
    
    cout << "> Aleatório : ";
    for ( int i =0; i < TAM ; i ++) vetor [i] = rand ()% TAM ; // preenche o vetor aleatoriamente
    gettimeofday (& antes , NULL ); quickSort ( vetor ,0 , TAM -1); gettimeofday (& depois , NULL );
    microssegundos = ( depois . tv_sec - antes . tv_sec ) * 1000000 + depois . tv_usec - antes . tv_usec ;
    if ( estaOrdenado ( vetor , TAM )) cout << microssegundos << " us" << endl ; else cout << " FALHOU " << endl ;
    return 0;
}
