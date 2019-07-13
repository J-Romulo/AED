#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main()
{
    avl* arvore1 = NULL;
    int opcao, elem;
    while(opcao != 999)
    {
        printf("1 - Inserir Elemento\n2 - Percurso pre-order\n3 - Remover Elemento\n999 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            printf("Digite o elemento:\n");
            scanf("%d", &elem);
            if(arvore1 == NULL)
            {
                arvore1 = inicializar(arvore1, elem);
            }
            else
            {
                arvore1 = insercao_avl(arvore1, elem);
            }
            break;
        case 2:
            pre_order(arvore1);
            printf("\n");
            break;
        case 3:
            printf("Digite o elemento:\n");
            scanf("%d", &elem);
            arvore1 = remove_no(arvore1, elem);
            break;
        case 999:
            break;
        }
    }

}
