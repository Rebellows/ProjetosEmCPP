void insertionSort(int *dados, int tam) {
  for (int i=1; i<tam; ++i) {
      int base = dados[i];
      int j = i-1;
      while ( j>=0 && base < dados[j] ) {
            dados[j+1] = dados[j];
            --j;
      }
      dados[j+1] = base;
  }
}
