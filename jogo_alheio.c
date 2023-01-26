/*Jogo de truco em C*/
/*Versão 0.20*/

/*Bibliotecas utilizadas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Estados:
   0=normal
   1=trucado
   2=vale seis
   3=vale nove
   4=vale doze
      */

/*Constantes*/
#define opcoes 4
#define versao 0.20
#define TRUE 1
#define FALSE 0
#define ptsmax 12
#define g "(Gato)"
#define c "(Copas)"
#define e "(Espadilha)"
#define m "(Mole)"
#define truco "truco"
#define seis "seis"
#define nove "nove"
#define doze "doze"
#define vazio "vazio"
#define autor2 "Celito Gregolon Junior" /*Ordem alfabética*/
#define autor1 "Carlos Eduardo Weber"
#define autor3 "Ricardo Oenning"
#define part "Partidas"
#define sal "Pontos"
#define jog "Jogador"
#define vit "Vitrias"

/*Variáveis Globais*/
char nome[40] = "Design";
int pnts[2];
int pntsrod[2];
int baralho[40];
int matriz[40];
int mao[2][3];
int mesa[2][3];
int cartas[40];
char ranknomes[100][40];
int rankpts[100];
int rankpartidas[100];
int rankvitorias[100];
FILE *fl;
FILE *arq;
int primeiro, virada, turno, rodada, estado, last, saldo, inicial, continua, qly, sorteado, local, npartidas, vitorias;
char status[6][10] = {vazio, truco, seis, nove, doze, vazio};
char esp;

/*Funções e procedimentos definidos*/
void embaralha(void);
int sorteia(int max);
void distribui(void);
void pcplay(void);
void jgplay(void);
void atribui(void);
char toon(int card);
char carta(int card);
void save(void);
void pcpensa(void);
void pctruca(void);
void pcordena(void);
void jgtruca(void);
void jogo(void);
void sobre(void);
void rank(void);

/*Principal*/
void main()
{
   /*Variáveis locais*/
   int opcao, i;

   /*Início*/
   opcao = opcoes + 1;
   while (opcao != opcoes)
   {
      /* Pede para que o usuário escolha uma opção*/
      printf("\n");
      printf("************************\n");
      printf("O que voce deseja fazer?\n");
      printf("\t1 - Jogar truco\n");
      printf("\t2 - Ver ranking\n");
      printf("\t3 - Sobre...\n");
      printf("\t4 - Sair\n");
      printf("\nDigite uma opcao:");
      scanf("%d", &opcao);
      strcpy(&status[1], &truco);
      strcpy(&status[2], &seis);
      strcpy(&status[3], &nove);
      strcpy(&status[4], &doze);
      /*Verifica possíveis entradas erradas*/
      if ((opcao < 1) || (opcao > opcoes))
      {
         printf("\a\n\nVALOR INCORRETO!\n\n");
         printf("Por favor escolha uma opcaoo entre 1 e %d\n\n", opcoes);
         system("Pause");
      }
      if (opcao == 1)
      {
         jogo();
      }
      if (opcao == 2)
      {
         rank();
      }
      if (opcao == 3)
      {
         sobre();
      }
   }
}

void sobre(void)
{
   /**/ printf("\n\n");
   printf("Programa: Super Truco\n>>");
   esp = getch();
   printf("\nVersao: %3.2f\n>>", versao);
   esp = getch();
   printf("\nAutores:\n");
   printf("\t%s\n", autor1);
   printf("\t%s\n", autor2);
   printf("\t%s\n>>", autor3);
   esp = getch();
   printf("\nComentarios\n");
   printf("\t       Este programa foi feito em novembro de 2004 como trabalho\n");
   printf("\tde conclusao da disciplina de Processamento de Dados (PRD) da \n");
   printf("\t3 fase do curso de Engenharia Eletrica da Universidade do Estado\n");
   printf("\tde Santa Catarina (UDESC).\n>>");
   esp = getch();
}

