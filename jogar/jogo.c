#include <stdio.h>
#include <stdlib.h>

int main (){
    
    /*
    menu
    printf (BOLD "\nSelecione uma opcao para comecar: " NONE); 
            Sleep (400);
            printf (C_CYAN "\n1. Jogar" NONE); Sleep (100);
            printf ("\n2. Ranking"); Sleep (100);
            printf ("\n3. Sobre"); Sleep (100);
            printf ("\n4. Sair"); Sleep (100);
            printf ("\n");
            printf ("Opcao: ");
            scanf ("%d", &option);
            */
           /*
           switch(option){

            case 1:
            return jogar;
            break;

            case 2:
            return ranking;
            break;

            case 3:
            return sobre;
            break;

            case 4:
            break;

            default:
            printf("Opcao invalida!");
           }
           */
           
}

    //função mandar cair
    //função pedir x
    //função fugir

void jogar(){

    //struct com os dados do jogador
    int i, opcao;
    for(i=0; i<12; i++){
        //continua  jogo
    }
    printf("FIM DE JOGO/n");
    printf("Selecione uma opcao: /n");
    printf("1- Iniciar novo jogo/n");
    printf("2- Voltar para o menu principal /n");
    scanf("%d", &opcao);

    if(opcao==1){
        return jogar;
    }
    else if(opcao==2){
        return main; //lembrar que o arquivo de ranking deve ser atualizado
    }

}
int truco() {
        int op;
        printf("");//menu com as opcoes de truco
        scanf("%d", &op);
        
        //sequencia de if else retornando uma funcao de acordo com a opcao
        if(op==1){
            return //mandar cair;
        }
        else if(op==2){
            return //pedir x, onde x sera 6,9 ou 12
        }
        else if(op==3){
            return //fugir
        }
            else{
                printf("Opcao invalida!");
            }
        }

    int empate(){ //no escuro

    }

    int mao11(){

    }


//função ranking com o arquivo do ranking

int sobre(){
    /*
        Sleep (500);
        printf ( BOLD "\nSOBRE: \n" NONE);
        printf ("   Projeto: Jogo de truco mineiro criado para o TCD (trabalho de conclusao de disciplina) de Programacao Procedimental\n");
        printf ("   Autores: Ana Alice Cordeiro de Souza @alicecordeiro__\n");
        printf ("            Ester Freitas @esterzolas\n            Fernanda Ferreira de Melo @nandafm8\n            Jean Souto G. Moreira @jean.soutoo");
        printf (BOLD "\n   Turma 69 de Ciencia da Computacao / FACOM - UFU / 2022.1 (15/01/2023)");
        printf (C_BLUE "\n   Obrigado por jogar! %c", 3, NONE);
        printf ("\n");
        Sleep (500);
    */   
}
