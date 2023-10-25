// Exercicio001, Gabriel Dorneles Rebello T011, criação de classes com herança, 23/10/23

#include <iostream>
#include <iomanip>

using namespace std;

class Pessoa {
private:
    string nome;
    string RG;
public:
    Pessoa() {
        nome = "";
        RG = "";
    }
    Pessoa(string n, string r) {
        nome = n;
        RG = r;
    }
    string obtemNome() { return nome; }
    string obtemRG() { return RG; }
    void defineNome(string n) { nome = n; } 
    void defineRG(string r) { RG = r; }
};

class Aluno : public Pessoa {
private: 
    string matricula;
    int anoIngresso;
public:
    Aluno() : Pessoa("", "") {
        matricula = "";
        anoIngresso = 0;
    }
    Aluno(string n, string r, string m, int ai) : Pessoa(n, r) {
        matricula = m;
        anoIngresso = ai;
    }
    string obtemMatricula() { return matricula; }
    int obtemAnoIngresso() { return anoIngresso; }
    void defineMatricula(string m) { matricula = m; }
    void defineAnoIngresso(int ai) { anoIngresso = ai; }
};

class Professor : public Pessoa {
private:
    string unidade;
    int anoIngresso;
    double salarioFixo;
public:
    Professor() : Pessoa("", ""){
        unidade = "";
        anoIngresso = 0;
        salarioFixo = 0.0;
    }
    Professor(string n, string r, string u, int ai, double s) : Pessoa(n, r) {
        unidade = u;
        anoIngresso = ai;
        salarioFixo = s;
    }
    string obtemUnidade() { return unidade; }
    int obtemAnoIngresso() { return anoIngresso; }
    double obtemSalarioFixo() { return salarioFixo; }
    void defineUnidade(string u) { unidade = u; }
    void defineAnoIngresso(int ai) { anoIngresso = ai; }
    void defineSalarioFixo(double s) { salarioFixo = s; }
};

void imprimePessoa(Pessoa *p) {
    cout << "Nome: " << p->obtemNome() << endl;
    cout << "RG: " << p->obtemRG() << endl;
    cout << "----------" << endl;
}

void imprimeAluno(Aluno *a) {
    cout << "Nome: " << a->obtemNome() << endl;
    cout << "RG: " << a->obtemRG() << endl;
    cout << "Matricula: " << a->obtemMatricula() << endl;
    cout << "Ano de Ingresso: " << a->obtemAnoIngresso() << endl;
    cout << "----------" << endl;
}

void imprimeProfessor(Professor *p) {
    cout << "Nome: " << p->obtemNome() << endl;
    cout << "RG: " << p->obtemRG() << endl;
    cout << "Unidade: " << p->obtemUnidade() << endl;
    cout << "Ano de Ingresso: " << p->obtemAnoIngresso() << endl;
    cout << "Salario Fixo: " << fixed << setprecision(4) << p->obtemSalarioFixo() << endl;
    cout << "----------" << endl;
}

int main() {
    Pessoa pe1("Pessoa 1","11111");
    imprimePessoa(&pe1);
    Pessoa pe2;
    imprimePessoa(&pe2);
    pe2.defineNome("Pessoa 2");
    imprimePessoa(&pe2);
    pe2.defineRG("22222");
    imprimePessoa(&pe2);
    
    Aluno al3("Aluno 3","33333","00001-1",2013);
    imprimeAluno(&al3);
    Aluno al4;
    imprimeAluno(&al4);
    al4.defineNome("Aluno 4");
    imprimeAluno(&al4);
    al4.defineRG("44444");
    imprimeAluno(&al4);
    al4.defineMatricula("00002-2");
    imprimeAluno(&al4);
    al4.defineAnoIngresso(2014);
    imprimeAluno(&al4);

    Professor pr5("Professor 5","55555","EP",2015,5555.55);
    imprimeProfessor(&pr5);
    Professor pr6;
    imprimeProfessor(&pr6);
    pr6.defineNome("Professor 6");
    imprimeProfessor(&pr6);
    pr6.defineRG("66666");
    imprimeProfessor(&pr6);
    pr6.defineUnidade("EN");
    imprimeProfessor(&pr6);
    pr6.defineAnoIngresso(2016);
    imprimeProfessor(&pr6);
    pr6.defineSalarioFixo(6666.66);
    imprimeProfessor(&pr6);

    return 0;
}
