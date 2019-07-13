#include <stdio.h>
#include <stdlib.h>
#include "LDAGrafo.h"

grafo_LDA* carregar_grafo(const char* arquivo){
    char caractere, caractere2;
    int peso, i, j;

    grafo_LDA* grafo = (grafo_LDA*)malloc(sizeof(grafo_LDA));

    FILE* file = fopen(arquivo, "r");

    fscanf(file, "%d", &grafo->vertices);
    fscanf(file, "%d", &grafo->arestas);


    grafo->lista = (vertice*)malloc(sizeof(vertice)*grafo->vertices);
    grafo->pesos_arestas = (int*)malloc(sizeof(int)*grafo->arestas);

    for(i = 0; i < grafo->vertices; i++){
        vertice* ponto = (vertice*)malloc(sizeof(vertice));
        ponto->nome = ' ';
        while(ponto->nome == '\n' || ponto->nome == ' '){
            fscanf(file, "%c", &ponto->nome);
        }

        grafo->lista[i]= ponto;
    }

    for(i = 0; i < grafo->vertices; i++){
        grafo->lista[i]->aresta = (vertice*)malloc(sizeof(vertice)*grafo->arestas);
        grafo->lista[i]->pesos = (int*)malloc(sizeof(int)*grafo->arestas);
        for(j = 0; j < grafo->arestas; j++){
            grafo->lista[i]->aresta[j] = NULL;
            grafo->lista[i]->aresta[j] = NULL;
        }
    }

    for(i = 0; i < grafo->arestas; i++){
        caractere = ' ';
        caractere2 = ' ';
        peso = -1;
        while(caractere == ' ' || caractere == '\n'){
            fscanf(file, "%c", &caractere);
        }
        while(caractere2 == ' ' || caractere2 == '\n'){
            fscanf(file, "%c", &caractere2);
        }
        while(peso == -1){
            fscanf(file, "%d", &peso);
            grafo->pesos_arestas[i]= peso;
        }

        ligar_pontos(grafo, caractere, caractere2, peso, 1);
    }

    fclose(file);

    return grafo;

}

void ligar_pontos(grafo_LDA* grafo, char caractere, char caractere2, int peso, int dirigido){
    if(dirigido){
        vertice* ponto2;
        for(int i = 0; i < grafo->vertices; i++){
            if(grafo->lista[i]->nome == caractere2){
                ponto2 = grafo->lista[i];
            }
        }

        for(int i = 0; i < grafo->vertices; i++){
            if(grafo->lista[i]->nome == caractere){
                for(int j = 0; j < grafo->arestas; j++){
                    if(grafo->lista[i]->aresta[j] == NULL){
                        grafo->lista[i]->aresta[j] = ponto2;
                        grafo->lista[i]->pesos[j] = peso;
                        break;
                    }
                }
            }
        }
    }else{
        vertice* ponto;
        for(int i = 0; i < grafo->vertices; i++){
            if(grafo->lista[i]->nome == caractere){
                ponto = grafo->lista[i];
            }
        }

        for(int i = 0; i < grafo->vertices; i++){
            if(grafo->lista[i]->nome == caractere2){
                for(int j = 0; j < grafo->arestas; j++){
                    if(grafo->lista[i]->aresta[j] == NULL){
                        grafo->lista[i]->aresta[j] = ponto;
                        grafo->lista[i]->pesos[j] = peso;
                        break;
                    }
                }
            }
        }

        vertice* ponto2;
        for(int i = 0; i < grafo->vertices; i++){
            if(grafo->lista[i]->nome == caractere2){
                ponto2 = grafo->lista[i];
            }
        }

        for(int i = 0; i < grafo->vertices; i++){
            if(grafo->lista[i]->nome == caractere){
                for(int j = 0; j < grafo->arestas; j++){
                    if(grafo->lista[i]->aresta[j] == NULL){
                        grafo->lista[i]->aresta[j] = ponto2;
                        grafo->lista[i]->pesos[j] = peso;
                        break;
                    }
                }
            }
        }
    }
}

void imprimir_grafo(grafo_LDA* grafo){
    for(int i = 0; i < grafo->vertices; i++){
        printf("%c: ", grafo->lista[i]->nome);
        for(int j = 0; j < grafo->arestas; j++){
            if(grafo->lista[i]->aresta[j] != NULL){
                printf("%d-%c ",grafo->lista[i]->pesos[j],grafo->lista[i]->aresta[j]->nome);
            }
        }
        printf("\n");
    }
}

