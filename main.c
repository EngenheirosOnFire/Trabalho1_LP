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

typedef struct infoPiloto
{
    int num;
    char nome[50];
    char carro[50];
} PILOTO;

typedef struct infoProva
{
    PILOTO piloto;
    int tempoProva;
    int aprovado;
} PROVA;

typedef struct infotempos
{
    int num, tempo;
    char etapaI[3]; //Etapa inicial
    char etapaF[3]; //Etapa Final
} TEMPOS;

typedef struct infoDistancias
{
    char etapaI[3]; //Etapa inicial
    char etapaF[3]; //Etapa Final
    float distancia;
} DISTANCIAS;

int nPilotosCount();                                                                                                                    //contagem do numero de pilotos registados no ficheiro pilotos.txt
void Etapas(int *n);                                                                                                                    //função que retira os valores no começo do ficheiro de tempos.txt e guarda em duas posições do vetor n, sendo n[0]<-nEtapas,n[1]<-nPilotos
void loadTempos(TEMPOS *etapa);                                                                                                         //carregamento das informações do ficheiro tempos.txt para uma estrutura que guarda os tempos, saltando os valores iniciais a frente
void loadDistancias(DISTANCIAS *distancias);                                                                                            //carregamento das informações do distancias.txt para o struck DISTANCIAS
void loadPilotos(PILOTO *piloto);                                                                                                       //carregamento das informações ds pilotos.txt para o struct PILoTOS
int nPilotosCount();                                                                                                                    //contagem de pilotos contidos no ficheiro pilotos.txt
int verificaProva(TEMPOS *tempos, int n, int *aprovados);                                                                               //verificação de quantos pilotos têm prova valida
void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int n, int nPilotos);                                                      //carregamenteo das informações dos vários structs para um struct final contento informação da prova por completo
void ordenaTemposDesc(PROVA *prova, int nPilotos, int aprovados);                                                                       //ordenção e amostra dos tempos por ordem descendente
void medTemposEtapa(TEMPOS *tempos, int n, int *aprovados, int *medTempos, int nAprovados);                                             //media de tempos por etapa
void extremos(PROVA *prova, int nPilotos, int *tempoExtremos);                                                                          //Amostra do piloto mais rapido e mais lento
void menorTempo(TEMPOS *tempos, int nEtapas, int maior);                                                                                //Amostra do menor tempo possivel para realizar a prova
void velocidadesMedias(DISTANCIAS *distancias, int nEtapas, int aprovados, int *medTempos);                                             //Amostra das velocidades medias da prova
void menu(TEMPOS *tempos, PILOTO *pilotos, DISTANCIAS *distancias, PROVA *prova, int nTotal, int nPilotos, int nEtapas, int aprovados); //Menu principal do programa

void Etapas(int *n)
{
    FILE *f;
    f = fopen("tempos.txt", "r");
    fscanf(f, "%d;%d\n", &n[0], &n[1]);
    fclose(f);
}

