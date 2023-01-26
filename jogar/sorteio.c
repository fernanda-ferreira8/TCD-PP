#include <stdio.h> // biblioteca de entrada e saída
#include <time.h> // biblioteca que possibilita utilizar o tempo como semente para a função rand
#include <Windows.h> // biblioteca que permite o funcionamento da função my_sleep (pausas)

typedef struct // tipo de cartas, usado para dar aos jogadores suas cartas
{
    int jogador1[3];
    int jogador2[3];
}cartas;

void my_sleep(int sleepms) // função que permite "pausar" a execução por um tempo determinado
{
    Sleep(sleepms);
} 

int embaralhar_cartas (int *b, int i) // função para emnbaralhar as cartas de forma aleatória
{
    int carta_temporaria; // carta temporaria que será usada para não ter perda de dados ao embaralhar
    int troca, embaralhar = 0; // troca - variavel usada para determinar a posição a ser trocada // embaralhar - usado para contar quantas vezes será embaralhado o baralho

    printf ("Embaralhando, aguarde...");

    while(embaralhar <= 3) // repetição que mantém o baralho sendo embaralhado repetidas vezes
    {
        if (embaralhar == 0) // enfeite
        {
            printf (" %c", 5);
        }

        if (embaralhar == 1) // enfeite
        {
            printf (" %c", 3);
        }

        if (embaralhar == 2) // enfeite
        {
            printf (" %c", 6);
        }

        if (embaralhar == 3) // enfeite
        {
            printf (" %c\n", 4);
        }

        for (i = 0; i < 40; i++) // repetição que garante que TODAS as cartas serão trocadas de local
        {
            troca = rand() % 40;

            my_sleep(50); // espaço de tempo para a função rand trocar de valor

            carta_temporaria = b[i];
            b[i] = b[troca];
            b[troca] = carta_temporaria;
        }
        embaralhar++;
    } 
    return;
}

cartas sorteio_cartas () // função que irá fazer o sorteio das cartas de cada jogador em casa rodada
{
    int baralho_embaralhado [40] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40}; // baralho com todas as cartas em ordem
    int carta_baralho; // carta sorteada para um dos jogadores 
    int j, i; // índices
    cartas cartas_jogo; // variavel para armazenar as cartas de cada jogador

    embaralhar_cartas (baralho_embaralhado, 40); // função de embaralhar sendo chamada para realizar sua função e garantir a aleatoriedade

    printf ("Sorteando cartas... %c", 2);

    my_sleep(500); // pequena pausa

    for (i = 0; i < 3; i++) // repetição para sortear as cartas do primeiro jogador
    {
        carta_baralho = rand () % 40;
        cartas_jogo.jogador1[i] = baralho_embaralhado[carta_baralho];

        for (j = 0; j < i; j++) // repetição atrelada a condição abaixo
        {
            if (cartas_jogo.jogador1[j] == cartas_jogo.jogador1[i]) // primeira condição para evitar duplicidade de cartas
            {
                i--;
            }
        } 
    }

    for (i = 0; i < 3; i++) // repetição para sortear as cartas do segundo jogador
    {
        carta_baralho = rand () % 40;
        cartas_jogo.jogador2[i] = baralho_embaralhado[carta_baralho];

        for (j = 0; j < i; j++) // repetição atrelada a condição abaixo
        {
            if (cartas_jogo.jogador2[j] == cartas_jogo.jogador2[i]) // segunda condição para evitar duplicidade de cartas
            {
                i--;
            }
        } 

        for (j = 0; j < 3; j++) // repetição atrelada a condição abaixo
        {
            if (cartas_jogo.jogador2[i] == cartas_jogo.jogador1[j]) // terceira condição para evitar duplicidade de cartas
            {
                i = -1;
            }
        }
    }

    return cartas_jogo;
}

int main ()
{
    int i;
    cartas cartas_jogo;

    srand (time (NULL));

    cartas_jogo = sorteio_cartas ();

    printf ("\ncartas1: %d %d %d\ncartas2: %d %d %d", cartas_jogo.jogador1[0], cartas_jogo.jogador1[1], cartas_jogo.jogador1[2], cartas_jogo.jogador2[0], cartas_jogo.jogador2[1], cartas_jogo.jogador2[2]);

    return 0;
}