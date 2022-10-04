#ifndef LINHA
#define LINHA
#define CELULA
#define LISTA

// Quantidade de posicoes que a PRINCIPAL vai ter
#define QTD_LINHA_PRINCIPAL 1000
// Quantidade de posicoes que a CACHE vai ter
#define QTD_LINHA_CACHE 16
// Quantidade de acessos que vao ocorrer na PRINCIPAL
#define TAM_ENTRADA_ACESSOS 24
// Variacao maxima dos valores da PRINCIPAL
#define RANGE_PRINCIPAL_VALORES 1000

typedef struct{
    int valor1;     //valor da primeira coluna da linha
    int valor2;     //valor da segunda coluna da linha
    int posicaoValor1;     //valor da primeira coluna da linha
    int posicaoValor2;     //valor da segunda coluna da linha
    int alteracao;   //se vai haver alteracao na primeira coluna da linha
    int fifo;
}LinhaCache;

typedef struct Celula{
    LinhaCache Linha;
    struct Celula* Prox;
}Celula;

typedef struct{
    struct Celula* Primeiro;
    struct Celula* Ultimo;
    int Tamanho;
}TipoLista;

#endif