void busca_largura(grafo_LDA* grafo, char vertice_inicial){
    int i;
    int cont = 0;
    int pos = 0;
    vertice** fila = (vertice*)malloc(sizeof(vertice)*grafo->vertices);
    vertice* raiz = (vertice*)malloc(sizeof(vertice));

    for(i = 0; i < grafo->vertices; i++){
        fila[i] = NULL;
    }

    for(i = 0; i < grafo->vertices; i++){
        if(grafo->lista[i]->nome == vertice_inicial){
            fila[cont] = grafo->lista[i];
            fila[cont]->cor = CINZA;
            fila[cont]->distancia = 0;
            fila[cont]->pai = NULL;
            pos++;
        }else{
            grafo->lista[i]->cor = BRANCO;
            grafo->lista[i]->pai = NULL;
            grafo->lista[i]->distancia = -1;
        }
    }


    while(cont < grafo->vertices){
        for(i = 0; i < grafo->arestas; i++){
            if(fila[cont]->aresta[i] != NULL){
                if(fila[cont]->aresta[i]->cor == BRANCO){
                    fila[cont]->aresta[i]->cor = CINZA;
                    fila[cont]->aresta[i]->distancia = fila[cont]->distancia + 1;
                    fila[pos] = fila[cont]->aresta[i];
                    fila[pos]->pai = fila[cont];
                    pos++;
                }
            }else{
                break;
            }
        }
        fila[cont]->cor = PRETO;
        cont++;
    }


    imprimir_fila(grafo, fila);
    printf("\n");
    imprimir_caminhos(fila, grafo->vertices);
}

void imprimir_fila(grafo_LDA* grafo, vertice** fila){
    for(int i = 0; i < grafo->vertices; i++){
        if(fila[i] != NULL){
            printf("%c", fila[i]->nome);
        }else{
            break;
        }
    }
}

void imprimir_caminhos(vertice** fila, int vertices){
    for(int i = 0; i < vertices; i++){
        for(fila[i]; fila[i] != NULL; fila[i] = fila[i]->pai){
            printf("%c", fila[i]->nome);
            if(fila[i]->pai != NULL){
                printf("<-");
            }
        }
        printf("\n");
    }
}

void busca_profundidade(grafo_LDA* grafo){
    int* tempo = (int*)malloc(sizeof(int));
    for(int i = 0; i < grafo->vertices; i++){
        grafo->lista[i]->pai = NULL;;
        grafo->lista[i]->cor = BRANCO;
    }
    tempo = 0;
    for(int i = 0; i < grafo->vertices; i++){
        if(grafo->lista[i]->cor == BRANCO){
            busca_profundidade2(grafo, grafo->lista[i], tempo);
        }
    }

}

void busca_profundidade2(grafo_LDA* grafo, vertice* vertice, int* tempo){
    vertice->cor = CINZA;
    tempo++;
    vertice->tempo_inicio = tempo;
    for(int i = 0; i < grafo->arestas; i++){
        if(vertice->aresta[i] != NULL){
            if(vertice->aresta[i]->cor == BRANCO){
                vertice->aresta[i]->pai = vertice;
                busca_profundidade2(grafo, vertice->aresta[i], tempo);
            }
        }else{
            break;
        }
    }
    vertice->cor = PRETO;
    vertice->tempo_final = tempo++;
}

void algoritmo_Kruskal(grafo_LDA* grafo){
    int i, j, menor, pesototal;
    int* arvores = (int*)malloc(sizeof(int)*grafo->vertices);
    vertice** fila = (vertice*)malloc(sizeof(vertice)*grafo->vertices);

    for(i = 0; i < grafo->vertices; i++){
        arvores[i] = i;
        fila[i] = grafo->lista[i];
        grafo->lista[i]->pai = NULL;
    }

    pesototal = 0;
    menor = -1;
    ordenar_pesos(grafo, grafo->pesos_arestas);
    menor = menor_peso(grafo, grafo->pesos_arestas, menor);

    while(menor != -1){
        for(i = 0; i < grafo->vertices; i++){
            for(j = 0; j < grafo->arestas; j++){
                if(grafo->lista[i]->pesos[j] == menor){
                    if(!mesma_arvore(grafo, arvores, i, grafo->lista[i]->aresta[j])){
                        if(grafo->lista[i]->aresta[j]->pai != NULL){
                            grafo->lista[i]->pai = grafo->lista[i]->aresta[j];
                        }else{
                            grafo->lista[i]->aresta[j]->pai = grafo->lista[i];
                        }
                        pesototal += menor;
                    }
                }
            }
        }
        menor = menor_peso(grafo,grafo->pesos_arestas, menor);
    }
    printf("%d\n", pesototal);
    imprimir_caminhos(fila, grafo->vertices);
}

