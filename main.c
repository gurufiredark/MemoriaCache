# include <stdio.h>
# include <string.h>
# include <time.h>
# include "toolsFila.c"
# include "toolsPrincipalCache.c"

int main (){
    int opcao;
    srand((unsigned)time(NULL));

    // Criacao da memoria PRINCIPAL
    int memPrincipal[QTD_LINHA_PRINCIPAL];
    for(int i=0; i<QTD_LINHA_PRINCIPAL; i++){
        memPrincipal[i] = rand() % RANGE_PRINCIPAL_VALORES;
    }
    printf("\n\n---> Imprimindo memoria PRINCIPAL\n");
    for(int i=0; i<QTD_LINHA_PRINCIPAL; i++){
        printf("posicao %d -> %d   ", i, memPrincipal[i]);
        if(i%6 == 0){
            printf("\n");
        }
    }

    // Criacao da ordemm de acesso na PRINCIPAL
    int acessosPRINCIPAL[TAM_ENTRADA_ACESSOS];
    for(int i=0; i<TAM_ENTRADA_ACESSOS; i++){
        acessosPRINCIPAL[i] = rand() % QTD_LINHA_PRINCIPAL;
    }
    // 1 Se haverá alteracao e 0 se não havera
    int alteracaoEntrada[TAM_ENTRADA_ACESSOS];
    for(int i=0; i<TAM_ENTRADA_ACESSOS; i++){
        alteracaoEntrada[i] = rand() % 2;
    }

    printf("\n\n---> Imprimindo ordem de acesso da memoria PRINCIPAL\n");
    for(int i=0; i<TAM_ENTRADA_ACESSOS; i++){
        printf("acesso %d -> alteracao %d\n", acessosPRINCIPAL[i], alteracaoEntrada[i]);
    }



    printf("\n---> Criou lista vazia para memoria Cache\n"); // Cria uma lista vazia para memoia Cache
    TipoLista memCache;
    FLVazia(&memCache);

    for(int acessoAtual = 0; acessoAtual < TAM_ENTRADA_ACESSOS; acessoAtual++){ // Percorre todos os valores de acesso a principal
        
        printf("\n\n---> Pegando posicao %d na memoria PRINCIPAL\n", acessosPRINCIPAL[acessoAtual]);

        // Cria uma celula com o valor da posicao da PRINCIPAL que foi acessado
        Celula a;
        a.Linha.alteracao = alteracaoEntrada[acessoAtual];
        a.Linha.fifo = acessoAtual;
        if(acessosPRINCIPAL[acessoAtual] % 2 == 0){
            a.Linha.posicaoValor1 = memPrincipal[acessosPRINCIPAL[acessoAtual]];
            a.Linha.posicaoValor2 = memPrincipal[acessosPRINCIPAL[acessoAtual]+1];
            if(alteracaoEntrada[acessoAtual] == 1){
                a.Linha.valor1 = rand() % RANGE_PRINCIPAL_VALORES;
                printf("\n--> Alteracao do valor: %d => %d", memPrincipal[a.Linha.posicaoValor1], a.Linha.valor1);
            }else{
                a.Linha.valor1 = memPrincipal[a.Linha.posicaoValor1];
            }
            a.Linha.valor2 = memPrincipal[a.Linha.posicaoValor2];
        }else{
            a.Linha.posicaoValor1 = memPrincipal[acessosPRINCIPAL[acessoAtual]-1];
            a.Linha.posicaoValor2 = memPrincipal[acessosPRINCIPAL[acessoAtual]];
            a.Linha.valor1 = memPrincipal[a.Linha.posicaoValor1];
            if(alteracaoEntrada[acessoAtual] == 1){
                a.Linha.valor2 = rand() % RANGE_PRINCIPAL_VALORES;      
                printf("\n--> Alteracao do valor: %d => %d", memPrincipal[a.Linha.posicaoValor2], a.Linha.valor2);
            }else{
                a.Linha.valor2 = memPrincipal[a.Linha.posicaoValor2];
            }
        }

        // Busca a celula na memoria cache
        printf("\n--> Buscando celula %d - %d | %d - %d na memoria cache\n", a.Linha.posicaoValor1, a.Linha.valor1, a.Linha.posicaoValor2, a.Linha.valor2);
        Celula* encontrou = buscaNaCache(a, &memCache);
        if(encontrou == NULL){ // Se nao encontrou
            printf("\n-> Nao esta na cache\n");
            if(memCache.Tamanho < QTD_LINHA_CACHE){ // Se a cache não estiver cheia insere no fim da lista
                printf("\n> Inserindo na cache\n");
                Insere(a.Linha, &memCache);
            }else{ // Se a cache estiver cheia, usa um dos metodos FIFO ou LRU
                printf("\n> Cache cheia\n> Metodo de substituicao:");
                // Menu de opções
                printf("\n1 - Metodo de substituicao FIFO");
                printf("\n2 - Metodo de substituicao LRU");
                printf("\n>>> ");
                scanf("%d", &opcao);
                if(opcao == 1){
                    // Coloca o valor que foi inserido primeiro no topo da lista para ser removido
                    reorganizaFifo(&memCache);
                }
                // Remove o prieiro da lista
                removePrimeiroLista(a, &memCache, memPrincipal);
            }
        }else{
            printf("\n-> Achou na posicao na cache (HIT)\n");
            // Em caso de HIT atualiza a memoria cache colocando a celula na ultma posicao e a cache eh impressa
            reorganizaHit(encontrou, &memCache);
            Imprime(memCache);
            
        }
    }

    printf("\n\n---> Imprimindo memoria PRINCIPAL\n");
    for(int i=0; i<QTD_LINHA_PRINCIPAL; i++){
        printf("posicao %d -> %d   ", i, memPrincipal[i]);
        if(i%6 == 0){
            printf("\n");
        }
    }
    
    printf("\n\n---> Imprimindo memoria cache\n");
    Imprime(memCache);

    printf("\n\nPrograma Finalizado :) (digite qualquer numero para fechar)\n");
    scanf("%d", &opcao);
    return 0;

}