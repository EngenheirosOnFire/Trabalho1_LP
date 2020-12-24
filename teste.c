/*********************************************************************
**    Nome: Exemplo nome											**
**    Autor: Roberto Barreto - Henrique Cartucho - Vincent Rebena	**
**    Data: 23/12/2020												**
*********************************************************************/

#include <stdio.h>
#include <string.h>
typedef struct teste
{

    char vetor[3];
    char vetor1[3];

} TESTE;
void loadTempos(TESTE *teste)
{
    char teste_[3], teste_1[3];
    int i = 0;
    strcpy(teste_, "E1");
    strcpy(teste_1, "E2");
    while (i <= 8)
    {
        strcpy(teste[i].vetor, teste_);
        strcpy(teste[i].vetor1, teste_1);
        printf("vetor: %s", teste[i].vetor);
        printf("vetor1: %s", teste[i].vetor1);
        i++;
    }
}
void main()
{
    int i = 0;
    TESTE teste[8];
    loadTempos(teste);
    while (i <= 8)
    {
        printf("vetor: %s", teste[i].vetor);
        printf("vetor1: %s", teste[i].vetor1);
    }
}