void loadTempos(TEMPOS *etapa)
{

    FILE *f;
    int res, i = 0;
    f = fopen("tempos.txt", "r");
    fseek(f, sizeof(int), SEEK_SET); //saltar a primeira linha a frente
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
    //ler o ficheiro até a função encontrar o fim do ficheiro
    while (res != EOF)
    {
        //%[^;]->ler todos os carateres até encontrar o caracter ';'
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

    //ler o ficheiro até a função encontrar o fim do ficheiro
    while (res != EOF)
    {
        //%[^;]->ler todos os carateres até encontrar o caracter ';'
        res = fscanf(f, "%d;%[^;];%[^\n]\n", &piloto[i].num, piloto[i].nome, piloto[i].carro);

        i++;
    }
    fclose(f);
}

int nPilotosCount()
{
    FILE *f;
    int contador = 0; //pois sempre irá existir pelomenos um piloto
    char c;
    f = fopen("pilotos.txt", "r");
    //verificar todos os caracteres até encontrar '\n', sempre que '\n' for encontrado é contado mais um piloto pois existe 1 piloto por linha
    for (c = getc(f); c != EOF; c = getc(f))
    {
        if (c == '\n')
            contador++;
    }
    fclose(f);
    return contador;
}

int verificaProva(TEMPOS *tempos, int n, int *aprovados)
{
    int contador = 0;        //conta numero de vezes que numero aparece
    int contadorPilotos = 0; //conta o numero de pilotos aprovados
    int numPilotoAprv;
    for (int i = 0, a = 0; i <= n; i++)
    {
        contador++;
        for (int j = i + 1; j <= n; j++)
        {
            if (tempos[i].num == tempos[j].num)
                contador++;
        }
        //verificar se existem 3 etapas com o numero do piloto
        if (contador == 3)
        {
            aprovados[a] = tempos[i].num; //colocar o numero do piloto aprovado num vetor
            contadorPilotos++;            //contar mais um piloto
            a++;
        }
        contador = 0;
    }
    return contadorPilotos;
}

int loadVerificaProva(TEMPOS *tempos, int n)
{
    int contador = 0;        //conta numero de vezes que numero aparece
    int contadorPilotos = 0; //conta o numero de pilotos aprovados
    for (int i = 0; i <= n; i++)
    {
        contador++;
        for (int j = i + 1; j <= n; j++)
        {
            if (tempos[i].num == tempos[j].num)
                contador++;
            //verificar se existem 3 etapas com o numero do piloto
        }
        if (contador == 3)
        {
            contadorPilotos++; //contar mais um piloto
        }
        contador = 0;
    }
    return contadorPilotos;
}

void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int n, int nPilotos)
{

    for (int i = 0; i <= nPilotos; i++)
    {
        int tempoTotal = 0, contador = 0;
        prova[i].piloto.num = piloto[i].num;
        for (int j = 0; j <= n; j++)
        {
            //verificar se existe mais numeros iguais e somar o contador
            if (piloto[i].num == tempos[j].num)
            {
                tempoTotal += tempos[j].tempo; //se houver um numero igual o tempo desse numero tem de ser somado ao tempoTotal
                contador++;
            }
        }
        //encontrar o piloto com o numero do piloto com prova valida
        strcpy(prova[i].piloto.nome, piloto[i].nome);   //copia do nome do piloto
        strcpy(prova[i].piloto.carro, piloto[i].carro); //copia do carro do piloto
        prova[i].tempoProva = tempoTotal;               //copia do tempo total de prova para o struct
        if (contador == 3)
        {
            prova[i].aprovado = 1; //se tiver todas as etapas registadas está aprovado
        }
        else
        {
            prova[i].aprovado = 0; //senão não está aprovado
        }
        contador = 0;
    }
}

void ordenaTemposDesc(PROVA *prova, int nPilotos, int aprovados)
{
    int contador, auxNum = 0, auxTempo = 0, auxApr = 0, a = 0;
    char auxNome[50], auxCarro[50], tempoMin;
    float tempoSec;
    PROVA provaOrdenado[aprovados];

    //copia do vetor prova para outro vetor para assim não alterar o vetor original e este vetor apenas conter os pilotos aprovados
    for (int i = 0; i <= nPilotos; i++)
    {

        if (prova[i].aprovado == 1)
        {

            provaOrdenado[a].piloto.num = prova[i].piloto.num;
            provaOrdenado[a].tempoProva = prova[i].tempoProva;
            provaOrdenado[a].aprovado = prova[i].aprovado;
            strcpy(provaOrdenado[a].piloto.nome, prova[i].piloto.nome);
            strcpy(provaOrdenado[a].piloto.carro, prova[i].piloto.carro);

            a++;
        }
    }
    //ordenação de forma descendente do vetor que contém a copia do original
    for (int i = 0; i < aprovados; i++)
    {

        for (int j = i + 1; j < aprovados; j++)
        {

            if (provaOrdenado[i].tempoProva < provaOrdenado[j].tempoProva)
            {
                //existiu a necessidade de criar uam variavel do tipo aux para guardar os valores da posição i
                //visto que esta ia ser substituida por as informações da posição j
                auxNum = provaOrdenado[i].piloto.num;
                auxTempo = provaOrdenado[i].tempoProva;
                auxApr = provaOrdenado[i].aprovado;
                strcpy(auxNome, provaOrdenado[i].piloto.nome);
                strcpy(auxCarro, provaOrdenado[i].piloto.carro);

                provaOrdenado[i].piloto.num = provaOrdenado[j].piloto.num;
                provaOrdenado[i].tempoProva = provaOrdenado[j].tempoProva;
                provaOrdenado[i].aprovado = provaOrdenado[j].aprovado;
                strcpy(provaOrdenado[i].piloto.nome, provaOrdenado[j].piloto.nome);
                strcpy(provaOrdenado[i].piloto.carro, provaOrdenado[j].piloto.carro);

                provaOrdenado[j].piloto.num = auxNum;
                provaOrdenado[j].tempoProva = auxTempo;
                provaOrdenado[j].aprovado = auxApr;
                strcpy(provaOrdenado[j].piloto.nome, auxNome);
                strcpy(provaOrdenado[j].piloto.carro, auxCarro);
            }
        }
    }
    //imprimir as informações ordenadas
    for (int i = 0; i < aprovados; i++)
    {
        //vamos transformar o tempo em minutos
        tempoMin = (provaOrdenado[i].tempoProva / 1000) / 60;
        //transformar o tempo em segundos e milésimos
        tempoSec = ((float)provaOrdenado[i].tempoProva / (float)1000) - (tempoMin * 60);
        printf("\nNumero: %d\t| Nome: %s\t| Carro: %s\t| tempo: %d:%.3f", provaOrdenado[i].piloto.num, provaOrdenado[i].piloto.nome, provaOrdenado[i].piloto.carro, tempoMin, tempoSec);
    }
}

