enum cor { VERMELHO, PRETO };

typedef int type_key;

typedef struct no_rb
{
    type_key valor;
    enum cor cor;
    struct no_rb* dir;
    struct no_rb* esq;
    struct no_rb* pai;
    int duploPreto;

} no_rb;

typedef no_rb *arvoreRB;

void inicializar(arvoreRB* raiz);
void adicionar(arvoreRB *elemento, int valor);
void ajustar(arvoreRB *raiz, arvoreRB elemento);
void remover(arvoreRB raiz, int valor, arvoreRB *pai);
void rebalanceamento(arvoreRB elementoDP, arvoreRB *pai);

int eh_raiz(arvoreRB elemento);
int eh_filho_esquerdo(arvoreRB elemento);
int eh_filho_direito(arvoreRB elemento);
arvoreRB tio(arvoreRB elemento);
arvoreRB irmao(arvoreRB elemento);

int maior_elemento(arvoreRB raiz);

void rotacao_esquerda(arvoreRB *raiz, arvoreRB elemento);
void rotacao_direita(arvoreRB *raiz, arvoreRB elemento);

enum cor cor(arvoreRB no);
void imprimir(arvoreRB raiz);
