/*****************************************************************
**    Nome: Prova de Rally		                                **
**    Autor: Roberto Barreto\Henrique Cartucho\Vincent Rebena	**
**    Data: 18/12/2020			                                **
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

//variaveis globais
//int n = 0; //tamanho do vetor de PILOTOS inicialmente

typedef struct infoPiloto
{
    int num;
    char nome[50];
    char carro[50];
} PILOTO;

typedef struct infoProva
{
    int pos;
    PILOTO piloto;
    int tempoProva;
} PROVA;

typedef struct infotempos
{
    int num;
    char etapaI[3]; //Etapa inicial
    char etapaF[3]; //Etapa Final
    int tempo;
} TEMPOS;

typedef struct infoDistancias
{
    char etapaI[3]; //Etapa inicial
    char etapaF[3]; //Etapa Final
    float distancia;
} DISTANCIAS;

int nPilotosCount();                         //contagem do numero de pilotos registados no ficheiro pilotos.txt
void nEtapas(int *n);                        //função que retira os valores no começo do ficheiro de tempos.txt e guarda em duas posições do vetor n, sendo n[0]<-nEtapas,n[1]<-nPilotos
void loadTempos(TEMPOS *etapa);              //carregamento das informações do ficheiro tempos.txt para uma estrutura que guarda os tempos, saltando os valores iniciais a frente
void loadDistancias(DISTANCIAS *distancias); //carregamento das informações do distancias.txt para o struck DISTANCIAS
void loadPilotos(PILOTO *piloto);            //carregamento das informações ds pilotos.txt para o struct PILoTOS

void menu()
{
    /* int escolha, nPilotos;
    PILOTO pilotos[n];
    printf("\n**************************");
    printf("\n** 1 - Mostrar pilotos\t**");
    printf("\n** 2 - Mostrar Tempos\t**");
    printf("\n** 3 - Mostrar Provas\t**");
    printf("\n** 4 - Sair\t\t**");
    printf("\n**************************");
    printf("\n escolha: ");
    scanf("%d", &escolha);
    if (escolha != 4)
    {
        switch (escolha)
        {
        case 1:
            if (n > 0)
                mostrarPilotos(pilotos);
            else
                printf("Erro: Nao existe Pilotos");
            getchar();
            break;
        case 2:

            break;
        case 3:

            break;
        default:
            printf("Opcao invalida");
            break;
        }
        menu();
    }
    else
    {
        return;
    }
    //menu(pilotos, n, nE);*/
}

void nEtapas(int *n)
{

    FILE *f;

    f = fopen("tempos.txt", "r");
    //colocar aqui para ler o primeiro valor e não repetir o valor final
    fscanf(f, "%d;%d\n", &n[0], &n[1]);
    fclose(f);
}

void loadTempos(TEMPOS *etapa)
{

    FILE *f;
    int res, i = 0;
    f = fopen("tempos.txt", "r");
    fseek(f, sizeof(int), SEEK_SET);
    //colocar aqui para ler o primeiro valor e não repetir o valor final

    //enquanto tiver o que ler, vai ler
    while (res != EOF)
    {

        res = fscanf(f, "%d;%[^;];%[^;];%d\n", &etapa[i].num, etapa[i].etapaI, etapa[i].etapaF, &etapa[i].tempo);

        i++;
    }
    fclose(f);
}

void loadDistancias(DISTANCIAS *distancias)
{
    FILE *f;
    int res, i = 0;
    f = fopen("distancias.txt", "r");

    while (res != EOF)
    {

        res = fscanf(f, "%[^;];%[^;];%f\n", distancias[i].etapaI, distancias[i].etapaF, &distancias[i].distancia);

        i++;
    }
    fclose(f);
}

void loadPilotos(PILOTO *piloto)
{
    FILE *f;
    int res, i = 0;
    f = fopen("pilotos.txt", "r");

    //colocar aqui para ler o primeiro valor e não repetir o valor final
    //enquanto tiver o que ler, vai ler
    while (res != EOF)
    {

        res = fscanf(f, "%d;%[^;];%[^\n]\n", &piloto[i].num, piloto[i].nome, piloto[i].carro);

        i++;
    }
    fclose(f);
}

int nPilotosCount()
{
    FILE *f;
    int res, i = 0, num;
    char nome[50], carro[50];
    f = fopen("pilotos.txt", "r");
    res = fscanf(f, "%d;%[^;];%[^\n]\n", &num, nome, carro);
    //colocar aqui para ler o primeiro valor e não repetir o valor final
    //enquanto tiver o que ler, vai ler
    while (res != EOF)
    {
        res = fscanf(f, "%d;%[^;];%[^\n]\n", &num, nome, carro);
        i++;
    }
    fclose(f);
    return i;
}

void main()
{
    int n[1], nTotal, nTempos, nPilotos;
    nEtapas(n);
    //valores q estão no começo do ficheiro tempos.txt com as informações dos Pilotos e Etapas
    nTempos = n[0];
    nPilotos = n[1];
    //o total de etapas que têm de estar registadas é o numero de etapas a multiplicar pelo
    //numero de pilotos que está no ficheiro
    nTotal = nTempos * nPilotos;
    //carregamento dos tempos para o vetor da estrutura TEMPOS
    TEMPOS tempos[nTotal];
    loadTempos(tempos);
    printf("\nTempos:");
    for (int i = 0; i < nTotal; i++)
    {
        printf("\n Numero Piloto: %d", tempos[i].num);
        printf("\n Etapa inicial: %s", tempos[i].etapaI);
        printf("\n Etapa Final: %s", tempos[i].etapaF);
        printf("\n Tempo: %dms\n", tempos[i].tempo);
    }

    //Carregamento das distancias das etapas para o vetor da estrutura DISTANCIAS
    DISTANCIAS distancias[nTempos];
    loadDistancias(distancias);
    printf("\nDistancias:");
    for (int i = 0; i < nTempos; i++)
    {
        printf("\n Etapa inicial: %s", distancias[i].etapaI);
        printf("\n Etapa Final: %s", distancias[i].etapaF);
        printf("\n Distancia: %.2fM\n", distancias[i].distancia);
    }

    //carregamento das informações dos pilotos para o vetor da estrutura PILOTO
    nPilotos = nPilotosCount();
    PILOTO pilotos[nPilotos];
    loadPilotos(pilotos);
    printf("\nPilotos:");
    for (int i = 0; i < nPilotos; i++)
    {
        printf("\n Num: %d", pilotos[i].num);
        printf("\n Nome: %s", pilotos[i].nome);
        printf("\n Carro: %s\n", pilotos[i].carro);
    }
}