void medTemposEtapa(TEMPOS *tempos, int n, int *aprovados, int *medTempos, int nAprovados)
{
    int somaP_E1 = 0, mediaP_E1, somaE1_E2 = 0, mediaE1_E2, somaE2_C = 0, mediaE2_C;
    //verificar o vetor tempos por completo
    for (int t = 0; t <= n; t++)
    {
        for (int j = 0; j <= nAprovados; j++)
        {
            //se o numero for igual ao numero do piloto aprovado ir buscar as informações do tempo
            if (tempos[t].num == aprovados[j])
            {

                if ((strcmp(tempos[t].etapaI, "P") == 0) && (strcmp(tempos[t].etapaF, "E1") == 0))
                {
                    somaP_E1 += tempos[t].tempo;
                }
                else if ((strcmp(tempos[t].etapaI, "E1") == 0) && (strcmp(tempos[t].etapaF, "E2") == 0))
                {
                    somaE1_E2 += tempos[t].tempo;
                }
                else
                {
                    somaE2_C += tempos[t].tempo;
                }
            }
        }
    }
    //media vai ser a soma dos tempos dividindo por o total de aprovados
    mediaP_E1 = somaP_E1 / nAprovados;
    mediaE1_E2 = somaE1_E2 / nAprovados;
    mediaE2_C = somaE2_C / nAprovados;
    medTempos[0] = mediaP_E1;
    medTempos[1] = mediaE1_E2;
    medTempos[2] = mediaE2_C;
    //apresentação das medias
}

void extremos(PROVA *prova, int nPilotos, int *tempoExtremos)
{
    int menor = prova[0].tempoProva, maior = prova[0].tempoProva, menorNum = 0, maiorNum = 0;
    //percorrer o vetor prova todo
    for (int i = 0; i <= nPilotos; i++)
    {
        //verificar se é um piloto aprovado
        if (prova[i].aprovado == 1)
        {
            //verficar se é maior ou menor que o menor ou maior tempo registado
            //guardar o local do vetor onde fica o menor e o maior
            if (prova[i].tempoProva < menor)
            {
                menor = prova[i].tempoProva;
                menorNum = i;
            }
            if (prova[i].tempoProva > maior)
            {
                maior = prova[i].tempoProva;
                maiorNum = i;
            }
        }
    }

    tempoExtremos[0] = maiorNum;
    tempoExtremos[1] = menorNum;
}