void rank(void)
{
   char car;
   int i;
   if ((arq = fopen("rank.txt", "r")) == NULL)
   {
      arq = fopen("Rank.txt", "w");
      for (i = 0; i < 100; i++)
         fprintf(arq, "%s %d %d %d\n", vazio, 0, 0, 0);
      fclose(arq);
      arq = fopen("rank.txt", "r");
   }
   printf("\n");
   printf(" Rank -%15s\t%10s\t%8s%10s\n\n", jog, part, vit, sal);
   for (i = 0; i < 10; i++)
   {
      fscanf(arq, "%s%d%d%d", ranknomes[i], &rankpartidas[i], &rankvitorias[i], &rankpts[i]);
      printf("%3d   -%15s\t%8d\t%5d\t%9d\n", i + 1, ranknomes[i], rankpartidas[i], rankvitorias[i], rankpts[i]);
   }
   printf("\n");
   system("Pause");
   fclose(arq);
   if ((strcmp(&ranknomes[0], &vazio)) != 0)
   {
      car = 'a';
      while ((car != 's') && (car != 'n'))
      {
         printf("\nVoc\^ deseja limpar a lista?(s/n)\n");
         scanf("%s", &car);
         if (car == 's')
         {
            arq = fopen("Rank.txt", "w");
            for (i = 0; i < 100; i++)
               fprintf(arq, "%s %d %d %d\n", vazio, 0, 0, 0);
            printf("Lista limpa!\n\n");
            system("Pause");
         }
         fclose(arq);
      }
   }
}

