#include <stdio.h>
#include <Windows.h>


void gotoxy(int x, int y);
void print_carregar(int x, int y, float velocidade);


int main()
{
    system("clear");
    printf("  Carregando...");
    print_carregar(5, 15, 400);
    return 0;
}


void gotoxy(int x, int y)
{
    HANDLE stdOutput;
    COORD pos;

    stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(stdOutput, pos);
    }


void print_carregar(int x, int y, float velocidade)
{
    int i;
    int bar = 175; /*caracter a ser imprimido*/

    for(i = 0; i < 80; i++)
    {
        if(((i % 20) == 0) && (i != 60))
        {
            velocidade /= 7;
            gotoxy(x, y);
            bar++;
        }
        if(i == 60)
        {
            velocidade /= 3;
            bar += 41;
            gotoxy(x, y);
        }
        printf("%c", bar);
        Sleep(velocidade);
    }
}
