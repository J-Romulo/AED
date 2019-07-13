#include <stdio.h>
#include <stdlib.h>

typedef enum{BRANCO, CINZA, PRETO}cor;
typedef struct vertice{
    char* nome;
    struct vertice** aresta;
    int* pesos;
    struct vertice* pai;
    enum cor* cor;
    int tempo_inicio;
    int tempo_final;
    int distancia;
}vertice;
typedef struct grafo_LDA{
    int vertices;
    int arestas;
    int* pesos_arestas;
    struct vertice** lista;
}grafo_LDA;

grafo_LDA* carregar_grafo(const char* arquivo);
void ligar_pontos(grafo_LDA* grafo, char caractere, char caractere2, int peso, int dirigido);
void imprimir_grafo(grafo_LDA* grafo);

void busca_largura(grafo_LDA* grafo, char vertice_inicial);
void imprimir_fila(grafo_LDA* grafo, vertice** fila);
void imprimir_caminhos(vertice** fila, int vertices);

void busca_profundidade(grafo_LDA* grafo);
void busca_profundidade2(grafo_LDA* grafo, vertice* vertice, int* tempo);

void algoritmo_Kruskal(grafo_LDA* grafo);
void ordenar_pesos(grafo_LDA* grafo, int* pesos);
int menor_peso(grafo_LDA* grafo, int* pesos, int menor);
int mesma_arvore(grafo_LDA* grafo, int* arvores, int i, vertice* vertice);

void algoritmo_Prim(grafo_LDA* grafo);
int posicao(grafo_LDA* grafo, vertice* vert);

void algoritmo_BellmanFord(grafo_LDA* grafo, char vertice_inicial);
