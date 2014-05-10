/// Tomás Abril
//implementando A*
//caminho do duende

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#define quadrado " # "
#define cam " + "
#else
#define CLEAR "clear"
#define quadrado " \u2588 "
#define cam " \u25C6 "
#endif
#ifdef WINDOWS
#define CLEAR "cls"
#define quadrado " # "
#define cam " + "
#endif

typedef struct Posicao{
	bool visitado;
	int i;
	int j;
	int dist;
	int peso;
}Posicao;

void inserir(Posicao x);
Posicao proximo();
int filaVazia();
void criaLabirinto();
void mostralab();
int calculaCaminho();
void olhaProx();
void anda();

int **lab, tam;
Posicao duende;
Posicao saida;
Posicao *fila;
int posescrita=0, posleitura=0, qtparede=5;
Posicao posatual;

int main()
{
	srand(time(NULL));
	printf("\n tamanho do labirinto: ");
	scanf("%d", &tam);
	fila=(Posicao*)malloc(sizeof(Posicao)*(tam*tam+1));
	printf("\n quantidade de parede de 0 a 9 (padrao 5): ");
	scanf("%d", &qtparede);
	criaLabirinto();
	mostralab();
	printf("\n onde o duende comeca? ");
	scanf("%d %d", &duende.i, &duende.j);
	printf("\n onde e a saida? ");
	scanf("%d %d", &saida.i, &saida.j);
	printf("\n");

	posatual.visitado=1;
	posatual.i=duende.i;
	posatual.j=duende.j;
	posatual.dist=0;
	fila[0]=posatual;

	lab[duende.i][duende.j]=-3;
	lab[saida.i][saida.j]=0;
	int comp = calculaCaminho();
	mostralab();
	printf("\n");
	anda();
	mostralab();
	printf("\n tamanho do caminho: %d\n\n", comp);

	return 0;
}

void criaLabirinto()
{
	int i, j;
	lab=(int**)malloc(sizeof(int*)*tam);
	for(i=0; i<tam; i++)
	{
		lab[i]=(int*)malloc(sizeof(int)*tam);
	}
	for(i=0; i<tam; i++)
		for(j=0; j<tam; j++)
		{
			if(i==0 || j==0 || i==tam-1 || j==tam-1)
				lab[i][j]=-1;
			else
			{
				if(rand()%10 < qtparede)
					lab[i][j]=-1;
				else
					lab[i][j]=-2;
			}
		}
}

void mostralab()
{
	//system(CLEAR);
	int i, j;
	printf("   ");
	for(i=0; i<tam; i++)
		printf("%2d ", i);
	printf("\n");
	for(i=0; i<tam; i++)
	{
		printf("%2d ", i);
		for(j=0; j<tam; j++)
		{
			if(lab[i][j]==-1)
				printf(quadrado);
			else if(lab[i][j]==0)
				printf(" S ");
			else if(lab[i][j]==-3)
				printf(" D ");
			else if(lab[i][j]==-2)
				printf(" - ");
			else if(lab[i][j]==-4)
				printf(cam);
			else
				printf("%2d ", lab[i][j]);

		}
		printf("\n");
	}
}

void inserir(Posicao x)
{
	posescrita++;
	fila[posescrita]=x;
}

Posicao proximo()
{
	int ic, x, menor=tam*tam;
	for(ic=0; ic<=posescrita; ic++)
	{
		if( (fila[ic]).visitado == 0 && (fila[ic]).peso < menor )
		{
			menor=(fila[ic]).peso;
			x=ic;
		}
		if( (fila[ic]).visitado == 0 && (fila[ic]).peso == menor )
		{
			if(fila[ic].dist < fila[x].dist)
				x=ic;
		}
	}
	(fila[x]).visitado=1;
	return fila[x];
}

int calculaCaminho()
{
	int cont=0;
	while(lab[posatual.i][posatual.j]!=0)
	{
		olhaProx();
		cont++;
	}
	return posatual.dist;
}

void olhaProx()
{
	int ct, nao, delta;
	nao=1;
	int io, jo;
	Posicao inserido;
	posatual.visitado=1;
	for(io=posatual.i-1; io<=posatual.i+1; io++)
	{
		for(jo=posatual.j-1; jo<=posatual.j+1; jo++)
		{
			nao=1;
			if( lab[io][jo] == 0)
			{
				inserido.visitado=0;
				inserido.i=io;
				inserido.j=jo;
				inserido.dist=(posatual.dist)+1;
				if(abs(inserido.i - saida.i) < abs(inserido.j - saida.j))
					delta= abs(inserido.j - saida.j);
				else
					delta= abs(inserido.i - saida.i);
				(inserido.peso)= delta + inserido.dist;
				inserir(inserido);
			}
			else if( posatual.i == io && posatual.j == jo )
			{}
			else if( (lab[io][jo]) == -2 )
			{
				for(ct=0; ct<=posescrita; ct++)	//check se ja está na fila
				{
					if( ((fila[ct]).i) == io && ((fila[ct]).j) == jo )
					{
						nao=0;
					}
				}
				if(nao == 1)
				{
					inserido.visitado=0;
					inserido.i=io;
					inserido.j=jo;
					inserido.dist=(posatual.dist)+1;
					if(abs(inserido.i - saida.i) < abs(inserido.j - saida.j))
						delta= abs(inserido.j - saida.j);
					else
						delta= abs(inserido.i - saida.i);
						(inserido.peso)= delta + inserido.dist;
					lab[io][jo]=inserido.dist;
					inserir(inserido);
				}
			}
		}
	}

	posatual = proximo();
}

void anda()
{
	int io, jo, menor=tam*tam, menori, menorj, fim=0;
	menori=posatual.i;
	menorj=posatual.j;
	do
	{
		menor=tam*tam;
		for(io=posatual.i-1; io<=posatual.i+1; io++)
		{
			for(jo=posatual.j-1; jo<=posatual.j+1; jo++)
			{
    				if(lab[io][jo]==-3)
					fim=1;
				if( io == posatual.i && jo == posatual.j)
				{}
				else if( lab[io][jo] < menor && lab[io][jo] > 0 )
				{
					menor=lab[io][jo];
					menori=io;
					menorj=jo;
				}
			}
		}
		if(fim)
			break;
		posatual.i = menori;
		posatual.j = menorj;
		lab[menori][menorj] = -4;
		//mostralab();
	}while( fim!= 1);
}

