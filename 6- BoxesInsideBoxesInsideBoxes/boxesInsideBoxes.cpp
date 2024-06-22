#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>
#include <sstream>
#include <math.h>

using namespace std;
using namespace chrono;

struct Caixa {
    int l, w, h;
};

vector<Caixa> lerArquivo();
void dfs(int nodo, vector<vector<int>> &adj, vector<bool> &comparadas, vector<int> &dp);
bool comparaCaixas(Caixa a, Caixa b);

int main() {
    vector<Caixa> caixas = lerArquivo();
    int n = caixas.size();

    auto inicio = high_resolution_clock::now();

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (comparaCaixas(caixas[i], caixas[j])) {
                adj[i].push_back(j);
            }
        }
    }

    vector<bool> comparadas(n, false);
    vector<int> dp(n, 1);
    for (int i = 0; i < n; ++i) {
        if (!comparadas[i]) {
            dfs(i, adj, comparadas, dp);
        }
    }

    int maiorSequencia = *max_element(dp.begin(), dp.end());

    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<nanoseconds>(fim - inicio);

    cout << "Caso: " << n << " || " << "Resultado: " << maiorSequencia << " || " << "Tempo: " << duracao.count() / pow(10, 6)  << "ms" << endl;

    return 0;
}

vector<Caixa> lerArquivo() {
    ifstream arquivo("src/caso10000.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao ler arquivo";
        exit(1);
    }
    vector<Caixa> caixas;
    string linha;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        Caixa caixa;
        if (iss >> caixa.l >> caixa.w >> caixa.h) {
            vector<int> dimensoes = {caixa.l, caixa.w, caixa.h};
            sort(dimensoes.begin(), dimensoes.end());
            caixa.l = dimensoes[0];
            caixa.w = dimensoes[1];
            caixa.h = dimensoes[2];
            caixas.push_back(caixa);
        }
    }
    return caixas;
}

void dfs(int nodo, vector<vector<int>> &adj, vector<bool> &comparadas, vector<int> &dp) {
    comparadas[nodo] = true;
    for (int vizinho : adj[nodo]) {
        if (!comparadas[vizinho]) {
            dfs(vizinho, adj, comparadas, dp);
        }
        dp[nodo] = max(dp[nodo], 1 + dp[vizinho]);
    }
}

bool comparaCaixas(Caixa a, Caixa b) {
    return a.l < b.l && a.w < b.w && a.h < b.h;
}