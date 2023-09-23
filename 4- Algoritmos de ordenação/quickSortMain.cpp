#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#define TAM  10000
using namespace std;
void quickSort(int *dados, int ini, int fim);

int estaOrdenado(int *dados, int tam) {
  for (int i=0; i<tam-1; ++i) if (dados[i] > dados[i+1]) return 0;
  return 1;
}

int main() {
  int vetor[TAM];
  struct timeval antes, depois;
  unsigned long microssegundos;
  srand(time(0));

  cout << "> Ordenado:  ";
  for (int i=0; i<TAM; i++) vetor[i] = i; //preenche o vetor ordenado
  gettimeofday(&antes, NULL);   quickSort(vetor,0,TAM-1);   gettimeofday(&depois, NULL);
  microssegundos = (depois.tv_sec - antes.tv_sec) * 1000000 + depois.tv_usec - antes.tv_usec;
  if (estaOrdenado(vetor,TAM)) cout << microssegundos << " us" << endl; else cout << "FALHOU" << endl;

  cout << "> Invertido: ";
  for (int i=0; i<TAM; i++) vetor[i] = TAM - i; //preenche o vetor invertido
  gettimeofday(&antes, NULL);   quickSort(vetor,0,TAM-1);   gettimeofday(&depois, NULL);
  microssegundos = (depois.tv_sec - antes.tv_sec) * 1000000 + depois.tv_usec - antes.tv_usec;
  if (estaOrdenado(vetor,TAM)) cout << microssegundos << " us" << endl;  else cout << "FALHOU" << endl;

  cout << "> Aleatório: ";
  for (int i=0; i<TAM; i++) vetor[i] = rand()%TAM; //preenche o vetor aleatoriamente
  gettimeofday(&antes, NULL);   quickSort(vetor,0,TAM-1);   gettimeofday(&depois, NULL);
  microssegundos = (depois.tv_sec - antes.tv_sec) * 1000000 + depois.tv_usec - antes.tv_usec;
  if (estaOrdenado(vetor,TAM)) cout << microssegundos << " us" << endl; else cout << "FALHOU" << endl;

  return 0;
}
