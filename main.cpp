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

///Estrutura que guarda informações sobre os pilotos
///@param num ➔ Número do piloto
///@param nome ➔ Nome do piloto
///@param carro ➔ Carro do piloto
typedef struct infoPiloto
{
    ///Esta variavel indica o numero do piloto
    int num;
    ///Esta variavel guarda o nome do piloto
    ///@note Foi dado aos vetores nome e carro tamanho 50 para assim ser possivel colocar qualquer tamanho de nomes nos mesmos
    char nome[50];
    ///Esta variavel guarda o carro do piloto
    ///@note Foi dado aos vetores nome e carro tamanho 50 para assim ser possivel colocar qualquer tamanho de nomes nos mesmos
    char carro[50];
} PILOTO;

///Estrutura que guarda informações de toda a prova
///@param piloto ➔ Variável que guarda as informações dos pilotos
///@param tempoProva ➔ Tempo total de prova
///@param aprovado ➔ Variavél que guarda se o piloto está aprovado ou não
typedef struct infoProva
{
    ///Variável do tipo **PILOTO**, esta variável vai conter todas as informações do piloto, pois é do tipo **struct infoPiloto**
    ///@see infoPiloto
    PILOTO piloto;
    ///Variável do tipo inteiro para guardar o tempo total de prova
    ///@note É do tipo **long int** pois o numero pode ficar grande demais para a liguagem pois c tem um limite maximo de numero
    long int tempoProva;
    ///Variável do tipo int para guardar se o piltoo foi aprovado ou não
    ///@note **aprovado** varia entre 0 e 1,(0➔reprovado,1➔aprovado)
    int aprovado;
} PROVA;

///Estrutura que guarda os nomes das etapas todas
///@param etapaNome ➔ Variável que guarda o nome das etapas
typedef struct infoEtapas
{
    ///Variável do tipo char para guardar o nome das etapas
    ///@note O tamanho é 3 pois precisa de guardar 'E' '1' e '\0' logo tem de ter 4 espaços reservados e não apenas 3
    char etapaNome[3]; //Etapa inicial
} ETAPAS;

///Estrutura que guarda informações de tempos de toda a prova
///@param num ➔ Variável que guarda o numero referente ao numero do piloto
///@param tempo ➔ Tempo que o piloto demorou a realizar a etapa
///@param etapaI ➔ Variável que guarda o nome da etapa inical
///@param etapaF ➔ Variável que guarda o nome da etapa final
///@note Os tempos são dados de acordo com (E1;E2) daí ter etapa inicial e etapa final
typedef struct infoTempos
{
    ///Variável que guarda o numero do piloto que realizou esta etapa
    int num;
    ///Variável que guarda o tempo que o piloto demorou a realizar esta etapa
    long int tempo;
    ///Variável que guarda a etapa inicial
    char etapaI[3]; //Etapa inicial
    ///Variável que guarda a etapa final
    char etapaF[3]; //Etapa Final
} TEMPOS;

///Estrutura que guarda informações das distancias da prova
///@param etapaI ➔ Variável que guarda o nome da etapa inical
///@param etapaF ➔ Variável que guarda o nome da etapa final
///@param distancia ➔ Variável que guarda a distancia da etapa
///@note os tempos são dados de acordo com (E1;E2) daí ter etapa inicial e etapa final
typedef struct infoDistancias
{
    ///Variável que guarda a etapa inicial
    char etapaI[3]; //Etapa inicial
    ///Variável que guarda a etapa final
    char etapaF[3]; //Etapa Final
    ///Variável do tipo **float** pois é necessário guardar os centimetros também, não só os metros como inteiro
    float distancia;
} DISTANCIAS;

void Etapas(int *n, char *nomeProva);                                                                                    //função que retira os valores no começo do ficheiro de tempos.txt e guarda em duas posições do vetor n, sendo n[0]<-nEtapas,n[1]<-nPilotos
void loadTempos(TEMPOS *etapa, char *nomeProva);                                                                         //carregamento das informações do ficheiro tempos.txt para uma estrutura que guarda os tempos, saltando os valores iniciais a frente
void loadDistancias(DISTANCIAS *distancias, char *nomeProva);                                                            //carregamento das informações do distancias.txt para o struck DISTANCIAS
void loadPilotos(PILOTO *piloto, char *nomeProva);                                                                       //carregamento das informações ds pilotos.txt para o struct PILoTOS
void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int n, int nPilotos, int nEtapa);                           //carregamenteo das informações dos vários structs para um struct final contento informação da prova por completo
int nPilotosCount(char *nomeProva);                                                                                      //contagem de pilotos contidos no ficheiro pilotos.txt
void verificaProva(TEMPOS *tempos, int n, int *aprovados, int nEtapas);                                                  //verificação de quantos pilotos têm prova valida
void ordenaTemposDesc(PROVA *prova, int nPilotos, int aprovados);                                                        //ordenção e amostra dos tempos por ordem descendente
void medTemposEtapa(TEMPOS *tempos, ETAPAS *etapas, int n, int *aprovados, int *medTempos, int nAprovados, int nEtapas); //media de tempos por etapa
void extremos(PROVA *prova, int nPilotos, int *tempoExtremos);                                                           //Amostra do piloto mais rapido e mais lento
void menorTempo(TEMPOS *tempos, ETAPAS *etapas, int nTotal, int maior, int nEtapas);                                     //Amostra do menor tempo possivel para realizar a prova
void velocidadesMedias(DISTANCIAS *distancias, ETAPAS *etapas, int nEtapas, int *medTempos);                             //Amostra das velocidades medias da prova
void loadTudo(char *nomeProva);
void menu(TEMPOS *tempos, PILOTO *pilotos, DISTANCIAS *distancias, PROVA *prova, ETAPAS *etapas, int nTotal, int nPilotos, int nEtapas, int aprovados, char *nomeProva); //Menu principal do programa

///Esta função organiza o vetor distancias
/**   
 * @brief Esta função coloca primeiramente a etapa partida na primeira posição do vetor ou seja a posição 0 para depois organizar o restante vetor.
 * @brief Para organizar o restante vetor é retirado momentaneamente de cada etapa iniciada por 'E' o caracter 'E' para assim organizar por números de etapa
 * @brief Existiu a necessidade de criar variáveis auxiliares para guardar os valores contidos numa das posições do vetor, neste caso do i pois os valores de i vão ser substituídos pelos de j perdendo assim os valores
 * @param distancias ➔ Variável do tipo DISTANCIAS que é um apontador para o vetor distancias que contém todas as distâncias da prova
 * @param nEtapas ➔ Variável do tipo inteiro que recebe o número de etapas
 * @param auxDist ➔ Variável auxiliar para guardar a distância
 * @param auxEtapaI ➔ Variável auxiliar para guardar o nome da etapa inicial
 * @param auxEtapaF ➔ Variável auxiliar para guardar o nome da etapa inicial
 * @see infoDistancias
 */
