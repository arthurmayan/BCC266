#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int *RAM;
int **memoriaInstrucoes;

int PI = 3; 

void alocarRAM();
void alocaMemoriaInstrucoes(int linha, int coluna);
void desaloca(int nlinhas);

void montarLevarRAM(int variavel, int indiceRAM);
int montarTrazerRAM(int indiceRAM);

void maquina();
void maquinaTraduzida();
void maquinaInterpretada();

void montarInstrucoesProgramaAleatorio();

int adicao(int n1, int n2);
int subtracao(int n1, int n2);
void montarInstrucoesProgramaMultiplicacao(int multiplicando, int multiplicador);
void montarInstrucoesProgramaDivisao(int dividendo, int divisor);

int montarPotenciacao(int base, int expoente);
int montarQuadrado(int elevarQuad, int quadrado);
int montarCubo(int elevarCubo,int cubo);
int raiz_quadrada (int numero);
int montarAreaTriangulo(int base, int altura);
int montarProgramaAreaCircuferencia(int raio);
int montarProgramaComprimentoCircuferecia(int raio);

int areaQuadrado(int lado);
int areaRetangulo(int B, int h);
int areaParalelogramo(int B, int h);
int areaLosango(int D, int d);
int formulaHeron(int a, int b, int c);
int areaCoroaCircular(int R, int r);
int fatorial(int nroFatorial);
int areaTrapezio(int h, int B, int b);
int areaCubo(int a);
int volumeCubo(int a);
int areaParalelepipedo(int a, int b, int c);
int volumeParalelepipedo(int a, int b, int c);

int montarTermoGeralPA(int a1PA, int razaoPA, int termoEncontrar);
int montarTermoGeralPG(int a1PG, int razaoPG, int termoEncontrarPG);

int montarSomaTermosPA(int a1PA, int razaoPA, int termoEncontrarPA);
int montarSomaTermoPG(int a1, int razao, int termoEncontrar);


