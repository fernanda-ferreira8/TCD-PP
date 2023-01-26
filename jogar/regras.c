#include <stdio.h>
#include <time.h>

typedef struct // tipo de jogador, usado para armazenar os dados dos jogadores em cada partida/rodada
{
    char nome[20];
    int pontos;
    int cartas[3];
    int vitoria_temp;
} jogador;

int main()
{
    jogador jogador1, jogador2;
    int x;

    x = rand() % 2;
    
    //pela primeira vez
    if (x == 1)
    {
        jogador1.vitoria_temp = 1;
    }
    else if (x == 2)
    {
        jogador2.vitoria_temp = 1;
    }
    
    if (jogador1.vitoria_temp != 0)
    {
        jogador1.vitoria_temp = 0;
        // chamar o jogo pra começar aq
    }
    else if (jogador2.vitoria_temp != 0)
    {
        jogador2.vitoria_temp = 0;
        // chamar o jogo pra começar aq
    }



    
}