void arrumarVetor(DISTANCIAS *distancias, int nEtapas)
{
    int auxDist;
    char auxEtapaI[3], auxEtapaF[3];
    for (int i = 0; i < nEtapas; i++)
    {
        if (i != 0 && strcmp(distancias[i].etapaI, "P") == 0)
        {
            auxDist = distancias[i].distancia;
            strcpy(auxEtapaI, distancias[i].etapaI);
            strcpy(auxEtapaF, distancias[i].etapaF);

            strcpy(distancias[i].etapaI, distancias[0].etapaI);
            strcpy(distancias[i].etapaF, distancias[0].etapaF);
            distancias[i].distancia = distancias[0].distancia;

            strcpy(distancias[0].etapaI, auxEtapaI);
            strcpy(distancias[0].etapaF, auxEtapaF);
            distancias[0].distancia = auxDist;
        }
    }
    for (int i = 0; i < nEtapas; i++)
    {
        char ch[] = "E";
        char *ptr = strtok(distancias[i].etapaI, ch);
        for (int j = 0; j < nEtapas; j++)
        {
            char ch1[] = "E";
            char *ptr1 = strtok(distancias[i].etapaI, ch1);
            if (ptr > ptr1)
            {
                strcpy(auxEtapaI, distancias[i].etapaI);
                strcpy(auxEtapaF, distancias[i].etapaF);
                auxDist = distancias[i].distancia;

                strcpy(distancias[i].etapaI, distancias[j].etapaI);
                strcpy(distancias[i].etapaF, distancias[j].etapaF);
                distancias[i].distancia = distancias[j].distancia;

                strcpy(distancias[j].etapaI, auxEtapaI);
                strcpy(distancias[j].etapaF, auxEtapaF);
                distancias[j].distancia = auxDist;
            }
        }
    }
}

///Esta função le apenas a primeira linha do ficheiro etapas
/**
 * @brief Esta função lê apenas a primeira linha do ficheiro tempos, a primeira linha do ficheiro tempos contem as informações da quantidade de etapas
 *  e de pilotos presentes no ficheiro
 * @brief Esta função tem um apontador para o vetor N que vai guardar na posição 0 a quantidade de etapas e na posição 1 a quantidade de pilotos
 * @brief Para a leitura do ficheiro foi criado um apontador do tipo file para o ficheiro, de seguida foi atribuido a este apontador a abertura do ficheiro 
 * tempos e assim aberto o ficheiro tempos
 * @brief Para ler foi efetuado um fscanf e lido apenas um linha, e guardado no vetor N os valores lidos
 * @param n ➔ Variável do tipo inteiro que é apontador para o vetor n 
 * @param nomeProva ➔ Variável do tipo char apontador para o vetor que contém o nome da prova
 * @param f ➔ Variável do tipo FILE que é apontador para o ficheiro tempos.txt
 * @param prova ➔ Vetor que vai receber e juntar o nome da prova e o nome do ficheiro para assim obter o caminho para o ficheiro corretamente e é depois utilizada na função fopen
 */
void Etapas(int *n, char *nomeProva)
{
    FILE *f;
    char prova[30];
    strcpy(prova, nomeProva);
    strcat(prova, "/tempos.txt");

    if (f = fopen(prova, "r"))
    {
        fscanf(f, "%d;%d\n", &n[0], &n[1]);
        fclose(f);
    }
    else
    {
        fflush(stdin);
        printf("\nFicheiro nao existe!");
        printf("\nIntroduza o nome da pasta da prova: ");
        scanf("%s", prova);
        loadTudo(prova);
    }
}

///Esta função le o ficheiro tempos e coloca os valores no vetor tempos
/**
 * @brief Esta função contem um apontador para um ficheiro, este apontador é depois igualado à abertura do ficheiro tempos.txt,
 * para efetuar a leitura apenas dos valores que são importantes a primeira linha terá de ser ignorada, para isso é utilizada a
 * função fseek para "saltar" a primeira linha
 * @brief Após ignorar a primeira linha vai ser efetuada a leitura do restante do ficheiro e guardadas as informações nos parâmetros do tempo
 * até chegar ao fim do ficheiro (EOF), utilizando a função fscanf facilmente se deteta EOF, pois a função quando chega ao fim do ficheiro devolve EOF
 * @brief Para a leitura do ficheiro foi criado um apontador do tipo file para o ficheiro, de seguida foi atribuido a este apontador
 * a abertura do ficheiro tempos e assim aberto o ficheiro tempos
 * @param tempos ➔ Variável do tipo TEMPOS que é um apontador para o vetor tempos para assim ser possivel atribuir valores ao vetor tempos
 * @param nomeProva ➔ Variável do tipo char que é um apontador para o vetor nomeProva que contém o nome da prova a abrir
 * @param f ➔ Variável do tipo ficheiro que é um apontador
 * @param res ➔ Variável do tipo inteiro que guarda o valor devolvido pela função fsanf
 * @param i ➔ Variável do tipo inteiro que vai efetuar a contagem dos ciclos do while
 * @param prova ➔ Variável que vai receber o caminho do ficheiro tempos.txt
 * @see infoTempos

 */
void loadTempos(TEMPOS *tempos, char *nomeProva)
{

    FILE *f;
    int res, i = 0;
    char prova[30];
    strcpy(prova, nomeProva);
    strcat(prova, "/tempos.txt");

    if (f = fopen(prova, "r"))
    {
        fseek(f, sizeof(int), SEEK_SET); //saltar a primeira linha a frente
        //enquanto tiver o que ler, vai ler
        while (res != EOF)
        {
            res = fscanf(f, "%d;%[^;];%[^;];%d\n", &tempos[i].num, tempos[i].etapaI, tempos[i].etapaF, &tempos[i].tempo);
            i++;
        }
        fclose(f);
    }
    else
    {
        fflush(stdin);
        printf("\nFicheiro nao existe!");
        printf("\nIntroduza o nome da pasta da prova: ");
        scanf("%s", prova);
        loadTudo(prova);
    }
}

///Esta função le o ficheiro distancias e coloca os valores no vetor distancias
/**
 * @brief Esta função efetua a abertura do ficheiro distancias.txt e efetua um ciclo while que percorre o ficheiro todo e guarda os valores no vetor distancias
 * @param distancias ➔ Variável do tipo DISTANCIAS que é um apontador que recebe o vetor distancia para serem colocados os valores no mesmo
 * @param nomeProva ➔ Variável do tipo char que contém o nome da prova a abrir
 * @param res ➔ Variável do tipo inteiro que guarda o valor devolvido pela função fscanf
 * @param i ➔ Variável do tipo inteiro que conta o número de ciclos que o ciclo while usa, esta variável é utilizada para saber a posição do vetor colocar a informação lida
 * @param prova ➔ Variável do tipo char que recebe o caminho para o ficheiro distancias.txt que é depois utilizada na função fopen
 * @param f ➔ Variável do tipo FILE que é um apontador e mais tarde vai ser atribuído a função fopen
 * @see infoDistancias
 */
void loadDistancias(DISTANCIAS *distancias, char *nomeProva)
{
    FILE *f;
    int res, i = 0;
    char prova[30];
    strcpy(prova, nomeProva);
    strcat(prova, "/distancias.txt");

    if (f = fopen(prova, "r"))
    {
        //enquanto tiver o que ler, vai ler
        while (res != EOF)
        {
            res = fscanf(f, "%[^;];%[^;];%f\n", distancias[i].etapaI, distancias[i].etapaF, &distancias[i].distancia);
            i++;
        }
        fclose(f);
    }
    else
    {
        fflush(stdin);
        printf("\nFicheiro nao existe!");
        printf("\nIntroduza o nome da pasta da prova: ");
        scanf("%s", prova);
        loadTudo(prova);
    }
}

