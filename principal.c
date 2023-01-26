#include <stdio.h> // biblioteca de entrada e saída
#include <time.h> // biblioteca que possibilita utilizar o tempo como semente para a função rand
#include <Windows.h> // biblioteca que permite o funcionamento da função Sleep (pausas) e outras funções
#include <truco.h>

// DEFINES USADOS NO FRONT
#define NONE        "\033[0m"   // FORMATAÇÕES
#define BOLD        "\033[1m"   //
#define HALFBRIGHT  "\033[2m"   //
#define UNDERSCORE  "\033[4m"   //
#define BLINK       "\033[5m"   //
#define REVERSE     "\033[7m"   //
#define C_BLACK     "\033[30m"  // CORES DE FONTES
#define C_RED       "\033[31m"  //
#define C_GREEN     "\033[32m"  //
#define C_YELLOW    "\033[33m"  //
#define C_BLUE      "\033[34m"  //
#define C_MAGENTA   "\033[35m"  //
#define C_CYAN      "\033[366m" //
#define C_GRAY      "\033[37m"  //
#define BG_BLACK    "\033[40m"  // CORES DE FUNDO
#define BG_RED      "\033[41m"  //
#define BG_GREEN    "\033[42m"  //
#define BG_YELLOW   "\033[43m"  // 
#define BG_BLUE     "\033[44m"  //
#define BG_MAGENTA  "\033[45m"  //
#define BG_CYAN     "\033[46m"  //  
#define BG_GRAY     "\033[47m"  //

typedef struct // tipo de cartas, usado para dar aos jogadores suas cartas
{
    int jogador1[3];
    int jogador2[3];
}cartas;

typedef struct  // tipo de jogador, usado para armazenar os dados dos jogadores em cada partida/rodada
{
    char nome [20];
    int pontos;
    int cartas[3];
    int vitoria_temp;
}jogador;

int embaralhar_cartas (int *b, int i);
cartas sorteio_cartas ();
void switch1 (int cartas1);
void imprimir (cartas *cartas_jogo);

int main ()
{
    printf("mudança\n");
    int i, option;
    cartas cartas_jogo;

    //system("start SOVIET.mp3.mp3"); 

    srand (time (NULL)); // semente das funções rand que embaralham tudo 

    for (i = 0; i < 70; i++) // enfeite
    {
        printf (" ");
    }
    printf (BOLD C_MAGENTA "%c BEM VINDO AO JOGO %c\n", 2, 2, NONE); // enfeite
    
    for (i = 0; i < 170; i++) // enfeite 
    {
        printf (BOLD C_GREEN "_" NONE);
        Sleep(1);
    }

    do // laço geral que mantém o jogo até que seja selecionado "sair"
    {
        do // laço que garante que uma opção valida seja selecionada
        {

            printf (BOLD "\nSelecione uma opcao para comecar: " NONE); 
            Sleep (400);
            printf (C_CYAN "\n1. Jogar" NONE); Sleep (100);
            printf ("\n2. Ranking"); Sleep (100);
            printf ("\n3. Sobre"); Sleep (100);
            printf ("\n4. Sair"); Sleep (100);
            printf ("\n");
            printf ("Opcao: ");
            scanf ("%d", &option);

            if (option < 1 || option > 4) // condição para avisar caso uma opção invalida tenha sido selecionada
            {
                printf ("Opcao invalida!\n");
            }

            Sleep(500); // perae

        }while(option < 1 || option > 4);

        for (i = 0; i < 170; i++) // enfeite
        {
            printf (BOLD C_GREEN "_" NONE);
            Sleep (1);
        }

        if (option == 4) // caso seja selecionado "sair", essa condição irá agradecer e encerrar o programa
        {
            printf (BOLD C_BLUE "\nObrigado por jogar! %c\n\n", 3, NONE);
            break;
        }

        if (option == 3) // condição que irá mostrar as coisas da seção "sobre"
        {
        Sleep (500);
        printf ( BOLD "\nSOBRE: \n" NONE);
        printf ("   Projeto: Jogo de truco mineiro criado para o TCD (trabalho de conclusao de disciplina) de Programacao Procedimental\n");
        printf ("   Autores: Ana Alice Cordeiro de Souza @alicecordeiro__\n");
        printf ("            Ester Freitas @esterzolas\n            Fernanda Ferreira de Melo @nandafm8\n            Jean Souto G. Moreira @jean.soutoo");
        printf (BOLD "\n   Turma 69 de Ciencia da Computacao / FACOM - UFU / 2022.1 (15/01/2023)");
        printf (C_BLUE "\n   Obrigado por jogar! %c", 3, NONE);
        printf ("\n");
        Sleep (500);
        }

        if (option == 3) // condição do enfeite
        {
            for (i = 0; i < 170; i++) // enfeite
            {
                printf (BOLD C_GREEN "_" NONE);
                Sleep(1);
            }
        }

        if (option == 1) // condição PRINCIPAL que irá iniciar o jogo
        {
            cartas_jogo = sorteio_cartas ();

            printf ("\ncartas1: %d %d %d\ncartas2: %d %d %d", cartas_jogo.jogador1[0], cartas_jogo.jogador1[1], cartas_jogo.jogador1[2], cartas_jogo.jogador2[0], cartas_jogo.jogador2[1], cartas_jogo.jogador2[2]);

            imprimir (&cartas_jogo);
        }

        if (option == 1) // condição do enfeite
        {
            printf ("\n");
            for (i = 0; i < 170; i++) // enfeite
            {
                printf (BOLD C_GREEN "_" NONE);
                Sleep(1);
            }
        }

    }while (option != 4);

    return 0;
}

