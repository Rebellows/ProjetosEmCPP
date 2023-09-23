void merge(int *dados, int ini, int meio, int fim) {
  int p = ini, q = meio+1, k=0;
  int *aux = new int[fim-ini+1];
  for (int i = ini; i <= fim; i++){
      if (p > meio)                 aux[k++] = dados[q++];
      else if (q > fim)             aux[k++] = dados[p++];
      else if( dados[p] < dados[q]) aux[k++] = dados[p++];
      else                          aux[k++] = dados[q++];
  }
  for (int p=0; p<k; p++) dados[ini++] = aux[p];
  delete[] aux;
}

void mergeSort(int *dados, int ini, int fim) {
  if ( ini >= fim ) return;
  int meio = (ini + fim) / 2;
  mergeSort(dados, ini, meio);
  mergeSort(dados, meio+1, fim);
  merge(dados,ini,meio,fim);
}
