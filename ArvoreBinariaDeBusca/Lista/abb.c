#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct arvore
{
  int info;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

Arvore *cria_arvore_vazia(void)
{
  return NULL;
}

Arvore *constroi_arv(int info, Arvore *esq, Arvore *dir)
{
  Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
  arv->info = info;
  arv->esq = esq;
  arv->dir = dir;
  return arv;
}

void arvore_libera(Arvore *a)
{
  if (a != NULL)
  {
    arvore_libera(a->esq);
    arvore_libera(a->dir);
    free(a);
  }
}

Arvore *inserir(Arvore *a, int v)
{
  if (a == NULL)
    a = constroi_arv(v, NULL, NULL);
  else if (a->info < v)
    a->dir = inserir(a->dir, v);
  else
    a->esq = inserir(a->esq, v);
  return a;
}

Arvore *remover(Arvore *a, int v)
{
  if (a != NULL)
  {
    if (a->info < v)
      a->dir = remover(a->dir, v);
    else if (a->info > v)
      a->esq = remover(a->esq, v);
    else
    {
      if (a->esq == NULL && a->dir == NULL)
      {
        free(a);
        a = NULL;
      }
      else if (a->esq == NULL)
      {
        Arvore *tmp = a;
        a = a->dir;
        free(tmp);
      }
      else if (a->dir == NULL)
      {
        Arvore *tmp = a;
        a = a->esq;
        free(tmp);
      }
      else
      {
        Arvore *tmp = a->esq;
        while (tmp->dir != NULL)
          tmp = tmp->dir;
        a->info = tmp->info;
        tmp->info = v;
        a->esq = remover(a->esq, v);
      }
    }
  }

  return a;
}

int buscar(Arvore *a, int v)
{
  if (a == NULL)
    return 0;
  else if (a->info < v)
    return buscar(a->dir, v);
  else if (a->info > v)
    return buscar(a->esq, v);
  else
    return 1;
}

void pre_order(Arvore *a)
{
  if (a != NULL)
  {
    printf("%d ", a->info);
    pre_order(a->esq);
    pre_order(a->dir);
  }
}

Arvore *cria_arvore_estatica(Arvore *a)
{
  a = inserir(a, 50);
  a = inserir(a, 30);
  a = inserir(a, 90);
  a = inserir(a, 20);
  a = inserir(a, 40);
  a = inserir(a, 95);
  a = inserir(a, 10);
  a = inserir(a, 35);
  a = inserir(a, 45);
  return a;
}

void main_ex_01()
{
  Arvore *a = cria_arvore_vazia();
  a = cria_arvore_estatica(a);

  printf("\n");
  pre_order(a);
  printf("\n");

  if (buscar(a, 45))
    printf("O elemento [45] existe na arvore.\n");
  else
    printf("O elemento [45] NAO existe na arvore.\n");

  printf("Removendo 45...\n");
  remover(a, 45);

  pre_order(a);
  printf("\n");

  if (buscar(a, 45))
    printf("O elemento [45] existe na arvore.\n");
  else
    printf("O elemento [45] NAO existe na arvore.\n");

  arvore_libera(a);
  a = NULL;
}

int min(Arvore *a)
{
  if (a == NULL)
  {
    printf("Arvore inválida.\n");
    exit(1);
  }
  else if (a->esq == NULL)
    return a->info;
  else
    return min(a->esq);
}

int max(Arvore *a)
{
  if (a == NULL)
  {
    printf("Arvore inválida.\n");
    exit(1);
  }
  else if (a->dir == NULL)
    return a->info;
  else
    return max(a->dir);
}

void main_ex_02()
{
  Arvore *a = cria_arvore_vazia();
  a = cria_arvore_estatica(a);

  printf("\n");
  pre_order(a);
  printf("\n");
  printf("MIN: %5d\nMAX: %5d\n", min(a), max(a));

  arvore_libera(a);
  a = NULL;
  printf("\n");
}

Arvore *cria_arvore_em_orden(Arvore *a, int n)
{
  for (int i = 0; i < n; i++)
    a = inserir(a, i);
  return a;
}

void main_ex_03()
{
  printf("Gerando Arvore ordenada\n");
  Arvore *a = cria_arvore_vazia();
  clock_t start = clock();

  a = cria_arvore_em_orden(a, 100000);
  printf("Buscando\n");

  int existe = buscar(a, 500000);

  clock_t end = clock();
  double dt = (double)(end - start) / CLOCKS_PER_SEC;

  if (existe)
    printf("O elemento [1000000] existe na arvore (%fs)\n", dt);
  else
    printf("O elemento [1000000] NAO existe na arvore (%fs)\n", dt);

  arvore_libera(a);
  a = NULL;
  printf("\n");
}

Arvore *cria_arvore_aleatoria(Arvore *a, int n)
{
  srand(time(NULL));
  for (int i = 0; i < n; i++)
    a = inserir(a, rand() % n);
  return a;
}

void main_ex_04()
{
  printf("Gerando Arvore Aleatoria\n");
  Arvore *a = cria_arvore_vazia();
  a = cria_arvore_aleatoria(a, 100000);
  clock_t start = clock();

  printf("Buscando\n");
  int existe = buscar(a, 1000000);

  clock_t end = clock();
  double dt = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

  if (existe)
    printf("O elemento [1000000] existe na arvore (%fms)\n", dt);
  else
    printf("O elemento [1000000] NAO existe na arvore (%fms)\n", dt);

  arvore_libera(a);
  a = NULL;
}

void imprime_decrescente(Arvore *a)
{
  if (a != NULL)
  {
    imprime_decrescente(a->dir);
    printf("%d ", a->info);
    imprime_decrescente(a->esq);
  }
}

void main_ex_05()
{
  Arvore *a = cria_arvore_vazia();
  a = cria_arvore_estatica(a);

  printf("\n");
  imprime_decrescente(a);
  printf("\n");

  arvore_libera(a);
  a = NULL;
}

int main()
{
  main_ex_01();
  main_ex_02();
  main_ex_03();
  main_ex_04();
  main_ex_05();
  return 0;
}
