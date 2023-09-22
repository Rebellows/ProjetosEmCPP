#include <iostream>
#include <sstream>
#include "Filme.hpp"

Filme::Filme(int n, string t, int f, string e) { 
    numero = n; 
    titulo = t; 
    faixaEtaria = f; 
    estilo = e; 
}
Filme::~Filme() {}
int Filme::obtemNumero() const { return numero; }
string Filme::obtemTitulo() const { return titulo; }
int Filme::obtemFaixaEtaria() const { return faixaEtaria; }
string Filme::obtemEstilo() const { return estilo; }
string Filme::str() const {
    string numerostr = to_string(numero);
    string output = "";
    if (faixaEtaria == 0) {
        output += titulo + " [" + numerostr + "] - " + "LIVRE" + " - " + estilo;
    }
    else {
        string faixaEtariastr = to_string(faixaEtaria);
        output += titulo + " [" + numerostr + "] - " + faixaEtariastr + " anos" + " - " + estilo;
    }
    return output;
}
void Filme::defineNumero(int n) { numero = n; }
void Filme::defineTitulo(string t) { titulo = t; }
void Filme::defineFaixaEtaria(int f) { faixaEtaria = f; }
void Filme::defineEstilo(string e) { estilo = e; }
bool Filme::operator<(const Filme &f) const { return faixaEtaria < f.obtemFaixaEtaria(); }
istream &operator>>(istream &in, Filme &f) { 
    string t, e; 
    int n, fa; 
    in >> n;
    in.ignore(); 
    getline(in, t); 
    in >> fa;
    in.ignore(); 
    getline(in, e); 
    f.defineNumero(n); 
    f.defineTitulo(t); 
    f.defineFaixaEtaria(fa); 
    f.defineEstilo(e); 
    return in; 
}
ostream &operator<<(ostream &out, const Filme &f) { 
    out << f.obtemNumero() << endl;
    out << f.obtemTitulo() << endl; 
    out << f.obtemFaixaEtaria() << endl;
    out << f.obtemEstilo() << endl;
    return out; 
}