int main()
{
	int opcao = INT_MAX, resultado;
	int multiplicador = 7, multiplicando = 5;
	int nlinhas = 10, ncolunas = 4;
	int dividendo = 12, divisor = 3;
	int base = 3, expoente = 2;
	int elevarQuad = 5, quadrado = 2;
	int elevarCubo = 5, cubo = 3;
	int n1 = 20, n2 = 5;
	int a1 = 1, razao = 3; 
	int numero = 625;
	int termoEncontrarPA = 10, razaoPA = 3, a1PA = 1;
	int termoEncontrarPG = 20, razaoPG = 2, a1PG = 2;
	int a1x = 7, razaox = 2, termoEncontrarx = 10;
	int raio = 30, basex = 6, altura = 2;
	int lado = 17;
	int B = 40, h = 4;
	int D = 10, d = 7;
	int a = 9, b = 7, c = 14;
	int R = 10, r = 8;
	int nroFatorial = 5;
	int hTrap = 3, BTrap = 8, bTrap = 5;
	int aCubo = 7;
	int aParal = 60, bParal = 25, cParal = 30;

	alocarRAM();
	
	while (opcao != 0)
	{
		menu(); scanf("%d", &opcao); printf("\n===============================================\n");

		switch (opcao)
		{
			case 1:
				printf("\n");
				alocaMemoriaInstrucoes(nlinhas, ncolunas);
				montarInstrucoesProgramaAleatorio();
				maquina();
				break;
			case 2:
				printf("\n A soma de %d + %d ?? igual a %d.\n", n1, n2, adicao(n1, n2));
				break;
			case 3:
				printf("\n %d menos %d ?? igual a %d.\n", n1, n2, subtracao(n1, n2));
				break;
			case 4:
				nlinhas = multiplicador + 3;
				montarInstrucoesProgramaMultiplicacao(multiplicador, multiplicando);
				printf("\n %d multiplicado por %d ?? igual a %d.\n", multiplicador, multiplicando, RAM[1]);
				break;
			case 5:
				nlinhas = 5;
				montarInstrucoesProgramaDivisao(dividendo, divisor);
				printf("\n O n??mero %d divido por %d ?? igual a %d.\n",dividendo, divisor, RAM[3]);
				break;
			case 6:
				printf("\n %d elevado a %d ?? igual a %d.\n", base, expoente, montarPotenciacao(base, expoente));
				break;
			case 7:
				printf("\n %d elevado ao quadrado ?? igual a %d.\n", elevarQuad, montarQuadrado(elevarQuad, quadrado));
				break;
			case 8:
				resultado = montarCubo(elevarCubo, cubo);
				nlinhas = resultado + 3;
				printf("\n %d elevado ao cubo ?? igual a %d.\n",elevarCubo, resultado);
				break;
			case 9:
				printf("\n A raiz de %d ?? igual a %d.\n",numero, raiz_quadrada(numero));
				break;
			case 10:
				printf("\nResultado da Progress??o Aritm??tica considerando:\nA1 = %d\nRaz??o = %d\nTermo = %d\n?? igual a %d.\n",a1, razao, termoEncontrarPA, montarTermoGeralPA(a1, razao, termoEncontrarPA));
				break;
			case 11:
				printf("\nResultado da Progress??o Geom??trica considerando:\nA1 = %d\nRaz??o = %d\nTermo = %d\n?? igual a %d.\n",a1, razao, termoEncontrarPA,  montarTermoGeralPA(a1, razao, termoEncontrarPA));
				break;
			case 12:
				printf("\nResultado da Soma de Termos da Progress??o Aritm??tica considerando:\nA1 = %d\nRaz??o = %d\nTermo = %d\n?? igual a %d.\n",a1PA, razaoPA, termoEncontrarPA, montarSomaTermosPA(a1PA, razaoPA, termoEncontrarPA));
				break;
			case 13:
				printf("\nResultado da Soma de Termos da Progress??o Geom??trica considerando:\nA1 = %d\nRaz??o = %d\nTermo = %d\n?? igual a %d.\n",a1x, razaox, termoEncontrarx, montarSomaTermoPG(a1x, razaox, termoEncontrarx));
				break;
			case 14:
				printf("\n A ??rea da circufer??cia de raio de %d ?? igual a %d.\n", raio, montarProgramaAreaCircuferencia(raio));
				break;
			case 15:
				printf("\n O comprimento da circufer??ncia com raio de %d ?? igual a %d.\n", raio, montarProgramaComprimentoCircuferecia(raio));
				break;
			case 16:
				printf("\n A ??rea do triangulo com base %d e altura %d ?? igual a %d.\n",basex, altura, montarAreaTriangulo(basex, altura));
				break;
			case 17:
				printf("\n A ??rea de um quadrado com %d cm de lado ?? igual a %d cm??.\n", lado, areaQuadrado(lado));
				break;
			case 18:
				printf("\n O ret??ngulo com base %d e altura %d tem a area de %d cm??.\n",B, h, areaRetangulo(B, h));
				break;
			case 19:
				printf("\n O paralelogramo com base %d e altura %d tem a area de %d cm??.\n",B, h, areaParalelogramo(B, h));
				break;
			case 20:
				printf("\n A ??rea de um losango que possui diagonal maior medindo %d e diagonal menor medindo %d ?? igual a %d cm??.\n", D, d, areaLosango(D,d));
				break;
			case 21:
				printf("\n Resultado Formula de Heron: %d.\n", formulaHeron(a, b, c));
				break;
			case 22:
				printf("\n Resultado da ??rea da Coroa Circular: %d?? m??.\n", areaCoroaCircular(R, r));
				break;
			case 23:
				printf("\n Fatorial de %d = %d.\n", nroFatorial, fatorial(nroFatorial));
				break;
			case 24:
				printf("\n ??rea do Trap??zio: %d cm??.\n", areaTrapezio(hTrap, BTrap, bTrap));
				break;
			case 25:
			 	printf("\n A ??rea do cubo ?? igual a %d mm??.\n", areaCubo(aCubo));
				break;
			case 26:
				printf("\n O volume do cubo ?? igual a %d cm??.\n", volumeCubo(aCubo));
				break;
			case 27:
				printf("\n A ??rea do paralelepido ?? igual a %d cm??.\n", areaParalelepipedo(aParal, bParal, cParal));
				break;
			case 28:
				printf("\n O volume do paralelepido ?? igual a %d cm??.\n", volumeParalelepipedo(aParal, bParal, cParal));
				break;
		}

	}

	if (opcao != 0)
	{
		desaloca(nlinhas);
	}

	free(RAM);

	return 0;
}

