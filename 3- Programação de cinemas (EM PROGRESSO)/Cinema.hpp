// Cinema.hpp (Roland Teodorowitsch; 17 maio 2023)

#ifndef _CINEMA_HPP
#define _CINEMA_HPP

#include "Endereco.hpp"

using namespace std;

class Cinema {
private:
  int numero;    
  string nome;
  Endereco endereco;
  int salas;
public:
  Cinema();
  Cinema(int n, string nm, Endereco &e, int s);
  ~Cinema();
  int obtemNumero() const;
  string obtemNome() const;
  Endereco obtemEndereco() const;
  int obtemSalas() const;
  string str() const;
  void defineNumero(int n);
  void defineNome(string nm);
  void defineEndereco(Endereco &e);
  void defineSalas(int s);
  bool operator<(const Cinema &c) const;
  friend istream &operator>>(istream &in,Cinema &c);
  friend ostream &operator<<(ostream &out,const Cinema &c);
};

#endif
