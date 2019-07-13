#include <stdio.h>
#include <stdlib.h>
#include "grafoMDA.h"

grafo_MDA* carregarGrafo(const char* arquivo){
    grafo_MDA* grafo = (grafo_MDA*)malloc(sizeof(grafo_MDA));

    FILE* file;
    char vertice1 = ' ';
    char vertice2 = ' ';
    int vertices,peso;

    file = fopen(arquivo, "r");
    fscanf(file, "%d", &grafo->vertices);
    fscanf(file, "%d", &grafo->arestas);


    grafo->lista = (char*)malloc(sizeof(char) * grafo->vertices);
    grafo->pai = (char*)malloc(sizeof(char) * grafo->vertices);
    grafo->pesos = (int*)malloc(sizeof(int) * grafo->arestas);
    grafo->cores = (cor*)malloc(sizeof(cor) * grafo->vertices);
    grafo->tempo_inicio = (int*)malloc(sizeof(int) * grafo->vertices);
    grafo->tempo_final = (int*)malloc(sizeof(int) * grafo->vertices);
    grafo->distancia = (int*)malloc(sizeof(int) * grafo->vertices);

    for(int i = 0; i < grafo->vertices; i++){
        grafo->lista[i] = ' ';
        grafo->pai[i] = NULL;
        grafo->distancia[i] = NULL;
        grafo->tempo_inicio[i] = NULL;
        grafo->tempo_final[i] = NULL;
        while(grafo->lista[i] == ' ' || grafo->lista[i] == '\n'){
            fscanf(file, "%c", &grafo->lista[i]);
        }
    }

    cria_matriz(grafo);

    for(int i = 0; i < grafo->arestas; i++){
        vertice1 = ' ';
        vertice2 = ' ';
        peso = -1;
        while(vertice1 == ' ' || vertice1 == '\n'){
            fscanf(file, "%c", &vertice1);
        }
        while(vertice2 == ' ' || vertice2 == '\n'){
            fscanf(file, "%c", &vertice2);
        }
        while(peso == -1){
            fscanf(file, "%d", &peso);
            grafo->pesos[i] = peso;
        }


        cria_aresta(grafo, vertice1, vertice2, peso, 1);
    }


    fclose(file);

    return grafo;

}

void cria_matriz(grafo_MDA* grafo){
    grafo->matriz = calloc(grafo->vertices, sizeof(int*));
    for(int i = 0; i <= grafo->vertices; i++){
        grafo->matriz[i] = calloc (grafo->vertices, sizeof(int*));
    }

    for(int i = 0; i < grafo->vertices; i++){
        for(int j = 0; j < grafo->vertices; j++){
            if(i == j){
                grafo->matriz[i][j] = 0;
            }else{
                grafo->matriz[i][j] = -1;
            }
        }
    }
}

void cria_aresta(grafo_MDA* grafo, char vertice1, char vertice2, int peso, int dirigido){
    int pos1 = posicao_vertice(grafo, vertice1);
    int pos2 = posicao_vertice(grafo, vertice2);

    if(dirigido){
        grafo->matriz[pos1][pos2] = peso;
    }else{
        grafo->matriz[pos1][pos2] = peso;
        grafo->matriz[pos2][pos1] = peso;
    }
}

int posicao_vertice(grafo_MDA* grafo, char vertice){
    for(int i = 0; i < grafo->vertices; i++){
        if(grafo->lista[i] == vertice){
            return i;
        }
    }
}

