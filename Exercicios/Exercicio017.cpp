#include <iostream>

using namespace std;

class VetorDinamico {
private:
    int *dados;
    int qtd;
    int max;
public:
    VetorDinamico(int tam) {
        max = tam;
        qtd = 0;
        dados = new int[max];
    }
    int adiciona(int n) {
        if (qtd == max) {
            int novoMax = max * 1.5;
            int *dadosNovos = new int[novoMax];
            for (int i=0;i<qtd;++i)
                dadosNovos[i] = dados[i];
            delete dados;
            dados = dadosNovos;
            max = novoMax;
        }
        dados[qtd++] = n;
    }
    int getQtdDados() { return qtd; }
    int getDado(int i) { return dados[i]; }
};
int main () {
    VetorDinamico V1(5);
    int dado;
    do {
        cin >> dado;
        if (dado > 0) V1.adiciona(dado); else break;
    } while(1);
    for (int i = 0; i < V1.getQtdDados(); i++)
        cout << V1.getDado(i) << endl;
    return 0;
}
