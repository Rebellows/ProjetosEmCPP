#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <chrono>

using namespace std;
using namespace chrono;

vector<string> lerArquivo();

void segueDireita(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal);
void segueEsquerda(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal);
void segueCima(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal);
void segueBaixo(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal);

int main() {
    int valorFinal = 0;
    vector<string> mapa = lerArquivo();
    int inicio = 0;
    auto comeco = high_resolution_clock::now();
    while (mapa[inicio][0] != '-')
        inicio++;
    int altura = 0, direcao = 1; 
    int i = inicio, j = 0;
    while (mapa[i][j] != '#') {
        string valor = "0";
        if (direcao == 1) 
            segueDireita(mapa, altura, direcao, i, j, valor, valorFinal);
        else if (direcao == -1) 
            segueEsquerda(mapa, altura, direcao, i, j, valor, valorFinal);
        else if (altura == 1) 
            segueBaixo(mapa, altura, direcao, i, j, valor, valorFinal);
        else 
            segueCima(mapa, altura, direcao, i, j, valor, valorFinal);
    }
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<nanoseconds>(fim - comeco);
    cout << "Mapa: CasoG" << mapa.size() << " | Valor Final: R$" << valorFinal << ",00" << " | Tempo: " << duracao.count() << "ns" << endl;
    return 0;
}

vector<string> lerArquivo() {
    ifstream arquivo("src/casoG2000.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao ler arquivo";
        exit(1);
    }
    int linhas, colunas;
    arquivo >> linhas >> colunas;
    vector<string> mapa;
    string linha;
    arquivo.ignore();
    while(getline(arquivo, linha)) 
        mapa.push_back(linha);
    arquivo.close();
    return mapa;
}

void segueDireita(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal) {
    while (mapa[i][j] != '/' && mapa[i][j] != '\\' && mapa[i][j] != '#') {
        if (mapa[i][j] != '-' && mapa[i][j] != '|') 
            valor.push_back(mapa[i][j]);
        else {
            valorFinal += stoi(valor);
            valor = "0";
        }
        if (j + 1 < mapa[i].size() && (mapa[i][j+1] == '/' || mapa[i][j+1] == '\\' || mapa[i][j+1] == '#')) {
            valorFinal += stoi(valor);
            valor = "0";
        } 
        
        j++;
    }
    if (mapa[i][j] == '/') {
        direcao = 0;
        altura = -1;
        i--;
    }
    else if (mapa[i][j] == '\\') {
        direcao = 0;
        altura = 1;
        i++;
    }
}

void segueEsquerda(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal) {
    while (mapa[i][j] != '/' && mapa[i][j] != '\\' && mapa[i][j] != '#') {
        if (mapa[i][j] != '-' && mapa[i][j] != '|') 
            valor.push_back(mapa[i][j]);
        else {
            valorFinal += stoi(valor);
            valor = "0";
        }
        if (j - 1 >= 0 && (mapa[i][j-1] == '/' || mapa[i][j-1] == '\\' || mapa[i][j-1] == '#')) {
            valorFinal += stoi(valor);
            valor = "0";
        } 
        j--;
    }
    if (mapa[i][j] == '/') {
        direcao = 0;
        altura = 1;
        i++;
    }
    else if (mapa[i][j] == '\\') {
        direcao = 0;
        altura = -1;
        i--;
    }
}

void segueCima(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal) {
    while (mapa[i][j] != '/' && mapa[i][j] != '\\' && mapa[i][j] != '#') {
        if (mapa[i][j] != '-' && mapa[i][j] != '|') 
            valor.push_back(mapa[i][j]);
        else {
            valorFinal += stoi(valor);
            valor = "0";
        }
        if (i - 1 >= 0 && (mapa[i-1][j] == '/' || mapa[i-1][j] == '\\' || mapa[i-1][j] == '#')) {
            valorFinal += stoi(valor);
            valor = "0";
        } 
        i--;
    }
    if (mapa[i][j] == '/') {
        direcao = 1;
        altura = 0;
        j++;
    }
    else if (mapa[i][j] == '\\') {
        direcao = -1;
        altura = 0;
        j--;
    }    
}
void segueBaixo(vector<string> &mapa, int &altura, int &direcao, int &i, int &j, string &valor, int &valorFinal) {
    while (mapa[i][j] != '/' && mapa[i][j] != '\\' && mapa[i][j] != '#') {
        if (mapa[i][j] != '-' && mapa[i][j] != '|') 
            valor.push_back(mapa[i][j]);
        else {
            valorFinal += stoi(valor);
            valor = "0";
        }
        if (i + 1 < mapa.size() && (mapa[i+1][j] == '/' || mapa[i+1][j] == '\\' || mapa[i+1][j] == '#')) {
            valorFinal += stoi(valor);
            valor = "0";
        } 
        i++;
    }
    if (mapa[i][j] == '/') {
        direcao = -1;
        altura = 0;
        j--;
    }
    else if (mapa[i][j] == '\\') {
        direcao = 1;
        altura = 0;
        j++;
    }
}