void ordenar_pesos(grafo_LDA* grafo, int* pesos){
    int aux, continua;
    do{
        continua = 0;
        for(int i = 0; i < grafo->arestas-1; i++){
            if(pesos[i] > pesos[i+1]){
                aux = pesos[i];
                pesos[i] = pesos[i+1];
                pesos[i+1] = aux;
                continua = i;
            }
        }
    }while(continua != 0);
}

int menor_peso(grafo_LDA* grafo, int* pesos, int menor){
    for(int i = 0; i < grafo->arestas; i++){
        if(menor < pesos[i]){
            menor = pesos[i];
            return menor;
        }
    }
    return -1;
}

int mesma_arvore(grafo_LDA* grafo, int* arvores, int i, vertice* vertice){
    for(int j = 0; j < grafo->vertices; j++){
        if(grafo->lista[j] == vertice){
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
    }
}

void algoritmo_Prim(grafo_LDA* grafo){
    int i, j, menor, pesototal, primeiro;
    vertice** pai = (vertice*)malloc(sizeof(vertice)*grafo->vertices);
    vertice* senhor;
    int index;

    for(i = 0; i < grafo->vertices; i++){
        pai[i] = NULL;
        grafo->lista[i]->pai = NULL;
    }

    pesototal = 0;
    pai[0] = grafo->lista[0];
    while(1){
        primeiro = 1;
        menor = 0;
        for(i = 0; i < grafo->vertices; i++){
            if(pai[i] != NULL){
                for(j = 0; j < grafo->arestas; j++){
                    if(pai[posicao(grafo, grafo->lista[i]->aresta[j])] == NULL){
                        if(primeiro){
                            menor = grafo->lista[i]->pesos[j];
                            senhor = grafo->lista[i];
                            index = posicao(grafo, grafo->lista[i]->aresta[j]);
                            primeiro = 0;
                        }else{
                            if(menor > grafo->lista[i]->pesos[j]){
                                menor = grafo->lista[i]->pesos[j];
                                senhor = grafo->lista[i];
                                index = posicao(grafo, grafo->lista[i]->aresta[j]);
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
        pai[index] = senhor;

    }

    for(i = 1; i < grafo->vertices; i++){
        grafo->lista[i]->pai = pai[i];
    }

    printf("%d\n", pesototal);
    imprimir_caminhos(grafo->lista, grafo->vertices);
}

int posicao(grafo_LDA* grafo, vertice* vert){
    for(int i = 0; i < grafo->vertices; i++){
        if(grafo->lista[i] == vert){
            return i;
        }
    }
    return -1;
}

void algoritmo_BellmanFord(grafo_LDA* grafo, char vertice_inicial){
    int i, j, origem;

    for(i = 0; i < grafo->vertices; i++){
        grafo->lista[i]->distancia = 999; //"infinito"
        grafo->lista[i]->pai = NULL;
        if(grafo->lista[i]->nome == vertice_inicial){
            origem = i;
        }
    }

    grafo->lista[origem]->distancia = 0;

    for(i = 0; i < grafo->vertices; i++){
        for(j = 0; j < grafo->arestas; j++){
            if(grafo->lista[i]->aresta[j] != NULL){
                if(grafo->lista[i]->distancia + grafo->lista[i]->pesos[j] < grafo->lista[i]->aresta[j]->distancia){
                    grafo->lista[i]->aresta[j]->distancia = grafo->lista[i]->distancia + grafo->lista[i]->pesos[j];
                    grafo->lista[i]->aresta[j]->pai = grafo->lista[i];
                }
            }
        }
    }

    imprimir_caminhos(grafo->lista, grafo->vertices);
}