void jogo(void)
{
   char ch[5], tipo[40], car;
   int i, primeira, vale, naipe0, naipe1, valor;

   srand(time(NULL));
   for (i = 0; i < 40; i++)
      matriz[i] = 39 - i;

   /*Pede o nome do jogador*/
   printf("\n\nDigite seu nome:");
   scanf("%s", &nome);
   pnts[0] = 0;
   pnts[1] = 0;
   primeiro = sorteia(2);
   rodada = 0;
   vitorias = 0;
   npartidas = 0;
   saldo = 0;
   while ((pnts[0] < ptsmax) && (pnts[1] < ptsmax))
   {
      /*embaralha as cartas*/
      embaralha();
      /*Distribui as cartas entre os jogadores*/
      distribui();
      /*Atribui uma pontuação as cartas para fins de comparação do valor das mesmas*/
      atribui();
      pntsrod[0] = 0;
      pntsrod[1] = 0;
      inicial = primeiro;
      turno = -1;
      estado = 0;
      vale = 0;
      last = 2;
      local = 1;
      sorteado = sorteia(40);
      while ((pntsrod[0] < 2) && (pntsrod[1] < 2))
      {
         printf("\n***********************************\n");
         turno = turno + 1;
         mesa[1][turno] = -1;
         /*Os jogadores jogam as cartas*/
         pcordena();
         continua = TRUE;
         if ((pnts[0] == 11) && (pnts[1] == 11))
         {
            printf("\n\t*** Escurinha! ***\n");
         }
         if (inicial == 0)
         {
            if (((pnts[0] == 11) && (pnts[1] < 11)) && (turno == 0))
            {
               printf("Pc esta  com mao de 11.\n>>");
               esp = getch();
               if (qly < 45)
               {
                  printf("\nPc correu.\n>>");
                  pntsrod[1] = 3;
                  continua = FALSE;
               }
               else
               {
                  printf("\nPc aceitou.\n>>");
                  estado = 1;
                  last = -1;
               }
               esp = getch();
            }
            if (((pnts[1] == 11) && (pnts[0] < 11)) && (turno == 0))
            {
               printf("Voce esta  com mao de 11.\n>>");
               esp = getch();
               printf("\nVirada: %c %c\n", carta(virada), toon(virada));
               printf("\nSua mao eh:\n");
               for (i = 0; i < 3; i++)
               {
                  tipo[0] = '{FONTE}';
                  if (cartas[mao[1][i]] == 13)
                     strcpy(&tipo, &g);
                  if (cartas[mao[1][i]] == 12)
                     strcpy(&tipo, &c);
                  if (cartas[mao[1][i]] == 11)
                     strcpy(&tipo, &e);
                  if (cartas[mao[1][i]] == 10)
                     strcpy(&tipo, &m);
                  printf("%c %c %s\n", carta(mao[1][i]), toon(mao[1][i]), tipo);
               }
               car = 'a';
               while ((car != 's') && (car != 'n'))
               {
                  printf("Voc\^ aceita?(s/n)");
                  scanf("%s", &car);
               }
               if (car == 'n')
               {
                  pntsrod[0] = 3;
                  continua = FALSE;
               }
               else
               {
                  estado = 1;
                  last = -1;
               }
            }
            if (continua == TRUE)
               pctruca();
            if (continua == TRUE)
               pcplay();
            local = 2;
            if (continua == TRUE)
               jgtruca();
            if (continua == TRUE)
               jgplay();
         }
         else
         {
            if (((pnts[0] == 11) && (pnts[1] < 11)) && (turno == 0))
            {
               printf("Pc esta  com mao de 11.\n>>");
               esp = getch();
               if (qly < 60)
               {
                  printf("\nPc correu.\n>>");
                  pntsrod[1] = 3;
                  continua = FALSE;
               }
               else
               {
                  printf("\nPc aceitou.\n>>");
                  estado = 1;
                  last = -1;
               }
               esp = getch();
            }
            if (((pnts[1] == 11) && (pnts[0] < 11)) && (turno == 0))
            {
               printf("Voce esta  com mao de 11.\n>>");
               esp = getch();
               printf("\nVirada: %c %c\n", carta(virada), toon(virada));
               printf("\nSua mao eh:\n");
               for (i = 0; i < 3; i++)
               {
                  tipo[0] = '{FONTE}';
                  if (cartas[mao[1][i]] == 13)
                     strcpy(&tipo, &g);
                  if (cartas[mao[1][i]] == 12)
                     strcpy(&tipo, &c);
                  if (cartas[mao[1][i]] == 11)
                     strcpy(&tipo, &e);
                  if (cartas[mao[1][i]] == 10)
                     strcpy(&tipo, &m);
                  printf("%c %c %s\n", carta(mao[1][i]), toon(mao[1][i]), tipo);
               }
               car = 'a';
               while ((car != 's') && (car != 'n'))
               {
                  printf("Voc\^ aceita?(s/n)");
                  scanf("%s", &car);
               }
               if (car == 'n')
               {
                  pntsrod[0] = 3;
                  continua = FALSE;
               }
               else
               {
                  estado = 1;
                  last = -1;
               }
            }
            local = 1;
            if (continua == TRUE)
               jgtruca();
            if (continua == TRUE)
               jgplay();
            if (continua == TRUE)
               pctruca();
            if (continua == TRUE)
               pcplay();
         }
         if ((pntsrod[0] < 2) && (pntsrod[1] < 2))
         {
            /*Avalia o resultado do turno*/
            if (cartas[mesa[0][turno]] > cartas[mesa[1][turno]])
            {
               inicial = 0;
               if ((vale == 1) || (vale == 2))
                  pntsrod[0] = 3;
               else
                  pntsrod[0]++;
               if (turno == 0)
                  primeira = 0;
               printf("\nPc levou este turno.\n>>");
            }
            if (cartas[mesa[0][turno]] < cartas[mesa[1][turno]])
            {
               inicial = 1;
               if ((vale == 1) || (vale == 2))
                  pntsrod[1] = 3;
               else
                  pntsrod[1]++;
               if (turno == 0)
                  primeira = 1;
               printf("\nVoc\^ levou este turno.\n>>");
            }
            if (cartas[mesa[0][turno]] == cartas[mesa[1][turno]])
            {
               if (turno == 0)
               {
                  vale = 1;
                  printf("\nTurno empatado.\n>>");
               }
               if (turno == 1)
                  if (vale == 0)
                  {
                     pntsrod[primeira] = 3;
                     printf("\nTurno empatado.\n>>");
                  }
                  else
                  {
                     vale = 2;
                     printf("\nTurno empatado.\n>>");
                  }
               if (turno == 2)
               {
                  if (vale == 2)
                  {
                     naipe0 = (int)(mesa[1][3] / 10);
                     naipe1 = (int)(mesa[1][3] / 10);
                     if (naipe0 > naipe1)
                     {
                        pntsrod[0] = 3;
                        printf("\nTurno empatado.\n>>");
                     }
                     else
                     {
                        pntsrod[1] = 3;
                        printf("\nTurno empatado.\n>>");
                     }
                  }
                  else
                  {
                     pntsrod[primeira] = 3;
                     printf("\nTurno empatado.\n>>");
                  }
               }
            }
            esp = getch();
         }
      }
      printf("\n***********************************\n");
      valor = estado * 3;
      if (estado == 0)
         valor = 1;
      if (pntsrod[0] >= 2)
      {
         if (pnts[0] == 11)
            valor = 1;
         pnts[0] = pnts[0] + valor;
         if (valor == 1)
            printf("\nPc ganhou 1 ponto\n");
         else
            printf("\nPc ganhou %d pontos\n", valor);
         printf("\n***********************************\n");
      }
      if (pntsrod[1] >= 2)
      {
         if (pnts[1] == 11)
            valor = 1;
         if (valor == 1)
            printf("\nVoc\^ ganhou 1 ponto\n");
         else
            printf("\nVoc\^ ganhou %d pontos\n", valor);
         pnts[1] = pnts[1] + valor;
         printf("\n***********************************\n");
      }
      esp = getch();
      if (pnts[0] > 12)
         pnts[0] = 12;
      if (pnts[1] > 12)
         pnts[1] = 12;
      printf("\n\tPLACAR PARCIAL\n");
      printf("\t---------------------\n\t Pc =   %d\n", pnts[0]);
      printf("\t---------------------\n\t %s =   %d\n", nome, pnts[1]);
      printf("\t---------------------\n");
      printf(">>");
      esp = getch();
      if ((pnts[0] >= ptsmax) || (pnts[1] >= ptsmax))
      {
         if (pnts[0] >= ptsmax)
         {
            npartidas++;
            saldo = pnts[1] - ptsmax;
            printf("\n\n\tVOCE PERDEU!!!\n\n");
         }
         if (pnts[1] >= ptsmax)
         {
            vitorias++;
            npartidas++;
            saldo = ptsmax - pnts[0];
            printf("\n\n\tVOCE GANHOU!!!\n\n");
         }
         system("Pause");
      }
      if (primeiro == 0)
         primeiro++;
      else
         primeiro--;
      rodada++;
   }
   save();
}

