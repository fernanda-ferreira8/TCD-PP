 #include <stdio.h>

int main ()
{
    FILE *ranking;
    char palavra[20];

    ranking = fopen ("arquivo.txt", "a");

    printf("Escreva uma palavra para testar gravacao de arquivo: ");
    scanf("%s", palavra);
  
    //usando fprintf para armazenar a string no arquivo
    fprintf(ranking, "%s", palavra);

    fclose (ranking);

    return 0;
}