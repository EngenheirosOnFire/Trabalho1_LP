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
    char nome[15];
    ///Esta variavel guarda o carro do piloto
    ///@note Foi dado aos vetores nome e carro tamanho 50 para assim ser possivel colocar qualquer tamanho de nomes nos mesmos
    char carro[15];
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