#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *file;
    char prova[30];
    strcpy(prova, "prova1");
    strcat(prova, "/tempos.txt");
    if (file = fopen(prova, "r"))
    {
        fclose(file);
        printf("file exists");
    }
    else
    {
        printf("file doesn't exist");
    }

    return 0;
}