///Esta função le o ficheiro pilotos.txt e coloca os valores no vetor piloto
/**
* @brief Esta função efetua a abertura do ficheiro pilotos.txt e efetua um ciclo while que percorre o ficheiro todo e guarda os valores no vetor pilotos
* @param piloto ➔ Variável do tipo PILOTO que é um apontador que recebe o vetor pilotos para serem colocador as informações dos pilotos no mesmo
* @param nomeProva ➔ Variável do tipo char que contém o nome da prova a abrir
* @param res ➔ Variável do tipo inteiro que guarda o valor devolvido pela função fscanf
* @param i ➔ Variável do tipo inteiro que conta o número de ciclos que o ciclo while usa, esta variável é utilizada para saber a posição do vetor colocar a informação lida
* @param prova ➔ Variável do tipo char que recebe o caminho para o ficheiro distancias.txt que é depois utilizada na função fopen
* @param f ➔ Variável do tipo FILE que é um apontador e mais tarde vai ser atribuído a função fopen
* @see infoPiloto
*/
void loadPilotos(PILOTO *piloto, char *nomeProva)
{
    FILE *f;
    int res, i = 0;
    char prova[30];
    strcpy(prova, nomeProva);
    strcat(prova, "/pilotos.txt");

    if (f = fopen(prova, "r"))
    {
        //enquanto tiver o que ler, vai ler
        while (res != EOF)
        {
            res = fscanf(f, "%d;%[^;];%[^\n]\n", &piloto[i].num, piloto[i].nome, piloto[i].carro);
            i++;
        }
        fclose(f);
    }
    else
    {
        fflush(stdin);
        printf("\nFicheiro nao existe!");
        printf("\nIntroduza o nome da pasta da prova: ");
        scanf("%s", prova);
        loadTudo(prova);
    }
}

///Esta função coloca os valores dos vetores anteriores num vetor final
/**
 * @brief Esta função recebe os vetores prova, tempos e pilotos para colocar os seus valores num vetor final
 * @brief A função prova tem dentro da mesma um ciclo for que serve para percorrer todos os pilotos e colocar as informações dos mesmos no vetor prova
 * e para obter o tempo total de prova foi então criado outro ciclo for que procura por o número do piloto atual no vetor tempos e efetua o somatório
 * do tempo do piloto sempre que encontra uma correspondência e por fim coloca o somatório no parametro tempoTotal do vetor
 * @param prova ➔ Variável do tipo PROVA que recebe o vetor prova para o mesmo receber os valores dos outros vetores
 * @param tempos ➔ Variável do tipo TEMPOS que recebe o vetor tempos para aproveitar as informações dos tempos
 * @param piloto ➔ Variável do tipo PILOTOS que recebe o vetor pilotos para aproveitar as informações dos pilotos
 * @param nTotal ➔ Variável do tipo inteiro que recebe o total de tempos a ler
 * @param nPilotos ➔ Variável do tipo inteiro que recebe o número de pilotos inscritos na prova
 * @param nEtapas ➔ Variável do tipo inteiro que recebe o número total de etapas existentes na prova
 * @see infoProva, infoTempos, infoPiloto
 */
void loadProva(PROVA *prova, TEMPOS *tempos, PILOTO *piloto, int nTotal, int nPilotos, int nEtapas)
{

    for (int i = 0; i <= nPilotos; i++)
    {

        int tempoTotal = 0, contador = 0;
        prova[i].piloto.num = piloto[i].num;

        for (int j = 0; j <= nTotal; j++)
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

        if (contador == nEtapas)
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

///Esta função le o ficheiro pilotos.txt e conta o numero de linhas
/**
 * @brief Como cada linha no ficheiro pilotos.txt equivale a um piloto, então para se obter o número total de pilotos na prova
 * basta efetuar a contagem no número de linhas no ficheiro.
 * @brief Para efetuar a contagem do número de linhas foi efetuado um ciclo for que percorre o ficheiro todo até encontrar EOF (end of file)
 * este ciclo faz uso da função getc para ler todos os caracters, sempre que o caracter lido fosse "\n" new line, significa que existe mais uma linha
 * obtendo assim o número de linhas
 * @param nomeProva ➔ Apontador para o nome da prova
 * @param f ➔ Apontador do tipo ficheiro que vai ser utilizado para efetuar a abertura do ficheiro pilotos.txt
 * @param contador ➔ Variável do tipo int que sempre que se encontra o caracter "\n" se incrementa por 1
 * @param c ➔ Variável do tipo char que vai lhe ser atribuido os caracters a ler
 * @param prova ➔ Variável do tipo char que vai ser utilizada para juntamente com a varaivel nomeProva obter o caminho para o ficheiro pilotos.txt
 * @returns Número de linhas contadas pelo parametro contador
 */
int nPilotosCount(char *nomeProva)
{
    FILE *f;
    int contador = 1; //pois sempre irá existir pelomenos um piloto
    char c;
    char prova[30];
    strcpy(prova, nomeProva);
    strcat(prova, "/pilotos.txt");

    if (f = fopen(prova, "r"))
    {
        //verificar todos os caracteres até encontrar '\n', sempre que '\n' for encontrado é contado mais um piloto pois existe 1 piloto por linha
        for (c = getc(f); c != EOF; c = getc(f))
        {
            if (c == '\n')
                contador++;
        }
        fclose(f);
    }
    else
    {
        fflush(stdin);
        printf("\nFicheiro nao existe!");
        printf("\nIntroduza o nome da pasta da prova: ");
        scanf("%s", prova);
        loadTudo(prova);
    }
    return contador;
}

///Esta função vai efetuar a verificação dos pilotos aprovados
/**
 * @brief Esta função percorre o vetor tempos por completo e verifica se um piloto aparece tantas vezes quantas etapas existem
 * @brief Para efetuar esta verificação foram efetuados dois ciclos for, o primeiro for serviria para obter um numero de piloto a comparar com o restante do vetor
 * e o segundo vetor serviria para percorrer o restante do vetor e caso fosse encontrado um piloto com o mesmo, a variável contador(que contém a contagem de vezes que o piloto aparece)
 * vai ser incrementada por 1.
 * @brief No fim do segundo ciclo for é verificado se a variável contador contou tantos pilotos quantas provas existem, aprovando ou não assim o piloto
 * @param tempos ➔ Apontador do tipo TEMPOS para o vetor tempos, para assim obter acesso ao vetor tempos
 * @param nTotal ➔ Variável do tipo inteiro que contém o número total de valores ler
 * @param aprovados ➔ Apontador do tipo inteiro para o vetor aprovados para assim ficar registado em um vetor os pilotos aprovados
 * @param nEtapas ➔ Variável do tipo inteiro que contém o número de etapas existentes na prova
 * @param contador ➔ Variável do tipo inteiro cujo objetivo é contar o número de vezes que um piloto está em um vetor
 * @see infoTempos
 */
void verificaProva(TEMPOS *tempos, int nTotal, int *aprovados, int nEtapas)
{
    int contador = 0;        //conta numero de vezes que numero aparece
    int contadorPilotos = 0; //conta o numero de pilotos aprovados
    for (int i = 0, a = 0; i <= nTotal; i++)
    {
        contador++;
        for (int j = i + 1; j <= nTotal; j++)
        {
            if (tempos[i].num == tempos[j].num)
                contador++;
        }
        //verificar se existem 3 etapas com o numero do piloto
        if (contador == nEtapas)
        {
            aprovados[a] = tempos[i].num; //colocar o numero do piloto aprovado num vetor
            a++;
        }
        contador = 0;
    }
}

///Esta fnção vai efetuar a verificação dos pilotos aprovados
/**
 * @brief Esta função percorre o vetor tempos por completo e verifica se um piloto aparece tantas vezes quantas etapas existem
 * @brief Para efetuar esta verificação foram efetuados dois ciclos for, o primeiro for serviria para obter um numero de piloto a comparar com o restante do vetor
 * e o segundo vetor serviria para percorrer o restante do vetor e caso fosse encontrado um piloto com o mesmo, a variável contador (que contém a contagem de vezes que o piloto aparece)
 * vai ser incrementada por 1.
 * @brief No fim do segundo ciclo for é verificado se a variável contador contou tantos pilotos quantas provas existem, aprovando ou não assim o piloto
 * @param tempos ➔ Apontador do tipo TEMPOS para o vetor tempos, para assim obter acesso ao vetor tempos
 * @param nTotal ➔ Variável do tipo inteiro que contém o número total de valores ler
 * @param aprovados ➔ Apontador do tipo inteiro para o vetor aprovados para assim ficar registado em um vetor os pilotos aprovados
 * @param nEtapas ➔ Variável do tipo inteiro que contém o número de etapas existentes na prova
 * @param contador ➔ Variável do tipo inteiro cujo objetivo é contar o número de vezes que um piloto está em um vetor
 * @param contadorPilotos ➔ Variável do tipo inteiro cujo objetivo é contar o número de pilotos aprovados
 * @returns Contagem de pilotos aprovados contados pela variável contadorPilotos
 * @see infoTempos

 */
int loadVerificaProva(TEMPOS *tempos, int n, int nEtapas)
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
        if (contador == nEtapas)
        {
            contadorPilotos++; //contar mais um piloto
        }
        contador = 0;
    }
    return contadorPilotos;
}