void menorTempo(TEMPOS *tempos, int nTotal, int maior)
{
    int menorP_E1 = maior, menorE1_E2 = maior, menorE2_C = maior, menor;
    int tempoMin, tempoMinP_E1, tempoMinE1_E2, tempoMinE2_C;
    float tempoSec, tempoSecP_E1, tempoSecE1_E2, tempoSecE2_C;
    for (int i = 0; i < nTotal; i++)
    {

        if ((strcmp(tempos[i].etapaI, "P") == 0) && (strcmp(tempos[i].etapaF, "E1") == 0))
        {
            if ((tempos[i].tempo < menorP_E1) && (tempos[i].tempo != 0))
            {
                menorP_E1 = tempos[i].tempo;
            }
        }
        else if ((strcmp(tempos[i].etapaI, "E1") == 0) && (strcmp(tempos[i].etapaF, "E2") == 0))
        {

            if ((tempos[i].tempo < menorE1_E2) && (tempos[i].tempo != 0))
            {
                menorE1_E2 = tempos[i].tempo;
            }
        }
        else if ((strcmp(tempos[i].etapaI, "E2") == 0) && (strcmp(tempos[i].etapaF, "C") == 0))
        {

            if ((tempos[i].tempo < menorE2_C) && (tempos[i].tempo != 0))
            {
                menorE2_C = tempos[i].tempo;
            }
        }
    }
    menor = menorP_E1 + menorE1_E2 + menorE2_C;
    //vamos transformar o tempo em minutos
    tempoMinP_E1 = (menorP_E1 / 1000) / 60;
    tempoMinE1_E2 = (menorE1_E2 / 1000) / 60;
    tempoMinE2_C = (menorE2_C / 1000) / 60;
    tempoMin = (menor / 1000) / 60;

    //transformar o tempo em segundos e milésimos
    tempoSecP_E1 = ((float)menorP_E1 / (float)1000) - (tempoMinP_E1 * 60);
    tempoSecE1_E2 = ((float)menorE1_E2 / (float)1000) - (tempoMinE1_E2 * 60);
    tempoSecE2_C = ((float)menorE2_C / (float)1000) - (tempoMinE2_C * 60);
    tempoSec = ((float)menor / (float)1000) - (tempoMin * 60);

    printf("\nMenor tempo possivel(Partida-Etapa1):%d:%.3f", tempoMinP_E1, tempoSecP_E1);
    printf("\nMenor tempo possivel(Etapa1-Etapa2):%d:%.3f", tempoMinE1_E2, tempoSecE1_E2);
    printf("\nMenor tempo possivel(Etapa2-Chegada):%d:%.3f", tempoMinE2_C, tempoSecE2_C);
    printf("\nMenor tempo possivel:%d:%.2f", tempoMin, tempoSec);
}

void velocidadesMedias(DISTANCIAS *distancias, int nEtapas, int aprovados, int *medTempos)
{
    float distanciaP_E1, distanciaE1_E2, distanciaE2_C, distancia, medias[aprovados], tempoP_E1, tempoE1_E2, tempoE2_C;
    //verificar todas as distancias e guardar em variaveis
    for (int j = 0; j < nEtapas; j++)
    {
        if ((strcmp(distancias[j].etapaI, "P") == 0) && (strcmp(distancias[j].etapaF, "E1") == 0))
        {
            distanciaP_E1 = distancias[j].distancia;
        }
        else if ((strcmp(distancias[j].etapaI, "E1") == 0) && (strcmp(distancias[j].etapaF, "E2") == 0))
        {
            distanciaE1_E2 = distancias[j].distancia;
        }
        else
        {
            distanciaE2_C = distancias[j].distancia;
        }
    }
    //transformar o tempo em segundos
    tempoP_E1 = (float)medTempos[0] / (float)1000;
    tempoE1_E2 = (float)medTempos[1] / (float)1000;
    tempoE2_C = (float)medTempos[2] / (float)1000;

    //velocidade media é igual à distancia percorrida a dividir pelo tempo demorado
    medias[0] = distanciaP_E1 / tempoP_E1;
    medias[1] = distanciaE1_E2 / tempoE1_E2;
    medias[2] = distanciaE2_C / tempoE2_C;

    printf("\nVelocidade Media (Partida-Etapa1):%.2fm/s", medias[0]);
    printf("\nVelocidade Media (Etapa1-Etapa2):%.2fm/s", medias[1]);
    printf("\nVelocidade Media (Etapa2-Chegada):%.2fm/s", medias[2]);
}

