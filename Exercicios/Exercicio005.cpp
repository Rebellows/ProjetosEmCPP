// Exercicio002, Gabriel Dorneles Rebello (T014), array organizado com bubblesort decrescente, 22/08/23

#include <iostream>

using namespace std;

void bubbleSort(int array[], int n) {
    int trocou;
    do {
        trocou = 0;
        for ( int j = 0; j < n - 1; j++) {
            if ( array[j] < array[j+1]) {
                int aux = array[j];
                array[j] = array[j+1];
                array[j+1] = aux;
                trocou = 1;

            }
        }
        for (int i = 0; i < n; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    while (trocou);    
}
int main() {
    int n;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    bubbleSort(array, n);
}