///Esta função ordena o vetor prova por ordem descendente de tempo e mostra ao utilizador
/**
 * @brief Esta função primeiramente para não criar conflitos com o vetor original e também para o vetor apenas conter pilotos aprovados
 * é realizada a cópia do vetor prova por completo para outro vetor que tem de tamanho a quantidade de pilotos aprovados
 * @brief Para organizar o vetor são realizados dois ciclos for, o primeiro obtém um tempo e o segundo compara esse tempo com o restante do vetor e sempre que encontra um
 * tempo maior, estes trocam de lugar para assim organizar o vetor do maior tempo de prova para o menor tempo
 * @brief Por fim para mostrar ao utilizador o vetor ordenado de forma descendente é realizado um ciclo for que percorre o vetor por completo, converte o tempo de milésimos para
 * minutos e segundos e ainda mostra as informações para o utilizador
 * @param prova ➔ Apontador do tipo PROVA para o vetor prova, para assim ser possível aceder ao vetor
 * @param nPilotos ➔ Variável do tipo inteiro que recebe o número de pilotos em prova
 * @param aprovados ➔ Variável do tipo inteiro que recebe a quantidade de pilotos aprovados para assim o vetor cópia do vetor provas apenas ter o tamanho dos pilotos aprovados
 * @param auxNum ➔ Variável que serve como auxiliar na troca de valores no vetor, guardando o numero do piloto de uma das posições
 * @param auxTempo ➔ Variável que serve como auxiliar na troca de valores no vetor, guardando o tempo de uma das posições
 * @param auxApr ➔ Variável que serve como auxiliar na troca de valores no vetor, guardando a aprovação de cada pessoa
 * @param auxNome ➔ Variável que serve como auxiliar na troca de valores no vetor, guardando o nome do piloto de uma das posições
 * @param auxCarro ➔ Variável que serve como auxiliar na troca de valores no vetor, guardando o nome do carro de uma das posições
 * @param a ➔ Variável do tipo inteiro que serve como contador auxiliar do vetor copia pois ao percorrer o vetor original caso não existam 2 pilotos seguidos aprovados o vetor a receber não pode
 * avançar também duas posições fazendo assim este contador incrementar por 1 a cada vez que o vetor é modificado
 * @param tempoMin ➔ Variável do tipo inteiro que vai receber o tempo em minutos da sua conversão
 * @see infoProva
 */