void tabelaClassificativa(PROVA *prova, int nPilotos)
{
    int auxNum, auxTempo, auxApr, tempoMin, diTempoLdr, diTempoAnt, tempoLdr;
    float tempoSec, diLdr, diAnt;
    char auxNome[30], auxCarro[30];
    printf("\n-----------------------------------------------------------------------------------------------------------------");
    printf("\n|    Posicao\t|     Numero\t|      Nome\t|     Carro\t| Tempo de prova |    Di.Ant.    |    Di.Ldr.   |");
    printf("\n-----------------------------------------------------------------------------------------------------------------");
    //organizar de forma crescente de tempo o vetor prova
    //colocar os não aprovados no final assim facilitando a amostra dos pilotos afrente a realizar
    for (int i = 0; i < nPilotos; i++)
    {

        for (int j = i + 1; j < nPilotos; j++)
        {

            if (prova[i].tempoProva > prova[j].tempoProva)
            {
                //existiu a necessidade de criar uam variavel do tipo aux para guardar os valores da posição i
                //visto que esta ia ser substituida por as informações da posição j
                auxNum = prova[i].piloto.num;
                auxTempo = prova[i].tempoProva;
                auxApr = prova[i].aprovado;
                strcpy(auxNome, prova[i].piloto.nome);
                strcpy(auxCarro, prova[i].piloto.carro);

                prova[i].piloto.num = prova[j].piloto.num;
                prova[i].tempoProva = prova[j].tempoProva;
                prova[i].aprovado = prova[j].aprovado;
                strcpy(prova[i].piloto.nome, prova[j].piloto.nome);
                strcpy(prova[i].piloto.carro, prova[j].piloto.carro);

                prova[j].piloto.num = auxNum;
                prova[j].tempoProva = auxTempo;
                prova[j].aprovado = auxApr;
                strcpy(prova[j].piloto.nome, auxNome);
                strcpy(prova[j].piloto.carro, auxCarro);
            }
        }
    }
    //percorrer o vetor prova todo apenas mostrando os aprovados
    for (int i = 0, a = 0; i < nPilotos; i++)
    {

        //caso seja um piloto aprovado
        if (prova[i].aprovado == 1)
        {
            //vamos transformar o tempo em minutos
            tempoMin = (prova[i].tempoProva / 1000) / 60;
            //transformar o tempo em segundos e milésimos
            tempoSec = ((float)prova[i].tempoProva / (float)1000) - (tempoMin * 60);

            //se for o primeiro colocado
            if (a == 0)
            {
                a++;
                //apenas colocar os ultimos valores a zeros
                printf("\n|\t%d\t|\t%d\t|%10s\t|%10s\t|    %2d:%.3f   |\t0\t |\t0\t|", a, prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro, tempoMin, tempoSec);
                //guardar o tempo do lider em ms
                tempoLdr = prova[i].tempoProva;
            }
            else
            {
                //a diferença de tempo para o lider é o o tempo do piloto subtraindo o tempo do lider
                diTempoLdr = prova[i].tempoProva - tempoLdr;
                //a dirença do anterior é retornando atrás e vendo o ultimo piloto lido
                diTempoAnt = prova[i].tempoProva - prova[i - 1].tempoProva;

                //caso os tempos sejam negativos é necessário colocar a zeros, caso não é necessário transformar em segundos e milesimos denovo
                if (diTempoLdr < 0)
                    diLdr = 0;
                else
                    diLdr = ((float)diTempoLdr / (float)1000);

                if (diTempoAnt < 0)
                    diAnt = 0;
                else
                    diAnt = ((float)diTempoAnt / (float)1000);
                a++;
                //mostrar as informações do piloto
                printf("\n|\t%d\t|\t%d\t|%10s\t|%10s\t|    %2d:%6.3f   |     %.3f\t |    %.3f\t|", a, prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro, tempoMin, tempoSec, diAnt, diLdr);
            }
        }
    }
    //percorrer o vetor prova todo apenas mostrando os não aprovados
    for (int i = 0; i < nPilotos; i++)
    {
        if (prova[i].aprovado == 0)
        {
            //informações dos pilotos que não fizeram a prova por completo
            printf("\n|\t-\t|\t%d\t| %10s\t| %10s\t|\t-\t |\t-\t |\t-\t|", prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro);
        }
    }

    printf("\n-----------------------------------------------------------------------------------------------------------------");
}

