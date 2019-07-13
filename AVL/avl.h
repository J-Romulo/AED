typedef struct no
{
    struct no* dir;
    struct no* esq;
    int info;
    int bal;
    int propagFB;
} avl;

avl* inicializar(avl* arvore, int elem);
avl* insercao_avl(avl* arvore, int elem);
avl* imbalance_esq(avl* arvore);
avl* imbalance_dir(avl* arvore);
avl* rot_dir(avl* arvore);
avl* rot_esq(avl* arvore);
avl* rot_esq_dir(avl* arvore);
avl* rot_dir_esq(avl* arvore);
void pre_order(arvore);
int menor_no(avl* arvore);
int buscar_no(avl* arvore, int elem);
avl* remove_no(avl* arvore, int elem);
