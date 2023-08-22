// Exercicio023, Gabriel Dorneles Rebello (T014), array de struct organizado com insertion sort, 22/08/23

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

void insertionSort(registro array[], int n) {
    for (int k = 1; k < n; k++) {
        registro base = array[k];
        int j = k - 1;
        while (j >= 0 && compara(base, array[j])) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = base;
        for (int i = 0; i < n; i++) {
            cout << array[i].iden << "/" << array[i].num << " ";
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
    insertionSort(array, n);
    return 0;
}