int embaralhar_cartas (int *b, int i) // função para emnbaralhar as cartas de forma aleatória
{
    int carta_temporaria; // carta temporaria que será usada para não ter perda de dados ao embaralhar
    int troca, embaralhar = 0; // troca - variavel usada para determinar a posição a ser trocada // embaralhar - usado para contar quantas vezes será embaralhado o baralho

    printf ("\nEmbaralhando, aguarde...");

    while(embaralhar <= 3) // repetição que mantém o baralho sendo embaralhado repetidas vezes
    {
        if (embaralhar == 0) // enfeite ♣
        {
            printf (" %c", 5);
        }

        if (embaralhar == 1) // enfeite ♥
        {
            printf (" %c", 3);
        }

        if (embaralhar == 2) // enfeite ♠
        {
            printf (" %c", 6);
        }

        if (embaralhar == 3) // enfeite ♦
        {
            printf (" %c\n", 4);
        }

        for (i = 0; i < 40; i++) // repetição que garante que TODAS as cartas serão trocadas de local
        {
            troca = rand() % 40;

            Sleep(50); // espaço de tempo para a função rand trocar de valor

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

    Sleep(500); // pequena pausa

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
                i--;
            }
        }
    }

    return cartas_jogo;
}

void switch1 (int cartas1) // função com switch usado para imprimir cada carta individualmente
{
    switch (cartas1)
    {
        case 1:
            printf ("A%c", 4); // daqui até o 10 são ♦
        break;

        case 2:
            printf ("2%c", 4);
        break;

        case 3:
            printf ("3%c", 4);
        break;

        case 4:
            printf ("4%c", 4);
        break;

        case 5:
            printf ("5%c", 4);
        break;

        case 6:
            printf ("6%c", 4);
        break;

        case 7:
            printf ("%c 7%c", 26, 4);
        break;

        case 8:
            printf ("Q%c", 4);
        break;

        case 9:
            printf ("J%c", 4);
        break;

        case 10:
            printf ("K%c", 4);
        break;

        case 11:
            printf ("%c A%c", 26, 6); // daqui até o 20 são ♠
        break;

        case 12:
            printf ("2%c", 6);
        break;

        case 13:
            printf ("3%c", 6);
        break;

        case 14:
            printf ("4%c", 6);
        break;

        case 15:
            printf ("5%c", 6);
        break;

        case 16:
            printf ("6%c", 6);
        break;

        case 17:
            printf ("7%c", 6);
        break;

        case 18:
            printf ("Q%c", 6);
        break;

        case 19:
            printf ("J%c", 6);
        break;

        case 20:
            printf ("K%c", 6);
        break;

        case 21:
            printf ("A%c", 3); // daqui até o 30 são ♥
        break;

        case 22:
            printf ("2%c", 3);
        break;

        case 23:
            printf ("3%c", 3);
        break;

        case 24:
            printf ("4%c", 3);
        break;

        case 25:
            printf ("5%c", 3);
        break;

        case 26:
            printf ("6%c", 3);
        break;

        case 27:
            printf ("%c 7%c", 26, 3);
        break;

        case 28:
            printf ("Q%c", 3);
        break;

        case 29:
            printf ("J%c", 3);
        break;

        case 30:
            printf ("K%c", 3);
        break;

        case 31:
            printf ("A%c", 5); // daqui até o 40 são ♣
        break;

        case 32:
            printf ("2%c", 5);
        break;

        case 33:
            printf ("3%c", 5);
        break;

        case 34:
            printf ("%c 4%c", 26, 5);
        break;

        case 35:
            printf ("5%c", 5);
        break;

        case 36:
            printf ("6%c", 5);
        break;

        case 37:
            printf ("7%c", 5);
        break;

        case 38:
            printf ("Q%c", 5);
        break;

        case 39:
            printf ("J%c", 5);
        break;

        case 40:
            printf ("K%c", 5);
        break;
    }
}

void imprimir (cartas *cartas_jogo) // função chamada para imprimir as 3 cartas iniciais do jogador humano
{
    printf ("\n1. ");
    switch1 (cartas_jogo->jogador2[0]);
    printf ("\n2. ");
    switch1 (cartas_jogo->jogador2[1]);
    printf ("\n3. ");
    switch1 (cartas_jogo->jogador2[2]);
}