void embaralha(void)
{
   int num, i, j, k;
   char ch[2];
   for (i = 0; i < 40; i++)
   {
      num = sorteia(40 - i);
      baralho[i] = matriz[num];
      for (j = num; j < (39); j++)
         matriz[j] = matriz[j + 1];
   }
   for (i = 0; i < 40; i++)
      matriz[i] = baralho[i];
}

int sorteia(int max)
{
   return ((int)max * rand() / (RAND_MAX + 1));
}

void distribui(void)
{
   int a, b, i;
   for (a = 0; a < 3; a++)
   {
      for (b = 0; b < 2; b++)
      {
         mao[b][a] = baralho[a * 2 + b];
      }
   }
   virada = baralho[6];
   printf("\n***********************************\n");
   printf("Rodada %2d", rodada + 1);
   printf("\n>>");
   esp = getch();
   if (primeiro == 0)
      printf("\nPc come\
>>");
   else
      printf("\nVoc\^ come\
>>");
   printf("");
   esp = getch();
}

void pcplay(void)
{
   int num, i, j, wx, ql, jogou, valormao;
   char tipo[40];

   /*Pc escolhe carta para jogar*/
   if (inicial == 0)
   {
      if ((pntsrod[0] == 0) && (turno > 0))
      {
         if (cartas[mao[0][1]] > 6)
            num = sorteia(3 - turno);
         else
            num = 0;
      }
      else
         num = sorteia(3 - turno);
   }
   if ((pnts[0] == 11) || (pnts[1] == 11))
      num = sorteia(3 - turno);
   if (inicial == 1)
   {
      jogou = FALSE;
      for (i = (2 - turno); i >= 0; i--)
      {
         if ((cartas[mao[0][i]] > cartas[mesa[1][turno]]) && (jogou == FALSE))
         {
            num = i;
            jogou = TRUE;
         }
      }
      if (jogou == FALSE)
         for (i = (2 - turno); i >= 0; i--)
         {
            if ((cartas[mao[0][i]] > cartas[mesa[1][turno]]) && (jogou == FALSE))
            {
               num = i;
               jogou = TRUE;
            }
         }
      if (jogou == FALSE)
         num = 2 - turno;
      if ((pntsrod[0] == pntsrod[1]) && (turno != 0))
         num = 0;
   }

   tipo[0] = '{FONTE}';
   mesa[0][turno] = mao[0][num];
   for (i = num; i < (2 - turno); i++)
      mao[0][i] = mao[0][i + 1];
   if (cartas[mesa[0][turno]] == 13)
      strcpy(&tipo, &g);
   if (cartas[mesa[0][turno]] == 12)
      strcpy(&tipo, &c);
   if (cartas[mesa[0][turno]] == 11)
      strcpy(&tipo, &e);
   if (cartas[mesa[0][turno]] == 10)
      strcpy(&tipo, &m);
   printf("\nPc jogou:  %c %c  %s\n", carta(mesa[0][turno]), toon(mesa[0][turno]), tipo);
   printf(">>");
   esp = getch();
}

