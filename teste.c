/*********************************************************************
**    Nome: Exemplo nome											**
**    Autor: Roberto Barreto - Henrique Cartucho - Vincent Rebena	**
**    Data: 23/12/2020												**
*********************************************************************/

#include <stdio.h>
#include <string.h>

void main()
{
    char etapaI[3];
    char teste[3];
    strcpy(etapaI, "E1");
    strcpy(teste, "E2");
    printf("teste: %d", strcmp(etapaI, teste));
}
