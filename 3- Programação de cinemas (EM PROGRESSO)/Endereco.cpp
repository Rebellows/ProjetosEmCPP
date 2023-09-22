#include <iostream>
#include <sstream>
#include "Endereco.hpp"

Endereco::Endereco(string l, int n, string c, string b, string cp, string cd, string e) {
    logradouro = l;
    numero = n;
    complemento = c;
    bairro = b;
    cep = cp;
    cidade = cd;
    estado = e;   
}
Endereco::~Endereco() {}
string Endereco::obtemLogradouro() const { return logradouro; }
int Endereco::obtemNumero() const { return numero; }
string Endereco::obtemComplemento() const { return complemento; }
string Endereco::obtemBairro() const { return bairro; }
string Endereco::obtemCEP() const { return cep; }
string Endereco::obtemCidade() const { return cidade; }
string Endereco::obtemEstado() const { return estado; }
string Endereco::str() const {
    string numerostr = to_string(numero);
    string output = "";
    output += logradouro + ", " + numerostr + " - " + complemento + " - Bairro " + bairro + " - " + cidade + " - " + estado;
    return output;
}
void Endereco::defineLogradouro(string l) { logradouro = l; }
void Endereco::defineNumero(int n) { numero = n; }
void Endereco::defineComplemento(string c) { complemento = c; }
void Endereco::defineBairro(string b) { bairro = b; }
void Endereco::defineCEP(string cp) { cep = cp; }
void Endereco::defineCidade(string cd) { cidade = cd; }
void Endereco::defineEstado(string e) { estado = e; }
istream &operator>>(istream &in,Endereco &e) {
    int n;
    string l, c, b, cp, cd, es;
    getline(in, l);
    in >> n;
    in.ignore(); 
    getline(in, c);
    getline(in, b);
    getline(in, cp);
    getline(in, cd);
    getline(in, es);
    e.defineLogradouro(l);
    e.defineNumero(n);
    e.defineComplemento(c);
    e.defineBairro(b);
    e.defineCEP(cp);
    e.defineCidade(cd);
    e.defineEstado(es);
    return in;
}
ostream &operator<<(ostream &out,const Endereco &e) {
    out << e.obtemLogradouro() << endl;
    out << e.obtemNumero() << endl;
    out << e.obtemComplemento() << endl;
    out << e.obtemBairro() << endl;
    out << e.obtemCEP() << endl;
    out << e.obtemCidade() << endl;
    out << e.obtemEstado() << endl;
    return out;
}