void jgplay(void)
{
   int num, i, vle;
   char tipo[40];
   num = 10;
   while ((num < 0) || (num > (2 - turno)))
   {
      printf("\nVirada:  %c %c\n", carta(virada), toon(virada));
      if ((pnts[0] == 11) && (pnts[1] == 11))
      {
         printf("\nQue carta voc\^ quer jogar?(1");
         for (i = 1; i < (3 - turno); i++)
            printf("/%d", i + 1);
         printf(")\n");
         scanf("%d", &num);
         num--;
      }
      else
      {
         printf("\nQue carta voc\^ quer jogar?\n");
         for (i = 0; i < (3 - turno); i++)
         {
            tipo[0] = '{FONTE}';
            if (cartas[mao[1][i]] == 13)
               strcpy(&tipo, &g);
            if (cartas[mao[1][i]] == 12)
               strcpy(&tipo, &c);
            if (cartas[mao[1][i]] == 11)
               strcpy(&tipo, &e);
            if (cartas[mao[1][i]] == 10)
               strcpy(&tipo, &m);
            printf("%d - %c %c %s\n", i + 1, carta(mao[1][i]), toon(mao[1][i]), tipo);
         }
         scanf("%d", &num);
         num--;
      }
      if ((num < 0) || (num > (2 - turno)))
      {
         printf("\a\n\tVALOR INCORRETO!!\n");
         printf("\nDigite sua opcao entre 0 e %d\n", (2 - turno));
         system("Pause");
      }
      else
      {
         tipo[0] = '{FONTE}';
         if (cartas[mao[1][num]] == 13)
            strcpy(&tipo, &g);
         if (cartas[mao[1][num]] == 12)
            strcpy(&tipo, &c);
         if (cartas[mao[1][num]] == 11)
            strcpy(&tipo, &e);
         if (cartas[mao[1][num]] == 10)
            strcpy(&tipo, &m);
         printf("Voc\^ jogou: %c %c %s\n", carta(mao[1][num]), toon(mao[1][num]), tipo);
         printf(">>");
      }
      esp = getch();
   }
   mesa[1][turno] = mao[1][num];
   for (i = num; i < (2 - turno); i++)
      mao[1][i] = mao[1][i + 1];
}

void atribui(void)
{
   int vle, a, i, j, card;
   if ((virada % 10) < 9)
   {
      card = (virada % 10) + 1;
   }
   else
      card = 0;
   vle = 0;
   for (i = 0; i < 4; i++)
   {
      vle = 0;
      for (j = 0; j < 10; j++)
      {
         if (card == j)
            cartas[10 * i + j] = 10 + i;
         else
         {
            cartas[10 * i + j] = vle;
            vle = vle + 1;
         }
      }
   }
}

char toon(int card)
{
   int vle, x;
   vle = (int)(card / 10);
   if (vle == 0)
      x = 4;
   if (vle == 1)
      x = 6;
   if (vle == 2)
      x = 3;
   if (vle == 3)
      x = 5;
   return ("%c", x);
}

