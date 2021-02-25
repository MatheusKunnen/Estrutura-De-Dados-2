#include "arvore.h"

Arvore *cria_arv_vazia()
{
  return NULL;
}

void destroi_arv(Arvore *arv)
{
  if (arv != NULL)
  {
    destroi_arv(arv->esq);
    destroi_arv(arv->dir);
    free(arv);
  }
}

Arvore *constroi_arv(char elem, Arvore *esq, Arvore *dir)
{
  Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
  arv->info = elem;
  arv->esq = esq;
  arv->dir = dir;
  return arv;
}
int is_empty(Arvore *a)
{
  return a == NULL;
}

void imprime_pre_ordem(Arvore *a)
{
  if (!is_empty(a))
  {
    printf("%c ", a->info);
    imprime_pre_ordem(a->esq);
    imprime_pre_ordem(a->dir);
  }
}

void imprime_in_ordem(Arvore *a)
{
  if (!is_empty(a))
  {
    imprime_in_ordem(a->esq);
    printf("%c ", a->info);
    imprime_in_ordem(a->dir);
  }
}

void imprime_pos_ordem(Arvore *a)
{
  if (!is_empty(a))
  {
    imprime_pos_ordem(a->esq);
    imprime_pos_ordem(a->dir);
    printf("%c ", a->info);
  }
}

void main_ex_01(Arvore *a)
{
  printf("PRE-ORDEM: ");
  imprime_pre_ordem(a);
  printf("\n");
  printf(" IN-ORDEM: ");
  imprime_in_ordem(a);
  printf("\n");
  printf("POS-ORDEM: ");
  imprime_pos_ordem(a);
  printf("\n");
}
int pertence_arv(Arvore *a, char c)
{
  if (!is_empty(a))
    return a->info == c || pertence_arv(a->esq, c) || pertence_arv(a->dir, c);
  else
    return 0;
}

void main_ex_02(Arvore *a)
{
  int c_in_a = pertence_arv(a, 'c');
  if (c_in_a)
    printf("C PERTENCE À ARVORE \n");
  else
    printf("C NÃO PERTENCE À ARVORE \n");
  int w_in_a = pertence_arv(a, 'w');
  if (w_in_a)
    printf("W PERTENCE À ARVORE \n");
  else
    printf("W NÃO PERTENCE À ARVORE \n");
}

int conta_nos(Arvore *a)
{
  if (!is_empty(a))
    return 1 + conta_nos(a->esq) + conta_nos(a->dir);
  else
    return 0;
}

void main_ex_03(Arvore *a)
{
  printf("A árvore tem %d nós.\n", conta_nos(a));
}

int calcula_altura_arvore(Arvore *a)
{
  if (!is_empty(a))
  {
    int h_esq = is_empty(a->esq) ? -1 : calcula_altura_arvore(a->esq),
        h_dir = is_empty(a->dir) ? -1 : calcula_altura_arvore(a->dir);
    return 1 + (h_esq > h_dir ? h_esq : h_dir);
  }
  else
    return 0;
}

void main_ex_04(Arvore *a)
{
  printf("A árvore tem altura %d .\n", calcula_altura_arvore(a));
}

int e_folha(Arvore *a)
{
  return !is_empty(a) && is_empty(a->esq) && is_empty(a->dir);
}

int conta_nos_folha(Arvore *a)
{
  if (!e_folha(a))
  {
    int f_esq = is_empty(a->esq) ? 0 : conta_nos_folha(a->esq),
        f_dir = is_empty(a->dir) ? 0 : conta_nos_folha(a->dir);
    return f_esq + f_dir;
  }
  else
    return 1;
}

void main_ex_05(Arvore *a)
{
  printf("A árvore tem %d nós folha.\n", conta_nos_folha(a));
}

int main(int argc, char **argv)
{
  Arvore *a = constroi_arv('a', constroi_arv('b', cria_arv_vazia(), constroi_arv('d', cria_arv_vazia(), cria_arv_vazia())),
                           constroi_arv('c', constroi_arv('e', cria_arv_vazia(), cria_arv_vazia()), constroi_arv('f', cria_arv_vazia(), cria_arv_vazia())));
  main_ex_01(a);
  putchar('\n');
  main_ex_02(a);
  putchar('\n');
  main_ex_03(a);
  putchar('\n');
  main_ex_04(a);
  putchar('\n');
  main_ex_05(a);
  destroi_arv(a);
  a = NULL;
  return 0;
}
