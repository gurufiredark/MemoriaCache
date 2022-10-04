#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "estrutura.h"

//Busca um valor na memoria principal e retorna NULL caso nao encontre ou a linha em que o valor se encontra na cache
Celula* buscaNaCache(Celula cel, TipoLista *memCache){
    Celula* aux;
    aux = memCache->Primeiro;
    while(aux != NULL){
        if(aux->Linha.posicaoValor1 == cel.Linha.posicaoValor1 || aux->Linha.posicaoValor2 == cel.Linha.posicaoValor2){
            return aux;
        }
        aux = aux->Prox;
    }
    return aux;
}

// Caso a cache esteja cheia, retira o valor que esta no topo da lista
// Por LRU o valor menos acessado estara no topo
int removePrimeiroLista(Celula valor, TipoLista *memCache, int *memPrincipal){
    printf("\n> Limpou uma linha\n");

    if(memCache->Primeiro->Prox->Linha.alteracao == 1){
        int posicaoValor1 = memCache->Primeiro->Prox->Linha.posicaoValor1;
        int posicaoValor2 = memCache->Primeiro->Prox->Linha.posicaoValor2;
        printf("\n>> Alterou a linha %d da PRINCIPAL: %d => %d", posicaoValor1, memPrincipal[posicaoValor1], memCache->Primeiro->Prox->Linha.valor1);
        printf("\n>> Alterou a linha %d da PRINCIPAL: %d => %d", posicaoValor2, memPrincipal[posicaoValor2], memCache->Primeiro->Prox->Linha.valor2);
        memPrincipal[posicaoValor1] = memCache->Primeiro->Prox->Linha.valor1;
        memPrincipal[posicaoValor2] = memCache->Primeiro->Prox->Linha.valor2;
        
    }
    Retira(memCache->Primeiro, memCache);
    Insere(valor.Linha, memCache);
    printf("\n\n> Inseriu o novo\n");
    return 0;
}

// Coloca a celula que tem o valor FIFO mais baixo para o topo
// A celula com o valor FIFO mais baixo corresponde a primeira celula adicionada
// Nesse caso a proxima a ser removida
int reorganizaFifo(TipoLista *memCache){
    printf("\n> Metodo FIFO\n");
    Celula *remocaoPorFifo = memCache->Primeiro->Prox;
    Celula *aux = memCache->Primeiro->Prox;
    while(aux != NULL){
        if(aux->Linha.fifo < remocaoPorFifo->Linha.fifo){
            remocaoPorFifo = aux;
        }
        aux = aux->Prox;
    }
    aux = memCache->Primeiro->Prox;
    while(aux != NULL && memCache->Primeiro != remocaoPorFifo){
        if(aux->Prox == remocaoPorFifo){
            printf("\n> Movendo o primeiro adicionado para para o comeco da lista\n");
            aux->Prox = remocaoPorFifo->Prox;
            remocaoPorFifo->Prox = memCache->Primeiro->Prox->Prox;
            memCache->Primeiro->Prox = remocaoPorFifo;
        }
        aux = aux->Prox;
    }
}

// No caso de HIT a celula que foi visitada é enviada para o fim da lista para ser a ultima a ser removida
int reorganizaHit(Celula *encontrou, TipoLista *memCache){
    Celula *aux = memCache->Primeiro->Prox;
    while(aux != NULL && memCache->Ultimo != encontrou){
        if(aux->Prox == encontrou){
            printf("\n> Movendo para o final da lista\n");
            aux->Prox = encontrou->Prox;
            memCache->Ultimo->Prox = encontrou;
            memCache->Ultimo = encontrou;
            memCache->Ultimo->Prox = NULL;
        }
        aux = aux->Prox;
    }
}