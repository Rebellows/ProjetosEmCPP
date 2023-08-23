// Exercicio007, Gabriel Dorneles Rebello (T011), cria classe pessoa com atributos definidos, 23/08/23

#include <iostream>

using namespace std;

class Pessoa {
private:
    string nome;
    int anoNasc;
public:
    Pessoa() {
        nome;
        anoNasc = 0;
    }
    Pessoa(string n, int a) {
        nome = n;
        anoNasc = a;
    }
    void defineNome(string n) {
        nome = n;
    }
    void defineAnoNascimento(int a) {
        anoNasc = a;
    }
    string obtemNome() {
        return nome;
    }
    int obtemAnoNascimento() {
        return anoNasc;
    }
    int obtemIdade(int anoAtual) {
        int idade = anoAtual - anoNasc;
        if (anoAtual < anoNasc) {
            return -1;
        }
        else {
            return idade;
        }
    }
    int obtemIdadeEmMeses(int anoAtual) {
        int idade = anoAtual - anoNasc;
        if (anoAtual < anoNasc) {
            return -1;
        }
        else {
            return idade*12;
        }
    }
};

int main() {
    Pessoa *p = new Pessoa();
    cout << "[" << p->obtemNome() << "](" << p->obtemAnoNascimento() << ")" << endl;
    p->defineNome("Friedrich Wilhelm Nietzsche");
    p->defineAnoNascimento(1844);
    cout << "[" << p->obtemNome() << "](" <<
                   p->obtemAnoNascimento() << "/" <<
                   p->obtemIdade(1900) << " anos/" <<
                   p->obtemIdadeEmMeses(1900) << " meses)" << endl;
    delete p;
    Pessoa *rn = new Pessoa("Fulano",2020);
    cout << "Nome = " << rn-> obtemNome() << endl;
    cout << "Ano de Nascimento = " << rn->obtemAnoNascimento() << endl;
    for (int i=2018; i<2025; ++i)
        cout << i << " " << rn->obtemIdade(i) << " " << rn->obtemIdadeEmMeses(i) << endl;
    delete rn;
    return 0;
}