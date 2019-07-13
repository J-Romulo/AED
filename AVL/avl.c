#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

avl* inicializar(avl* arvore, int elem)
{
    arvore = (avl*)malloc(sizeof(avl));
    arvore->dir = NULL;
    arvore->esq = NULL;
    arvore->info = elem;
    arvore->bal = 0;

    return arvore;
}
avl* insercao_avl(avl* arvore, int elem)
{
    if(arvore == NULL)
    {
        arvore = (avl*)malloc(sizeof(avl));
        arvore->dir = NULL;
        arvore->esq = NULL;
        arvore->info = elem;
        arvore->bal = 0;
        arvore->propagFB = 1;
    }
    else if(elem < arvore->info)
    {
        arvore->esq = insercao_avl(arvore->esq, elem);

        if(arvore->esq->propagFB == 1)
        {
            switch (arvore->bal)
            {
            case 1:
                arvore->bal = 0;
                arvore->propagFB = 0;
                break;
            case 0:
                arvore->bal = -1;
                arvore->propagFB = 1;
                break;
            case -1:
                arvore = imbalance_esq(arvore);
                arvore->propagFB = 0;
                break;
            }
        }
        else
        {
            arvore->propagFB = 0;
        }
    }
    else if(elem > arvore->info)
    {
        arvore->dir = insercao_avl(arvore->dir, elem);

        if(arvore->dir->propagFB == 1)
        {
            switch (arvore->bal)
            {
            case -1:
                arvore->bal = 0;
                arvore->propagFB = 0;
                break;
            case 0:
                arvore->bal = 1;
                arvore->propagFB = 1;
                break;
            case 1:
                arvore = imbalance_dir(arvore);
                arvore->propagFB = 0;
                break;
            }
        }
        else
        {
            arvore->propagFB = 0;
        }
    }

    return arvore;
}

avl* imbalance_esq(avl* arvore)
{
    avl *aux;
    aux = arvore->esq;

    if(aux->bal == -1)
    {
        arvore = rot_dir(arvore);
    }
    else
    {
        arvore = rot_esq_dir(arvore);
    }

    arvore->bal = 0;

    return arvore;
}

avl* imbalance_dir(avl* arvore)
{
    avl *aux;
    aux = arvore->dir;

    if(aux->bal == 1)
    {
        arvore = rot_esq(arvore);
    }
    else
    {
        arvore = rot_dir_esq(arvore);
    }
    arvore->bal = 0;

    return arvore;
}

avl* rot_dir(avl* arvore)
{
    avl* u;
    u = arvore->esq;
    arvore->esq = u->dir;
    u->dir = arvore;
    arvore->bal = 0;
    arvore = u;

    return arvore;
}

avl* rot_esq(avl* arvore)
{
    avl* u;
    u = arvore->dir;
    arvore->dir = u->esq;
    u->esq = arvore;
    arvore->bal = 0;
    arvore = u;

    return arvore;
}

avl* rot_esq_dir(avl* arvore)
{
    avl *u, *v;
    u = arvore->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    arvore->esq = v->dir;
    v->dir = arvore;
    if(v->bal == -1)
    {
        arvore->bal = 1;
    }
    else
    {
        arvore->bal = 0;
    }
    if(v->bal == 1)
    {
        u->bal = -1;
    }
    else
    {
        u->bal = 0;
    }
    arvore = v;

    return arvore;
}

avl* rot_dir_esq(avl* arvore)
{
    avl *u, *v;
    u = arvore->dir;
    v = u->esq;
    u->esq = v->dir;
    v->dir = u;
    arvore->dir = v->esq;
    v->esq = arvore;
    if(v->bal == 1)
    {
        arvore->bal = -1;
    }
    else
    {
        arvore->bal = 0;
    }
    if(v->bal == -1)
    {
        u->bal = 1;
    }
    else
    {
        u->bal = 0;
    }
    arvore = v;

    return arvore;
}

void pre_order(avl *arvore)
{
    if(arvore != NULL)
    {
        printf("[%d,%d]", arvore->info, arvore->bal);
        pre_order(arvore->esq);
        pre_order(arvore->dir);
    }
}


int menor_no(avl* arvore)
{
    if(arvore == NULL)
    {
        return NULL;
    }
    else if(arvore->esq == NULL)
    {
        return arvore->info;
    }
    else
    {
        menor_no(arvore->esq);
    }
}

int buscar_no(avl* arvore, int elem)
{

    if(arvore == NULL)
    {
        return 0;
    }
    else if(arvore->info == elem)
    {
        return 1;
    }
    else if(elem < arvore->info)
    {
        buscar_no(arvore->esq, elem);
    }
    else
    {
        buscar_no(arvore->dir, elem);
    }
}

avl* remove_no(avl* arvore, int elem)
{
    avl* aux;
    if(arvore == NULL)
    {
        return arvore;
    }
    else if(buscar_no(arvore, elem) != 1)
    {
        return arvore;
    }
    else if(arvore->info == elem)
    {
        if(arvore->esq == NULL && arvore->dir == NULL)
        {
            free(arvore);
            return NULL;
        }
        else if(arvore->esq == NULL && arvore->dir != NULL)
        {
            aux = arvore->dir;
            free(arvore);
            return aux;
        }
        else if(arvore->esq != NULL && arvore->dir == NULL)
        {
            aux = arvore->esq;
            free(arvore);
            return aux;
        }
        else if(arvore->esq != NULL && arvore->dir != NULL)
        {
            aux = menor_no(arvore->dir);
            arvore->dir = remove_no(arvore->dir, aux->info);
            arvore->info = aux->info;

            return arvore;
        }
    }
    else if(elem <= arvore->info)
    {
        arvore->esq = remove_no(arvore->esq, elem);

        switch (arvore->bal)
        {
        case 1:
            arvore = imbalance_dir(arvore);

            break;
        case 0:
            arvore->bal = 1;

            break;
        case -1:
            arvore->bal = 0;

            break;
        }
    }

    else if(elem > arvore->info)
    {

        arvore->dir = remove_no(arvore->dir, elem);


        switch (arvore->bal)
        {
        case -1:
            arvore = imbalance_esq(arvore);
            break;
        case 0:
            arvore->bal = -1;
            break;
        case 1:
            arvore->bal = 0;
            break;
        }
    }

    return arvore;
}

