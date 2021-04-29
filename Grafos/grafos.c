#include <stdio.h>
#include <stdlib.h>

/*Estrutura para um nó em uma lista encadeada: */
typedef struct noA
{
  int id;           /*Identificador armazenado no nó. */
  struct noA *next; /* Próximo nó na lista encadeada. */
  int w;
} NoA;

/*Estrutura de Grafo com lista de adjacências: */
typedef struct grafoA
{
  int E;     /* Quantidade de arestas. */
  int V;     /* Quantidade de vértices. */
  NoA **Adj; /* Lista de adjacências. */
} GrafoA;

/*Estrutura de Grafo com matriz de adjacências: */
typedef struct grafoM
{
  int E;     /* Quantidade de arestas. */
  int V;     /* Quantidade de vértices. */
  int **Mat; /* Matrix de adjacências. */
} GrafoM;

/*Função para criar um grafo com lista de adjacências.*/
GrafoA *criar_grafo_adj(int tamanho)
{
  int v;
  GrafoA *G = (GrafoA *)malloc(sizeof(GrafoA));
  G->E = 0;
  G->V = tamanho;
  G->Adj = (NoA **)malloc(tamanho * sizeof(NoA *));
  for (v = 0; v < G->V; v++)
  {
    G->Adj[v] = NULL;
  }
  return G;
}

