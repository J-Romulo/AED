typedef struct arvore_BST
{
    int num;
    struct no* dir;
    struct no* esq;

} arvore_BST;

arvore_BST* inicializar_arvore();
arvore_BST* inserir_elemento(arvore_BST* arvore, int num);
arvore_BST* remover_elemento(arvore_BST* atual);
arvore_BST* remove_arvBin(arvore_BST* arvore, int elem);
int esta_vazia(arvore_BST* arvore);
void imprimir_arvore(arvore_BST* arvore, int tipo);
int busca(arvore_BST* arvore, int elem);
int maior_elemento(arvore_BST* arvore);
int menor_elemento(arvore_BST* arvore);
int antecessor(arvore_BST* arvore, int elem);
int sucessor(arvore_BST* arvore, int elem);
int altura_arvore(arvore_BST* arvore);
int pai_elem(arvore_BST* arvore, int num);
