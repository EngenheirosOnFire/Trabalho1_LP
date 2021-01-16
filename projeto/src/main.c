/*****************************************************************
**    Nome: Prova de Rally		                                **
**    Autor: Roberto Barreto\Henrique Cartucho\Vincent Rebena	**
**    Data: 18/12/2020			                                **
****************************************************************/

#include <stdio.h>
#include <header.h>

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