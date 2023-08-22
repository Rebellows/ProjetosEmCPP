// Exercicio015, Gabriel Dorneles Rebello (T011), coloca números de uma matriz em módulo, 20/08/23
#include <iostream>

using namespace std;

int main() {
    int lin, col;
    cin >> lin >> col;
    int matriz[lin][col];
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            cin >> matriz[i][j];
        }
    }
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matriz[i][j] < 0) {
                matriz[i][j] = matriz[i][j]*(-1);
                cout << matriz[i][j] << " ";
            }
            else {
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
}
