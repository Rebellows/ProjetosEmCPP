// app1.cpp (Roland Teodorowitsch; 4 set. 2023)

#include <iostream>
#include "Aplicacao.hpp"

int main() {
  Aplicacao aplicacao;

  if (!aplicacao.carregaFilmes("filmes.txt")) return 0;
  cout << "----------" << endl;
  aplicacao.mostraFilmes();
  aplicacao.ordenaFilmes();
  if (!aplicacao.salvaFilmes("filmes.txt.out")) return 0;
  cout << "----------" << endl;
  aplicacao.mostraFilmes();

  cout << "----------" << endl;
  return 0;
}
