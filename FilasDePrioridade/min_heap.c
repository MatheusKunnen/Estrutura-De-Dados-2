#include <stdio.h>
#include <stdlib.h>

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

void min_heapify(int v[], int n, int i)
{
  int esq = esquerda(i),
      dir = direita(i),
      menor = i;

  if (esq < n && v[menor] >= v[esq])
    menor = esq;

  if (dir < n && v[menor] >= v[dir])
    menor = dir;
  if (menor != i)
  {
    trocar(v, i, menor);
    min_heapify(v, n, menor);
  }
}

void build_min_heap(int v[], int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    min_heapify(v, n, i);
}

int heap_extract_min(int v[], int *size)
{
  if (size == NULL || *size <= 0)
  {
    printf("ERROR:heap_extract_min: em heap vazio\n");
    exit(1);
  }

  trocar(v, 0, --(*size));
  min_heapify(v, *size, 0);
  return v[(*size)];
}

void heap_decrease_key(int v[], int i, int chave, int n)
{
  if (v[i] <= chave)
  {
    return;
  }
  v[i] = chave;

  while (v[pai(i)] > v[i])
  {
    trocar(v, pai(i), i);
    i = pai(i);
  }
}

void min_heap_insert(int v[], int chave, int *n)
{
  v[(*n)++] = chave + 1;
  heap_decrease_key(v, *n - 1, chave, *n);
}

int main()
{

  int size = 10;

  int v[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

  imprimir(v, size);

  build_min_heap(v, size);

  imprimir(v, size);

  heap_extract_min(v, &size);

  imprimir(v, size);

  /*Modificando a última chave {16} para o valor {1}!*/
  heap_decrease_key(v, size - 1, 1, size);

  imprimir(v, size);

  /*Inserindo uma nova chave com valor {0}!*/
  min_heap_insert(v, 0, &size);

  imprimir(v, size);

  return 0;
}
