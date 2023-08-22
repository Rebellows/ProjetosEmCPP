// Exercicio012, Gabriel Dorneles Rebello (T011), retorna linha de menor valor em matriz recebida, 19/08/23
#include <iostream>

using namespace std;

int main() {
    int valor, num, tam;
    cin >> tam;
    int matriz[tam][tam];
    for (int l = 0; l < tam; l++) {
        for (int c = 0; c < tam; c++) {
            cin >> matriz[l][c];
        }
    }
    num = matriz[0][0];
    for (int l = 0; l < tam; l++) {
        for (int c = 0; c < tam; c++) {
            if (matriz[l][c] < num) {
                num = matriz[l][c];
                valor = l;
            }
        }
    }
    cout << valor << endl;
    return 0;
}