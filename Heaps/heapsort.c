#include <stdio.h>

int pai(int i)
{
  return (i - 1) / 2;
}

int esquerda(int i)
{
  return (i * 2) + 1;
}

int direita(int i)
{
  return (i * 2) + 2;
}

void trocar(int V[], int a, int b)
{
  int aux = V[a];
  V[a] = V[b];
  V[b] = aux;
}

void imprimir(int V[], int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    printf("%d ", V[i]);
  }
  printf("\n");
}

void max_heapify(int *v, int n, int i)
{
  int esq = esquerda(i),
      dir = direita(i),
      maior = i;

  if (esq < n && v[maior] <= v[esq])
    maior = esq;

  if (dir < n && v[maior] <= v[dir])
    maior = dir;

  if (maior != i)
  {
    trocar(v, i, maior);
    max_heapify(v, n, maior);
  }
}
void build_max_heap(int *v, int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    max_heapify(v, n, i);
}

void heap_sort(int v[], int n)
{
  build_max_heap(v, n);
  for (int i = n - 1; i >= 1; i--)
  {
    trocar(v, 0, i);
    max_heapify(v, --n, 0);
  }
}

int main()
{

  int i;

  int size = 10;

  int V[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

  printf("Vetor inicial : ");
  imprimir(V, size);

  heap_sort(V, size);

  printf("Vetor ordenado: ");
  imprimir(V, size);

  return 0;
}