#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Pessoa {
    string nome;
    double altura;
    Data aniversario;
};

int main() {
    const int maximo = 10;
    Pessoa pessoas[maximo];
    int qntPessoas = 0;
    
    while (true) {
        string escolha;
        getline(cin, escolha);
        
        if (escolha == "+") {
            
            if (qntPessoas < maximo) {
                
                Pessoa novaPessoa;
                
                getline(cin, novaPessoa.nome);
                string strAltura;
                getline(cin, strAltura);
                novaPessoa.altura = stod(strAltura);
                string strDia;
                getline(cin, strDia);
                novaPessoa.aniversario.dia = stoi(strDia);
                string strMes;
                getline(cin, strMes);
                novaPessoa.aniversario.mes = stoi(strMes);
                string strAno;
                getline(cin, strAno);
                novaPessoa.aniversario.ano = stoi(strAno);
                
                pessoas[qntPessoas] = novaPessoa;
                qntPessoas++;
                cout << "> OK" << endl;
            }
            
            else {
                cout << "> VETOR CHEIO" << endl;
                string ignoredInput;
                getline(cin, ignoredInput);
               string ignoredInput2;
                getline(cin, ignoredInput2);
                string ignoredInput3;
                getline(cin, ignoredInput3);
                string ignoredInput4;
                getline(cin, ignoredInput4);
                string ignoredInput5;
                getline(cin, ignoredInput5);
              
            }
        }
        
        else if (escolha == ".") {
            break;
        }
        else {
            cout << "> OPCAO INVALIDA" << endl;
        }
    }
    string strEscolhaMes;
    getline(cin, strEscolhaMes);
    int escolhaMes = stoi(strEscolhaMes);
            
    bool achou = false;
            
    for (int i = 0; i < maximo; i++) {
        if (pessoas[i].aniversario.mes == escolhaMes) {
            cout << pessoas[i].nome << ";" << fixed << setprecision(4) << pessoas[i].altura << ";" << pessoas[i].aniversario.dia << "," << pessoas[i].aniversario.mes << "," << pessoas[i].aniversario.ano << endl;
            achou = true;
                
            
        }
    }
    if (!achou) {
        cout << "> SEM ANIVERSARIOS" << endl;
    }
    return 0;
}