#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

void inicializar(arvoreRB *raiz)
{
    *raiz = NULL;
}

void adicionar(arvoreRB *elemento, int valor)
{
    arvoreRB pai, no, novo;
    pai = NULL;
    no = *elemento;

    while(no != NULL)
    {
        pai = no;
        if(no->valor < valor)
        {
            no = no->dir;
        }
        else
        {
            no = no->esq;
        }
    }

    novo = (arvoreRB)malloc(sizeof(struct no_rb));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = pai;
    novo->valor = valor;
    novo->cor = VERMELHO;

    if(eh_raiz(novo))
    {
        *elemento = novo;
    }
    else
    {
        if(valor > pai->valor)
        {
            pai->dir = novo;
        }
        else
        {
            pai->esq = novo;
        }
    }

    ajustar(elemento, novo);

}

void ajustar(arvoreRB *raiz, arvoreRB elemento)
{
    while(cor(elemento->pai) == VERMELHO)
    {

        if(elemento->pai == NULL)
        {
            elemento->cor = PRETO;
        }
        else if(cor(tio(elemento)) == VERMELHO)
        {
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;

            elemento = elemento->pai->pai;
        }

        else if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai))
        {
            rotacao_direita(raiz, elemento->pai->pai);
        }
        else if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai))
        {
            rotacao_esquerda(raiz, elemento->pai->pai);
        }

        else if(eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai))
        {
            rotacao_esquerda(raiz, elemento->pai);
            rotacao_direita(raiz, elemento->pai);
        }
        else if(eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai))
        {
            rotacao_direita(raiz, elemento->pai);
            rotacao_esquerda(raiz, elemento->pai);

        }
    }

    (*raiz)->cor = PRETO;
}

void remover(arvoreRB raiz, int valor, arvoreRB *pai)
{
    arvoreRB aux;
    if(raiz == NULL)
    {

    }
    else if(raiz->valor == valor)
    {

        if(raiz->dir != NULL && raiz->esq != NULL)
        {
            raiz->valor = maior_elemento(raiz->esq);
            remover(raiz->esq, raiz->valor, pai);
        }
        else if(raiz->dir != NULL && raiz->esq == NULL)
        {
            aux = raiz->dir;
            aux->pai = raiz->pai;
            aux->cor = PRETO;
            if(raiz->valor < raiz->pai->valor)
            {
                raiz->pai->esq = NULL;
            }
            else
            {
                raiz->pai->dir = NULL;
            }
            free(raiz);
        }
        else if(raiz->dir == NULL && raiz->esq != NULL)
        {
            aux = raiz->esq;
            aux->pai = raiz->pai;
            aux->cor = PRETO;
            if(raiz->valor < raiz->pai->valor)
            {
                raiz->pai->esq = NULL;
            }
            else
            {
                raiz->pai->dir = NULL;
            }
            free(raiz);
        }
        else if(raiz->dir == NULL && raiz->esq == NULL)
        {
            if(raiz->cor == VERMELHO)
            {
                if(raiz->valor < raiz->pai->valor)
                {
                    raiz->pai->esq = NULL;
                }
                else
                {
                    raiz->pai->dir = NULL;
                }
                free(raiz);
            }
            else
            {
                raiz->duploPreto = 1;
                rebalanceamento(raiz, pai);
                if(raiz->valor < raiz->pai->valor)
                {
                    raiz->pai->esq = NULL;
                }
                else
                {
                    raiz->pai->dir = NULL;
                }
                free(raiz);
            }
        }
    }
    else if(raiz->valor < valor)
    {

        remover(raiz->dir, valor, pai);

    }
    else if(raiz->valor > valor)
    {

        remover(raiz->esq, valor, pai);

    }
}