char carta(int card)
{
   int vle;
   char x;
   vle = card % 10;
   if (vle > 7)
      x = ("\c", 42 + vle);
   if (vle == 7)
      x = 'A';
   if (vle == 6)
      x = 'K';
   if (vle == 5)
      x = 'J';
   if (vle == 4)
      x = 'Q';
   if (vle < 4)
      x = ("%c", 52 + vle);
   return x;
}

void save(void)
{
   int i, pos, njogadores, pontos, j;
   char nm[40];

   /*Abre o arquivo para leitura, se existir*/
   if ((arq = fopen("Rank.TXT", "r")) != NULL)
   {
      /*Obtem os nomes e a pontuação*/
      for (i = 0; i < 100; i++)
      {
         fscanf(arq, "%s%d%d%d", &ranknomes[i], &rankpartidas[i], &rankvitorias[i], &rankpts[i]);
      }
   }

   /*senão, o cria*/
   else
   {
      arq = fopen("Rank.txt", "w");
      for (i = 0; i < 100; i++)
      {
         fprintf(arq, "%s %d %d %d\n", vazio, 0, 0, 0);
         strcpy(&ranknomes[i], &vazio);
         rankpartidas[i] = 0;
         rankvitorias[i] = 0;
         rankpts[i] = 0;
      }
   }

   /*fecha o arquivo*/
   fclose(arq);

   /*procura o nome e conta o número de jogadores na lista*/
   njogadores = 0;
   pos = -1;
   i = 0;
   while ((pos == -1) || (i == njogadores))
   {
      if (strcmp(&ranknomes[i], &nome) == 0)
         pos = i;
      if ((pos == -1) && (i == 99))
         pos = 100;
      if (strcmp(&ranknomes[i], &vazio) != 0)
         njogadores++;
      i++;
   }

   /*se encontrar, acrescenta ou diminui seus pontos*/
   if (pos < 100)
   {
      rankpartidas[pos] = rankpartidas[pos] + npartidas;
      rankpts[pos] = rankpts[pos] + saldo;
      rankvitorias[pos] = rankvitorias[pos] + vitorias;
   }

   /*senão, adiciona-lhe ao final da lista*/
   else
   {
      njogadores++;
      rankpartidas[njogadores - 1] = npartidas;
      rankvitorias[njogadores - 1] = vitorias;
      rankpts[njogadores - 1] = saldo;
      strcpy(&ranknomes[njogadores - 1], &nome);
   }

   /*ordena a lista em forma decrescente*/
   for (i = 0; i < (njogadores - 1); i++)
   {
      for (j = 0; j < (njogadores - 1); j++)
      {
         if (rankvitorias[j] < rankvitorias[j + 1])
         {
            pontos = rankpts[j];
            rankpts[j] = rankpts[j + 1];
            rankpts[j + 1] = pontos;

            pontos = rankvitorias[j];
            rankvitorias[j] = rankvitorias[j + 1];
            rankvitorias[j + 1] = pontos;

            pontos = rankpartidas[j];
            rankpartidas[j] = rankpartidas[j + 1];
            rankpartidas[j + 1] = pontos;

            strcpy(&nm, &ranknomes[j]);
            strcpy(&ranknomes[j], &ranknomes[j + 1]);
            strcpy(&ranknomes[j + 1], &nm);
         }
         else
         {
            if (rankvitorias[j] == rankvitorias[j + 1])
            {
               if (rankpts[j] < rankpts[j + 1])
               {
                  pontos = rankpts[j];
                  rankpts[j] = rankpts[j + 1];
                  rankpts[j + 1] = pontos;

                  pontos = rankvitorias[j];
                  rankvitorias[j] = rankvitorias[j + 1];
                  rankvitorias[j + 1] = pontos;

                  pontos = rankpartidas[j];
                  rankpartidas[j] = rankpartidas[j + 1];
                  rankpartidas[j + 1] = pontos;

                  strcpy(&nm, &ranknomes[j]);
                  strcpy(&ranknomes[j], &ranknomes[j + 1]);
                  strcpy(&ranknomes[j + 1], &nm);
               }
               else
               {
                  if (rankpts[j] == rankpts[j + 1])
                  {
                     if (rankpartidas[j] < rankpartidas[j + 1])
                     {
                        pontos = rankpts[j];
                        rankpts[j] = rankpts[j + 1];
                        rankpts[j + 1] = pontos;

                        pontos = rankvitorias[j];
                        rankvitorias[j] = rankvitorias[j + 1];
                        rankvitorias[j + 1] = pontos;

                        pontos = rankpartidas[j];
                        rankpartidas[j] = rankpartidas[j + 1];
                        rankpartidas[j + 1] = pontos;

                        strcpy(&nm, &ranknomes[j]);
                        strcpy(&ranknomes[j], &ranknomes[j + 1]);
                        strcpy(&ranknomes[j + 1], &nm);
                     }
                  }
               }
            }
         }
      }
   }

   /*recria o arquivo para escrita*/
   if ((arq = fopen("Rank.txt", "w")) == NULL)
   {
      printf("\n\aErro de leitura.\nO arquivo 'Rank.Txt' pode estar corrompido ou danificado.\n");
   }
   else
   {
      /*escreve os dados da lista*/
      for (i = 0; i < 100; i++)
      {
         fprintf(arq, "%s %d %d %d\n", ranknomes[i], rankpartidas[i], rankvitorias[i], rankpts[i]);
      }
   }

   /*fecha o arquivo*/
   fclose(arq);
}

