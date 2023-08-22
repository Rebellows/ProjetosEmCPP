// Exercicio013, Gabriel Dorneles Rebello (T014), array de struct organizado com selection sort, 22/08/23

#include <iostream>
#include <string>

using namespace std;

struct registro {
    string iden;
    int num;
};

bool compara(const registro& a, const registro& b) {
    if (a.iden != b.iden) {
        return a.iden < b.iden;
    }
    return a.num < b.num;
}

void selectionSort(registro array[], int n) {
    for (int j = 0; j < n -1; j++) {
        int men = j;
        for (int k = j+1; k < n; k++)
            if (compara(array[k], array[men])) {
                men = k;
            }
        if (men != j) {
            registro aux = array[men];
            array[men] = array[j];
            array[j] = aux;
        }
        for (int l = 0; l < n; l++) {
            cout << array[l].iden << "/" << array[l].num << " ";
        }
        cout << endl;
    }    
}

int main() {
    int n;
    cin >> n;
    registro array[n];
    for (int i = 0; i < n; i++) {
        cin >> array[i].iden >> array[i].num;
    }
    selectionSort(array, n);
    return 0;
}