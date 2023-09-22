// Programacao.hpp (Roland Teodorowitsch; 4 set. 2023)

#ifndef _PROGRAMACAO_HPP
#define _PROGRAMACAO_HPP

#include "Cinema.hpp"
#include "Filme.hpp"

using namespace std;

class Programacao {
private:
  Cinema *cinema;
  int sala;
  Filme *filme;
  int tipoDeExibicao; // 1 = LEG, 2 = DUB, 3 = 3D LEG, 4 = 3D DUB, 5 = NAC
  string horarios;
public:
  Programacao(Cinema *c=nullptr, int s=0, Filme *f=nullptr, int t=0, string h="");
  ~Programacao();
  Cinema *obtemCinema() const;
  int obtemSala() const;
  Filme *obtemFilme() const;
  int obtemTipoDeExibicao() const;
  string obtemHorarios() const;
  string str(bool incluiCinema) const;
  void defineCinema(Cinema *c);
  void defineSala(int s);
  void defineFilme(Filme *f);
  void defineTipoDeExibicao(int t);
  void defineHorarios(string h);
};

#endif