void menu()
{
	printf("\n===================== MENU ====================\n\n");
	printf("0) Sair\n");
	printf("1) Programa Aleatorio \n");
	printf("2) Programa Soma \n");
	printf("3) Programa Subtra????o \n");
	printf("4) Programa Multiplica????o \n");
	printf("5) Programa Divis??o \n");
	printf("6) Programa Potencia????o \n");
	printf("7) Programa Elevar Quadrado \n");
	printf("8) Programa Elevar Cubo \n");
	printf("9) Programa Raiz \n");
	printf("10) Programa Progress??o Aritm??tica \n");
	printf("11) Programa Progress??o Geom??trica \n");
	printf("12) Programa Soma Termos Progress??o Aritm??tica \n");
	printf("13) Programa Soma Termos Progress??o Geom??trica \n");
	printf("14) Programa Comprimento Circunfer??ncia \n");
	printf("15) Programa ??rea Circunfer??ncia \n");
	printf("16) Programa ??rea Tri??ngulo \n");
	printf("17) Programa ??rea Quadrado \n");
	printf("18) Programa ??rea Ret??ngulo \n");
	printf("19) Programa ??rea Paralelogramo \n");
	printf("20) Programa ??rea Losango \n");
	printf("21) Programa da Formula de Heron \n");
	printf("22) Programa da ??rea da Coroa Circular \n");
	printf("23) Programa Fatorial \n");
	printf("24) Programa ??rea Trap??zio \n");
	printf("25) Programa ??rea do Cubo\n");
	printf("26) Programa Volume do Cubo\n");
	printf("27) Programa ??rea do paralelep??pedo\n");
	printf("28) Programa Volume do paralelep??pedo\n");

	printf("\nDigite o n??mero desejado: ");
}



void alocarRAM()
{
	RAM = malloc(100 * sizeof(int));

	srand(time(NULL));

	int recebeAleatorio;

	for (int i = 0; i < 100; i++)
	{
		recebeAleatorio = rand() % 1000;
		RAM[i] = recebeAleatorio;

		// printf("%d ", RAM[i]);
	}

	printf("\n");
}

void alocaMemoriaInstrucoes(int linha, int coluna)
{

	memoriaInstrucoes = malloc(linha * sizeof(int *));

	for (int i = 0; i < linha; i++)
	{
		(memoriaInstrucoes)[i] = malloc(coluna * sizeof(int));
	}

	/* for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            memoriaInstrucoes[i][j] = 0;

            printf("%d ", memoriaInstrucoes[i][j]);
        }
        printf("\n");
    } */
}

void desaloca(int nlinhas)
{
	for (int i = 0; i < nlinhas; i++)
		free(memoriaInstrucoes[i]);

	free(memoriaInstrucoes);
}

void montarLevarRAM(int variavel, int indiceRAM){
	int* umaInstrucao = NULL;
	int nInstrucao = 4;
	int resultado;

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = variavel;
	umaInstrucao[2] = indiceRAM;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);
}

int montarTrazerRAM(int indiceRAM){
	int* umaInstrucao = NULL;
	int nInstrucao = 4;
	int resultado;

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 3;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = indiceRAM;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);

	resultado = RAM[umaInstrucao[2]];

	free(umaInstrucao);

	return resultado;
}


void maquina()
{
	//registradores
	int PC = 0;
	int opcode = INT_MAX;
	while (opcode != -1)
	{
		int *umaInstrucao = memoriaInstrucoes[PC];
		opcode = umaInstrucao[0];
		switch (opcode)
		{
		//levar para RAM
		case 0:
		{
			RAM[umaInstrucao[2]] = umaInstrucao[1];
			printf("LEVANDO PARA RAM: %d\n", umaInstrucao[1]);

			break;
		}
		case 1:
		{
			//somar
			int end1 = umaInstrucao[1];
			int end2 = umaInstrucao[2];
			//buscar na RAM
			int conteudoRam1 = RAM[end1];
			int conteudoRam2 = RAM[end2];
			int soma = conteudoRam1 + conteudoRam2;
			//salvando resultado na RAM
			RAM[umaInstrucao[3]] = soma;

			printf("somando %d\n", soma);
			break;
		}
		case 2:
		{
			//subtrair
			int end1 = umaInstrucao[1];
			int end2 = umaInstrucao[2];
			//buscar na RAM
			int conteudoRam1 = RAM[end1];
			int conteudoRam2 = RAM[end2];
			int sub = conteudoRam1 - conteudoRam2;
			//salvando resultado na RAM
			RAM[umaInstrucao[3]] = sub;

			printf("subtraindo %d\n", sub);

			break;
		}
		}

		PC++;
	}
}

