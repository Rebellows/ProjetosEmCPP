#include <iostream>
#include <fstream>
#include "Aplicacao.hpp"

Aplicacao::Aplicacao() {
    numCinemas = 0;
    numFilmes = 0;
    numProgramacao = 0;
}
Aplicacao::~Aplicacao() {
    for(int i = 0; i < numCinemas; i++) {
        delete cinemas[i];
    }
    for(int j = 0; j < numFilmes; j++) {
        delete filmes[j];
    }
    for(int k = 0; k < numProgramacao; k++) {
        delete programacao[k];
    }        
}
bool Aplicacao::carregaFilmes(string nomeArquivo) {
    ifstream arq;
    string nome, genero;
    int numero, faixaEtaria;
    arq.open(nomeArquivo, ios::in);
    if(!arq.is_open()) return false;
    while(arq >> numero) {
        arq.ignore();
        getline(arq, nome);
        arq >> faixaEtaria;
        arq.ignore();
        getline(arq, genero);
        filmes[numFilmes] = new Filme(numero, nome, faixaEtaria, genero);
        numFilmes++;      
    }
    arq.close();
    return true;
}
bool Aplicacao::salvaFilmes(string nomeArquivo) {
    ofstream arq;
    arq.open(nomeArquivo, ios::out);    
    if (!arq.is_open()) return false;
    for (int i = 0; i < numFilmes; i++) {
        arq << *filmes[i];
    }
    arq.close();
    return true;
}
void Aplicacao::mostraFilmes() {
    for (int i = 0; i < numFilmes; i++) {
        cout << filmes[i]->str() << endl;
    }
}
void Aplicacao::ordenaFilmes() {
    for (int i = 0; i < numFilmes - 1; i++) {
        for (int j = 0; j < numFilmes - i - 1; j++) {
            if (*filmes[j+1] < *filmes[j]) {
                Filme *aux = filmes[j+1];
                filmes[j+1] = filmes[j];
                filmes[j] = aux;
            }
        }
    }
}
Filme *Aplicacao::obtemFilme(int id) {
    for (int i = 0; i < numFilmes; i++) {
        if (filmes[i]->obtemNumero() == id) {
            return filmes[i];
        }
    }
    return nullptr;
}

bool Aplicacao::carregaCinemas(string nomeArquivo) {
    ifstream arq;
    int num, n, s;
    string nm, log, com, bai, cep, cid, est;
    arq.open(nomeArquivo, ios::in);
    if(!arq.is_open()) return false;
    while(arq >> num) {
        arq.ignore();
        getline(arq, nm);
        getline(arq, log);
        arq >> n;
        arq.ignore();
        getline(arq, com);
        getline(arq, bai);
        getline(arq, cep);
        getline(arq, cid);
        getline(arq, est);
        arq >> s;
        Endereco en(log, n, com, bai, cep, cid, est);
        cinemas[numCinemas] = new Cinema(num, nm, en, s);
        numCinemas++;      
    }
    arq.close();
    return true;    
}
bool Aplicacao::salvaCinemas(string nomeArquivo) {
    ofstream arq;
    arq.open(nomeArquivo, ios::out);    
    if (!arq.is_open()) return false;
    for (int i = 0; i < numCinemas; i++) {
        arq << *cinemas[i];
    }
    arq.close();
    return true;
}
void Aplicacao::mostraCinemas() {
    for (int i = 0; i < numCinemas; i++) {
        cout << cinemas[i]->str() << endl;
    }
}
void Aplicacao::ordenaCinemas() {
    for (int i = 0; i < numCinemas - 1; i++) {
        for (int j = 0; j < numCinemas - i - 1; j++) {
            if (*cinemas[j+1] < *cinemas[j]) {
                Cinema *aux = cinemas[j+1];
                cinemas[j+1] = cinemas[j];
                cinemas[j] = aux;
            }
        }
    }
}
Cinema *Aplicacao::obtemCinema(int id) {
    for (int i = 0; i < numCinemas; i++) {
        if (cinemas[i]->obtemNumero() == id) {
            return cinemas[i];
        }
    }
    return nullptr;
}

bool Aplicacao::carregaProgramacao(string nomeArquivo) {
    ifstream arq;
    string h;
    int cInt, fInt, s, t;
    arq.open(nomeArquivo, ios::in);
    if (!arq.is_open()) return false;
    while (arq >> cInt) {
        arq >> s;
        arq >> fInt;
        arq >> t;
        arq.ignore();
        getline(arq, h);     
        Cinema *c = obtemCinema(cInt);
        Filme *f = obtemFilme(fInt);
        programacao[numProgramacao] = new Programacao(c, s, f, t, h);
        numProgramacao++;
    }
    arq.close();
    return true;
}
void Aplicacao::mostraProgramacao() {
    ordenaCinemas();
    for (int i = 0; i < 4; i++) {
        cout << cinemas[i]->obtemNome() << "\n" << endl;
        int cinemaNumero = cinemas[i]->obtemNumero();
        bool programacaoEncontrada = false;
        for (int j = 0; j < numProgramacao; j++) {
            if (programacao[j]->obtemCinema()->obtemNumero() == cinemaNumero) {
                if (!programacaoEncontrada) {
                    programacaoEncontrada = true;
                }
                cout << programacao[j]->str(programacaoEncontrada) << endl;
            }
        }
        cout << endl;
    }
}