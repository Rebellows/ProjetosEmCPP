// Exercicio001, Gabriel Dorneles Rebello (T011), construção de duas classes, sendo elas Turma e Aluno

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

#define MAX_ALUNOS 10

class Aluno {
private:
    int matricula;
    string nome;
    double nota;
public:
    Aluno() {
        matricula = 0;
        nome = "";
        nota = -1.0;
    }
    Aluno(int m, string n, double no) {
        matricula = m;
        nome = n;
        nota = no;
    }
    int obtemMatricula() {
        return matricula;
    }
     void defineMatricula(int m) {
        matricula = m;
   
    }
    string obtemNome() {
        return nome;
    }
    void defineNome(string n) {
        nome = n;
    }
    double obtemNota() {
        return nota;
    }
    void defineNota(double no) {
        nota = no;
    }
    string str() {
        return nome + " (" + std::to_string(nota) + ")";
    }
};

class Turma {

};

int main() {
    Aluno *discente[] = {
        new Aluno(1,"Benedito",9.1),
        new Aluno(2,"Carlos",8.2),
        new Aluno(3,"Daniela",7.3),
        new Aluno(4,"Elisabeth",6.4),
        new Aluno(5,"Fernanda",5.5),
        new Aluno(6,"Gilson",9.6),
        new Aluno(7,"Heitor",8.5),
        new Aluno(8,"Irineu",7.4),
        new Aluno(9,"Joana",3.2),
        new Aluno(10,"Klaus",-1.0),
        new Aluno(11,"Laura",9.8)
    };
    int numDiscentes = sizeof(discente)/sizeof(Aluno *);
    Turma *turma = new Turma(0,"SEM ALUNOS","INDEFINIDO");
    int a;
    cout << turma->str() << endl;
    turma->defineNumero(123);
    turma->defineDisciplina("Linguagem C");
    turma->defineProfessor("Alberto");
    for (a=0; a<5; ++a)
        if (!turma->adicionaAluno(discente[a])) { cerr << "ERRO"; exit(1); }
    for (a=0; a<5; ++a)
        if (turma->obtemAluno(a) != discente[a]) { cerr << "ERRO"; exit(1); }
    for (; a<numDiscentes; ++a)
        if (turma->obtemAluno(a) != nullptr) { cerr << "ERRO"; exit(1); }
    cout << turma->str() << endl;
    for (a=5; a<MAX_ALUNOS; ++a)
        if (!turma->adicionaAluno(discente[a])) { cerr << "ERRO"; exit(1); }
    for (; a<numDiscentes; ++a)
        if (turma->adicionaAluno(discente[a])) { cerr << "ERRO"; exit(1); }
    for (a=0; a<MAX_ALUNOS; ++a)
        if (turma->obtemAluno(a) != discente[a]) { cerr << "ERRO"; exit(1); }
    cout << turma->str() << endl;
    delete turma;
    for (int i=0; i<numDiscentes; ++i)
        delete discente[i];
    return 0;
}