void maquinaInterpretada(int *umaInstrucao)
{
	int end1, end2, end3, conteudoRAM1, conteudoRAM2, soma, sub;

	int opcode = umaInstrucao[0];
	switch (opcode)
	{
		//Levar para RAM
	case 0:
	{
		RAM[umaInstrucao[2]] = umaInstrucao[1];
		break;
	}
	case 1:
	{
		//Somar
		end1 = umaInstrucao[1];
		end2 = umaInstrucao[2];
		//Buscar na RAM
		conteudoRAM1 = RAM[end1];
		conteudoRAM2 = RAM[end2];
		soma = conteudoRAM1 + conteudoRAM2;
		//Salvando resultado na RAM
		end3 = umaInstrucao[3];
		RAM[end3] = soma;

		break;
	}
	case 2:
	{
		//Subtrair
		end1 = umaInstrucao[1];
		end2 = umaInstrucao[2];
		//Buscar na RAM
		conteudoRAM1 = RAM[end1];

		conteudoRAM2 = RAM[end2];
		sub = conteudoRAM1 - conteudoRAM2;
		//Salvando resultado na RAM
		end3 = umaInstrucao[3];
		//printf("---%d---\n", end3);
		RAM[end3] = sub;

		break;
	}
	// trazer da ram
	case 3:
	{
		umaInstrucao[1] = RAM[umaInstrucao[2]];
		break;
	}
	}
}

void maquinaTraduzida()
{
	//registradores
	int PC = 0;
	int opcode = INT_MAX; //maior inteiro poss??vel 2^31 -1 =~ 2bi
	while (opcode != -1)
	{
		int *umaInstrucao = memoriaInstrucoes[PC];
		opcode = memoriaInstrucoes[PC][0];
		maquinaInterpretada(umaInstrucao);
		PC++;
	}
}



int adicao(int n1, int n2) 
{
	int* umaInstrucao = NULL;
	int nInstrucao = 4;
	int resultado;

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = n1;
	umaInstrucao[2] = 0;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = n2;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 1; 
	umaInstrucao[1] = 0;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = 3;
	maquinaInterpretada(umaInstrucao);
	
	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 3;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = 3;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);
	
	resultado = umaInstrucao[1];

	free(umaInstrucao);

	return resultado;
}

int subtracao(int n1, int n2)
{
	int* umaInstrucao = NULL;
	int nInstrucao = 4;
	int resultado;

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = n1;
	umaInstrucao[2] = 0;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = n2;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);

	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 2; 
	umaInstrucao[1] = 0;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = 3;
	maquinaInterpretada(umaInstrucao);
	
	umaInstrucao = malloc(nInstrucao * sizeof(int));
	umaInstrucao[0] = 3;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = 3;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);
	
	resultado = umaInstrucao[1];

	free(umaInstrucao);

	return resultado;
}

void montarInstrucoesProgramaMultiplicacao(int multiplicando, int multiplicador)
{
	alocaMemoriaInstrucoes(multiplicador + 3, 4);

	int *umaInstrucao = NULL;
	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = multiplicando;
	umaInstrucao[2] = 0;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[0] = umaInstrucao;

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = 0;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[1] = umaInstrucao;

	for (int i = 0; i < multiplicador; i++)
	{
		umaInstrucao = malloc(4 * sizeof(int));
		umaInstrucao[0] = 1;
		umaInstrucao[1] = 0;
		umaInstrucao[2] = 1;
		umaInstrucao[3] = 1;
		memoriaInstrucoes[i + 2] = umaInstrucao;
	}

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = -1;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = -1;
	umaInstrucao[3] = -1;

	memoriaInstrucoes[multiplicador + 2] = umaInstrucao;

	maquinaTraduzida();
}

