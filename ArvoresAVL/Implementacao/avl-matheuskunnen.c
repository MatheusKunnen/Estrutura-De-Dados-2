#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  char chave;
  int altura;
  struct node *esq;
  struct node *dir;
} No, Arvore;

/*----------------------*/
int maior(int esq, int dir)
{
  return (esq > dir ? esq : dir);
}

/*----------------------*/
int altura(Arvore *a)
{
  return a == NULL ? -1 : a->altura;
}

int atualizar_altura(Arvore *a)
{
  return 1 + maior(altura(a->esq), altura(a->dir));
}

/*----------------------*/
int balanceamento(Arvore *a)
{
  return altura(a->dir) - altura(a->esq);
}

/*----------------------*/
Arvore *rotacao_simples_esq(Arvore *a)
{
  No *tmp = a->dir;
  a->dir = tmp->esq;
  tmp->esq = a;
  a->altura = atualizar_altura(a);
  tmp->altura = atualizar_altura(tmp);
  return tmp;
}

/*----------------------*/
Arvore *rotacao_simples_dir(Arvore *a)
{
  No *tmp = a->esq;
  a->esq = tmp->dir;
  tmp->dir = a;
  a->altura = atualizar_altura(a);
  tmp->altura = atualizar_altura(tmp);
  return tmp;
}

/*----------------------*/
Arvore *rotacao_dupla_esq(Arvore *a)
{
  a->dir = rotacao_simples_dir(a->dir);
  return rotacao_simples_esq(a);
}

/*----------------------*/
Arvore *rotacao_dupla_dir(Arvore *a)
{
  a->esq = rotacao_simples_esq(a->esq);
  return rotacao_simples_dir(a);
}

/*----------------------*/
Arvore *atualizar_fb_dir(Arvore *a)
{
  a->altura = atualizar_altura(a);
  if (balanceamento(a) == 2)
  {
    if (balanceamento(a->dir) >= 0)
      a = rotacao_simples_esq(a);
    else
      a = rotacao_dupla_esq(a);
  }
  return a;
}

/*----------------------*/
Arvore *atualizar_fb_esq(Arvore *a)
{
  a->altura = atualizar_altura(a);
  if (balanceamento(a) == -2)
  {
    if (balanceamento(a->esq) <= 0)
      a = rotacao_simples_dir(a);
    else
      a = rotacao_dupla_dir(a);
  }
  return a;
}

/*----------------------*/
Arvore *inserir(Arvore *a, char chave)
{
  if (a == NULL)
  {
    a = (No *)malloc(sizeof(No));
    a->altura = 0;
    a->chave = chave;
    a->esq = NULL;
    a->dir = NULL;
  }
  else if (a->chave < chave)
  {
    a->dir = inserir(a->dir, chave);
    a = atualizar_fb_dir(a);
  }
  else
  {
    a->esq = inserir(a->esq, chave);
    a = atualizar_fb_esq(a);
  }
  return a;
}

/*----------------------*/
Arvore *remover(Arvore *a, char chave)
{
  if (a == NULL)
  {
    return NULL;
  }
  else
  {
    if (chave < a->chave)
    {
      a->esq = remover(a->esq, chave);
      a = atualizar_fb_dir(a);
    }
    else if (chave > a->chave)
    {
      a->dir = remover(a->dir, chave);
      a = atualizar_fb_esq(a);
    }
    else
    {
      if ((a->esq == NULL) && (a->dir == NULL))
      {
        free(a);
        a = NULL;
      }
      else if (a->esq == NULL)
      {
        No *tmp = a;
        a = a->dir;
        free(tmp);
      }
      else if (a->dir == NULL)
      {
        No *tmp = a;
        a = a->esq;
        free(tmp);
      }
      else
      {
        No *tmp = a->esq;
        while (tmp->dir != NULL)
        {
          tmp = tmp->dir;
        }
        a->chave = tmp->chave;
        tmp->chave = chave;
        a->esq = remover(a->esq, chave);
        a = atualizar_fb_dir(a);
      }
    }
    return a;
  }
}

/*----------------------*/
void imprimir_in_order(Arvore *a, int nivel)
{
  if (a != NULL)
  {
    int i;
    for (i = 0; i < nivel; i++)
    {
      printf("      ");
    }
    printf("Chave: \033[1m%c\033[0m (altura: %d, fb: %+d) no nível: %d\n", a->chave, a->altura, balanceamento(a), nivel);
    imprimir_in_order(a->esq, nivel + 1);
    imprimir_in_order(a->dir, nivel + 1);
  }
}

/*----------------------*/
int main()
{

  Arvore *AVL = NULL;
  char valores[] = {'Q', 'Z', 'B', 'Y', 'T', 'M', 'E', 'W', 'X', 'S', 'F', 'G', 'A', 'H', 'N', 'O', 'P', 'R'};
  int n = 18;

  char valores_remover[] = {'A', 'H', 'E', 'W', 'G', 'N', 'P', 'O'};
  int n2 = 8;
  for (int i = 0; i < n; i++)
    AVL = inserir(AVL, valores[i]);

  imprimir_in_order(AVL, 0);

  for (int i = 0; i < n2; i++)
  {
    printf("\nRemovendo \"%c\"\n", valores_remover[i]);
    AVL = remover(AVL, valores_remover[i]);
    imprimir_in_order(AVL, 0);
  }
  return 0;
}