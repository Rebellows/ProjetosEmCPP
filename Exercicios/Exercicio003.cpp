// Exercicio013, Gabriel Dorneles Rebello (T011), retorna pirâmide de número ímpar, 20/08/23
#include <iostream>

using namespace std;

int piramide(int n) {
    for (int i = 1; i <= (n+1)/2; i++) {
       for (int j = 1; j < i; j++) {
            cout << "  ";
       }
       int a = i;
       for (int j = i; j <= n - i + 1; ++j) {
            cout << a << " ";
            a++;
       }
       cout << endl;
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    piramide(n);
}