#include <stdio.h>
#include <stdlib.h>
/*SELECCION*/
int main()
{
  int vec[6] = {6, 4, 2, 5, 3, 1};
  int aux, i, j, minPos, n = 6;

  printf("\nLos elementos ingresados son \n");
  for (i = 0; i < n; i++)
    printf(" %d ", vec[i]);

  for (i = 0; i < n; i++)
  {
    minPos = i;
    for (j = i + 1; j < n; j++)
      if (vec[j] < vec[minPos])
        minPos = j;

    aux = vec[i];
    vec[i] = vec[minPos];
    vec[minPos] = aux;
  }
  printf("\n\nLos elementos ordenados por seleccion son \n");
  for (i = 0; i < n; i++)
    printf(" %d ", vec[i]);
  return 0;
}