// Filme.hpp (Roland Teodorowitsch; 4 set. 2023)

#ifndef _FILME_HPP
#define _FILME_HPP

#include <string>	

using namespace std;

class Filme {
private:
  int numero;
  string titulo;
  int faixaEtaria;
  string estilo;
public:
  Filme(int n=-1, string t="", int f=-1, string e="");
  ~Filme();
  int obtemNumero() const;
  string obtemTitulo() const;
  int obtemFaixaEtaria() const;
  string obtemEstilo() const;
  string str() const;
  void defineNumero(int n);
  void defineTitulo(string t);
  void defineFaixaEtaria(int f);
  void defineEstilo(string e);
  bool operator<(const Filme &f) const;
  friend istream &operator>>(istream &in,Filme &f);
  friend ostream &operator<<(ostream &out,const Filme &f);
};

#endif