void ordenaTemposDesc(PROVA *prova, int nPilotos, int aprovados)
{
    int auxNum = 0, auxTempo = 0, auxApr = 0, a = 0;
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

///Esta função efetua a media dos tempos por prova
/**
 * @brief Esta função primeiramente para organizar os somatórios foi criado um vetor chamado soma que vai ser inicialmente igualado a 0, este vetor está organizado
 * sendo a primeira linha a etapa P e o restante visto que a função arrumarVetor
 * @brief São então criados dois ciclos for um ciclo para percorrer o vetor tempos e outro para percorrer o vetor aprovados, verificando então se o piloto estava no conjunto 
 * de pilotos aprovados ou não
 * @brief Após esta ação é verificado ainda dentro do segundo ciclo for se se está perante a primeira etapa, pois a primeira etapa estará sempre guardada na posição 0 do vetor soma de acordo com a organização previamente esquematizada
 * @brief Após a obtenção dos valores no vetor soma, são calculadas as médias, ou seja a soma total a dividir pela quantidade total de pilotos aprovados
 * @brief Após a verificação caso esteja perante a primeira etapa é então guardado o tempo na primeira etapa, caso contrário é guardado em outra posição do vetor pois o vetor etapas já está organizado de acordo com as etapas da prova
 * @param tempos ➔ Apontador do tipo TEMPOS que vai receber o vetor tempos
 * @param etapas ➔ Apontador do tipo ETAPAS que vai receber o vetor etapas
 * @param n ➔ Variável do tipo inteiro que recebe o número total de tempos a ler no vetor tempos
 * @param aprovados ➔ Apontador tipo inteiro que vai receber o vetor aprovados para assim ter acesso ao número dos pilotos aprovados
 * @param medTempos ➔ Apontador do tipo inteiro que vai receber o vetor medTempos para assim ser possível alterar o vetor fora da função
 * @param nAprovados ➔ Variável do tipo inteiro que recebe a quantidade de pilotos aprovados
 * @param nEtapas ➔ Variável do tipo inteiro que recebe a quantidade de etapas na prova
 * @param soma ➔ Variável do tipo double que é um vetor cujo objetivo é guardar organizadamente os valores da soma total de tempos
 * @param media ➔ Variável do tipo double que é um vetor cujo objetivo é guardar organizademente as medias de tempos da partida
 * @see infoTempos,infoEtapas
 */
void medTemposEtapa(TEMPOS *tempos, ETAPAS *etapas, int n, int *aprovados, int *medTempos, int nAprovados, int nEtapas)
{
    double soma[nEtapas], media[nEtapas];
    for (int i = 0; i <= nEtapas; i++)
    {
        soma[i] = 0;
    }
    //verificar o vetor tempos por completo
    for (int t = 0; t <= n; t++)
    {
        for (int j = 0; j <= nAprovados; j++)
        {
            //se o numero for igual ao numero do piloto aprovado ir buscar as informações do tempo
            if (tempos[t].num == aprovados[j])
            {

                if ((strcmp(tempos[t].etapaI, "P") == 0))
                {
                    soma[0] += tempos[t].tempo;
                }
                else
                {
                    for (int h = 0; h <= nEtapas; h++)
                    {
                        if ((strcmp(tempos[t].etapaI, etapas[h].etapaNome) == 0))
                        {

                            soma[h] += tempos[t].tempo;
                        }
                    }
                }
            }
        }
    }
    //media vai ser a soma dos tempos dividindo por o total de aprovados
    //mediaP_E1 = somaP_E1 / nAprovados;
    for (int i = 0; i <= nEtapas; i++)
    {
        medTempos[i] = soma[i] / nAprovados;
    }
}

///Esta função vai calcular o menor e maior tempo registado na prova
/**
 * @brief Primeiramente as variaveis menor e maior são igualadas aos tempos da posição 0 do vetor pois a sua primeira posição vai ser 
 * o maior e menor tempos lidos até ao momento
 * @brief Após as variáveis obterem valores para comparar é realizado um ciclo for que percorre todo o vetor prova e verifica se o piloto
 * foi aprovado e se o tempo lido é menor ou se é maior que o menor e maior tempos lidos, caso sejam os valores são alterados para os atuais
 * , e os números dos pilotos são guardados também, para assim ser possível verificar as informações dos pilotos fora da função
 * @brief Após se obter o maior e menor tempos, os números desses pilotos são guardados no vetor temposExtremos pois é um apontador e assim é possível
 * aceder a estes valores externamente pois se está a alterar um vetor externo
 * @param prova ➔ Apontador do tipo PROVA que recebe o vetor prova
 * @param nPilotos ➔ Variável do tipo inteiro que recebe o número total de pilotos inscritos na prova
 * @param temposExtremos ➔ Apontador do tipo inteiro que recebe o vetor numExtremos no qual se vai colocar o número dos pilotos
 * @param menor ➔ Variável do tipo inteiro que vai guardar o menor tempo lido
 * @param maior ➔ Variável do tipo inteiro que vai guardar o menor tempo lido
 * @param menorNum ➔ Variável do tipo inteiro que vai receber o número do piloto com o menor tempo registado
 * @param maiorNum ➔ Variável do tipo inteiro que vai recber o número do piltoos com o maior tempo registado
 * @see infoProva
 */
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

///Esta função vai encontrar o menor tempo que é possivel realizar a prova e as diversas etapas
/**
 * @brief Esta função vai primeiramente colocar em todas as posições do vetor menores com os maiores tempos lidos na função extremos
 * @brief Após colocar valores em todas as posições deste vetor, foram criados dois ciclos for que vai percorrer os vetores tempos e etapas, o
 * primeiro ciclo percorre o
 * vetor tempos e encontra tempos para comparar com o vetor etapas que é percorrido no segundo ciclo for e sempre que se encontra uma etapa igual á
 * etapa do vetor tempos verifica-se se o tempo é menor que o menor tempo lido até ao momento,
 * caso seja, o vetor de menores tempos lidos guarda esse valor no local o qual foi encontrado no vetor etapas, pois o vetor etapas está organizado
 * por etapa fazendo assim com que o vetor que guarda os menores números também esteja organizado
 * @brief Após guardar os valores no vetor o mesmo é convertido para minutos e segundos e visto que estava organizado foram criados mais dois vetores, um para guardar
 * os minutos e outro para guardar os segundos, ou seja o menor tempo na posição 0 estaria em minutos na posição 0 do vetor minutos e na posição 0 do vetor segundos
 * @brief É também efetuada a conversão do menor tempo lido em toda a prova que resulta do somatório do menor tempo de cada etapa
 * @brief Após todas as conversões é então apresentado ao utilizador todos os valores obtidos
 * @param tempos ➔ Apontador do tipo TEMPOS que recebe o vetor tempos
 * @param etapas ➔ Apontador do tipo ETAPAS que recebe o vetor etapas
 * @param nTotal ➔ Variável do tipo inteiro que recebe a quantidade de valores a ler no vetor tempos
 * @param maior ➔ Variável do tipo inteiro que recebe o maior tempo lido 
 * @param nEtapas ➔ Variável do tipo inteiro que recebe o número total de etapas existentes na prova
 * @param tempoMin ➔ Variável do tipo inteiro que é um vetor cuja função é guardar a conversão do tempo para minutos e tenho de tamanho nEtapas pois vai conter tempos de todas as etapas
 * @param menorTempoMin ➔ Variável do tipo inteiro que recebe o valor da conversão do menor tempo de prova total em minutos
 * @param menores ➔ Variável do tipo double que é um vetor cuja função é guardar os menores tempos de cada etapa da prova e tem tamanho nEtapas pois vão ter tantos tempos quantas etapas existem
 * @param totalTempo ➔ Variável do tipo double que vai conter o somatório dos menores tempos para assim obter o menor tempo possível de realizar a prova
 * @param tempoSec ➔ Variável do tipo double que é um vetor que vai receber o menor tempo convertido em segundos e milésimos de cada etapa
 * @param menorTempoSec ➔ Variável do tipo double que vai receber o menor tempo em que é possível efetuar a prova convertido em segundos e milésimos
 * @see infoTempos,infoEtapas
 */
void menorTempo(TEMPOS *tempos, ETAPAS *etapas, int nTotal, int maior, int nEtapas)
{
    int tempoMin[nEtapas], menorTempoMin;
    double menores[nEtapas], totalTempo = 0, tempoSec[nEtapas], menorTempoSec;

    for (int i = 0; i < nEtapas; i++)
    {
        menores[i] = maior;
    }
    for (int i = 0; i < nTotal; i++)
    {
        for (int j = 0; j < nEtapas; j++)
        {
            if (strcmp(tempos[i].etapaI, etapas[j].etapaNome) == 0 && tempos[i].tempo < menores[j])
                menores[j] = tempos[i].tempo;
        }
    }
    //vamos transformar o tempo em minutos
    for (int i = 0; i <= nEtapas; i++)
    {
        totalTempo += menores[i];
        tempoMin[i] = (menores[i] / 1000) / 60;
        tempoSec[i] = ((float)menores[i] / (float)1000) - (tempoMin[i] * 60);
    }

    menorTempoMin = (totalTempo / 1000) / 60;
    menorTempoSec = ((float)totalTempo / (float)1000) - (menorTempoMin * 60);
    for (int i = 0, a = 0; i < nEtapas; i++)
    {
        a = i + 1;
        if (i == 0)
            printf("\nMenor tempo possivel(Partida-Etapa1):%d:%.3f", tempoMin[i], tempoSec[i]);
        else if (i == nEtapas - 1)
            printf("\nMenor tempo possivel(Etapa%d-Chegada):%d:%.3f", i, tempoMin[i], tempoSec[i]);
        else
            printf("\nMenor tempo possivel(Etapa%d-Etapa%d):%d:%.3f", i, a, tempoMin[i], tempoSec[i]);
    }

    printf("\nMenor tempo possivel:%d:%.2f", menorTempoMin, menorTempoSec);
}

///Esta função vai calcular as velocidades medias de cada etapas e da prova por completo
/**
 * @brief Esta função primeiramente efetua dois ciclos for, sendo primeiro para percorrer o vetor distancias e o segundo para percorrer o vetor etapas e ir comparando
 * sempre que encontra uma etapa com o mesmo nome o mesmo guarda essa distancia num vetor na posição onde foi encontrada a etapa no vetor etapas pois este vetor já se encontra organizado e acrescenta também a distancia a variável total distancias que guarda o total das distancias da prova
 * @brief Após obter todas as distancias é então obtido a média de tempo de cada etapa a partir do vetor medTempos que contém a média de tempos calculado na função medTemposEtapa
 * e guardado em segundos no vetor tempo o qual também acrescenta o tempo à variável totalTempo que guarda o total de tempo que demora a efetuar a prova
 * @brief Após obter os tempos é então calculada a velocidade média que demora a efetuar a prova em m/s, a formula de calculo da velocidade media é distancia percorrida sobre o tempo que demorou a percorrer essa distancia,
 * utilizando então esta fórmula são calculadas as médias por etapa fazendo uso do vetor dEtapas e do vetor tempo pois ambos estão organizados para cada posição conter a mesma etapa
 * e então os valores vão também ser guardados organizadamente no vetor média
 * @brief Após o cálculo das médias é também calculada a velocidade média total da prova e apresentados estes valores ao utilizador fazendo uso da organização dos vetores
 * @param distancias ➔ Apontador do tipo DISTANCIAS que vai receber o vetor distancias
 * @param etapas ➔ Apontador do tipo ETAPAS que vai receber o vetor etapas
 * @param nEtapas ➔ Variável do tipo inteiro que vai receber o número total de etapas existentes na prova
 * @param medTempos ➔ Apontador do tipo inteiro que vai receber o vetor que contém as médias de tempos por etapa
 * @param dEtapas ➔ Variável do tipo inteiro que é um vetor e recebe a distância das etapas na partida
 * @param medias ➔ Variável do tipo real que é um vetor que vai receber as velocidades médias organizadas por posição 
 * @param tempo ➔ Variável do tipo real que vai receber as médias de tempos por etapa em segundos 
 * @param totalDist ➔ Variável do tipo float que guarda a distância total da prova 
 * @param totalTempo ➔ Variável do tipo float que guarda o total de tempo em segundos da prova por completo
 * @see infoDistancias,infoEtapas
 */
void velocidadesMedias(DISTANCIAS *distancias, ETAPAS *etapas, int nEtapas, int *medTempos)
{
    float dEtapas[nEtapas], medias[nEtapas], tempo[nEtapas], totalDist, totalTempo;

    //verificar todas as distancias e guardar em vetor relembrando que o ficheiro estará organizado
    for (int i = 0; i < nEtapas; i++)
    {
        for (int j = 0; j < nEtapas; j++)
        {
            if (strcmp(distancias[i].etapaI, etapas[j].etapaNome) == 0)
            {
                dEtapas[j] = distancias[i].distancia;
                totalDist += distancias[i].distancia;
            }
        }
    }
    //transformar o tempo em segundos
    for (int i = 0; i < nEtapas; i++)
    {
        tempo[i] = (float)medTempos[i] / (float)1000;
        totalTempo += tempo[i];
    }

    //velocidade media é igual à distancia percorrida a dividir pelo tempo demorado
    for (int i = 0; i < nEtapas; i++)
    {
        medias[i] = dEtapas[i] / tempo[i];
    }
    for (int i = 0, a = 0; i < nEtapas; i++)
    {
        a = i + 1;
        if (i == 0)
            printf("\nVelocidade Media (Partida-Etapa1):%.2fm/s", medias[i]);
        else if (i == nEtapas - 1)
            printf("\nVelocidade Media (Etapa%d-Chegada):%.2fm/s", i, medias[i]);
        else
            printf("\nVelocidade Media (Etapa%d-Etapa%d):%.2fm/s", i, a, medias[i]);
    }

    printf("\nVelocidade Media (Partida-Chegada):%.2fm/s", totalDist / totalTempo);
}

///Esta função vai demonstrar ao utilizador a tabela classificativa e também criar um ficheiro binário com a mesma
/**
 * @brief Primeiramente esta função efetua a abertura do ficheiro tabelaClassificativa.bin no modo de escrita em binário
 * @brief Após a abertura do ficheiro é escrito no ficheiro e também na consola o cabeçalho da tabela classificativa
 * @brief Após a escrita do cabeçalho é efetuado uma organização do vetor tempo prova por tempo para assim obter as posições corretas dos pilotos colocando os pilotos não aprovados
 *  em primeiro lugar
 * @brief Para efetuar então a escrita organizada dos pilotos foi criado um ciclo for que percorre o vetor prova por completo e verifica se o piloto foi aprovado pois
 * primeiramente é necessário escrever os pilotos aprovados
 * como ao realizar a organização do vetor os pilotos ficaram organizados por menor tempo ou seja com as posições corretas na prova não havia necessidade de mais organização
 * logo para obter a posição do piloto foi criada uma outra variável que é incrementada apenas quando um piloto aprovado é escrito conseguindo assim então a posição do piloto
 * @brief Para verificar a distância do líder, quando é escrito o primeiro piloto do vetor que esteja aprovado o tempo do mesmo é guardado numa variável e a cada piloto é efetuada a diferença entre o tempo do mesmo e o tempo do líder
 * e convertido para minutos e segundos
 * @brief O mesmo é efetuado para o calculo da distancia do anterior pois a cada piloto que é acrescentado à tabela, após o calculo da diferença do tempo do mesmo com o tempo do piloto anterior,
 * é atribuído o seu tempo à variável que guarda o tempo do piloto anterior
 * utilizando estes dados foi então escrito na consola e no ficheiro binário todos os pilotos aprovados organizados por posição
 * @brief Da mesma forma é calculada a distância do líder e do piloto anterior, alterando apenas que não é preciso conversão e que se trata de distância e não do tempo
 * @brief Para então escrever os pilotos não aprovados foi efetuado um novo ciclo for que percorrer todo o vetor prova verificando se o piloto não foi aprovado e caso não seja
 * apenas é escrito o seu nome número e carro, tanto na consola como no ficheiro binário
 * @param prova ➔ Apontador do tipo PROVA cujo objetivo é receber vetor prova
 * @param nPilotos ➔ Variável do tipo inteiro que recebe a quantidade de pilotos em prova 
 * @param nomeProva ➔ Apontador do tipo char para o vetor nomeProva que contém o nome da prova a abrir
 * @param auxNum ➔ Variável do tipo inteiro cujo objetivo é servir como auxiliar na troca de valores no vetor prova
 * @param auxTempo ➔ Variável do tipo inteiro cujo objetivo é servir como auxiliar na troca de valores no vetor prova
 * @param auxApr ➔ Variável do tipo inteiro cujo objetivo é servir como auxiliar na troca de valores no vetor prova
 * @param tempoMin ➔ Variável do tipo inteiro cujo objetivo é guardar o tempo em minutos da prova
 * @param diTempoLdr ➔ Variável do tipo inteiro cujo objetivo é guardar a diferença de tempo para o líder
 * @param diTempoAnt ➔ Variável do tipo inteiro cujo objetivo é guardar a diferença de tempo do piloto anterior
 * @param tempoLdr ➔ Variável do tipo inteiro cujo objetivo é guardar o tempo do líder
 * @param tempoSec ➔ Variável do tipo float cujo objetivo é guardar o tempo em segundo
 * @param diLdr ➔ Variável do tipo inteiro cujo objetivo é guardar a diferença do líder
 * @param diAnt ➔ Variável do tipo inteiro cujo objetivo é guardar a diferença do anterior
 * @param auxNome ➔ Variável do tipo char cujo objetivo é auxiliar a troca de nome na organização do vetor
 * @param auxCarro ➔ Variável do tipo char cujo objetivo é auxiliar a troca de nome do carro na organização do vetor
 * @param tabelaFile ➔ Variável do tipo char cujo objetivo é guardar o caminho onde vai ser guardado o ficheiro contendo a tabela
 * @see infoProva
 */
void tabelaClassificativa(PROVA *prova, int nPilotos, char *nomeProva)
{
    int auxNum, auxTempo, auxApr, tempoMin, diTempoLdr, diTempoAnt, tempoLdr;
    float tempoSec, diLdr, diAnt;
    char auxNome[30], auxCarro[30], tabelaFile[50];
    FILE *fp;
    strcpy(tabelaFile, nomeProva);
    strcat(tabelaFile, "/tabelaClassificativa.bin");
    fp = fopen(tabelaFile, "wb");
    printf("\n-----------------------------------------------------------------------------------------------------------------");
    printf("\n|    Posicao\t|     Numero\t|      Nome\t|     Carro\t| Tempo de prova |    Di.Ant.    |    Di.Ldr.   |");
    printf("\n-----------------------------------------------------------------------------------------------------------------");
    fprintf(fp, "\n-----------------------------------------------------------------------------------------------------------------");
    fprintf(fp, "\n|    Posicao\t|     Numero\t|      Nome\t|     Carro\t| Tempo de prova |    Di.Ant.    |    Di.Ldr.   |");
    fprintf(fp, "\n-----------------------------------------------------------------------------------------------------------------");
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
                printf("\n|\t%d\t|\t%d\t|%10s\t|%10s\t|    %3d:%.3f   |\t0\t |\t0\t|", a, prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro, tempoMin, tempoSec);
                fprintf(fp, "\n|\t%d\t|\t%d\t|%10s\t|%10s\t|    %3d:%.3f   |\t0\t |\t0\t|", a, prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro, tempoMin, tempoSec);
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
                printf("\n|\t%d\t|\t%d\t|%10s\t|%10s\t|   %3d:%6.3f   |     %.3f\t |    %.3f\t|", a, prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro, tempoMin, tempoSec, diAnt, diLdr);
                fprintf(fp, "\n|\t%d\t|\t%d\t|%10s\t|%10s\t|   %3d:%6.3f   |     %.3f\t |    %.3f\t|", a, prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro, tempoMin, tempoSec, diAnt, diLdr);
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
            fprintf(fp, "\n|\t-\t|\t%d\t| %10s\t| %10s\t|\t-\t |\t-\t |\t-\t|", prova[i].piloto.num, prova[i].piloto.nome, prova[i].piloto.carro);
        }
    }

    printf("\n-----------------------------------------------------------------------------------------------------------------");
    fprintf(fp, "\n-----------------------------------------------------------------------------------------------------------------");
    fclose(fp);
}

