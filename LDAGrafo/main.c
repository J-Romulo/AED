#include <stdio.h>
#include <stdlib.h>
#include "LDAGrafo.h"
int main()
{
    grafo_LDA* grafo = carregar_grafo("grafo.txt");
    imprimir_grafo(grafo);
    return 0;
}