void rebalanceamento(arvoreRB elementoDP, arvoreRB *pai)
{
    if(eh_raiz(elementoDP))   //CASO 1 ***
    {
        elementoDP->duploPreto = 0;
    }
    else if(eh_filho_esquerdo(elementoDP) && cor(elementoDP->pai) == PRETO && cor(irmao(elementoDP)) == VERMELHO && cor(irmao(elementoDP)->esq) == PRETO && cor(irmao(elementoDP)->dir) == PRETO)   // CASO 2 FILHO ESQUERDO
    {
        rotacao_esquerda(pai, elementoDP->pai);
        elementoDP->pai->cor = VERMELHO;
        elementoDP->pai->pai->cor = PRETO;
        rebalanceamento(elementoDP, pai);
    }
    else if(eh_filho_direito(elementoDP) && cor(elementoDP->pai) == PRETO && cor(irmao(elementoDP)) == VERMELHO && cor(irmao(elementoDP)->esq) == PRETO && cor(irmao(elementoDP)->dir) == PRETO)   // CASO 2 FILHO DIREITO
    {
        rotacao_direita(pai, elementoDP->pai);
        elementoDP->pai->cor = VERMELHO;
        elementoDP->pai->pai->cor = PRETO;
        rebalanceamento(elementoDP, pai);
    }
    else if(cor(elementoDP->pai) == PRETO && cor(irmao(elementoDP)) == PRETO && cor(irmao(elementoDP)->esq) == PRETO && cor(irmao(elementoDP)->dir) == PRETO)   // CASO 3
    {
        elementoDP->duploPreto = 0;
        elementoDP->pai->duploPreto = 1;
        irmao(elementoDP)->cor = VERMELHO;
        rebalanceamento(elementoDP->pai, pai);
    }
    else if(cor(elementoDP->pai) == VERMELHO && cor(irmao(elementoDP)) == PRETO && cor(irmao(elementoDP)->dir) == PRETO && cor(irmao(elementoDP)->esq) == PRETO)   // CASO 4 ***
    {
        elementoDP->pai->cor = PRETO;
        irmao(elementoDP)->cor = VERMELHO;
    }
    else if(eh_filho_esquerdo(elementoDP) && cor(irmao(elementoDP)) == PRETO && cor(irmao(elementoDP)->esq) == VERMELHO && cor(irmao(elementoDP)->dir) == PRETO)   // CASO 5 FILHO ESQUERDO
    {
        rotacao_direita(pai, irmao(elementoDP));
        irmao(elementoDP)->cor = PRETO;
        irmao(elementoDP)->dir->cor = VERMELHO;
        rebalanceamento(elementoDP, pai);
    }
    else if(eh_filho_direito(elementoDP) && cor(irmao(elementoDP)) == PRETO && cor(irmao(elementoDP)->esq) == VERMELHO && cor(irmao(elementoDP)->dir) == PRETO)   // CASO 5 FILHO DIREITO
    {
        rotacao_esquerda(pai, irmao(elementoDP));
        irmao(elementoDP)->cor = PRETO;
        irmao(elementoDP)->esq->cor = VERMELHO;
        rebalanceamento(elementoDP, pai);
    }
    else if(eh_filho_esquerdo(elementoDP) && cor(irmao(elementoDP)) == PRETO && cor(irmao(elementoDP)->dir) == VERMELHO)   // CASO 6 *** FILHO ESQUERDO
    {
        rotacao_esquerda(pai, elementoDP->pai);
        elementoDP->pai->cor = PRETO;
        tio(elementoDP)->cor = PRETO;
    }
    else if(eh_filho_direito(elementoDP) && cor(irmao(elementoDP)) == PRETO && cor(irmao(elementoDP)->esq) == VERMELHO)   // CASO 6 *** FILHO DIREITO
    {
        rotacao_direita(pai, elementoDP->pai);
        elementoDP->pai->cor = PRETO;
        tio(elementoDP)->cor = PRETO;
    }
}




int eh_raiz(arvoreRB elemento)
{
    return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvoreRB elemento)
{
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvoreRB elemento)
{
    return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvoreRB tio(arvoreRB elemento)
{
    return irmao(elemento->pai);
}

arvoreRB irmao(arvoreRB elemento)
{
    if(eh_filho_esquerdo(elemento))
        return elemento->pai->dir;
    else
        return elemento->pai->esq;
}




int maior_elemento(arvoreRB raiz)
{
    if(raiz == NULL)
        return -1;
    if(raiz->dir == NULL)
        return raiz->valor;
    else
        return maior_elemento(raiz->dir);
}




void rotacao_esquerda(arvoreRB *raiz, arvoreRB elemento)
{
    arvoreRB pivo;
    int filhoDireito = eh_filho_direito(elemento);
    pivo = elemento->dir;
    elemento->dir = pivo->esq;
    pivo->esq = elemento;
    pivo->pai = elemento->pai;
    elemento->pai = pivo;


    if(elemento->dir != NULL)
    {
        elemento->dir->pai = elemento;
    }

    elemento->cor = VERMELHO;
    pivo->cor = PRETO;

    if(pivo->pai == NULL)
    {
        *raiz = pivo;
    }
    else if(filhoDireito)
    {
        pivo->pai->dir = pivo;
    }
    else
    {
        pivo->pai->esq = pivo;
    }
}

void rotacao_direita(arvoreRB *raiz, arvoreRB elemento)
{
    arvoreRB pivo;
    int filhoEsquerdo = eh_filho_esquerdo(elemento);
    pivo = elemento->esq;
    elemento->esq = pivo->dir;
    pivo->dir = elemento;
    pivo->pai = elemento->pai;
    elemento->pai = pivo;

    if(elemento->esq != NULL)
    {
        elemento->esq->pai = elemento;
    }

    elemento->cor = VERMELHO;
    pivo->cor = PRETO;

    if(pivo->pai == NULL)
    {
        *raiz = pivo;
    }
    else if(filhoEsquerdo)
    {
        pivo->pai->esq = pivo;
    }
    else
    {
        pivo->pai->dir = pivo;
    }
}




enum cor cor(arvoreRB no)
{
    enum cor corRaiz;
    if(no==NULL || no->cor == PRETO)
        corRaiz = PRETO;
    else
        corRaiz = VERMELHO;
    return corRaiz;
}

void imprimir(arvoreRB raiz)
{
    if(raiz != NULL)
    {
        if(raiz->cor == VERMELHO)
        {
            printf("[%d;%s]", raiz->valor, "VERMELHO");
        }
        else
        {
            printf("[%d;%s]", raiz->valor, "PRETO");
        }
        imprimir(raiz->esq);
        imprimir(raiz->dir);
    }
}