void montarInstrucoesProgramaDivisao(int dividendo, int divisor)
{
	//0 => salvar na mem??ria
	//3 => trazer da mem??ria
	//1 => opcode => somar
	//2 => opcode => subtrair
	//-1 => halt

	// 12 / 3 = (12-3); (9-3); (6-3); (3-3); (0-3) => 4
	// 15 / 4 = (15-4); (11-4); (7-4); (3-4) => 3

	//monto um programa apenas para levar os dados para RAM

	alocaMemoriaInstrucoes(5, 4);

	int *umaInstrucao = NULL;
	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = divisor;
	umaInstrucao[2] = 0;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[0] = umaInstrucao; 

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = dividendo;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[1] = umaInstrucao;

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = 1;
	umaInstrucao[2] = 2;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[2] = umaInstrucao;

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 0;
	umaInstrucao[1] = 0;
	umaInstrucao[2] = 3;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[3] = umaInstrucao;

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = -1;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = -1;
	umaInstrucao[3] = -1;
	memoriaInstrucoes[4] = umaInstrucao;

	maquinaTraduzida();

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 3;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = 0;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);
	int ram0 = montarTrazerRAM(0);

	umaInstrucao = malloc(4 * sizeof(int));
	umaInstrucao[0] = 3;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = 1;
	umaInstrucao[3] = -1;
	maquinaInterpretada(umaInstrucao);
	int ram1 = montarTrazerRAM(0);

	while (ram1 >= ram0)
	{
		//subtrair
		umaInstrucao = malloc(4 * sizeof(int));
		umaInstrucao[0] = 2;
		umaInstrucao[1] = 1;
		umaInstrucao[2] = 0;
		umaInstrucao[3] = 1;
		maquinaInterpretada(umaInstrucao);

		//somar
		umaInstrucao = malloc(4 * sizeof(int));
		umaInstrucao[0] = 1;
		umaInstrucao[1] = 2;
		umaInstrucao[2] = 3;
		umaInstrucao[3] = 3;
		maquinaInterpretada(umaInstrucao);

		//trazer da RAM[0]
		umaInstrucao = malloc(4 * sizeof(int));
		umaInstrucao[0] = 3;
		umaInstrucao[1] = -1;
		umaInstrucao[2] = 0;
		umaInstrucao[3] = -1;
		maquinaInterpretada(umaInstrucao);
		ram0 = umaInstrucao[1];

		//trazer da RAM[1]
		umaInstrucao = malloc(4 * sizeof(int));
		umaInstrucao[0] = 3;
		umaInstrucao[1] = -1;
		umaInstrucao[2] = 1;
		umaInstrucao[3] = -1;
		maquinaInterpretada(umaInstrucao);
		ram1 = umaInstrucao[1];
	}
}



void montarInstrucoesProgramaAleatorio()
{
	//01|22|13|45 => isto ?? uma instru????o
	//02|33|12|01 => isto ?? outra instru????o

	//0 => opcode => salvar na mem??ria
	//1 => opcode => somar
	//2 => opcode => subtrair
	//-1 => opcode => halt

	//22 => significa um endere??o da RAM (10 endere??o)
	//13 => significa 2o endere??o
	//45 => significa 3o endereco
	//101 => EST?? FORA DO INTERVALO DE 0 A 99 DA MEM??RIA RAM
	int *umaInstrucao = NULL;

	srand(time(NULL));
	int recebeAleatorio;

	for (int i = 0; i < 9; i++)
	{
		umaInstrucao = malloc(4 * sizeof(int));

		recebeAleatorio = rand() % 3;
		umaInstrucao[0] = recebeAleatorio;

		recebeAleatorio = rand() % 100;
		umaInstrucao[1] = recebeAleatorio;

		recebeAleatorio = rand() % 100;
		umaInstrucao[2] = recebeAleatorio;

		recebeAleatorio = rand() % 100;
		umaInstrucao[3] = recebeAleatorio;

		memoriaInstrucoes[i] = umaInstrucao;
	}

	// Para sair da maquina
	umaInstrucao[0] = -1;
	umaInstrucao[1] = -1;
	umaInstrucao[2] = -1;
	umaInstrucao[3] = -1;

	memoriaInstrucoes[9] = umaInstrucao;
}



int montarPotenciacao(int base, int expoente)
{
	int resultado;
	montarLevarRAM(base, 0);
	resultado = montarTrazerRAM(0);

	int total;
	montarLevarRAM(0, 0);
	total = montarTrazerRAM(0);

	for ( int i = 0; i < expoente-1; i++)
	{        
		montarInstrucoesProgramaMultiplicacao(resultado, base);
		montarLevarRAM(RAM[1],0);
		resultado = montarTrazerRAM(0);
	}    
	return resultado;
}

