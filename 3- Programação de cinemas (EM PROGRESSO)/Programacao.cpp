#include <iostream>
#include <sstream>
#include "Programacao.hpp"

Programacao::Programacao(Cinema *c, int s, Filme *f, int t, string h) {
    cinema = c;
    sala = s;
    filme = f;
    tipoDeExibicao = t;
    horarios = h;
}
Programacao::~Programacao() {}
Cinema *Programacao::obtemCinema() const { return cinema; }
int Programacao::obtemSala() const { return sala; }
Filme *Programacao::obtemFilme() const { return filme; }
int Programacao::obtemTipoDeExibicao() const { return tipoDeExibicao; }
string Programacao::obtemHorarios() const { return horarios; } 
string Programacao::str(bool incluiCinema) const {
    string output = "";
    if (incluiCinema == true) {
        string salastr = to_string(sala);
        output += cinema->obtemNome() + " - " + "Sala " + salastr + ": " + filme->obtemTitulo() + " | " + horarios + " | ";
        if (tipoDeExibicao == 1) { output += "LEG | "; }
        if (tipoDeExibicao == 2) { output += "DUB | "; }
        if (tipoDeExibicao == 3) { output += "3D LEG | "; }
        if (tipoDeExibicao == 4) { output += "3D DUB | "; }
        if (tipoDeExibicao == 5) { output += "NAC | "; }
        if(filme->obtemFaixaEtaria() <= 1) { output += "[LIVRE] | " + filme->obtemEstilo(); }
        else { output += "[" + to_string(filme-> obtemFaixaEtaria()) + "] | " + filme->obtemEstilo(); }
    }
    else { return " "; }
    return output;
}
void Programacao::defineCinema(Cinema *c) { cinema = c; }
void Programacao::defineSala(int s) { sala = s; }
void Programacao::defineFilme(Filme *f) { filme = f; }
void Programacao::defineTipoDeExibicao(int t) { tipoDeExibicao = t; }
void Programacao::defineHorarios(string h) { horarios = h; }
