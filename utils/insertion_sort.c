#include <stdio.h>
#include <stdlib.h>

/// INSERCION
main()
{
  float t, aux, a[] = {10.0, 8.0, 5.5, 3.4, 3.2, 12.5, 2.2, 21.5, 9.4};
  int i, j, n = 9, pos;

  printf("\nLos elementos ingresados son \n");
  for (i = 0; i < 9; i++)
    printf("%d %8.2f\n", i, a[i]);

  for (i = 1; i < n; i++)
  {
    pos = i - 1;
    aux = a[i]; /// valor clave, se lo compara contra todos los elementos hacia la izquierda
    while (pos >= 0 && aux < a[pos])
    {
      a[pos + 1] = a[pos];
      pos = pos - 1;
    }
    a[pos + 1] = aux;
  }

  printf("\n\nLos elementos ordenados por insercion son \n");
  for (i = 0; i < n; i++)
    printf("%d %8.2f \n", i, a[i]);
}