void menu(TEMPOS *tempos, PILOTO *pilotos, DISTANCIAS *distancias, PROVA *prova, int nTotal, int nPilotos, int nEtapas, int aprovados)
{
    int escolha, medTempos[2], pilotosAprv[aprovados], numExtremos[1], maiorNum, menorNum;
    printf("\n**************************************************");
    printf("\n** 1 - Numero de pilotos\t\t\t**");
    printf("\n** 2 - Numero de pilotos com prova valida\t**");
    printf("\n** 3 - Pilotos por tempo descendente validos\t**");
    printf("\n** 4 - Media tempos etapas validos\t\t**");
    printf("\n** 5 - Piloto mais rapido e mais lento\t\t**");
    printf("\n** 6 - Menor tempo possivel de realizar a prova\t**");
    printf("\n** 7 - Media de velocidades \t\t\t**");
    printf("\n** 8 - Tabela classificativa da prova\t\t**");
    printf("\n** 9 - Sair\t\t\t\t\t**");
    printf("\n**************************************************");
    printf("\n escolha: ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        printf("\nNumero de pilotos: %d", nPilotosCount() + 1);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 2:
        printf("\nExistem %d concorrentes com prova valida!", verificaProva(tempos, nTotal, pilotosAprv));
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 3:
        ordenaTemposDesc(prova, nPilotos, aprovados);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 4:
        verificaProva(tempos, nTotal, pilotosAprv);
        medTemposEtapa(tempos, nTotal, pilotosAprv, medTempos, aprovados);

        printf("\nMedia tempos entre Partida e Etapa1 : %d:%.3f", (medTempos[0] / 1000) / 60, ((float)medTempos[0] / (float)1000) - ((medTempos[0] / 1000) / 60) * 60);
        printf("\nMedia tempos entre Etapa2 e Etapa1 : %d:%.3f", (medTempos[1] / 1000) / 60, ((float)medTempos[1] / (float)1000) - ((medTempos[1] / 1000) / 60) * 60);
        printf("\nMedia tempos entre Etapa1 e Chegada : %d:%.3f", (medTempos[2] / 1000) / 60, ((float)medTempos[2] / (float)1000) - ((medTempos[2] / 1000) / 60) * 60);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 5:
        extremos(prova, nPilotos, numExtremos);
        maiorNum = numExtremos[0];
        menorNum = numExtremos[1];
        //apresentação das informaçoes dos valores obtidos
        printf("\nMais rapido:");
        printf("\n ->Numero: %d", prova[menorNum].piloto.num);
        printf("\n ->Nome: %s", prova[menorNum].piloto.nome);
        printf("\n ->Carro: %s", prova[menorNum].piloto.carro);
        printf("\n ->Tempo de Prova: %d:%.3f", (prova[menorNum].tempoProva / 1000) / 60, (((float)prova[menorNum].tempoProva / (float)1000) - ((prova[menorNum].tempoProva / 1000) / 60) * 60));
        printf("\nMais lento:");
        printf("\n ->Numero: %d", prova[maiorNum].piloto.num);
        printf("\n ->Nome: %s", prova[maiorNum].piloto.nome);
        printf("\n ->Carro: %s", prova[maiorNum].piloto.carro);
        printf("\n ->Tempo de Prova: %d:%.3f", (prova[maiorNum].tempoProva / 1000) / 60, (((float)prova[maiorNum].tempoProva / (float)1000) - ((prova[maiorNum].tempoProva / 1000) / 60) * 60));
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 6:
        extremos(prova, nPilotos, numExtremos);
        maiorNum = numExtremos[0];
        menorTempo(tempos, nTotal, prova[maiorNum].tempoProva);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 7:
        verificaProva(tempos, nTotal, pilotosAprv);
        medTemposEtapa(tempos, nTotal, pilotosAprv, medTempos, aprovados);
        velocidadesMedias(distancias, nEtapas, aprovados, medTempos);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 8:
        tabelaClassificativa(prova, nPilotos);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 9:
        return;
        break;
    default:
        printf("Opcao invalida");
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    }
    menu(tempos, pilotos, distancias, prova, nTotal, nPilotos, nEtapas, aprovados);
}

void main()
{
    int n[1], nTotal, nEtapas, nPilotos, aprovados;
    Etapas(n);

    //valores q estão no começo do ficheiro tempos.txt com as informações dos Pilotos e Etapas
    nEtapas = n[0];
    nPilotos = n[1];

    //o total de etapas que têm de estar registadas é o numero de etapas a multiplicar pelo
    //numero de pilotos que está no ficheiro
    nTotal = nEtapas * nPilotos;

    //carregamento dos tempos para o vetor da estrutura TEMPOS
    TEMPOS tempos[nTotal];
    loadTempos(tempos);

    //Carregamento das distancias das etapas para o vetor da estrutura DISTANCIAS
    DISTANCIAS distancias[nEtapas];
    loadDistancias(distancias);

    //carregamento das informações dos pilotos para o vetor da estrutura PILOTO
    nPilotos = nPilotosCount();
    PILOTO pilotos[nPilotos];
    loadPilotos(pilotos);

    PROVA prova[nPilotos];
    loadProva(prova, tempos, pilotos, nTotal, nPilotos);
    aprovados = loadVerificaProva(tempos, nTotal);
    menu(tempos, pilotos, distancias, prova, nTotal, nPilotos, nEtapas, aprovados);
}