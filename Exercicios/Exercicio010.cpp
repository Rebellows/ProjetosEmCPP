// Exercicio013, Gabriel Dorneles Rebello (T011), cria classe unidadefederativa e calcula densidade populacional, 23/08/23


#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class UnidadeFederativa {
private:
    string nome;
    string sigla;
    string capital;
    double area;
    int pop;
public:
    UnidadeFederativa() {
        nome;
        sigla;
        capital;
        area = 0;
        pop = 0;
    }
    UnidadeFederativa(string n, string s, string c, double a, int p) {
        nome = n;
        sigla = s;
        capital = c;
        area = a;
        pop = p;
    }
    void defineNome(string n) {
        nome = n;
    }
    string obtemNome() {
        return nome;
    }
    void defineSigla(string s) {
        sigla = s;
    }
    string obtemSigla() {
        return sigla;
    }
    void defineCapital(string c) {
        capital = c;
    }
    string obtemCapital() {
        return capital;
    }
    void defineArea(double a) {
        area = a;
    }
    double obtemArea() {
        return area;
    }
    void definePopulacao(int p) {
        pop = p;
    }
    int obtemPopulacao() {
        return pop;
    }
    double obtemDensidade() {
        if (area == 0) {
            return -1;
        }
        else {
            return pop/area;
        }
    }
};

void mostraUF(UnidadeFederativa &uf) {
    cout << uf.obtemNome() << " (" << uf.obtemSigla() << ") - " << uf.obtemCapital();
    cout << " - Area = " << fixed << setprecision(4) << uf.obtemArea();
    cout << " - Pop. = " << uf.obtemPopulacao();
    cout << " - Densidade = " << fixed << setprecision(4) << uf.obtemDensidade() << endl;
}

int main() {
    UnidadeFederativa rs;
    mostraUF(rs);
    rs.defineNome("Rio Grande do Sul");
    rs.defineSigla("RS");
    rs.defineCapital("Porto Alegre");
    rs.defineArea(281748.5);
    rs.definePopulacao(11228091);
    mostraUF(rs);
    UnidadeFederativa sc("Santa Catarina","SC","Florianopolis",95346.2,6734568);
    mostraUF(sc);
    for (int i=0; i<10; ++i) {
        sc.definePopulacao( sc.obtemPopulacao()+100000 );
        mostraUF(sc);
    }
    return 0;
}