///Esta função tem o objetivo de servir como menu do software
/**
 * @brief Esta função primeiramente vai escrever na consola o menu do software
 * @brief Após mostrar o menu ao utilizador é lido a escolha do utilizador e realizado um switch para efetuar as funções corretas
 *  para a escolha do utilizador
 * @param tempos ➔ Apontador do tipo TEMPOS que recebe o vetor tempos
 * @param pilotos ➔ Apontador do tipo PILOTO que recebe o vetor pilotos
 * @param distancias ➔ Apontador do tipo DISTANCIAS que recebe o vetor distancias
 * @param prova ➔ Apontador do tipo PROVA que recebe o vetor prova
 * @param etapas ➔ Apontador do tipo ETAPAS que recebe o vetor etapas
 * @param nTotal ➔ Variável do tipo inteiro que recebe o número total de tempos no vetor tempos
 * @param nPilotos ➔ Variável do tipo inteiro que recebe o número total de pilotos inscritos na prova
 * @param nEtapas ➔ Variável do tipo inteiro que recebe o número total de etapas na prova
 * @param nAprovados ➔ Variável do tipo inteiro que recebe o número de pilotos aprovados
 * @param nomeProva ➔ Variável do tipo char que recebe o nome da pasta na qual está guardado os ficheiros da prova
 * @param escolha ➔ Variável do tipo inteiro que guarda a opção escolhida pelo utilizador
 * @param medTempos ➔ Variável do tipo inteiro que é um vetor cujo objetivo é guardar a media de tempos e tem de tamanho o número de etapas da prova
 * @param pilotosAprv ➔ Variável do tipo inteiro que é um vetor cujo objetivo é guardar o número dos pilotos que são aprovados na prova
 * @param numExtremos ➔ Variável do tipo inteiro que guarda o número dos pilotos mais rápido e mais lento
 * @param maiorNum ➔ Variável do tipo inteiro que guarda o número do piloto mais lento
 * @param menorNum ➔ Variável do tipo inteiro que guarda o número do piloto mais rápido
 * @param novaProva ➔ Variável do tipo char cujo objetivo é guardar o nome da pasta onde estão guardados os ficheiros com as informações da prova
 * @see infoEtapas,infoTempos,infoDistancias,infoPilotos,infoProva,menu
 */
