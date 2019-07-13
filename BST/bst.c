#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bst.h"

arvore_BST* inicializar_arvore(arvore_BST* arvore, int num)
{
    arvore = (arvore_BST*)malloc(sizeof(arvore_BST));
    arvore->num = num;
    arvore->dir = NULL;
    arvore->esq = NULL;

    return arvore;
}

arvore_BST* inserir_elemento(arvore_BST* arvore, int num)
{
    if(arvore == NULL)
    {
        arvore = (arvore_BST*)malloc(sizeof(arvore_BST));
        arvore->num = num;
        arvore->dir = NULL;
        arvore->esq = NULL;
    }
    else if(num < arvore->num)
    {
        arvore->esq = inserir_elemento(arvore->esq, num);
    }
    else
    {
        arvore->dir = inserir_elemento(arvore->dir, num);
    }
}

arvore_BST* remover_elemento(arvore_BST* atual)
{
    arvore_BST* no1;
    arvore_BST* no2;
    if(atual->esq == NULL)
    {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL)
    {
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual)
    {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

arvore_BST* remove_arvBin(arvore_BST* arvore, int elem)
{
    if(arvore == NULL)
    {
        return 0;
    }
    struct arvore_BST* ant = NULL;
    struct arvore_BST* atual = arvore;
    while(atual != NULL)
    {
        if(elem == atual->num)
        {
            if(atual == arvore)
            {
                arvore = remover_elemento(atual);
            }
            else
            {
                if(ant->dir == atual)
                {
                    ant->dir = remover_elemento(atual);
                }
                else
                {
                    ant->esq = remover_elemento(atual);
                }
            }
            return 1;
        }
        ant = atual;
        if(elem > atual->num)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }
    }
    return 0;
}

int esta_vazia(arvore_BST* arvore)
{
    if(arvore == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void imprimir_arvore(arvore_BST* arvore, int tipo)
{
    if(esta_vazia(arvore) == 0 && tipo == -1)
    {
        printf("[%d]", arvore->num);
        imprimir_arvore(arvore->esq, -1);
        imprimir_arvore(arvore->dir, -1);
    }
    else if(esta_vazia(arvore) == 0 && tipo == 0)
    {
        imprimir_arvore(arvore->esq, 0);
        printf("[%d]", arvore->num);
        imprimir_arvore(arvore->dir, 0);
    }
    else if(esta_vazia(arvore) == 0 && tipo == 1)
    {
        imprimir_arvore(arvore->esq, 1);
        imprimir_arvore(arvore->dir, 1);
        printf("[%d]", arvore->num);
    }
}

int busca(arvore_BST* arvore, int num)
{
    if(arvore == NULL)
    {
        return 0;
    }
    if(arvore->num == num)
    {
        return 1;
    }
    else if(num < arvore->num)
    {
        busca(arvore->esq, num);
    }
    else
    {
        busca(arvore->dir, num);
    }
}

int maior_elemento(arvore_BST* arvore)
{
    if(arvore->dir != NULL)
    {
        maior_elemento(arvore->dir);
    }
    else
    {
        return arvore->num;
    }
}

int menor_elemento(arvore_BST* arvore)
{
    if(arvore->esq != NULL)
    {
        menor_elemento(arvore->esq);
    }
    else
    {
        return arvore->num;
    }
}

int antecessor(arvore_BST* arvore, int elem)
{
    if(busca(arvore, elem) == 0)
    {
        return -1;
    }
    arvore_BST* aux1 = arvore;
    arvore_BST* aux2 = NULL;
    while(aux1 != NULL)
    {
        if(aux1->num == elem)
        {
            if(aux1->esq != NULL)
            {
                return maior_elemento(aux1->esq);
            }
            else
            {
                break;
            }
        }
        else if(elem > aux1->num)
        {
            aux2 = aux1;

            aux1 = aux1->dir;
        }
        else if(elem < aux1->num)
        {

            aux1 = aux1->esq;
        }
    }
    if(aux2!= NULL)
    {
        return aux2->num;
    }
    else
    {
        return -1;
    }

}

int sucessor(arvore_BST* arvore, int elem)
{
    if(busca(arvore, elem) == 0)
    {
        return -1;
    }
    arvore_BST* aux1 = arvore;
    arvore_BST* aux2 = NULL;
    while(aux1 != NULL)
    {
        if(aux1->num == elem)
        {
            if(aux1->dir != NULL)
            {
                return menor_elemento(aux1->dir);
            }
            else
            {
                break;
            }
        }
        else if(elem > aux1->num)
        {
            aux1 = aux1->dir;
        }
        else if(elem < aux1->num)
        {
            aux2 = aux1;
            aux1 = aux1->esq;
        }
    }
    if(aux2!= NULL)
    {
        return aux2->num;
    }
    else
    {
        return -1;
    }
}

int altura_arvore(arvore_BST* arvore)
{
    int altura = 1;

    if(arvore == NULL)
    {
        return 0;
    }
    else if(arvore->dir == NULL && arvore->esq == NULL)
    {
        return altura;
    }

    int alturaDir = altura_arvore(arvore->dir);
    int alturaEsq = altura_arvore(arvore->esq);

    if( alturaDir >= alturaEsq)
    {
        altura += alturaDir;
    }
    else
    {
        altura += alturaEsq;
    }

    return altura;

}

int pai_elem(arvore_BST* arvore, int num)
{
    if(busca(arvore, num) == 0)
    {
        return -1;
    }

    arvore_BST* pai = arvore;
    arvore_BST* filho1 = arvore->dir;
    arvore_BST* filho2 = arvore->esq;

    if(pai == NULL)
    {
        return -1;
    }
    else if(filho1 == NULL && filho2 == NULL)
    {
        return -1;
    }
    if(pai->num == num)
    {
        return -1;
    }
    if(filho1 != NULL)
    {
        if(filho1->num == num)
        {
            return pai->num;
        }
    }
    if(filho2 != NULL)
    {
        if(filho2->num == num)
        {
            return pai->num;
        }
    }
    if(num > pai->num)
    {
        pai_elem(pai->dir, num);
    }
    else if(num <= pai->num)
    {
        pai_elem(pai->esq, num);
    }
}