void pcpensa(void)
{
   int i, valormao;
   valormao = 0;
   for (i = 0; i < (3 - turno); i++)
      valormao = valormao + cartas[mao[0][i]];
   qly = 3 * valormao;
   if (turno == 0)
   {
      if (inicial == 1)
      {
         for (i = 0; i < 3; i++)
            if (cartas[mao[0][i]] > cartas[mesa[1][0]])
               qly = qly + 5;
         if (qly == (3 * valormao))
         {
            qly = 25 + sorteia(50); /*Facão*/
         }
      }
   }
   if (turno == 1)
   {
      if (pntsrod[0] == 1)
      {
         qly = 5 * valormao;
         if (cartas[mesa[0][1]] == -1)
         {
            if (cartas[mao[0][0]] >= 10)
               qly = 60;
            if (cartas[mao[9][1]] >= 8)
               qly = qly + 20;
         }
         else
         {
            if (cartas[mesa[0][1]] >= 11)
               qly = 65;
            if (cartas[mao[0][1]] >= 9)
               qly = 90;
         }
         if (cartas[mao[0][0]] == 13)
            qly = 100;
      }
      if (pntsrod[1] == 1)
      {
         if (cartas[mao[0][0]] < cartas[mesa[1][1]])
         {
            qly = 30 + sorteia(50); /*Facão*/
         }
         else
         {
            if (cartas[mao[0][1]] < cartas[mesa[1][1]])
            {
               qly = 20 + sorteia(50); /*Facão*/
            }
            else
            {
               qly = 4 * valormao + sorteado;
            }
         }
      }
      else
      {
         qly = 6 * cartas[mao[0][0]] + 2 * cartas[mao[0][1]] + sorteado;
      }
   }
   if (turno == 2)
   {
      if (inicial == 1)
      {
         if (cartas[mao[0][0]] > cartas[mesa[1][2]])
         {
            qly = 100;
         }
         else
         {
            if ((cartas[mao[0][0]] == cartas[mesa[1][2]]) && (cartas[mesa[0][0]] > cartas[mesa[1][0]]))
            {
               qly = 100;
            }
            else
            {
               qly = 30 + sorteia(60); /*Facão*/
            }
         }
      }
      if (cartas[mao[0][0]] == 13)
         qly = 100;
   }
}