/*Função para criar um grafo com matriz de adjacências.*/
GrafoM *criar_grafo_mat(int tamanho)
{
  int v;
  GrafoM *G = (GrafoM *)malloc(sizeof(GrafoM));
  G->E = 0;
  G->V = tamanho;
  G->Mat = (int **)malloc(tamanho * sizeof(int *));
  for (v = 0; v < G->V; v++)
  {
    G->Mat[v] = (int *)malloc(tamanho * sizeof(int));
  }
  return G;
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_adj(GrafoA *G)
{
  int v;
  for (v = 0; v < G->V; v++)
  {
    if (G->Adj[v] != NULL)
    {
      free(G->Adj[v]);
    }
  }
  free(G->Adj);
  free(G);
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_mat(GrafoM *G)
{
  int v;
  for (v = 0; v < G->V; v++)
  {
    if (G->Mat[v] != NULL)
    {
      free(G->Mat[v]);
    }
  }
  free(G->Mat);
  free(G);
}
void imprime_grafo_a(GrafoA *g, int showW)
{
  printf("Grafo (lista adjacência):\n");
  for (int i = 0; i < g->V; i++)
  {
    printf("%3d ->", i);
    for (NoA *tmp = g->Adj[i]; tmp != NULL; tmp = tmp->next)
    {
      printf(" %d", tmp->id);
      if (showW)
        printf(" (w:%2d) ", tmp->w);
    }
    putchar('\n');
  }
}

void imprime_grafo_m(GrafoM *g)
{
  printf("Grafo (matriz adjacência):\n");
  // Cabeceira
  printf("%2s  ", " ");
  for (int i = 0; i < g->V; i++)
    printf(" %d", i);
  printf("\n\n");
  // Matriz
  for (int i = 0; i < g->V; i++)
  {
    printf("%2d  ", i);
    for (int j = 0; j < g->V; j++)
      printf(" %d", g->Mat[i][j]);
    putchar('\n');
  }
}

void insere_no_gm(GrafoM *g, int a, int b, int w)
{
  // printf("%d %d %d\n", a, b, w);
  if (a >= g->V || b >= g->V)
    return;
  // Atualiza valor na matriz
  g->Mat[a][b] = w;
  // Aumenta nro de arestas
  g->E++;
}

void insere_no_ga(GrafoA *g, int a, int b, int w)
{
  // Cria no
  NoA *novo = (NoA *)malloc(sizeof(NoA));
  novo->id = b;
  novo->w = w;
  // Coloca no inicio da lista de adjacencias
  novo->next = NULL;
  NoA *tmp = g->Adj[a];
  if (tmp != NULL)
  {
    while (tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = novo;
  }
  else
  {
    g->Adj[a] = novo;
  }
  // Aumenta nro de arestas
  g->E++;
}

void ga_2_gm(GrafoA *gA, GrafoM *gM)
{
  for (int i = 0; i < gA->V; i++)
    for (NoA *tmp = gA->Adj[i]; tmp != NULL; tmp = tmp->next)
      insere_no_gm(gM, i, tmp->id, tmp->w);
}

int main_ex_01()
{
  printf("===============================\n");
  printf("        Exercicio 01\n");
  printf("===============================\n");
  int nVertices = 6; /*Número de vértices*/

  GrafoA *Ga = criar_grafo_adj(nVertices);
  GrafoM *Gm = criar_grafo_mat(nVertices);

  insere_no_ga(Ga, 0, 1, 1);
  insere_no_ga(Ga, 1, 0, 1);

  insere_no_ga(Ga, 0, 5, 1);
  insere_no_ga(Ga, 5, 0, 1);

  insere_no_ga(Ga, 0, 2, 1);
  insere_no_ga(Ga, 2, 0, 1);

  insere_no_ga(Ga, 1, 2, 1);
  insere_no_ga(Ga, 2, 1, 1);

  insere_no_ga(Ga, 1, 3, 1);
  insere_no_ga(Ga, 3, 1, 1);

  insere_no_ga(Ga, 2, 4, 1);
  insere_no_ga(Ga, 4, 2, 1);

  insere_no_ga(Ga, 2, 3, 1);
  insere_no_ga(Ga, 3, 2, 1);

  insere_no_ga(Ga, 3, 4, 1);
  insere_no_ga(Ga, 4, 3, 1);

  insere_no_ga(Ga, 4, 5, 1);
  insere_no_ga(Ga, 5, 4, 1);

  ga_2_gm(Ga, Gm); // Gera grafoM utilizando grafoA

  imprime_grafo_a(Ga, 0);
  imprime_grafo_m(Gm);

  liberar_grafo_adj(Ga);
  liberar_grafo_mat(Gm);

  return 0;
}

int main_ex_02()
{
  printf("===============================\n");
  printf("        Exercicio 02\n");
  printf("===============================\n");
  int nVertices = 6; /*Número de vértices*/

  GrafoA *Ga = criar_grafo_adj(nVertices);
  GrafoM *Gm = criar_grafo_mat(nVertices);

  insere_no_ga(Ga, 0, 1, 1);
  insere_no_ga(Ga, 0, 5, 1);
  insere_no_ga(Ga, 1, 2, 1);
  insere_no_ga(Ga, 1, 3, 1);
  insere_no_ga(Ga, 2, 0, 1);
  insere_no_ga(Ga, 2, 4, 1);
  insere_no_ga(Ga, 3, 2, 1);
  insere_no_ga(Ga, 4, 3, 1);
  insere_no_ga(Ga, 5, 4, 1);

  ga_2_gm(Ga, Gm); // Gera grafoM utilizando grafoA

  imprime_grafo_a(Ga, 0);
  imprime_grafo_m(Gm);

  liberar_grafo_adj(Ga);
  liberar_grafo_mat(Gm);

  return 0;
}

int n_arestas_incidentes_ga(GrafoA *g, int v)
{
  int n = 0;
  for (int i = 0; i < g->V; i++)
    for (NoA *tmp = g->Adj[i]; tmp != NULL; tmp = tmp->next)
      n += tmp->id == v;
  return n;
}

int n_arestas_incidentes_gm(GrafoM *g, int v)
{
  if (v >= g->V)
    return -1;
  int n = 0;
  for (int i = 0; i < g->V; i++)
    n += g->Mat[i][v] > 0;
  return n;
}

int n_arestas_saem_ga(GrafoA *g, int v)
{
  int n = 0;
  for (int i = 0; i < g->V; i++)
    for (NoA *tmp = g->Adj[i]; tmp != NULL; tmp = tmp->next)
      n += 1;
  return n;
}

int n_arestas_saem_gm(GrafoM *g, int v)
{
  if (v >= g->V)
    return -1;
  int n = 0;
  for (int i = 0; i < g->V; i++)
    n += g->Mat[v][i] > 0;
  return n;
}

void imprime_adjacentes_ga(GrafoA *g, int v)
{
  if (v >= g->V)
    exit(1);

  printf("Vértices adjacentes ao vértice %d:", v);

  for (NoA *tmp = g->Adj[v]; tmp != NULL; tmp = tmp->next)
    printf(" %d", tmp->id);

  putchar('\n');
}

void imprime_adjacentes_gm(GrafoM *g, int v)
{
  if (v >= g->V)
    exit(1);

  printf("Vértices adjacentes ao vértice %d:", v);

  for (int i = 0; i < g->V; i++)
    if (g->Mat[v][i] > 0)
      printf(" %d", i);

  putchar('\n');
}

int main_ex_03()
{
  printf("===============================\n");
  printf("        Exercicio 03\n");
  printf("===============================\n");
  int nVertices = 6; /*Número de vértices*/

  GrafoA *Ga = criar_grafo_adj(nVertices);
  GrafoM *Gm = criar_grafo_mat(nVertices);

  insere_no_ga(Ga, 0, 1, 1);
  insere_no_ga(Ga, 0, 3, 5);
  insere_no_ga(Ga, 1, 3, 8);
  insere_no_ga(Ga, 2, 0, 5);
  insere_no_ga(Ga, 2, 3, 4);
  insere_no_ga(Ga, 3, 3, 6);
  insere_no_ga(Ga, 3, 4, 3);
  insere_no_ga(Ga, 4, 2, 7);
  insere_no_ga(Ga, 4, 5, 9);
  insere_no_ga(Ga, 5, 0, 2);

  ga_2_gm(Ga, Gm); // Gera grafoM utilizando grafoA

  imprime_grafo_a(Ga, 1);
  imprime_grafo_m(Gm);

  printf("Nro. arestas incidentes ao vértice %d -> G.A.: %d \tG.M.: %d\n", 3, n_arestas_incidentes_ga(Ga, 3), n_arestas_incidentes_gm(Gm, 3));
  printf("Nro. arestas que saem do vértice %d -> G.A.: %d \tG.M.: %d\n", 3, n_arestas_saem_ga(Ga, 3), n_arestas_saem_gm(Gm, 3));
  imprime_adjacentes_ga(Ga, 2);
  imprime_adjacentes_gm(Gm, 2);

  liberar_grafo_adj(Ga);
  liberar_grafo_mat(Gm);

  return 0;
}

GrafoA *inv_grafo_adj(GrafoA *Ga)
{
  GrafoA *g = criar_grafo_adj(Ga->V);
  for (int i = 0; i < g->V; i++)
    for (NoA *tmp = Ga->Adj[i]; tmp != NULL; tmp = tmp->next)
      insere_no_ga(g, tmp->id, i, tmp->w);
  return g;
}
GrafoM *inv_grafo_mat(GrafoM *Gm)
{
  GrafoM *g = criar_grafo_mat(Gm->V);
  for (int i = 0; i < g->V; i++)
    for (int j = 0; j < g->V; j++)
      insere_no_gm(g, j, i, Gm->Mat[i][j]);
  return g;
}

int main_ex_04()
{
  printf("===============================\n");
  printf("        Exercicio 04\n");
  printf("===============================\n");
  int nVertices = 6; /*Número de vértices*/

  GrafoA *Ga = criar_grafo_adj(nVertices);
  GrafoM *Gm = criar_grafo_mat(nVertices);

  insere_no_ga(Ga, 0, 1, 1);
  insere_no_ga(Ga, 0, 5, 1);
  insere_no_ga(Ga, 1, 2, 1);
  insere_no_ga(Ga, 1, 3, 1);
  insere_no_ga(Ga, 2, 0, 1);
  insere_no_ga(Ga, 2, 4, 1);
  insere_no_ga(Ga, 3, 2, 1);
  insere_no_ga(Ga, 4, 3, 1);
  insere_no_ga(Ga, 5, 4, 1);

  ga_2_gm(Ga, Gm); // Gera grafoM utilizando grafoA

  GrafoA *GaT = inv_grafo_adj(Ga);
  GrafoM *GmT = inv_grafo_mat(Gm);

  imprime_grafo_a(GaT, 0);
  imprime_grafo_m(GmT);

  liberar_grafo_adj(Ga);
  liberar_grafo_mat(Gm);
  liberar_grafo_adj(GaT);
  liberar_grafo_mat(GmT);
  return 0;
}
/* */
int main()
{
  // return main_ex_01();
  // return main_ex_02();
  // return main_ex_03();
  return main_ex_04();
}
