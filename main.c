/*****************************************************************
**    Nome: Exemplo nome		                                **
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

typedef struct infoEtapas
{
    int num;
    char etapaI[3]; //Etapa inicial
    char etapaF[3]; //Etapa Final
    int tempo;
} ETAPAS;

typedef struct infoDistancias
{
    char etapaI[3]; //Etapa inicial
    char etapaF[3]; //Etapa Final
    float distancia;
} DISTANCIAS;

void mostrarPilotos(PILOTO *pilotos);
void loadTempos(ETAPAS *etapas);

void mostrarPilotos(PILOTO *pilotos)
{
    FILE *f;
    int res, num, i = 0;
    char nome[50], carro[50], string[50];
    f = fopen("pilotos.txt", "r");
    //colocar aqui para ler o primeiro valor e não repetir o valor final
    res = fscanf(f, "%d;%2s;%2s;%d\n", &num, &string);
    //enquanto tiver o que ler, vai ler
    while (res != EOF)
    {
        //separar a string por ;
        char *ptr = strtok(string, ";");
        strcpy(nome, ptr);

        //como sempre que a função strtok encontra um delimitador ela substitui por \0
        //entao sempre que se separa a string temos de partir do \0 ou NULL
        //EX:Roberto;Mustang | Roberto\0Mustang
        ptr = strtok(NULL, ";");
        strcpy(carro, ptr);

        printf("\nNumero \t:%d", num);
        printf("\nNome \t:%s", nome);
        printf("\nCarro \t:%s\n", carro);

        /*pilotos[i]->num = num;
        strcpy(pilotos[i]->nome, nome);
        strcpy(pilotos[i]->carro, carro);*/

        res = fscanf(f, "%d;%s;%s\n", &num, &string);
        i++;
    }
    fclose(f);
}

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

void loadInfo() // para n pilotos
{

    FILE *f;
    int res, num, i = 0;

    f = fopen("pilotos.txt", "r");

    //colocar aqui para ler o primeiro valor e não repetir o valor final
    res = fscanf(f, "%d\n", &num);
    if (res == EOF)
    {
        num = 0;
    }
    else
    {
        //enquanto tiver o que ler, vai ler
        while (res != EOF)
        {
            res = fscanf(f, "%d\n", &num);
            i++;
        }
    }
    printf("%d", num);
    fclose(f);
}

void nTempos(int *n) // para registo de etapas e pilotos
{

    FILE *f;

    f = fopen("tempos.txt", "r");
    //colocar aqui para ler o primeiro valor e não repetir o valor final
    fscanf(f, "%d;%d\n", &n[0], &n[1]);
    fclose(f);
}

void loadTempos(ETAPAS *etapa)
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

    // int n = 0, nE = 0; //n-> nº pilotos,nE->nº Etapas

    //loadInfo();

    int n[1], nTotal, nEtapas, nPilotos;
    nTempos(n);
    nEtapas = n[0];
    nPilotos = n[1];
    nTotal = nEtapas * nPilotos;

    ETAPAS etapas[nTotal];
    loadTempos(etapas);

    DISTANCIAS distancias[nEtapas];
    loadDistancias(distancias);

    nPilotos = nPilotosCount();
    PILOTO pilotos[nPilotos];
    loadPilotos(pilotos);
}