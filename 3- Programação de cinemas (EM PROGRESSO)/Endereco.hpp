// Endereco.hpp (Roland Teodorowitsch; 4 set. 2023)

#ifndef _ENDERECO_HPP
#define _ENDERECO_HPP

#include <string>	

using namespace std;

class Endereco {
private:
  string logradouro;
  int numero;  // -1 = sem número
  string complemento;
  string bairro;
  string cep;
  string cidade;
  string estado;
public:
  Endereco(string l="", int n=-1, string c="", string b="", string cp="", string cd="", string e="");
  ~Endereco();
  string obtemLogradouro() const;
  int obtemNumero() const;
  string obtemComplemento() const;
  string obtemBairro() const;
  string obtemCEP() const;
  string obtemCidade() const;
  string obtemEstado() const;
  string str() const;
  void defineLogradouro(string l);
  void defineNumero(int n);
  void defineComplemento(string c);
  void defineBairro(string b);
  void defineCEP(string cp);
  void defineCidade(string cd);
  void defineEstado(string e);
  friend istream &operator>>(istream &in,Endereco &e);
  friend ostream &operator<<(ostream &out,const Endereco &e);
};

#endif
