/* Rotina que faz o merge de duas partes de um vetor.

  array[begin] até array[mid-1] e array[mid] até array[end-1].

  Coloca o resultado em b e depois coloca todos os elementos

  de b de volta para array (de begin até end).

*/

void merge(int array[], int begin, int mid, int end) {
    int ib = begin;
    int im = mid;
    int j;
    int size = end-begin;
    int b[size];

    /* Enquanto existirem elementos na lista da esquerda ou direita */
    for (j = 0; j < (size); j++)  {
        if (ib < mid && (im >= end || array[ib] <= array[im]))  {
            b[j] = array[ib];
            ib = ib + 1;
        }
        else  {
            b[j] = array[im];
            im = im + 1;
        }
    }

    for (j=0, ib=begin; ib<end; j++, ib++) array[ib] = b[j];
}