void imprimir_grafo(grafo_MDA* grafo){
    printf("  ");
    for(int i = 0; i < grafo->vertices; i++){
        printf("%c ", grafo->lista[i]);
    }
    printf("\n");
    for(int i = 0; i < grafo->vertices; i++){
        printf("%c ", grafo->lista[i]);
        for(int j = 0; j < grafo->vertices; j++){
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

void busca_largura(grafo_MDA* grafo, char vertice_inicial){
    int i, pos_vertice;
    int cont = 0;
    int pos = 0;

    char* fila = (char*)malloc(sizeof(char) * grafo->vertices);
    for(i = 0; i < grafo->vertices; i++){
        fila[i] = NULL;
    }

    for(i = 0; i < grafo->vertices; i++){
        if(grafo->lista[i] == vertice_inicial){
            fila[cont] = grafo->lista[i];
            grafo->cores[i] = CINZA;
            grafo->pai[i] = NULL;
            pos++;
        }else{
            grafo->cores[i] = BRANCO;
            grafo->pai[i] = NULL;
        }
    }

    while(cont < grafo->vertices){
        pos_vertice = posicao_vertice(grafo, fila[cont]);
        for(i = 0; i < grafo->vertices; i++){
            if(grafo->matriz[pos_vertice][i] > 0){
                if(grafo->cores[i] == BRANCO){
                    grafo->cores[i] = CINZA;
                    grafo->pai[i] = grafo->lista[pos_vertice];
                    fila[pos] = grafo->lista[i];
                    pos++;
               }else{}
            }else{}
        }
        grafo->cores[pos_vertice] = PRETO;
        cont++;
    }

    imprimir_fila(grafo, fila);
    printf("\n");
    imprimir_caminhos(grafo, fila);
}

void imprimir_fila(grafo_MDA* grafo, char* fila){
    for(int i = 0; i < grafo->vertices; i++){
        printf("%c", fila[i]);
    }
}

void imprimir_caminhos(grafo_MDA* grafo, char* fila){
    int pos;
    char vertice;
    for(int i = 0; i < grafo->vertices; i++){
        vertice = fila[i];
        while(vertice != NULL){
            pos = posicao_vertice(grafo, vertice);
            printf("%c", grafo->lista[pos]);
            if(grafo->pai[pos] != NULL){
                pos = posicao_vertice(grafo, grafo->pai[pos]);
                vertice = grafo->lista[pos];
                printf("<-");
            }else{
                vertice = NULL;
            }
        }
        printf("\n");
    }
}

void busca_profundidade(grafo_MDA* grafo){
    int* tempo =(int*)malloc(sizeof(int));
    for(int i = 0; i < grafo->vertices; i++){
        grafo->pai[i] = NULL;;
        grafo->cores[i] = BRANCO;
    }
    tempo = 0;
    for(int i = 0; i < grafo->vertices; i++){
        if(grafo->cores[i] == BRANCO){
            busca_profundidade2(grafo, grafo->lista[i], tempo);
        }
    }
}

void busca_profundidade2(grafo_MDA* grafo, char* vertice, int* tempo){
    tempo++;
    for(int j = 0; j < grafo->vertices; j++){
        if(grafo->lista[j] == vertice){
            grafo->cores[j] = CINZA;
            grafo->tempo_inicio = tempo;
            for(int i = 0; i < grafo->vertices; i++){
                if(grafo->matriz[j][i] == 1){
                    if(grafo->cores[i] == BRANCO){
                        grafo->pai[i] = grafo->lista[j];
                        busca_profundidade2(grafo, grafo->lista[i], tempo);
                    }
                }
            }
            grafo->cores[j] = PRETO;
            grafo->tempo_final[j] = tempo++;
        }
    }
}

void algoritmo_Kruskal(grafo_MDA* grafo){
  int i, j, menor, pesototal;
    int* arvores = (int*)malloc(sizeof(int)*grafo->vertices);
    char* fila = (char*)malloc(sizeof(char)*grafo->vertices);

    for(i = 0; i < grafo->vertices; i++){
        arvores[i] = i;
        fila[i] = grafo->lista[i];
        grafo->pai[i] = NULL;
    }

    pesototal = 0;
    menor = -1;
    ordenar_pesos(grafo);
    menor = menor_peso(grafo, menor);

    while(menor != -1){
        for(i = 0; i < grafo->vertices; i++){
            for(j = 0; j < grafo->vertices; j++){
                if(grafo->matriz[i][j] == menor){
                    if(!mesma_arvore(grafo, arvores, i, j)){
                        if(grafo->pai[j] != NULL){
                            grafo->pai[i] = grafo->lista[j];
                        }else{
                            grafo->pai[j] = grafo->lista[i];
                        }
                        pesototal += menor;
                    }
                }
            }
        }
        menor = menor_peso(grafo, menor);
    }
    printf("%d\n", pesototal);
    imprimir_caminhos(grafo, fila);
}

void ordenar_pesos(grafo_MDA* grafo){
    int aux, continua;
    do{
        continua = 0;
        for(int i = 0; i < grafo->arestas-1; i++){
            if(grafo->pesos[i] > grafo->pesos[i+1]){
                aux = grafo->pesos[i];
                grafo->pesos[i] = grafo->pesos[i+1];
                grafo->pesos[i+1] = aux;
                continua = i;
            }
        }
    }while(continua != 0);
}

int menor_peso(grafo_MDA* grafo, int menor){
    for(int i = 0; i < grafo->arestas; i++){
        if(menor < grafo->pesos[i]){
            menor = grafo->pesos[i];
            return menor;
        }
    }
    return -1;
}

int mesma_arvore(grafo_MDA* grafo, int* arvores, int i, int j){
        if(arvores[i] == arvores[j]){
            return 1;
        }else{
            for(int k = 0; k < grafo->vertices; k++){
                if(arvores[k] == arvores[j]){
                    arvores[k] = arvores[i];
                }
            }
            return 0;
        }
}

void algoritmo_Prim(grafo_MDA* grafo){
    int i, j, menor, pesototal, primeiro;
    int orig, dest;

    for(i = 0; i < grafo->vertices; i++){
        grafo->pai[i] = NULL;
    }

    pesototal = 0;
    grafo->pai[0] = grafo->lista[0];
    while(1){
        primeiro = 1;
        menor = -1;
        for(i = 0; i < grafo->vertices; i++){
            if(grafo->pai[i] != NULL){
                for(j = 0; j < grafo->vertices; j++){
                    if(grafo->pai[j] == NULL){
                        if(primeiro){
                            if(grafo->matriz[i][j] != -1){
                                menor = grafo->matriz[i][j];
                            }
                            orig = i;
                            dest = j;
                            primeiro = 0;
                        }else{
                            if(menor > grafo->matriz[i][j] && grafo->matriz[i][j] != -1){
                                menor = grafo->matriz[i][j];
                                orig = i;
                                dest = j;
                            }
                        }
                    }
                }

            }
        }
        if(primeiro == 1){
            break;
        }
        pesototal += menor;
        grafo->pai[dest] = grafo->lista[orig];

    }
    grafo->pai[0] = NULL;


    printf("%d\n", pesototal);
    imprimir_caminhos(grafo, grafo->lista);
}

void algoritmo_BellmanFord(grafo_MDA* grafo, char vertice_inicial){
    int i, j, origem;

    for(i = 0; i < grafo->vertices; i++){
        grafo->distancia[i] = 999;
        grafo->pai[i] = NULL;
        if(grafo->lista[i] == vertice_inicial){
            origem = i;
        }
    }

    grafo->distancia[origem] = 0;

    for(i = 0; i < grafo->vertices; i++){
        for(j = 0; j < grafo->vertices; j++){
            if(grafo->matriz[i][j] > 0){
                if(grafo->distancia[i] + grafo->matriz[i][j] < grafo->distancia[j]){
                    grafo->distancia[j] = grafo->distancia[i] + grafo->matriz[i][j];
                    grafo->pai[j] = grafo->lista[i];
                }
            }
        }
    }

    imprimir_caminhos(grafo, grafo->lista);
}
