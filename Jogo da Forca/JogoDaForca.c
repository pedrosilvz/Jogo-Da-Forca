#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>
#include <locale.h>

// vari�veis globais
char palavrasecreta [TAMANHO_PALAVRA];
char chutes [26];                             
int chutesDados = 0;


void abertura() {                                        
    printf("\n====================================\n");
    printf("=           JOGO DA FORCA          =\n");
    printf("=  ESCREVA AS LETRAS EM CAPS LOCK  =\n");
    printf("====================================\n\n");

}

void chuta () {             

      printf("\nQual seu chute? ");
      char chute;
      scanf( " %c", &chute);        // o espa�o em " %c" � necess�rio quando voc� quer ler um char, pois ele desconsidera o ENTER   
      chutes[chutesDados] = chute;    // chutes na [posi��o tentativas] � igual ao chute que voc� deu
      chutesDados++;              

      printf("\n_____________________________\n");
      printf("\n       �LTIMO CHUTE: %c", chute);

        printf("\n       CHUTES DADOS:\n");
        for (int i = 0; i < chutesDados; i++) {
            printf(" %c ", chutes[i]);
      }
      
      printf("\n_____________________________\n");



      

}

int acertou () {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int jachutou (char letra) {

    int achou = 0;

     for (int j = 0; j < chutesDados; j++) {          // esse loop serve para varrer se o chute na [posi��o 0 ou mais] � igual a [posi��o 0 da array palavrasecreta] e assim por diante
        if (chutes[j] == letra) {                     // se a letra que est� no chutes na [posi��o j] for igual a igual letra que t� na palavrasecreta  [posi��o i] essa letra foi chutada         
            achou = 1;                               
            break;  
         }                    
      }               // conforme voc� vai chutando as letras, o n�mero do componente do array chutes vai aumentando (por exemplo, se eu chutar A, a letra vai para a posi��o 0 no array) 

    return achou;       // devolve o resultado dentro da vari�vel achou
}

void desenhaforca () {

    int erros = chutesErrados();
    printf("\n---------------------\n");
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%C    \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? ' ' : ' '), (erros >= 1 ? ')' : ' '));                                   // if tern�rio
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 4 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 5 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 6 ? '/' : ' '), (erros >= 7 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n---------------------\n");
    printf("\n");

     for (int i = 0; i < strlen(palavrasecreta); i++) {            // serve para varrer o array com o i = 0;
        
        int achou  =  jachutou(palavrasecreta[i]);      // passa a fun��o e os par�metros
            
            // aqui estava o c�digo

         if (achou) {
            printf ("%c ", palavrasecreta[i]);          // Se achou for 1 (verdadeiro) imprime a letra que voc� chutou no lugar do underline "_"
     } else {
            printf("_ ");                              // Caso a letra que voc� chutou n�o estiver na palavra, substitui por um underline "_"
    }         
  }
    printf("\n");
}

void adcionapalavra() {

    setlocale(LC_ALL, "Portuguese_Brazil");

    char quer;

    printf("\nVoc� jogador(a), deseja adcionar uma nova palavra no jogo? (S/N): ");
    scanf(" %c", &quer);

    if (quer == 'S') {
        char novapalavra [TAMANHO_PALAVRA];
        printf("\n Qual nova palavra voc� deseja adcionar? ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");      //r+ � leitura e escrita
        if (f == NULL) {
            setlocale(LC_ALL, "Portuguese_Brazil");
            printf("\nBanco de dados de palavras n�o dispon�vel!\n\n");
            exit(1);
        }

        int qtd;                          // pega quantidade de palavras no arquivo
        fscanf(f, "%d", &qtd);
        qtd++;                           // somou 1

        fseek(f, 0, SEEK_SET);          // Posicionou a cabe�a do arquivo pro come�o do arquivo    
        fprintf(f, "%d", qtd);          // Imprimiu em cima

        fseek(f, 0, SEEK_END);              // posiciona no fim do arquivo
        fprintf(f,"\n%s", novapalavra);

        fclose(f);

    }
}

void escolhepalavra() {
    // abriu o arquivo contendo as palavras
    FILE* f;                
    f = fopen("palavras.txt", "r");

    if(f == NULL) {
        setlocale(LC_ALL, "Portuguese_Brazil");
        printf("\nBanco de dados de palavras n�o dispon�vel!\n\n");
        exit(1);                                                            // exit (1) termina o programa
    }
    // descobri a quantidade de palavras que tem nesse arquivo (100 palavras)
    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    // calcula um n�mero rand�mico de 0 at� a quantidade de palavra (0 at� 99)
    srand(time(0));
    int randomico = rand() % qtddepalavras;

    // L� at� encontrar a palavra escolhida
    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%19s", palavrasecreta); // Evita estouro de buffer
    }

    fclose(f);
}

int chutesErrados () {
    int erros = 0;

    for (int i = 0; i < chutesDados; i++) {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++) {
            if (chutes [i] == palavrasecreta[j]) {
                existe = 1;
                break;
        }
     }
     
     if (!existe) erros++;

    }

    return erros;
}

int enforcou () {
    return chutesErrados() >= 7;                  // se o erro for maior ou igual a 7, enforca
}

int main () {
    setlocale(LC_ALL, "Portuguese_Brazil");
    escolhepalavra(palavrasecreta);

    abertura();                                     // invocar a fun��o "abertura"

    do { 

        desenhaforca();
        chuta ();                        // invoca a fun��o e recebe o endere�o de mem�ria da var�avel (*Ptentativas) na fun��o chuta e coloca na vari�vel (int tentativas)


    } while (!acertou() && !enforcou());
     

    if (acertou()) {
        printf("\n=================================================\n");
        printf("\n--> PARAB�NS!  VOC� ACERTOU A PALAVRA: %s\n", palavrasecreta);
        printf("\n=================================================\n");
    } else {
        printf("\n=================================================\n");
        printf("\n--> VOC� FOI ENFORCADO!! TENTE NOVAMENTE!\n");
        printf("----> A PALAVRA ERA: %s\n", palavrasecreta);
        printf("\n=================================================\n");
    }
    adcionapalavra();
}   