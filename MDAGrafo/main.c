#include <stdio.h>
#include <stdlib.h>
#include "grafoMDA.h"

int main()
{
    grafo_MDA* grafo = carregarGrafo("grafo.txt");
    imprimir_grafo(grafo);
    return 0;
}
