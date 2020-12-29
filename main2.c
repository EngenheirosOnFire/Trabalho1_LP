/*****************************************************************
**    Nome: Exemplo nome		                                **
**    Autor: Roberto Barreto\Henrique Cartucho\Vincent Rebena	**
**    Data: 18/12/2020			                                **
****************************************************************/

#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

//variaveis globais
int n = 0; //tamanho do vetor de PILOTOS inicialmente

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
    char etapaI[1]; //Etapa inicial
    char etapaF[1]; //Etapa Final
    int tempo;
} tempos;

void infoPilotos();
void guardarPilotos(int num, char nome, char carro);
void guardarTempos();
void mostrarPilotos(PILOTO *pilotos);

void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int n, int nPilotos)
{
    int contador = 0, a = 0, tempoTotal = 0;
    for (int i = 0; i <= n; i++)
    {

        contador++;

        for (int j = i + 1; j <= n; j++)
        {
            //tempo que recebemos da primeira leitura tem de ser o primeiro tempo a registar
            tempoTotal += tempos[i].tempo;
            //verificar se existe mais numeros iguais e somar o contador
            if (tempos[i].num == tempos[j].num)
            {
                contador++;
                tempoTotal += tempos[j].tempo; //se houver um numero igual o tempo desse numero tem de ser somado ao tempoTotal
            }
        }

        //verificar se existem 3 etapas com o numero do piloto caso sim tem prova valida
        if (contador == 3)
        {
            prova[a].piloto.num = tempos[i].num;
            //encontrar o piloto com o numero do piloto com prova valida
            for (int p = 0; p <= nPilotos; p++)
            {
                if (piloto[p].num == prova[a].piloto.num)
                {
                    strcpy(prova[a].piloto.nome, piloto[p].nome);
                    strcpy(prova[a].piloto.carro, piloto[p].carro);
                }
            }
            prova[a].tempoProva = tempoTotal;
            prova[a].aprovado = 1;
            contador = 0;
            a++;
        }
        else
        {
            contador = 0;
        }
    }
}

void infoPilotos() //PILOTO *ptr
{
    int num;
    char nome, carro;
    fflush(stdin);
    printf("Qual o Numero       :");
    scanf("%d", &num);
    fflush(stdin);
    printf("Qual o Nome         :");
    scanf(" %s", nome);
    printf("Qual o Carro        :");
    fflush(stdin);
    scanf(" %s", carro);
    guardarPilotos(num, nome, carro);
}

void guardarPilotos(int num, char nome, char carro)
{

    FILE *f; // defininçao de uma variavel associada a um ficheiro

    //f = fopen("teste.txt","w");//criar um ficheiro teste.txt em modo de escrita "w"
    f = fopen("pilotos.txt", "a"); //criar um ficheiro teste.txt em modo de atualizar sem apagar o anterior

    fprintf(f, "%d;%s;%s\n", num, nome, carro); // escrever no ficheiro criado

    fclose(f); //fechar o ficheiro pois nao se vai manipular mais o ficheiro
}

void guardarTempos()
{
    int num, tempo;
    char etapa1[3], etapa2[3], _etapa1[3];
    char numEtapa1[1], numEtapa2[1];

    printf("Introduza o numero do piloto: ");
    scanf("%d", &num);

    printf("\n(E<-Etapa|P<-Partida|C<-Chegada)\n");

    fflush(stdin);
    printf("Introduza o ponto de partida(E|P): ");
    scanf("%s", etapa1);
    strcpy(_etapa1, etapa1);

    fflush(stdin);
    printf("Introduza o ponto de chegada(E|C): ");
    scanf("%s", etapa2);

    fflush(stdin);
    printf("Introduza o tempo(ms): ");
    scanf("%d", &tempo);

    FILE *f; // defininçao de uma variavel associada a um ficheiro

    f = fopen("tempos.txt", "a"); //criar um ficheiro teste.txt em modo de atualizar sem apagar o anterior

    fprintf(f, "%d;%s;%s;%d\n", num, _etapa1, etapa2, tempo); // escrever no ficheiro criado

    fclose(f); //fechar o ficheiro pois nao se vai manipular mais o ficheiro
}

void mostrarPilotos(PILOTO *pilotos)
{
    FILE *f;
    int res, num, i = 0;
    char nome[50], carro[50], string[50], caracter;
    f = fopen("pilotos.txt", "r");
    //colocar aqui para ler o primeiro valor e não repetir o valor final
    res = fscanf(f, "%d;%s\n", &num, &string);
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

void mostrarTempos()
{
    FILE *f;
    int res, num, i = 0, tempo;
    char etapa1[50], etapa2[50], string[50], caracter;
    f = fopen("pilotos.txt", "r");
    //colocar aqui para ler o primeiro valor e não repetir o valor final
    res = fscanf(f, "%d;%s;%d\n", &num, &string, &tempo);
    //enquanto tiver o que ler, vai ler
    while (res != EOF)
    {
        //separar a string por ;
        char *ptr = strtok(string, ";");
        strcpy(etapa1, ptr);

        //como sempre que a função strtok encontra um delimitador ela substitui por \0
        //entao sempre que se separa a string temos de partir do \0 ou NULL
        //EX:Roberto;Mustang | Roberto\0Mustang
        ptr = strtok(NULL, ";");
        strcpy(etapa2, ptr);

        printf("\nNumero \t:%d", num);
        printf("\nEtapa1 \t:%s", nome);
        printf("\nEtapa2 \t:%s\n", carro);
        printf("\nTempo \t:%s\n", carro);

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
    int escolha, nPilotos;
    PILOTO pilotos[n];
    printf("\n**************************");
    printf("\n** 1 - Colocar pilotos\t**");
    printf("\n** 2 - Mostrar pilotos\t**");
    printf("\n** 3 - Colocar Tempos\t**");
    printf("\n** 4 - Mostrar Tempos\t**");
    printf("\n** 5 - Colocar Provas\t**");
    printf("\n** 6 - Mostrar Provas\t**");
    printf("\n** 7 - Sair\t\t**");
    printf("\n**************************");
    printf("\n escolha: ");
    scanf("%d", &escolha);
    if (escolha != 7)
    {
        switch (escolha)
        {
        //!verificar se é numero ou string
        case 1:
            printf("Quantidade de pilotos: ");
            scanf("%d", n);
            for (int i = 0; i <= n; i++)
                infoPilotos();
            break;
        case 2:
            if (n > 0)
                mostrarPilotos(pilotos);
            else
                printf("Erro: Nao existe Pilotos");
            getchar();
            break;
        case 3:
            if (n > 0)
                guardarTempos();
            else
                printf("Erro: Nao existe Pilotos");
            break;
        case 4:
            if (n > 0)
                guardarTempos();
            else
                printf("Erro: Nao existe Pilotos");
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
    //menu(pilotos, n, nE);
}
void loadInfo()
{

    FILE *f;
    int res, num, i = 0;
    char nome[50], carro[50], string[50], caracter;
    f = fopen("pilotos.txt", "r");

    //colocar aqui para ler o primeiro valor e não repetir o valor final
    res = fscanf(f, "%d;%s;%s\n", &num, &string);
    if (res == EOF)
    {
        num = 0;
    }
    else
    {
        //enquanto tiver o que ler, vai ler
        while (res != EOF)
        {
            res = fscanf(f, "%d;%s;%s\n", &num, &string);
            i++;
        }
    }
    fclose(f);
    n = num;
}
void main()
{
    // int n = 0, nE = 0; //n-> nº pilotos,nE->nº tempos

    loadInfo();

    menu();
}