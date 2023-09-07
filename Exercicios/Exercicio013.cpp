// Exercicio001, Gabriel Dorneles Rebello (T011), construção de duas classes, sendo elas Turma e Aluno, 07/09/2023

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
        string matriculastr = to_string(matricula);
        while (matriculastr.length() < 10) {
            matriculastr = "0" + matriculastr;
        }
        string resultado = nome + " (" + matriculastr + ")";
        if (nota != -1.0) {
            string notastr = to_string(nota);
            notastr = notastr.substr(0, 6);
            resultado += ": " + notastr;
        }
        return resultado;
    }
};

class Turma {
private:
    int turma;
    string disciplina;
    string professor;
    Aluno *alunos[MAX_ALUNOS];
    int numAlunos;
public:
    Turma() {
        turma = 0;
        disciplina = "";
        professor = "";
        numAlunos = 0;
    }
    Turma(int t, string d, string p) {
        turma = t;
        disciplina = d;
        professor = p;
        numAlunos = 0;
    }
    int obtemNumero() {
        return turma;
    }
    string obtemDisciplina() {
        return disciplina;
    }
    string obtemProfessor() {
        return professor;
    }
    Aluno *obtemAluno(int n) {
        if ( n >= 0 && n < numAlunos) {
            return alunos[n];
        }
        return nullptr;
    }
    int obtemNumAlunos() {
        return numAlunos;
    }
    void defineNumero(int n) {
        turma = n;
    }
    void defineDisciplina(string d) {
        disciplina = d;
    }
    void defineProfessor(string p) {
        professor = p;
    }
    bool adicionaAluno(Aluno *aluno) {
        if (numAlunos < 10) {
            alunos[numAlunos] = aluno;
            numAlunos++;
            return true;
        }
        return false;
    }
    double calculaMedia() {
        int cont = 0;
        if (numAlunos == 0) {
            return -1.0;
        }
        double total = 0.0;
        for (int i = 0; i < numAlunos; i++) {
            if (alunos[i]->obtemNota() != -1.0) {
                total += alunos[i]->obtemNota();
                cont++;
            }
        }
        return total / cont;
    }
    string str() {
        string resultado = "\n" + to_string(turma) + " - " + disciplina + " - Prof. " + professor;
        if (numAlunos > 0) {
            for (int i = 0; i < numAlunos; i++) {
                resultado += "\n" + alunos[i]->str();
            }
        }
        double media = calculaMedia();
        if (media >= 0) {
            string mediastr = to_string(media);
            mediastr = mediastr.substr(0, 6);
            resultado += "\nMEDIA = " + mediastr;
        }
        return resultado;
    }
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
