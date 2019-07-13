#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main()
{
    no* arvore1 = NULL;
    int opcao, elem;

    while(opcao != 999){
        printf("1 - Inserir um elemento\n2 - Percurso em Pre ordem\n3 - Percurso em ordem\n4 - Percurso em pos ordem\n5 - Remover elemento\n6 - Mostrar maior elemento\n7 - Mostrar menor elemento\n8 - Altura da arvore\n9 - Pai de um elemento\n10 - Sucessor\n11 - Antecessor\n999 - Encerrar programa\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            printf("Digite um elemento\n");
            scanf("%d", &elem);
            if(arvore1 == NULL){
                arvore1 = inicializarArvore(arvore1, elem);
            }else{
                inserirElemento(arvore1, elem);
            }
            break;
        case 2:
            imprimirArvore(arvore1, -1);
            printf("\n");
            break;
        case 3:
            imprimirArvore(arvore1, 0);
            printf("\n");
            break;
        case 4:
            imprimirArvore(arvore1, 1);
            printf("\n");
            break;
        case 5:
            printf("Digite um elemento\n");
            scanf("%d", &elem);
            remove_arvBin(arvore1, elem);
            break;
        case 6:
            printf("[%d]\n", maiorElemento(arvore1));
            break;
        case 7:
            printf("[%d]\n", menorElemento(arvore1));
            break;
        case 8:
            printf("%d\n", alturaArvore(arvore1));
            break;
        case 9:
            printf("Digite um elemento\n");
            scanf("%d", &elem);
            printf("%d\n", paiElem(arvore1, elem));
            break;
        case 10:
            printf("Digite um elemento\n");
            scanf("%d", &elem);
            printf("%d\n", sucessor(arvore1, elem));
            break;
        case 11:
            printf("Digite um elemento\n");
            scanf("%d", &elem);
            printf("%d\n", antecessor(arvore1, elem));
            break;
        }
    }

}
