/*
 ============================================================================
 Name        : TP1.c
 Author      : Alex
 Version     :
 Copyright   : Your copyright notice
 Description : Segundo TP de organizacaoo de computadores - Criacao da Maquina - Foco na Memoria Cache
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int *palavras;
    int endBloco;
    int custo;
    int cacheHit;
    time_t segundos;
} BlocoMemoria;

typedef struct
{
    int endBloco;
    int endPalavra;
} Endereco;

typedef struct
{
    Endereco add1;
    Endereco add2;
    Endereco add3;
    int opcode;
} Instrucao;

int opcaoPrograma;

int tamanhoDisco = 10000;
int tamanhoRAM = 1000;
int qdePalavrasBloco = 4;
int tamanhoCache1 = 16;
int tamanhoCache2 = 32;
int tamanhoCache3 = 64;
int tamanhoProgramaNormal = 10001;
int tamanhoProgramaTI = 101;
char *nomeArqNornal = "instrucoes.txt";
char *nomeArqTI = "tratador_interrupcao.txt";

long long int custo = 0;
long long int missC1 = 0;
long long int hitC1 = 0;
long long int missC2 = 0;
long long int hitC2 = 0;
long long int missC3 = 0;
long long int hitC3 = 0;
long long int missRAM = 0;
long long int hitRAM = 0;

Instrucao *memoriaInstrucoesNormal;
Instrucao *memoriaInstrucoesTI;
BlocoMemoria *cache1;
BlocoMemoria *cache2;
BlocoMemoria *cache3;
BlocoMemoria *RAM;

//BlocoMemoria
void setCustoMemoria(BlocoMemoria *aux, int custoAux);
void setEndBlocoMemoria(BlocoMemoria *aux, int endBlocoAux);
void setPalavrasMemoria(BlocoMemoria *aux, int * palavrasAux);
void setCacheHitMemoria(BlocoMemoria *aux, int cacheHitAux);
void setSegundosMemoria(BlocoMemoria *aux, int segundosAux);
int getCustoMemoria(BlocoMemoria *aux);
int* getPalavrasMemoria(BlocoMemoria *aux);
int getEndBlocoMemoria(BlocoMemoria *aux);


//Instrucao
void setOpcodeInstrucao(Instrucao *umaInstrucao, int opcodeAux);
void setAdd1Instrucao(Instrucao *umaInstrucao, Endereco *add1Aux);
void setAdd2Instrucao(Instrucao *umaInstrucao, Endereco *add2Aux);
void setAdd3Instrucao(Instrucao *umaInstrucao, Endereco *add3Aux);
int getOpcodeInstrucao(Instrucao *umaInstrucao);
Endereco* getAdd1Instrucao(Instrucao *umaInstrucao);
Endereco* getAdd2Instrucao(Instrucao *umaInstrucao);
Endereco* getAdd3Instrucao(Instrucao *umaInstrucao);

//Endereco
void setEndBlocoEndereco(Endereco *end, int endBlocoAux);
void setEndPalavraEndereco(Endereco *end, int endPalavraAux);
int getEndBlocoEndereco(Endereco *end);
int getEndPalavraEndereco(Endereco *end);

//Caches - MMU
void setEndBlocoCache(int endBlocoAux, int posicao, BlocoMemoria *qqCache);
void setCustoCache(int custoAux, int posicao, BlocoMemoria *qqCache);
void setCacheHitCache(int cacheHitAux, int posicao, BlocoMemoria *qqCache);
void setSegundosCache(int segundoAux, int posicao, BlocoMemoria *qqCache);
int getEndBlocoCache(int posicao, BlocoMemoria *qqCache);
int* getPalavrasCache(int posicao, BlocoMemoria *qqCache);
int getCacheHitMemoria(BlocoMemoria *aux);
time_t getSegundosCache(int posicao, BlocoMemoria *qqCache);

//Funcoes
void menu();
void menuPrintar();
void alocaMemorias();
void desalocaMemorias();
void montarRAM();
char* nomearDiretorioArquivos(int indice);
void montarCacheVazio(int tamanho, BlocoMemoria* qqCache);
void montarInstrucoesProgramaAleatorio(int tamanhoPrograma);
void montarInstrucaoGerador(char *nomeArq, int tamanhoPrograma);
void maquina(int PC, char *programa);
BlocoMemoria* buscarNasMemorias(Endereco *end);
int algoritmoSubstituicaoLRU(int conjuntoCache, int tamanhoCache);
void guardarInformacao(int posicaoCache, int tamanhoCache, int conjuntoCache2, int conjuntoCache3,  Endereco *endAux);
void invalidarPosicacoCache(int posicaoCacheX, int posicaoCacheY, int tamanhoCache);
void montarCachePrintar(int tamanho, BlocoMemoria *qqCache);
BlocoMemoria* endPalavraDisco(int endBloco);
void guardarInformacaoDisco(int endBlocoRAM, int *endPalavraRAM);

int main(){
    alocaMemorias();
    montarRAM();
    montarCacheVazio(tamanhoCache1, cache1);
    montarCacheVazio(tamanhoCache2, cache2);
    montarCacheVazio(tamanhoCache3, cache3);

    int opcao;

    do{
        menu();

        scanf("%d", &opcao);
		getchar();
		switch (opcao){
            case 1:
                opcaoPrograma = 1;
                montarInstrucoesProgramaAleatorio(tamanhoProgramaNormal);
                maquina(0, nomeArqNornal);

                printf("\n\nENCERROU O PROGRAMA!!\n\n");
                break;
            
            case 2:
                opcaoPrograma = 2;
                montarInstrucaoGerador(nomeArqNornal, tamanhoProgramaNormal);
                maquina(0, nomeArqNornal);

                
                printf("\n\nENCERROU O PROGRAMA!!!\n\n");
                break;
        }

    }while (opcao != 0);

    do{
        menuPrintar();

        scanf("%d", &opcao);
		getchar();
		switch (opcao){
            case 1:
                montarCachePrintar(tamanhoCache1, cache1);
                break;
            
            case 2:
                montarCachePrintar(tamanhoCache2, cache2);
                break;
            
            case 3:
                montarCachePrintar(tamanhoCache3, cache3);
                break;
        }
    }while (opcao != 0);

    desalocaMemorias();
    return 0;
}

void menuPrintar(){
    printf("\n========================== MENU =======================\n\n");
    printf("Printar Cache1 - 1\n");
    printf("Printar Cache2 - 2\n");
    printf("Printar Cache3 - 3\n");
    printf("Sair - Digite 0\n");
    printf("\n=======================================================\n\n");
	printf("Digite um numero: ");
}

void menu(){
	printf("\n========================== MENU =======================\n\n");
	printf("Maquina com Mapeamento Direto Aleatorio - Digite 1\n");
	printf("Maquina com Mapeamento Direto Arquivo - Digite 2\n");
	printf("Sair - Digite 0\n");
	printf("\n=======================================================\n\n");
	printf("Digite um numero: ");
}

void alocaMemorias(){
    RAM = malloc(tamanhoRAM * sizeof(BlocoMemoria));
    cache1 = malloc(tamanhoCache1 * sizeof(BlocoMemoria));
    cache2 = malloc(tamanhoCache2 * sizeof(BlocoMemoria));
    cache3 = malloc(tamanhoCache3 * sizeof(BlocoMemoria));
}

void desalocaMemorias(){
    free(RAM);
    free(cache1);
    free(cache2);
    free(cache3);
    free(memoriaInstrucoesNormal); 
}

void montarRAM()
{
    srand(time(NULL));
    int r;

    for (int i = 0; i < tamanhoRAM; i++)
    {
        BlocoMemoria *aux = malloc(sizeof(BlocoMemoria));

        int *palavrasAux = malloc(qdePalavrasBloco * sizeof(int));

        for(int j = 0; j < qdePalavrasBloco; j++){
            r = rand() % 1000000; 
            palavrasAux[j] = r;
        }

        setPalavrasMemoria(aux, palavrasAux);
        setEndBlocoMemoria(aux, i);
    
        RAM[i] = *aux;
    }

    for(int i = 0; i < tamanhoDisco; i++){
        char *nomeArqDisco = nomearDiretorioArquivos(i);

        FILE *arquivoDisco = fopen(nomeArqDisco, "w");

        int *palavrasAux = malloc(qdePalavrasBloco * sizeof(int));

        if(i <= tamanhoRAM){
            fprintf(arquivoDisco, "%d %d %d %d\n", 0, 0, 0, 0);
        }else{
            for(int j = 0; j < qdePalavrasBloco; j++){
                r = rand() % 1000000;
                palavrasAux[j] = r;
            }

            fprintf(arquivoDisco, "%d %d %d %d\n", palavrasAux[0], palavrasAux[1], palavrasAux[2], palavrasAux[3]);
        }

        fclose(arquivoDisco);
        free(nomeArqDisco);
    }
}

char* nomearDiretorioArquivos(int indice){
    char endArqTXT[10];
    char *diretorio = "/home/arthur/Documentos/TP_OrgComp/TP3/ArquivosTXT/";
    char *tipoArq = ".txt";
    sprintf(endArqTXT, "%d", indice);
    int tamanhoDiretorio = strlen(diretorio), tamanhoTipoArq = strlen(tipoArq), tamanhoEndArqTXT = strlen(endArqTXT);
    int tamanhoTotal = tamanhoDiretorio + tamanhoTipoArq + tamanhoEndArqTXT + 1;
    char *nomeArqDiscoAux = malloc(tamanhoTotal * sizeof(char));
    memcpy(nomeArqDiscoAux, diretorio, tamanhoTotal);
    strcat(nomeArqDiscoAux, endArqTXT);
    strcat(nomeArqDiscoAux, tipoArq);

    return nomeArqDiscoAux;
}

void montarCacheVazio(int tamanho, BlocoMemoria *qqCache){
    time_t segundoEntradoCache;
    time(&segundoEntradoCache);
    segundoEntradoCache = segundoEntradoCache - 10;

    for(int i = 0; i < tamanho; i++){
        BlocoMemoria *aux = malloc(sizeof(BlocoMemoria));

        //Forcando cache estar vazia
        setEndBlocoMemoria(aux, INT_MIN);
        setSegundosMemoria(aux, segundoEntradoCache);

        qqCache[i] = *aux;
    }
}

void montarCachePrintar(int tamanho, BlocoMemoria *qqCache){
    for(int i = 0; i < tamanho; i++){
        printf("\n==================== Cache =====================\n\n");
        printf("EndBloco: %d\n", qqCache[i].endBloco);
        printf("Custo: %d\n", qqCache[i].custo);
        printf("CacheHit: %d\n", qqCache[i].cacheHit);
        struct tm *data;
        data = localtime(&qqCache[i].segundos);

        printf("Segundos: %d:%d:%d\n", data->tm_hour, data->tm_min, data->tm_sec);
        printf("\n=================================================\n\n");
    }
}

void montarInstrucoesProgramaAleatorio(int tamanhoPrograma){
    srand(time(NULL));
    int r;

    if(tamanhoPrograma ==  tamanhoProgramaNormal){
        memoriaInstrucoesNormal = malloc(tamanhoPrograma * sizeof(Instrucao));

        for(int i = 0; i < tamanhoPrograma -1; i++){
            Instrucao *umaInstrucao = malloc(sizeof(Instrucao));

            r = rand() % 3;
            setOpcodeInstrucao(umaInstrucao, r);

            Endereco *add1 = malloc(sizeof(Endereco));
            r = rand() % tamanhoRAM;
            add1->endBloco = r;
            umaInstrucao->add1.endBloco = r;
            r = rand() % qdePalavrasBloco;
            add1->endPalavra = r;
            setAdd1Instrucao(umaInstrucao, add1);
            
            Endereco *add2 = malloc(sizeof(Endereco));
            r = rand() % tamanhoRAM;
            add2->endBloco = r;
            r = rand() % qdePalavrasBloco;
            add2->endPalavra = r;
            setAdd2Instrucao(umaInstrucao, add2);

            Endereco *add3 = malloc(sizeof(Endereco));
            r = rand() % tamanhoRAM;
            add3->endBloco = r;
            r = rand() % qdePalavrasBloco;
            add3->endPalavra = r;
            setAdd3Instrucao(umaInstrucao, add3);

            memoriaInstrucoesNormal[i] = *umaInstrucao;
        }

        Instrucao *umaInstrucao = malloc(sizeof(Instrucao));
        setOpcodeInstrucao(umaInstrucao, -1);
        memoriaInstrucoesNormal[tamanhoPrograma -1] = *umaInstrucao;
        free(umaInstrucao);
    }else if(tamanhoPrograma ==  tamanhoProgramaTI){
        memoriaInstrucoesNormal = malloc(tamanhoPrograma * sizeof(Instrucao));

        for(int i = 0; i < tamanhoPrograma -1; i++){
            Instrucao *umaInstrucao = malloc(sizeof(Instrucao));

            r = rand() % 3;
            setOpcodeInstrucao(umaInstrucao, r);

            Endereco *add1 = malloc(sizeof(Endereco));
            r = rand() % tamanhoRAM;
            add1->endBloco = r;
            umaInstrucao->add1.endBloco = r;
            r = rand() % qdePalavrasBloco;
            add1->endPalavra = r;
            setAdd1Instrucao(umaInstrucao, add1);
            
            Endereco *add2 = malloc(sizeof(Endereco));
            r = rand() % tamanhoRAM;
            add2->endBloco = r;
            r = rand() % qdePalavrasBloco;
            add2->endPalavra = r;
            setAdd2Instrucao(umaInstrucao, add2);

            Endereco *add3 = malloc(sizeof(Endereco));
            r = rand() % tamanhoRAM;
            add3->endBloco = r;
            r = rand() % qdePalavrasBloco;
            add3->endPalavra = r;
            setAdd3Instrucao(umaInstrucao, add3);

            memoriaInstrucoesTI[i] = *umaInstrucao;
        }

        Instrucao *umaInstrucao = malloc(sizeof(Instrucao));
        setOpcodeInstrucao(umaInstrucao, -1);
        memoriaInstrucoesTI[tamanhoPrograma -1] = *umaInstrucao;
        free(umaInstrucao);
    }
}

void montarInstrucaoGerador(char *nomeArq, int tamanhoPrograma){
    FILE *arquivo = fopen("instrucoes.txt", "r");
    int opcodeAux, endBlocoAux1, endPalavraAux1, endBlocoAux2, endPalavraAux2, endBlocoAux3, endPalavraAux3;

    if(strcmp(nomeArq, nomeArqNornal) == 0){
        memoriaInstrucoesNormal = malloc(tamanhoPrograma * sizeof(Instrucao));

        for(int i = 0; i < tamanhoPrograma - 1; i++){
            Instrucao *umaInstrucao = malloc(sizeof(Instrucao));

            fscanf(arquivo, "%d %d %d %d %d %d %d\n", &opcodeAux, &endBlocoAux1, &endPalavraAux1, &endBlocoAux2, &endPalavraAux2, &endBlocoAux3, &endPalavraAux3);
            
            setOpcodeInstrucao(umaInstrucao, opcodeAux);

            Endereco *add1 = malloc(sizeof(Endereco));
            add1->endBloco = endBlocoAux1;
            add1->endPalavra = endPalavraAux1;
            setAdd1Instrucao(umaInstrucao, add1);

            Endereco *add2 = malloc(sizeof(Endereco));
            add2->endBloco = endBlocoAux2;
            add2->endPalavra = endPalavraAux2;
            setAdd2Instrucao(umaInstrucao, add2);

            Endereco *add3 = malloc(sizeof(Endereco));
            add3->endBloco = endBlocoAux3;
            add3->endPalavra = endPalavraAux3;
            setAdd3Instrucao(umaInstrucao, add3);

            memoriaInstrucoesNormal[i] = *umaInstrucao;
        }

        Instrucao *umaInstrucao = malloc(sizeof(Instrucao));
        setOpcodeInstrucao(umaInstrucao, -1);
        memoriaInstrucoesNormal[tamanhoPrograma - 1] = *umaInstrucao;
        free(umaInstrucao);
    }else if(strcmp(nomeArq, nomeArqTI) == 0){
        memoriaInstrucoesTI = malloc(tamanhoPrograma * sizeof(Instrucao));

        for(int i = 0; i < tamanhoPrograma - 1; i++){
            Instrucao *umaInstrucao = malloc(sizeof(Instrucao));

            fscanf(arquivo, "%d %d %d %d %d %d %d\n", &opcodeAux, &endBlocoAux1, &endPalavraAux1, &endBlocoAux2, &endPalavraAux2, &endBlocoAux3, &endPalavraAux3);
            
            setOpcodeInstrucao(umaInstrucao, opcodeAux);

            Endereco *add1 = malloc(sizeof(Endereco));
            add1->endBloco = endBlocoAux1;
            add1->endPalavra = endPalavraAux1;
            setAdd1Instrucao(umaInstrucao, add1);

            Endereco *add2 = malloc(sizeof(Endereco));
            add2->endBloco = endBlocoAux2;
            add2->endPalavra = endPalavraAux2;
            setAdd2Instrucao(umaInstrucao, add2);

            Endereco *add3 = malloc(sizeof(Endereco));
            add3->endBloco = endBlocoAux3;
            add3->endPalavra = endPalavraAux3;
            setAdd3Instrucao(umaInstrucao, add3);

            memoriaInstrucoesTI[i] = *umaInstrucao;
	    }

        Instrucao *umaInstrucao = malloc(sizeof(Instrucao));
        setOpcodeInstrucao(umaInstrucao, -1);
        memoriaInstrucoesTI[tamanhoPrograma - 1] = *umaInstrucao;
        free(umaInstrucao);
    }

    fclose(arquivo);
}

//Registradores PC
void maquina(int PC, char *programa){
    int opcode = INT_MAX;
    int conteudo1, conteudo2, sub, soma;
    srand(time(NULL));
    int chance;
    
    while(opcode != -1){
        Instrucao *umaInstrucao = malloc(sizeof(Instrucao));

        if(programa == nomeArqNornal){
            *umaInstrucao = memoriaInstrucoesNormal[PC];
        }else if(programa == nomeArqTI){
            *umaInstrucao = memoriaInstrucoesTI[PC];
        }

        opcode = getOpcodeInstrucao(umaInstrucao);
        
        //TP2
        if(opcode != -1){        
            BlocoMemoria *dadoMemoriaAdd1 = malloc(sizeof(BlocoMemoria));
            dadoMemoriaAdd1 = buscarNasMemorias(getAdd1Instrucao(umaInstrucao));
            
            BlocoMemoria *dadoMemoriaAdd2 = malloc(sizeof(BlocoMemoria));
            dadoMemoriaAdd2 = buscarNasMemorias(getAdd2Instrucao(umaInstrucao));
            
            BlocoMemoria *dadoMemoriaAdd3 = malloc(sizeof(BlocoMemoria));
            dadoMemoriaAdd3 = buscarNasMemorias(getAdd3Instrucao(umaInstrucao));

            //incremento custos
            custo += getCustoMemoria(dadoMemoriaAdd1);
            custo += getCustoMemoria(dadoMemoriaAdd2);
            custo += getCustoMemoria(dadoMemoriaAdd3);

            //Validando hits e misses
            if(getCacheHitMemoria(dadoMemoriaAdd1) == 1){
                hitC1++;
            }
            else if(getCacheHitMemoria(dadoMemoriaAdd1) == 2){
                missC1++;
				hitC2++;
            }else if(getCacheHitMemoria(dadoMemoriaAdd1) == 3){
                missC1++;
				missC2++;
                hitC3++;	
            }else if(getCacheHitMemoria(dadoMemoriaAdd1) == 4){
                missC1++;
				missC2++;
                missC3++;
                hitRAM++;
            }else if(getCacheHitMemoria(dadoMemoriaAdd1) == 5){
                missC1++;
				missC2++;
                missC3++;
                missRAM++;
            }

            if(getCacheHitMemoria(dadoMemoriaAdd2) == 1){
                hitC1++;
            }
            else if(getCacheHitMemoria(dadoMemoriaAdd2) == 2){
                missC1++;
			    hitC2++;
            }else if(getCacheHitMemoria(dadoMemoriaAdd2) == 3){
                missC1++;
				missC2++;
                hitC3++;
                hitRAM++;
            }else if(getCacheHitMemoria(dadoMemoriaAdd1) == 5){
                missC1++;
				missC2++;
                missC3++;
                missRAM++;
            }

            if(getCacheHitMemoria(dadoMemoriaAdd3) == 1){
                hitC1++;
            }
            else if(getCacheHitMemoria(dadoMemoriaAdd3) == 2){
                missC1++;
				hitC2++;
            }else if(getCacheHitMemoria(dadoMemoriaAdd3) == 3){
                missC1++;
				missC2++;
                hitC3++;	
            }else if(getCacheHitMemoria(dadoMemoriaAdd3) == 4){
                missC1++;
				missC2++;
                missC3++;
                hitRAM++;
            }else if(getCacheHitMemoria(dadoMemoriaAdd1) == 5){
                missC1++;
				missC2++;
                missC3++;
                missRAM++;
            }

            printf("Custo ate o momento do programa em execucao: %lld\n", custo);
            printf("Hits e Misses ate o momento - C1 hit | C1 miss | C2 hit | C2 miss | C3 hit | C3 miss | RAM hit | RAM miss: %lld | %lld | %lld | %lld | %lld | %lld | %lld | %lld\n", hitC1 , missC1, hitC2, missC2, hitC3, missC3, hitRAM, missRAM);
            switch (opcode)
            {   
                //Levar para cache1 dados externos
                case 0:
                    printf("Nao ha demanda por levar dados externos para as memorias\n");

                    if(strcmp(programa, nomeArqNornal) == 0){
						//interrupcao interna devido ao tipo
						//25% de chance
						chance = rand() % 4;
						if(chance == 0){
							printf("\n\nINICIO - TRATADOR DE INTERRUPCAO\n\n");

                            if(opcaoPrograma == 1){
                                montarInstrucoesProgramaAleatorio(tamanhoProgramaTI);
                            }else if(opcaoPrograma ==2){
                                montarInstrucaoGerador(nomeArqTI, tamanhoProgramaTI);
                            }
							
							maquina(0, nomeArqTI);
                            free(memoriaInstrucoesTI);
							printf("\n\nFIM - TRATADOR DE INTERRUPCAO\n\n");
						}
					}

                    break;
                
                case 1:
                    conteudo1 = getPalavrasMemoria(dadoMemoriaAdd1)[umaInstrucao->add1.endPalavra];
                    conteudo2 = getPalavrasMemoria(dadoMemoriaAdd2)[umaInstrucao->add2.endPalavra];
                    soma = conteudo1 + conteudo2;

                    getPalavrasMemoria(dadoMemoriaAdd3)[umaInstrucao->add2.endPalavra] = soma;

                    printf("Somando %d\n", soma);                    
                    break;

                case 2:
                    conteudo1 = getPalavrasMemoria(dadoMemoriaAdd1)[umaInstrucao->add1.endPalavra];
                    conteudo2 = getPalavrasMemoria(dadoMemoriaAdd2)[umaInstrucao->add2.endPalavra];
                    sub = conteudo1 - conteudo2;

                    getPalavrasMemoria(dadoMemoriaAdd3)[umaInstrucao->add2.endPalavra] = sub;

                    printf("Subtraindo %d\n", sub);
                    break;
            }
            PC++;
        }

        if (strcmp(programa, nomeArqNornal) == 0){
            //interrupcao interna devido ao tipo
            //25% de chance
            chance = rand() % 4;
            if (chance == 0){
                printf("\n\nINICIO - TRATADOR DE INTERRUPCAO\n\n");

                if (opcaoPrograma == 1){
                    montarInstrucoesProgramaAleatorio(tamanhoProgramaTI);
                }
                else if (opcaoPrograma == 2){
                    montarInstrucaoGerador(nomeArqTI, tamanhoProgramaTI);
                }

                maquina(0, nomeArqTI);
                free(memoriaInstrucoesTI);
                printf("\n\nFIM - TRATADOR DE INTERRUPCAO\n\n");
            }
        }

    }
    
    float somaHit = hitC1 + hitC2 + hitC3 + hitRAM;
    float somaMiss = missC1 + missC2 + missC3 + missRAM;
    float MissHit = somaHit + somaMiss;

    float C1 = hitC1 * 100;
    float total1 = C1/MissHit;

    float C2 = hitC2 * 100;
    float total2 = C2/MissHit;
    
    float C3 = hitC3 * 100;
    float total3 = C3/MissHit;

    float RAM0 = hitRAM * 100;
    float total4 = RAM0/MissHit;

    float RAM4 = somaMiss * 100;
    float total5 = RAM4/MissHit;

    printf("Custo total do programa: %lld\n", custo);
    printf("Hits e Misses do programa - C1 hit | C1 miss | C2 hit | C2 miss | C3 hit | C3 miss | RAM hit | RAM miss: %lld | %lld | %lld | %lld | %lld | %lld | %lld | %lld\n", hitC1 , missC1, hitC2, missC2, hitC3, missC3, hitRAM, missRAM);
    printf("\n================================================================\n\n");
    printf("CUSTO C1: %.2f\n", total1);
    printf("CUSTO C2: %.2f\n", total2);
    printf("CUSTO C3: %.2f\n", total3);
    printf("RAM: %.2f\n", total4);
    printf("Disco: %.2f\n", total5);
}

BlocoMemoria* buscarNasMemorias(Endereco* end){
    int totalConjuntoCache1 = tamanhoCache1 / 4; 
    int totalConjuntoCache2 = tamanhoCache2 / 4;
    int totalConjuntoCache3 =  tamanhoCache3 / 4;

    int conjuntoCache1 = getEndBlocoEndereco(end) % totalConjuntoCache1;
    int conjuntoCache2 = getEndBlocoEndereco(end) % totalConjuntoCache2;
    int conjuntoCache3 = getEndBlocoEndereco(end) % totalConjuntoCache3;

    int custo = 0;
    int cacheHit = 0;


    time_t momentoAdicionadoCache;
    time(&momentoAdicionadoCache);

 
    for(int i = conjuntoCache1 * 4; i < conjuntoCache1 * 4 + 4; i++){
        if(getEndBlocoCache(i, cache1) == getEndBlocoEndereco(end)){
            custo = 10;
            cacheHit = 1;

            setCustoCache(custo, i, cache1);
            setCacheHitCache(cacheHit, i, cache1);
            setSegundosCache(momentoAdicionadoCache, i, cache1);

            return &cache1[i];
        }
    }

    for(int i = conjuntoCache2 * 4; i < conjuntoCache2 * 4 + 4; i++){
        if(getEndBlocoCache(i, cache2) == getEndBlocoEndereco(end)){
            custo = 110;
            cacheHit = 2;

            setCustoCache(custo, i, cache2);
            setCacheHitCache(cacheHit, i, cache2);
            setSegundosCache(momentoAdicionadoCache, i, cache2);

            return &cache2[i];
        }
    }

    for(int i = conjuntoCache3 * 4; i < conjuntoCache3 * 4 + 4; i++){
        if(getEndBlocoCache(i, cache3) == getEndBlocoEndereco(end)){
            custo = 1110;
            cacheHit = 3;

            setCustoCache(custo, i, cache3);
            setCacheHitCache(cacheHit, i, cache3);
            setSegundosCache(momentoAdicionadoCache, i, cache3);

            return &cache3[i];
        }
    }
    
    for(int i = 0; i < tamanhoRAM; i++){
        if(getEndBlocoCache(i, RAM) == getEndBlocoEndereco(end)){
            custo = 5550;
            cacheHit = 4;

            setCustoCache(custo, i, RAM);
            setCacheHitCache(cacheHit, i, RAM);
            setSegundosCache(momentoAdicionadoCache, i, RAM);

            return &RAM[i];
        }
    }

    custo = 11100;
    cacheHit = 5;

    BlocoMemoria *infoDisco = endPalavraDisco(getEndBlocoEndereco(end));
    setCustoMemoria(infoDisco, custo);
    setCacheHitMemoria(infoDisco, cacheHit);
    setSegundosMemoria(infoDisco, momentoAdicionadoCache);

    int posicaoRAM = algoritmoSubstituicaoLRU(0, tamanhoRAM);
    guardarInformacao(posicaoRAM, tamanhoRAM, 0, 0, end);

    RAM[posicaoRAM] = *infoDisco;

    int posicaoCache3 = algoritmoSubstituicaoLRU(conjuntoCache3, tamanhoCache3);
    guardarInformacao(posicaoCache3, tamanhoCache3, conjuntoCache2, conjuntoCache3, end);
                
    cache3[posicaoCache3] = RAM[posicaoRAM];
    invalidarPosicacoCache(posicaoRAM, posicaoRAM, tamanhoRAM);

    int posicaoCache2 = algoritmoSubstituicaoLRU(conjuntoCache2, tamanhoCache2);
    guardarInformacao(posicaoCache2, tamanhoCache2, conjuntoCache2, conjuntoCache3, end);

    cache2[posicaoCache2] = cache3[posicaoCache3];
    invalidarPosicacoCache(posicaoCache2, posicaoCache3, tamanhoCache3);

    int posicaoCache1 = algoritmoSubstituicaoLRU(conjuntoCache1, tamanhoCache1);
    guardarInformacao(posicaoCache1, tamanhoCache1, conjuntoCache2, conjuntoCache3, end);

    cache1[posicaoCache1] = cache2[posicaoCache2];
    invalidarPosicacoCache(posicaoCache1, posicaoCache2, tamanhoCache3);

    free(infoDisco);
    return &cache1[posicaoCache1];
}

BlocoMemoria* endPalavraDisco(int endBloco){
    char *nomeArqDisco = nomearDiretorioArquivos(endBloco);

    FILE *arquivoDisco = fopen(nomeArqDisco, "r");
    BlocoMemoria *infoDisco = malloc(sizeof(BlocoMemoria));

    int *palavrasAux = malloc(qdePalavrasBloco * sizeof(int));
    fscanf(arquivoDisco, "%d %d %d %d\n", &palavrasAux[0], &palavrasAux[1], &palavrasAux[2], &palavrasAux[3]);

    infoDisco->endBloco = endBloco;
    infoDisco->palavras = palavrasAux;

    fclose(arquivoDisco);
    free(nomeArqDisco);

    return infoDisco;
}

void guardarInformacao(int posicaoCache, int tamanhoCache, int conjuntoCache2, int conjuntoCache3,  Endereco *endAux){
    if(tamanhoCache == tamanhoCache1){
        int posicaoCache2 = algoritmoSubstituicaoLRU(conjuntoCache2, tamanhoCache2);
        int posicaoCache3 = algoritmoSubstituicaoLRU(conjuntoCache3, tamanhoCache3);
        int posicaoRAM = algoritmoSubstituicaoLRU(0, tamanhoRAM);
        
        if(getEndBlocoCache(posicaoCache, cache1) == getEndBlocoEndereco(endAux)){
            guardarInformacaoDisco(getEndBlocoCache(posicaoRAM, RAM), getPalavrasCache(posicaoRAM, RAM));
            RAM[getEndBlocoCache(posicaoRAM, RAM)] = cache3[posicaoCache3];
            cache3[posicaoCache3] = cache2[posicaoCache2];
            cache2[posicaoCache2] = cache1[posicaoCache];
        }
    }else if(tamanhoCache == tamanhoCache2){
        int posicaoCache3 = algoritmoSubstituicaoLRU(conjuntoCache3, tamanhoCache3);
        int posicaoRAM = algoritmoSubstituicaoLRU(0, tamanhoRAM);

        if(getEndBlocoCache(posicaoCache, cache2) == getEndBlocoEndereco(endAux)){
            guardarInformacaoDisco(getEndBlocoCache(posicaoRAM, RAM), getPalavrasCache(posicaoRAM, RAM));
            RAM[getEndBlocoCache(posicaoRAM, RAM)] = cache3[posicaoCache3];
            cache3[posicaoCache3] = cache2[posicaoCache];
        }
    }else if(tamanhoCache == tamanhoCache3){
        int posicaoRAM = algoritmoSubstituicaoLRU(0, tamanhoRAM);
        
        if(getEndBlocoCache(tamanhoCache, cache3) == getEndBlocoEndereco(endAux)){
            guardarInformacaoDisco(getEndBlocoCache(posicaoRAM, RAM), getPalavrasCache(posicaoRAM, RAM));
            RAM[getEndBlocoCache(posicaoRAM, RAM)] = cache3[posicaoCache];
        }
    }else if(tamanhoCache == tamanhoRAM){
        if(getEndBlocoCache(posicaoCache, RAM) == getEndBlocoEndereco(endAux)){
            guardarInformacaoDisco(getEndBlocoCache(posicaoCache, RAM), getPalavrasCache(posicaoCache, RAM));
        }
    }
}

void guardarInformacaoDisco(int endBlocoRAM, int *endPalavraRAM){
    char *nomeArqDisco =  nomearDiretorioArquivos(endBlocoRAM);
    FILE *arquivoDisco = fopen(nomeArqDisco, "w");

    BlocoMemoria infoDisco;

    infoDisco.palavras = endPalavraRAM;
        
    fprintf(arquivoDisco, "%d %d %d %d\n", infoDisco.palavras[0], infoDisco.palavras[1],  infoDisco.palavras[2],  infoDisco.palavras[3]);
    printf("\n\n**********************---------------------------- %d %d %d %d ----------------------------**********************\n\n", infoDisco.palavras[0], infoDisco.palavras[1],  infoDisco.palavras[2],  infoDisco.palavras[3]);

    fclose(arquivoDisco);
    free(nomeArqDisco);
}

void invalidarPosicacoCache(int posicaoCacheX, int posicaoCacheY, int tamanhoCache){
    time_t tempoMaisVelho;
    time(&tempoMaisVelho);
    tempoMaisVelho = tempoMaisVelho - 2100;

    if(tamanhoCache == tamanhoCache1){
        if(getEndBlocoCache(posicaoCacheX, cache1) == getEndBlocoCache(posicaoCacheY, cache2)){
            setSegundosCache(tempoMaisVelho, posicaoCacheY, cache2);
        }    
    }else if(tamanhoCache == tamanhoCache2){
        if(getEndBlocoCache(posicaoCacheX, cache2) == getEndBlocoCache(posicaoCacheY, cache3)){
            setSegundosCache(tempoMaisVelho, posicaoCacheY, cache3);
        }    
    }else if(tamanhoCache == tamanhoRAM){
        if(getEndBlocoCache(posicaoCacheX, cache3) == getEndBlocoCache(posicaoCacheY, RAM)){
            setSegundosCache(tempoMaisVelho, posicaoCacheY, RAM);
        }    
    }
}

int algoritmoSubstituicaoLRU(int conjuntoCache, int tamanhoCache){
    time_t posicaoMaisVelha;
    time(&posicaoMaisVelha);

    int posicaoCacheAux = 0;
    int contadorCache1 = 0;
    int contadorCache2 = 0;
    int contadorCache3 = 0;

    if(tamanhoCache == tamanhoCache1){
        for(int i = conjuntoCache * 4; i < conjuntoCache * 4 + 4; i++){
            if(cache1[i].segundos <= posicaoMaisVelha){
                posicaoMaisVelha = cache1[i].segundos;
                posicaoCacheAux = conjuntoCache * 4 + contadorCache1;
            }
            contadorCache1++;
        }
    }else if(tamanhoCache == tamanhoCache2){
        for(int i = conjuntoCache * 4; i < conjuntoCache * 4 + 4; i++){
            if(cache2[i].segundos <= posicaoMaisVelha){
                posicaoMaisVelha = cache2[i].segundos;
                posicaoCacheAux = conjuntoCache * 4 + contadorCache2;
            }
            contadorCache2++;
        }
    }else if(tamanhoCache == tamanhoCache3){
        for(int i = conjuntoCache * 4; i < conjuntoCache * 4 + 4; i++){
            if(cache3[i].segundos <= posicaoMaisVelha){
                posicaoMaisVelha = cache3[i].segundos;
                posicaoCacheAux = conjuntoCache * 4 + contadorCache3;
            }
            contadorCache3++;
        }
    }else if(tamanhoCache == tamanhoRAM){
        for(int i = 0; i <= tamanhoRAM; i++){
            if(RAM[i].segundos <= posicaoMaisVelha){
                posicaoMaisVelha = RAM[i].segundos;
                posicaoCacheAux = i;
            }
        }
    }

    return posicaoCacheAux;
}

//BlocoMemoria
void setCustoMemoria(BlocoMemoria *aux, int custoAux)
{
    aux->custo = custoAux;
}

void setEndBlocoMemoria(BlocoMemoria *aux, int endBlocoAux)
{
    aux->endBloco = endBlocoAux;
}

void setPalavrasMemoria(BlocoMemoria *aux, int* palavrasAux)
{
    aux->palavras = palavrasAux;
}

void setCacheHitMemoria(BlocoMemoria *aux, int cacheHitAux)
{
    aux->cacheHit = cacheHitAux;
}

void setSegundosMemoria(BlocoMemoria *aux, int segundosAux)
{
    aux->segundos = segundosAux;
}

int getCustoMemoria(BlocoMemoria *aux)
{
    return aux->custo;
}

int getCacheHitMemoria(BlocoMemoria *aux)
{
    return aux->cacheHit;
}

int* getPalavrasMemoria(BlocoMemoria *aux)
{
    return aux->palavras;
}

int getEndBlocoMemoria(BlocoMemoria *aux)
{
    return aux->endBloco;
}

//Instrucao
void setOpcodeInstrucao(Instrucao *umaInstrucao, int opcodeAux)
{
    umaInstrucao->opcode = opcodeAux;
}

void setAdd1Instrucao(Instrucao *umaInstrucao, Endereco *add1Aux)
{
    umaInstrucao->add1 = *add1Aux;
}

void setAdd2Instrucao(Instrucao *umaInstrucao, Endereco *add2Aux)
{
    umaInstrucao->add2 = *add2Aux;
}

void setAdd3Instrucao(Instrucao *umaInstrucao, Endereco *add3Aux)
{
    umaInstrucao->add3 = *add3Aux;
}

Endereco* getAdd1Instrucao(Instrucao *umaInstrucao)
{
    return &umaInstrucao->add1;
}

Endereco* getAdd2Instrucao(Instrucao *umaInstrucao)
{
    return &umaInstrucao->add2;
}

Endereco* getAdd3Instrucao(Instrucao *umaInstrucao)
{
    return &umaInstrucao->add3;
}

int getOpcodeInstrucao(Instrucao *umaInstrucao){
    return umaInstrucao->opcode;
}

//Endereco
void setEndBlocoEndereco(Endereco *end, int endBlocoAux)
{
    end->endBloco = endBlocoAux;
}

void setEndPalavraEndereco(Endereco *end, int endPalavraAux)
{
    end->endPalavra = endPalavraAux;
}

int getEndBlocoEndereco(Endereco *end)
{
    return end->endBloco;
}

int getEndPalavraEndereco(Endereco *end)
{
    return end->endPalavra;
}

//Cache --- MMU
void setEndBlocoCache(int endBlocoAux, int posicao, BlocoMemoria *qqCache){
    qqCache[posicao].endBloco = endBlocoAux;
}

void setCustoCache(int custoAux, int posicao, BlocoMemoria *qqCache)
{
    qqCache[posicao].custo = custoAux;
}

void setSegundosCache(int segundoAux, int posicao, BlocoMemoria *qqCache)
{
    qqCache[posicao].segundos = segundoAux;
}

void setCacheHitCache(int cacheHitAux, int posicao, BlocoMemoria *qqCache)
{
    qqCache[posicao].cacheHit = cacheHitAux;
}

int getEndBlocoCache(int posicao, BlocoMemoria *qqCache){
    return qqCache[posicao].endBloco;
}

int* getPalavrasCache(int posicao, BlocoMemoria *qqCache){
    return qqCache[posicao].palavras;
}

time_t getSegundosCache(int posicao, BlocoMemoria *qqCache){
    return qqCache[posicao].segundos;
}