void menu(TEMPOS *tempos, PILOTO *pilotos, DISTANCIAS *distancias, PROVA *prova, ETAPAS *etapas, int nTotal, int nPilotos, int nEtapas, int aprovados, char *nomeProva)
{
    int escolha, medTempos[nEtapas], pilotosAprv[aprovados], numExtremos[1], maiorNum, menorNum;
    char novaProva[30];
    printf("\n**************************************************");
    printf("\n** 1 - Numero de pilotos\t\t\t**");
    printf("\n** 2 - Numero de pilotos com prova valida\t**");
    printf("\n** 3 - Pilotos por tempo descendente validos\t**");
    printf("\n** 4 - Media tempos etapas validos\t\t**");
    printf("\n** 5 - Piloto mais rapido e mais lento\t\t**");
    printf("\n** 6 - Menor tempo possivel de realizar a prova\t**");
    printf("\n** 7 - Media de velocidades \t\t\t**");
    printf("\n** 8 - Tabela classificativa da prova\t\t**");
    printf("\n** 9 - Trocar de prova\t\t\t\t**");
    printf("\n** 10 - Sair\t\t\t\t\t**");
    printf("\n**************************************************");
    printf("\n escolha: ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        printf("\nNumero de pilotos: %d", nPilotosCount(nomeProva));
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 2:
        printf("\nExistem %d concorrentes com prova valida!", loadVerificaProva(tempos, nTotal, nEtapas));
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
        verificaProva(tempos, nTotal, pilotosAprv, nEtapas);
        medTemposEtapa(tempos, etapas, nTotal, pilotosAprv, medTempos, aprovados, nEtapas);
        for (int i = 0, a = 0; i < nEtapas; i++)
        {
            a = i + 1;
            if (i == 0)
                printf("\nMedia tempos entre Partida e Etapa%d : %d:%.3f", a, (medTempos[i] / 1000) / 60, ((float)medTempos[i] / (float)1000) - ((medTempos[i] / 1000) / 60) * 60);
            else if (i == nEtapas - 1)
                printf("\nMedia tempos entre Etapa%d e Chegada : %d:%.3f", i, (medTempos[i] / 1000) / 60, ((float)medTempos[i] / (float)1000) - ((medTempos[i] / 1000) / 60) * 60);
            else
                printf("\nMedia tempos entre Etapa%d e Etapa%d : %d:%.3f", i, a, (medTempos[i] / 1000) / 60, ((float)medTempos[i] / (float)1000) - ((medTempos[i] / 1000) / 60) * 60);
        }
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
        menorTempo(tempos, etapas, nTotal, prova[maiorNum].tempoProva, nEtapas);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 7:
        verificaProva(tempos, nTotal, pilotosAprv, nEtapas);
        medTemposEtapa(tempos, etapas, nTotal, pilotosAprv, medTempos, aprovados, nEtapas);
        velocidadesMedias(distancias, etapas, nEtapas, medTempos);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 8:
        tabelaClassificativa(prova, nPilotos, nomeProva);
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    case 9:
        printf("Introduza o nome da pasta da prova: ");
        scanf("%s", novaProva);
        loadTudo(novaProva);
        break;
    case 10:
        return;
        break;
    default:
        printf("Opcao invalida");
        fflush(stdin);
        printf("\n(Enter)");
        getchar();
        break;
    }
    menu(tempos, pilotos, distancias, prova, etapas, nTotal, nPilotos, nEtapas, aprovados, nomeProva);
}

