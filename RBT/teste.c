#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main()
{
    arvoreRB *arvore;
    inicializar(&arvore);
    int opcao, elem;

    while(opcao != 999)
    {
        printf("1 - ADICIONAR ELEMENTO\n2 - IMPRIMIR ARVORE\n3 - REMOVER ELEMENTO\n999 - SAIR\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            printf("DIGITE O ELEMENTO:\n");
            scanf("%d", &elem);
            adicionar(&arvore, elem);
            break;
        case 2:
            imprimir(arvore);
            printf("\n");
            break;
        case 3:
            printf("DIGITE O ELEMENTO:\n");
            scanf("%d", &elem);
            remover(arvore, elem, &arvore);
        case 999:
            break;
        }
    }
}
