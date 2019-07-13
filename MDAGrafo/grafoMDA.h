typedef enum cor{BRANCO, CINZA, PRETO}cor;
typedef struct grafo_mda{
    int** matriz;
    int vertices;
    int arestas;
    char* lista;
    char* pai;
    int* pesos;
    enum cor* cores;
    int* tempo_inicio;
    int* tempo_final;
    int* distancia;
}grafo_MDA;

grafo_MDA* carregar_grafo(const char* uri);
void cria_matriz(grafo_MDA* grafo);
void cria_aresta(grafo_MDA* grafo, char vertice1, char vertice2, int peso, int dirigido);
int posicao_vertice(grafo_MDA* grafo, char vertice);
void imprimir_grafo(grafo_MDA* grafo);

void busca_largura(grafo_MDA* grafo, char vertice_inicial);
void imprimir_fila(grafo_MDA* grafo, char* fila);
void imprimir_caminhos(grafo_MDA* grafo, char* fila);

void busca_profundidade(grafo_MDA* grafo);
void busca_profundidade2(grafo_MDA* grafo, char* vertice, int* tempo);

void algoritmo_Kruskal(grafo_MDA* grafo);
void ordenar_pesos(grafo_MDA* grafo);
int menor_peso(grafo_MDA* grafo, int menor);
int mesma_arvore( grafo_MDA* grafo, int* arvores, int i, int j);

void algoritmo_Prim(grafo_MDA* grafo);

void algoritmo_BellmanFord(grafo_MDA* grafo, char vertice_inicial);

