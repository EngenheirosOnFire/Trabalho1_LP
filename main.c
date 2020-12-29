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
int verificaProva(TEMPOS *tempos, int n);                                                                                               //verificação de quantos pilotos têm prova valida
void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int n, int nPilotos);                                                      //carregamenteo das informações dos vários structs para um struct final contento informação da prova por completo
void ordenaTemposDesc(PROVA *prova, int nPilotos, int aprovados);                                                                       //ordenção e amostra dos tempos por ordem descendente
void medTemposEtapa(TEMPOS *tempos, int n, int aprovados);                                                                              //media de tempos por etapa
void extremos(PROVA *prova, int nPilotos);                                                                                              //Amostra do piloto mais rapido e mais lento
void menorTempo(TEMPOS *tempos, int nEtapas);                                                                                           //Amostra do menor tempo possivel para realizar a prova
void velocidadesMedias(PROVA *prova, DISTANCIAS *distancias, int nPilotos, int nEtapas, int aprovados);                                 //Amostra das velocidades medias da prova
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

int verificaProva(TEMPOS *tempos, int n)
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
        }
        //verificar se existem 3 etapas com o numero do piloto
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
    char auxNome[50], auxCarro[50];
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
                strcpy(provaOrdenado[i].piloto.nome, prova[j].piloto.nome);
                strcpy(provaOrdenado[i].piloto.carro, prova[j].piloto.carro);

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
        printf("\nNumero: %d\t| Nome: %s\t| Carro: %s\t| tempo: %d", provaOrdenado[i].piloto.num, provaOrdenado[i].piloto.nome, provaOrdenado[i].piloto.carro, provaOrdenado[i].tempoProva);
    }
}

void medTemposEtapa(TEMPOS *tempos, int n, int aprovados)
{
    int somaP_E1 = 0, mediaP_E1, somaE1_E2 = 0, mediaE1_E2, somaE2_C = 0, mediaE2_C, contador = 0, num;
    for (int i = 0; i <= n; i++)
    {
        contador++;
        for (int j = i; j <= n; j++)
        {
            //verificar se o piloto foi aprovado
            if (tempos[i].num == tempos[j].num)
                contador++;

            num = tempos[i].num; //guardar o numero do piloto
        }
        //se for um piloto aprovado
        if (contador == 3)
        {
            //verificar o vetor tempos por completo
            for (int t = 0; t <= n; t++)
            {
                //se o numero for igual ao numero do piloto aprovado ir buscar as informações do tempo
                if (tempos[t].num == num)
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
        contador = 0;
    }
    //media vai ser a soma dos tempos dividindo por o total de aprovados
    mediaP_E1 = somaP_E1 / aprovados;
    mediaE1_E2 = somaE1_E2 / aprovados;
    mediaE2_C = somaE2_C / aprovados;
    //apresentação das medias
    printf("\nMedia tempos entre Partida e Etapa1 : %d", mediaP_E1);
    printf("\nMedia tempos entre Etapa2 e Etapa1 : %d", mediaE1_E2);
    printf("\nMedia tempos entre Etapa1 e Chegada : %d", mediaE2_C);
}

void extremos(PROVA *prova, int nPilotos)
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
    //apresentação das informaçoes dos valores obtidos
    printf("\nMais rapido:");
    printf("\n ->Numero: %d", prova[menorNum].piloto.num);
    printf("\n ->Nome: %s", prova[menorNum].piloto.nome);
    printf("\n ->Carro: %s", prova[menorNum].piloto.carro);
    printf("\n ->Tempo de Prova: %d ms", prova[menorNum].tempoProva);
    printf("\nMais lento:");
    printf("\n ->Numero: %d", prova[maiorNum].piloto.num);
    printf("\n ->Nome: %s", prova[maiorNum].piloto.nome);
    printf("\n ->Carro: %s", prova[maiorNum].piloto.carro);
    printf("\n ->Tempo de Prova: %d ms", prova[maiorNum].tempoProva);
}

void menorTempo(TEMPOS *tempos, int nEtapas)
{
    int menorP_E1 = tempos[0].tempo, menorE1_E2 = tempos[0].tempo, menorE2_C = tempos[0].tempo, menor;
    for (int i = 0; i <= nEtapas; i++)
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
        else
        {
            if ((tempos[i].tempo < menorE2_C) && (tempos[i].tempo != 0))
            {
                menorE2_C = tempos[i].tempo;
            }
        }
    }
    menor = menorP_E1 + menorE1_E2 + menorE2_C;
    printf("\nMenores tempo possivel:%d ms", menor);
}

void velocidadesMedias(PROVA *prova, DISTANCIAS *distancias, int nPilotos, int nEtapas, int aprovados)
{
    float tempoSec, distanciaP_E1, distanciaE1_E2, distanciaE2_C, velocidade = 0, distancia, medias[aprovados], aux;

    for (int i = 0; i < nEtapas; i++)
    {
        if ((strcmp(distancias[i].etapaI, "P") == 0) && (strcmp(distancias[i].etapaF, "E1") == 0))
        {
            distanciaP_E1 = distancias[i].distancia;
        }
        else if ((strcmp(distancias[i].etapaI, "E1") == 0) && (strcmp(distancias[i].etapaF, "E2") == 0))
        {
            distanciaE1_E2 = distancias[i].distancia;
        }
        else
        {
            distanciaE2_C = distancias[i].distancia;
        }
    }

    distancia = distanciaP_E1 + distanciaE1_E2 + distanciaE2_C;

    for (int i = 0, a = 0; i <= nPilotos; i++)
    {
        if (prova[i].aprovado == 1)
        {
            tempoSec = prova[i].tempoProva * 0.001;
            velocidade = (distancia / tempoSec); //m/s
            medias[a] = velocidade;
            a++;
        }
    }
    for (int i = 0; i < aprovados; i++)
    {
        for (int j = i + 1; j < aprovados; j++)
        {
            if (medias[j] < medias[i])
            {
                aux = medias[i];
                medias[i] = medias[j];
                medias[j] = aux;
            }
        }
    }
    for (int i = 0; i < aprovados; i++)
    {
        printf("\nVelocidade media: %.2f m/s", medias[i]);
    }
}

void menu(TEMPOS *tempos, PILOTO *pilotos, DISTANCIAS *distancias, PROVA *prova, int nTotal, int nPilotos, int nEtapas, int aprovados)
{
    int escolha;
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
    if (escolha != 9)
    {
        switch (escolha)
        {
        case 1:
            printf("\nNumero de pilotos: %d", nPilotosCount() + 1);
            fflush(stdin);
            printf("\n(Enter)");
            getchar();
            break;
        case 2:
            printf("\nExistem %d concorrentes com prova valida!", verificaProva(tempos, nTotal));
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
            medTemposEtapa(tempos, nTotal, aprovados);
            fflush(stdin);
            printf("\n(Enter)");
            getchar();
            break;
        case 5:
            extremos(prova, nPilotos);
            fflush(stdin);
            printf("\n(Enter)");
            getchar();
            break;
        case 6:
            menorTempo(tempos, nEtapas);
            fflush(stdin);
            printf("\n(Enter)");
            getchar();
            break;
        case 7:
            velocidadesMedias(prova, distancias, nPilotos, nEtapas, aprovados);
            fflush(stdin);
            printf("\n(Enter)");
            getchar();
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
    else
    {
        return;
    }
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
    aprovados = verificaProva(tempos, nTotal);
    menu(tempos, pilotos, distancias, prova, nTotal, nPilotos, nEtapas, aprovados);
}