void pctruca(void)
{
   int num, i;
   char tipo[40];
   pcpensa();
   if (((pnts[0] < 11) && (pnts[1] < 11)) && (((last == 1) || (last == 2)) && (estado < 4)))
   {
      if (qly > (50 + sorteia(20) + estado * 8))
      {
         printf("\nPc pediu %s.\n>>", status[estado + 1]);
         esp = getch();
         printf("\nVirada: %c %c\n", carta(virada), toon(virada));
         printf("\nSua mao eh:\n");
         if (mesa[1][turno] == -1)
         {
            for (i = 0; i < (3 - turno); i++)
            {
               tipo[0] = '{FONTE}';
               if (cartas[mao[1][i]] == 13)
                  strcpy(&tipo, &g);
               if (cartas[mao[1][i]] == 12)
                  strcpy(&tipo, &c);
               if (cartas[mao[1][i]] == 11)
                  strcpy(&tipo, &e);
               if (cartas[mao[1][i]] == 10)
                  strcpy(&tipo, &m);
               printf("%c %c %s\n", carta(mao[1][i]), toon(mao[1][i]), tipo);
            }
         }
         else
         {
            for (i = 0; i < (2 - turno); i++)
            {
               tipo[0] = '{FONTE}';
               if (cartas[mao[1][i]] == 13)
                  strcpy(&tipo, &g);
               if (cartas[mao[1][i]] == 12)
                  strcpy(&tipo, &c);
               if (cartas[mao[1][i]] == 11)
                  strcpy(&tipo, &e);
               if (cartas[mao[1][i]] == 10)
                  strcpy(&tipo, &m);
               printf("%c %c %s\n", carta(mao[1][i]), toon(mao[1][i]), tipo);
            }
         }
         printf("Digite:\n1 - Aceitar;\n2 - Correr\n");
         if (estado < 3)
            printf("3 - Pedir '%s'\n", status[estado + 2]);
         scanf("%d", &num);
         if (num == 1)
         {
            estado++;
            last = 0;
         }
         if (num == 2)
         {
            continua = FALSE;
            pntsrod[0] = 3;
         }
         if (num == 3)
         {
            last = 0;
            estado++;
            local = 0;
            jgtruca();
         }
      }
   }
}

void pcordena(void)
{
   int i, j, wx;
   /*Ordena as cartas do pc no primeiro turno*/
   if (turno == 0)
   {
      for (i = 0; i < 2; i++)
         for (j = 0; j < 2; j++)
            if (cartas[mao[0][j]] < cartas[mao[0][j + 1]])
            {
               wx = mao[0][j];
               mao[0][j] = mao[0][j + 1];
               mao[0][j + 1] = wx;
            }
   }
}

void jgtruca(void)
{
   char car;
   char tipo[40];
   int cont, i, num;
   if (((pnts[0] < 11) && (pnts[1] < 11)) && (((last == 0) || (last == 2)) && (estado < 4)))
   {
      cont = TRUE;
      if (local != 0)
      {
         printf("\nVirada: %c %c", carta(virada), toon(virada));
         printf("\nSua mao \`:\n");
         for (i = 0; i < (3 - turno); i++)
         {
            tipo[0] = '{FONTE}';
            if (cartas[mao[1][i]] == 13)
               strcpy(&tipo, &g);
            if (cartas[mao[1][i]] == 12)
               strcpy(&tipo, &c);
            if (cartas[mao[1][i]] == 11)
               strcpy(&tipo, &e);
            if (cartas[mao[1][i]] == 10)
               strcpy(&tipo, &m);
            printf("%c %c %s\n", carta(mao[1][i]), toon(mao[1][i]), tipo);
         }
         num = 0;
         while ((num != 1) && (num != 2))
         {
            printf("\nVoce quer pedir %s?\n", status[estado + 1]);
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            scanf("%d", &num);
         }

         if (num == 2)
            cont = FALSE;
      }
      if (cont == TRUE)
      {
         pcpensa();
         if ((qly > (sorteia(10) + (estado + 1) * 8 + 40)) && ((qly < (sorteia(10) + (estado + 2) * 8 + 40))) || (estado > 2))
         {
            estado++;
            last = 1;
            printf("\nPc aceitou!\n>>");
            esp = getch();
         }
         else
         {
            if ((qly > (sorteia(10) + (estado + 2) * 8 + 40)) && (estado < 3))
            {
               estado++;
               last = 1;
               printf("\nPc aceitou!\n>>");
               esp = getch();
               pctruca();
            }
            else
            {
               continua = FALSE;
               pntsrod[1] = 3;
               printf("\nPc correu!\n>>");
               esp = getch();
            }
         }
      }
   }
}