#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  char k[256];
  struct node *next;
} Node;

typedef struct hash
{
  int M;       /*Numero de entradas no hash. */
  int N;       /*Numero de chaves armazenadas.*/
  Node **list; /*Vetor de listas.*/
} Hash;

Hash *create_hash(int M)
{
  Hash *H = (Hash *)malloc(sizeof(Hash));
  H->M = M;
  H->N = 0;
  H->list = (Node **)malloc(M * sizeof(Node *));
  int h;
  for (h = 0; h < H->M; h++)
  {
    H->list[h] = NULL;
  }
  return H;
}

int hash_function(char *v, int M)
{
  int i, h = v[0];
  for (i = 1; v[i] != '\0'; i++)
    h = (h * 256 + v[i]) % M;
  return h;
}

void insert_chained(Hash *H, char *k)
{
  int h = hash_function(k, H->M);
  Node *n = (Node *)malloc(sizeof(Node));
  strcpy(n->k, k);
  n->next = H->list[h];
  H->list[h] = n;
  H->N++;
}

void print_hash(Hash *H)
{
  int h;
  for (h = 0; h < H->M; h++)
  {
    Node *aux;
    for (aux = H->list[h]; aux != NULL; aux = aux->next)
    {
      printf("| %s ", aux->k);
    }
    printf("| \n");
  }
}

void free_hash(Hash *H)
{
  int h;
  for (h = 0; h < H->M; h++)
  {
    free(H->list[h]);
  }
  free(H);
}

int main()
{

  int M = 7;

  Hash *H = create_hash(M);

  insert_chained(H, "Marina");
  insert_chained(H, "Pedro");
  insert_chained(H, "Joana");
  insert_chained(H, "Thais");
  insert_chained(H, "Fabio");
  insert_chained(H, "Jonas");
  insert_chained(H, "Joaquim");
  insert_chained(H, "Mauricio");
  insert_chained(H, "Jorge");
  insert_chained(H, "Ana");
  insert_chained(H, "Patricia");
  insert_chained(H, "Henrique");

  print_hash(H);

  free_hash(H);

  return 0;
}