int montarQuadrado(int elevarQuad, int quadrado)
{
	int resultado;
	montarLevarRAM(0, 0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(elevarQuad, elevarQuad);
	montarLevarRAM(RAM[1],0);
	resultado = montarTrazerRAM(0);

	return resultado;
}

int montarCubo(int elevarCubo, int cubo)
{
	int soma;
	montarLevarRAM(0, 0);
	soma = montarTrazerRAM(0);

	int resultado;
	montarLevarRAM(0, 0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(elevarCubo, elevarCubo);
	montarLevarRAM(RAM[1],0);
	soma = montarTrazerRAM(0);

	montarLevarRAM(adicao(soma, resultado), 0);
	resultado = montarTrazerRAM(0);

	desaloca(elevarCubo + 3);

	montarInstrucoesProgramaMultiplicacao(resultado, elevarCubo);
	montarLevarRAM(RAM[1],0);
	resultado = montarTrazerRAM(0);

	return resultado;
}

int raiz_quadrada (int numero)
{
	int recorre;
	montarLevarRAM(numero, 0);
	recorre = montarTrazerRAM(0);
	
	int resultadoM;
	montarLevarRAM(0, 0);
	resultadoM = montarTrazerRAM(0);

	int resultadoD;
	montarLevarRAM(0, 0);
	resultadoD = montarTrazerRAM(0);

	int resultadoD1;
	montarLevarRAM(0, 0);
	resultadoD1 = montarTrazerRAM(0);

    for(int i = 0; i <= 10; i++)
	{
		montarInstrucoesProgramaMultiplicacao(2, recorre);
		montarLevarRAM(RAM[1],0);
		resultadoM = montarTrazerRAM(0);

		montarInstrucoesProgramaDivisao(numero, resultadoM);
		montarLevarRAM(RAM[3],0);
		resultadoD1 = montarTrazerRAM(0);

		montarInstrucoesProgramaDivisao(recorre, 2);
		montarLevarRAM(RAM[3],0);
		resultadoD = montarTrazerRAM(0);

		montarLevarRAM(adicao(resultadoD, resultadoD1), 0);
		recorre = montarTrazerRAM(0);
    }
    return recorre;    
}

int montarAreaTriangulo(int base, int altura)
{
	//A = base * altura / 2
	int resultado;
	montarLevarRAM(0,0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(base, altura);
	montarLevarRAM(RAM[1],0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaDivisao(resultado , 2);
	montarLevarRAM(RAM[3],0);
	return montarTrazerRAM(0);
}

int montarProgramaAreaCircuferencia(int raio)
{
	//A = PI * r ^ 2
	int resultadoQuadrado;
	montarLevarRAM(montarQuadrado(raio , 2), 0);
	resultadoQuadrado = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(resultadoQuadrado, PI);
	montarLevarRAM(RAM[1],0);
	return montarTrazerRAM(0);
}

int montarProgramaComprimentoCircuferecia(int raio)
{
	//C = 2 * PI * r
	int resultado;
	montarLevarRAM(0,0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(2, PI);
	montarLevarRAM(RAM[1],0);
	resultado = montarTrazerRAM(0);

	desaloca(2);

	montarInstrucoesProgramaMultiplicacao(resultado, raio);
	montarLevarRAM(RAM[1],0);
	return montarTrazerRAM(0);
}


int areaQuadrado(int lado)
{
	montarInstrucoesProgramaMultiplicacao(lado, lado);
	montarLevarRAM(RAM[1],0);
	return montarTrazerRAM(0);
}

int areaRetangulo(int B, int h)
{
	montarInstrucoesProgramaMultiplicacao(B, h);
	montarLevarRAM(RAM[1],0);
	return montarTrazerRAM(0);
}

int areaParalelogramo(int B, int h)
{
	montarInstrucoesProgramaMultiplicacao(B, h);
	montarLevarRAM(RAM[1],0);
	return montarTrazerRAM(0);
}

int areaLosango(int D, int d)
{
	int mult;
	montarInstrucoesProgramaMultiplicacao(D, d);
	montarLevarRAM(RAM[1] ,0);
	mult = montarTrazerRAM(0);

	montarInstrucoesProgramaDivisao(mult, 2);
	montarLevarRAM(RAM[3] ,0);
	return montarTrazerRAM(0);
}

int formulaHeron(int a, int b, int c)
{
	// Heron calcula a ??rea de um tri??ngulo em fun????o das medidas dos seus tr??s lados.
	// A f??rmula de Heron de Alexandria ?? muito ??til quando n??o sabemos a altura do tri??ngulo.

	// ??? p * ( p - a ) * ( p - b ) * ( p - c ) 

	// p = ( a + b + c ) / 2


	int primeiraAdicao;
	montarLevarRAM(adicao(a,b), 0);
	primeiraAdicao = montarTrazerRAM(0);


	int totalAdicao;
	montarLevarRAM(adicao(primeiraAdicao, c), 0);
	totalAdicao = montarTrazerRAM(0);

	int p;
	montarInstrucoesProgramaDivisao(totalAdicao, 2);
	montarLevarRAM(RAM[3],0);
	p = montarTrazerRAM(0);


	int primeiroP;
	montarLevarRAM(subtracao(p, a), 0);
	primeiroP = montarTrazerRAM(0);

	int segundoP;
	montarLevarRAM(subtracao(p, b), 0);
	segundoP = montarTrazerRAM(0);

	int terceiroP;
	montarLevarRAM(subtracao(p, c), 0);
	terceiroP = montarTrazerRAM(0);


	montarInstrucoesProgramaMultiplicacao(p, primeiroP);
	montarLevarRAM(RAM[1], 0);
	
	montarInstrucoesProgramaMultiplicacao(montarTrazerRAM(0), segundoP);
	montarLevarRAM(RAM[1], 0);

	montarInstrucoesProgramaMultiplicacao(montarTrazerRAM(0), terceiroP);
	montarLevarRAM(RAM[1], 0);

	int totalMult = montarTrazerRAM(0);

	return raiz_quadrada(totalMult);
}

int areaCoroaCircular(int R, int r)
{
	//A = pi * (R?? - r??)

	int Rquad;
	montarLevarRAM(montarQuadrado(R, 2), 0);
	Rquad = montarTrazerRAM(0);

	int rquad;
	montarLevarRAM(montarQuadrado(r, 2), 0);
	rquad = montarTrazerRAM(0);


	montarLevarRAM(subtracao(Rquad, rquad), 0);
	return montarTrazerRAM(0);
}

int fatorial(int nroFatorial)
{
	int fat;
	montarLevarRAM(0, 0);
	fat = montarTrazerRAM(0);
	
	int n;
	montarLevarRAM(nroFatorial, 0);
	n = montarTrazerRAM(0);
	
	for(fat = 1; n > 1; n = n - 1)
	{
		montarInstrucoesProgramaMultiplicacao(fat, n);
		montarLevarRAM(RAM[1], 0);
		fat = montarTrazerRAM(0);
	}

	return montarTrazerRAM(0);
}

int areaTrapezio(int h, int B, int b)
{
	// A = ((B + b) . h) / 2 
	//A = ((8 + 5) . 3) / 2 
	// A = 19,5 cm??

	int somaBases;
	montarLevarRAM(adicao(B, b), 0);
	somaBases = montarTrazerRAM(0);

	int multi;
	montarInstrucoesProgramaMultiplicacao(somaBases, h);
	montarLevarRAM(RAM[1], 0);
	multi = montarTrazerRAM(0);

	montarInstrucoesProgramaDivisao(multi, 2);
	montarLevarRAM(RAM[3], 0);
	return montarTrazerRAM(0);
}

int areaCubo(int a)
{
	// = 6 a??

	int quad;
	montarLevarRAM(montarQuadrado(a,2), 0);
	quad = montarTrazerRAM(0);

	
	montarInstrucoesProgramaMultiplicacao(6, quad);
	montarLevarRAM(RAM[1], 0);
	return montarTrazerRAM(0);
}

int volumeCubo(int a)
{
	// v = a??
	montarLevarRAM(montarCubo(a, 3), 0);
	return montarTrazerRAM(0);	
}

int areaParalelepipedo(int a, int b, int c)
{
	// al = 2(ab+bc+ac)
	// al = 2( 60???25 +  25???30 +  60???30)
	// al  = 2(1500+750+1800)
	// al = 2???4050
	// al = 8100 cm2

	int mult1;
	montarInstrucoesProgramaMultiplicacao(a,b);
	montarLevarRAM(RAM[1], 0);
	mult1 = montarTrazerRAM(0);
	
	int mult2;
	montarInstrucoesProgramaMultiplicacao(b,c);
	montarLevarRAM(RAM[1], 0);
	mult2 = montarTrazerRAM(0);
	
	int mult3;
	montarInstrucoesProgramaMultiplicacao(a,c);
	montarLevarRAM(RAM[1], 0);
	mult3 = montarTrazerRAM(0);

	int result;
	montarLevarRAM(adicao(mult1, mult2), 0);
	result = montarTrazerRAM(0);

	int total;
	montarLevarRAM(adicao(result, mult3), 0);
	total = montarTrazerRAM(0);
	

	montarInstrucoesProgramaMultiplicacao(2, total);
	montarLevarRAM(RAM[1], 0);
	return montarTrazerRAM(0);
}

int volumeParalelepipedo(int a, int b, int c)
{
	// v = abc

	int mult1;
	montarInstrucoesProgramaMultiplicacao(a,b);
	montarLevarRAM(RAM[1], 0);
	mult1 = montarTrazerRAM(0);
	
	
	montarInstrucoesProgramaMultiplicacao(mult1,c);
	montarLevarRAM(RAM[1], 0);
	return montarTrazerRAM(0);
}



int montarTermoGeralPA(int a1PA, int razaoPA, int termoEncontrarPA)
{
	//An= a1 + (n - 1) * razao;
	int resultado;
	montarLevarRAM(subtracao(termoEncontrarPA, 1), 0);
	resultado = montarTrazerRAM(0);
	

	montarInstrucoesProgramaMultiplicacao(resultado, razaoPA);
	montarLevarRAM(RAM[1], 0);
	termoEncontrarPA = montarTrazerRAM(0);
	
	montarLevarRAM(adicao(a1PA, termoEncontrarPA), 0);
	return montarTrazerRAM(0);
	
}

int montarTermoGeralPG(int a1PG, int razaoPG, int termoEncontrarPG)
{
	//An = a1 * q ^ n - 1
	int resultadoSub;
	montarLevarRAM(subtracao(termoEncontrarPG, 1), 0);
	resultadoSub = montarTrazerRAM(0);

	
	int resultadoPotencia;
	montarLevarRAM(montarPotenciacao(razaoPG, resultadoSub), 0);
	resultadoPotencia = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(a1PG, resultadoPotencia);
	montarLevarRAM(RAM[1], 0);
	return montarTrazerRAM(0);

}

int montarSomaTermosPA(int a1, int razao, int termoEncontrar)
{
	//Sn = ((a1 + an). n) / 2
	int resultado;
	montarLevarRAM(adicao(1 , montarTermoGeralPA(a1, razao, termoEncontrar)), 0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaMultiplicacao(resultado, 10);
	montarLevarRAM(RAM[1], 0);
	resultado = montarTrazerRAM(0);
	
	montarInstrucoesProgramaDivisao(resultado, 2);
	montarLevarRAM(RAM[3], 0);
	return montarTrazerRAM(0);
}

int montarSomaTermoPG(int a1, int razao, int termoEncontrar)
{
	//Sn = a1 * (q ^ n - 1) / (q-1)

	int resultadoPotencia ;
	montarLevarRAM(montarPotenciacao(razao, termoEncontrar), 0);
	resultadoPotencia = montarTrazerRAM(0);

	int resultadoSub;
	montarLevarRAM(subtracao(resultadoPotencia, 1), 0);
	resultadoSub = montarTrazerRAM(0);

	int resultado;
	montarLevarRAM(resultadoSub, 0);
	resultado = montarTrazerRAM(0);

	montarLevarRAM(subtracao(razao, 1), 0);
	resultadoSub = montarTrazerRAM(0);

 	montarInstrucoesProgramaMultiplicacao(a1, resultado);
	montarLevarRAM(RAM[1], 0);
	resultado = montarTrazerRAM(0);

	montarInstrucoesProgramaDivisao(resultado, resultadoSub);
	montarLevarRAM(RAM[3], 0);
	return montarTrazerRAM(0);
}
   

   