///Esta função tem como objetivo realizar o carregamento das informações do ficheiro
/**
 * @brief Primeiramente vai ser executado a função Etapas para obter o número de etapas e de pilotos e é passado por parâmetro a variável n para guardar os valores
 *  que depois vão igualados a variáveis e também a variável nomeProva para se obter a pasta correta a abrir
 * @brief É então aproveitado o facto de se saber quantas etapas são para colocar etapas no vetor nomeEtapas, para o realizar é seguido o pensamento do que 3 etapas
 *  significa que a primeira etapa será P e as seguintes E1 e E2, aproveitando este raciocínio é criado um ciclo for que quando estamos no primeiro ciclo coloca a primeira etapa com P e nos seguintes ciclos será E+n ciclos
 * @brief Para iniciar o vetor tempos foi necessário obter o número total de tempos a ler, mas como no ficheiro tempos a primeira linha indica a quantidade de etapas e pilotos no ficheiro então
 *  o número de tempos a ler é o produto dos pilotos com as etapas, para então depois colocar os tempos no vetor tempos é chamada a função loadTempos e passado por parâmetro tempos e o nome da pasta dos ficheiros da prova
 * @brief Para iniciar o vetor distâncias foi utilizado então o número de etapas obtido na função Etapas pois contém o número total de etapas, de seguida para se colocar informações no vetor é
 * executada a função loadDistancias e passado por parâmetro o vetor distancias e nome da pasta a abrir para aceder aos ficheiros corretos, por ultimo é realizada a organização do vetor distancias por
 * nome da prova sendo a primeira P e as seguintes E+n, pois assim o vetor estaria organizado para o restante do código facilitando a programação do mesmo
 * @brief Para iniciar o vetor pilotos é primeiramente executada a função nPilotosCount e é igualado à variável nPilotos para assim guardar a quantidade total de pilotos inscritos na prova na variável nPilotos,
 * de seguida é então iniciado o vetor com tamanho de nPilotos e chamada a função loadPilotos na qual se passa por parâmetro o vetor pilotos e o nome da prova para assim se colocar os dados dentro do vetor
 * @brief Para iniciar o vetor prova é utilizado o tamanho de nPilotos pois este vetor vai conter as informações de todos os pilotos e as informações da prova referentes aos mesmos, para iniciar o vetor
 * é executada a função loadProva e passado por parâmetro os vetores prova, tempos e pilotos pois as informações dos mesmos vão ser colocadas no vetor prova, é também passado por parâmetro as variáveis
 * nTotal,nPilotos e nEtapas para se saber dentro da função quais são os limites dos vetores passados
 * @brief De seguida é contabilizado a quantidade de pilotos aprovados, foi esta ação efetuada pois para criar o vetor contendo o número dos pilotos aprovados seria necessário o número total de pilotos aprovados
 * @brief É por fim encaminhado para o vetor menu todas as variáveis obtidas nesta função para então serem utilizadas no restante código
 * @param nomeProva ➔ Variável do tipo char cujo objectivo é guardar o nome da pasta a abrir contendo as informações da prova
 * @param n ➔ Variável do tipo inteiro que é um vetor cujo objetivo é guardar na posição 0 o número de etapas da prova e na posição 1 o número de pilotos no ficheiro tempos.txt
 * @param nTotal ➔ Variável do tipo inteiro cujo objetivo é guardar o número total de informações a ler no ficheiro tempos.txt
 * @param nEtapas ➔ Variável do tipo inteiro cujo objetivo é guardar o número de etapas existentes na prova
 * @param nPilotos ➔ Variável do tipo inteiro cujo objetivo é guardar o número de pilotos existentes na prova e também o número de pilotos presentes no ficheiro tempos.txt
 * @param aprovados ➔ Variável do tipo inteiro cujo objetivo é guardar o número de pilotos aprovados
 * @see infoEtapas,infoTempos,infoDistancias,infoPilotos,infoProva,Etapas,loadTempos,loadDistancias,arrumarVetor,nPilotosCount,LoadProva,loadVerificaProva,menu
 */
void loadTudo(char *nomeProva)
{
    int n[1], nTotal, nEtapas, nPilotos, aprovados;

    Etapas(n, nomeProva);

    //valores q estão no começo do ficheiro tempos.txt com as informações dos Pilotos e Etapas
    nEtapas = n[0];
    nPilotos = n[1];
    ETAPAS nomeEtapas[nEtapas];
    for (int i = 0; i < nEtapas; i++)
    {
        char nome[3] = {'P', '\0'};
        if (i == 0)
        {
            strcpy(nomeEtapas[i].etapaNome, nome);
        }
        else
        {
            sprintf(nome, "%c%d", 'E', i);
            strcpy(nomeEtapas[i].etapaNome, nome);
        }
    }

    //o total de etapas que têm de estar registadas é o numero de etapas a multiplicar pelo
    //numero de pilotos que está no ficheiro
    nTotal = nEtapas * nPilotos;

    //carregamento dos tempos para o vetor da estrutura TEMPOS
    TEMPOS tempos[nTotal];
    loadTempos(tempos, nomeProva);

    //Carregamento das distancias das etapas para o vetor da estrutura DISTANCIAS
    DISTANCIAS distancias[nEtapas];
    loadDistancias(distancias, nomeProva);
    arrumarVetor(distancias, nEtapas);

    //carregamento das informações dos pilotos para o vetor da estrutura PILOTO
    nPilotos = nPilotosCount(nomeProva);
    PILOTO pilotos[nPilotos];
    loadPilotos(pilotos, nomeProva);

    PROVA prova[nPilotos];
    loadProva(prova, tempos, pilotos, nTotal, nPilotos, nEtapas);
    aprovados = loadVerificaProva(tempos, nTotal, nEtapas);

    menu(tempos, pilotos, distancias, prova, nomeEtapas, nTotal, nPilotos, nEtapas, aprovados, nomeProva);
}

///Esta é a função principal do programa
/**
 * @brief Esta função tem como objetivo iniciar o programa pois a mesma vai pedir ao utilizador o nome da prova que seria o nome da pasta que contém os ficheiros
 *  com informações da prova e de seguida vai executar a função loadTudo passando por parâmetro o nome da prova lido anteriormente
 * @param nomeProva ➔ Variável do tipo char que é um vetor cujo objetivo é guardar o nome da pasta que contém as informações da prova
 * @see loadTudo
 */
int main()
{

    char nomeProva[30];
    printf("Introduza o nome da pasta da prova: ");
    scanf("%s", nomeProva);
    loadTudo(nomeProva);
    return 0;
}