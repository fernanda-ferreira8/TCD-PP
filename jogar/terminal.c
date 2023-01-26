#include <stdio.h>

int vezHumano()
{
    int decisao;
    printf("Mao: 2\n"
           "Carta 1: "
           "Carta 2"
           "Carta 3"
           "Opcoes:"
           "1.Jogar carta!"
           "2.Pedir truco"
           "3.Jogar no escuro"
           "4.Desistir do jogo");
    scanf("%d", &decisao);

    swictch(decisao){
        case 1:
        printf("Digite qual carta que quer jogar!\nCarta: ");
        scanf("%d", &carta_player);
        return carta_player;
        break;

        case 2: 
        return //trucar
        break;

        case 3:
        return //jogar_escuro
        break;

        case 4:
        printf("GAME OVER");
        break;
    }
    return 0;
}