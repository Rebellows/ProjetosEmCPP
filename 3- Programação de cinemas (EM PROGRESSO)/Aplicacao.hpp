// Aplicacao.hpp (Roland Teodorowitsch; 7 set. 2023)

#ifndef _APLICACAO_HPP
#define _APLICACAO_HPP

#include <string>
#include "Cinema.hpp"
#include "Filme.hpp"
#include "Programacao.hpp"

#define MAX_CINEMAS 50
#define MAX_FILMES  100
#define MAX_PROGRAMACAO 250

using namespace std;

class Aplicacao {
private:
  Cinema *cinemas[MAX_CINEMAS];
  int numCinemas;
  Filme *filmes[MAX_FILMES];
  int numFilmes;
  Programacao *programacao[MAX_PROGRAMACAO];
  int numProgramacao;
public:
  Aplicacao(); // Primeira etapa
  ~Aplicacao();
  bool carregaFilmes(string nomeArquivo);
  bool salvaFilmes(string nomeArquivo);
  void mostraFilmes();
  void ordenaFilmes();
  Filme *obtemFilme(int id);

  bool carregaCinemas(string nomeArquivo); // Segunda etapa
  bool salvaCinemas(string nomeArquivo);
  void mostraCinemas();
  void ordenaCinemas();
  Cinema *obtemCinema(int id);

  bool carregaProgramacao(string nomeArquivo); // Terceira etapa
  void mostraProgramacao();
};

#endif
