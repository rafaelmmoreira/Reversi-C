#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<time.h>

int contajogadas(int vetor[20][20],int jog,int tamanho); // Conta as jogadas v�lidas
void mostraTabuleiro(int vetor[20][20],int tamanho);     // Mostra o tabuleiro 
void jogada(int vetor[20][20],int jog, int tamanho);     // Efetua cada jogada (humano)
void jogadacomp1(int vetor[20][20],int jog,int tamanho); // Efetua cada jogada (computador - "sem" IA) 
void jogadacomp2(int vetor[20][20],int jog,int tamanho); // Efetua cada jogada (computador - com IA)
void cabecalho();   // Imprime o cabe�alho com os cr�ditos e o logotipo na tela
void menu();        // Mostra o menu inicial na tela
void instrucoes();  // Mostra as instru��es na tela
void sobre();       // Mostra detalhes sobre o programa na tela
void animacao();    // Anima��o de abertura :)

int main(int argc, char* argv[]){
    int tamanho,i,j,jogador,ia,p1,p2,opcao=0;
    int tabuleiro[20][20];
    /*Vari�veis: tamanho = tamanho do tabuleiro; jogador = n�mero do jogador;
    ia = grau de IA; p1 e p2 = pontua��o de cada jogador; opcao = op��o do menu;
    i e j s�o contadores.
    O vetor tabuleiro tem tamanho 20x20, mas o jogo trabalhar� apenas com o 
    valor escolhido pelo jogador*/
    srand(time(NULL));  //inicializa o rand - ser� �til na fun��o jogadacomp1
    textbackground(WHITE);
    cabecalho();  //faz a anima��o na tela, limpa a mesma e imprime o menu inicial
    animacao();
    cabecalho();
    menu();
    /*O loop abaixo p�e o menu na tela e aguarda que o jogador digite uma das
    5 op��es v�lidas:
        1 = jogar contra o PC; 2 = jogar contra humano; 3 = instru��es;
        4 = ler sobre o programa; 5 = sair do programa (return 0)*/
    while((opcao<1)||(opcao>5)){
         opcao=getch()-48; //converte a tecla digitada para o numero inteiro correspondente
         if (opcao==3){
                cabecalho();
                instrucoes();
                opcao=0; //cai no loop do menu novamente
                cabecalho();
                menu();
         }
         if(opcao==4){
                cabecalho();
                sobre();
                opcao=0; //cai no loop do menu novamente
                cabecalho();
                menu();
         }

         if(opcao==5) return 0; //usu�rio apertou 5? encerre o main e saia do jogo ;)
         if ((opcao==2)||(opcao==1)){
             clrscr();
             textcolor(BLACK);
             textbackground(WHITE);
             //recebe o valor do tamanho do tabuleiro: 
             printf("Digite o tamanho do tabuleiro (par, entre 8 e 20): ");
             scanf("%d",&tamanho);
             //evita que o usuario escolha um tamanho invalido:
             while ((tamanho<8)||(tamanho>20)||(tamanho%2!=0)){
             printf("\nO tamanho deve ser par entre 8 e 20.\nDigite outro valor: ");
             scanf("%d",&tamanho);
             }
             //se o jogo for contra o PC, escolhe o grau de IA:
             if(opcao==1){
                    printf("Escolha o grau de inteligencia do computador(1 ou 2): ");
                    scanf("%d",&ia);
                    while((ia<1)||(ia>2)){
                        printf("\nO grau de inteligencia deve ser 1 ou 2. Digite novamente: ");
                        scanf("%d",&ia);
                    }
             }
             //zera todas as casas do tabuleiro:
             for(i=0;i<tamanho;i++){
                 for(j=0;j<tamanho;j++){
                 tabuleiro[i][j]=0;
                 }
             }
             //adiciona as primeiras pe�as; Jogador 1 tem valor "1", jogador 2 tem valor "-1":
             tabuleiro[tamanho/2-1][tamanho/2-1]=tabuleiro[tamanho/2][tamanho/2]=-1;
             tabuleiro[tamanho/2][tamanho/2-1]=tabuleiro[tamanho/2-1][tamanho/2]=1;
             //define o jogador 1 como primeiro jogador e coloca os dois pontos iniciais de cada um:
             jogador=1;
             p1=p2=2;
             textcolor(BLACK);
             textbackground(WHITE);
             /*roda o jogo at� que todas as casas estejam ocupadas ou um jogador
             n�o possa mais fazer jogadas v�lidas*/
             while (contajogadas(tabuleiro,jogador,tamanho)!=0){
                //limpa a tela, imprime o placar atualizado e mostra o tabuleiro atualizado:
                clrscr();    
                textcolor(CYAN);
                printf("PLACAR: ");
                textcolor(BLUE);
                printf("Jogador 1 - %d",p1);
                textcolor(BLACK);
                printf(" X ");
                textcolor(LIGHTRED);
                printf("%d - Jogador 2\n",p2);
                textcolor(BLACK);
                mostraTabuleiro(tabuleiro, tamanho);
                //efetua a jogada (do jogador humano):
                jogada(tabuleiro,jogador,tamanho);
                //atualiza o placar:
                p1=p2=0;
                for (i=0;i<tamanho;i++){
                   for (j=0;j<tamanho;j++){
                      if (tabuleiro[i][j]==1) p1++;
                      if (tabuleiro[i][j]==-1)p2++;
                   }
                }
                //inverte o jogador ao final da rodada:
                jogador=jogador*(-1);
                //efetua a jogada do computador, caso ele esteja jogando:
                if(opcao==1){
                    if(contajogadas(tabuleiro,jogador,tamanho)!=0){  
                        clrscr();    
                        textcolor(CYAN);
                        printf("PLACAR: ");
                        textcolor(BLUE);
                        printf("Jogador 1 - %d",p1);
                        textcolor(BLACK);
                        printf(" X ");
                        textcolor(LIGHTRED);
                        printf("%d - Jogador 2\n",p2);
                        textcolor(BLACK);  
                        mostraTabuleiro(tabuleiro,tamanho);
                        if (ia==1) jogadacomp1(tabuleiro,jogador,tamanho);
                        if (ia==2) jogadacomp2(tabuleiro,jogador,tamanho);
                        jogador=jogador*(-1);
                    }
                }
             }
             //mostra o vencedor ao final da partida e retorna ao menu:
             clrscr();
             mostraTabuleiro(tabuleiro,tamanho);
             printf("\nNao ha mais jogadas possiveis.\n");
             if (p1>p2) printf("Jogador 1 vence por %d a %d.\n",p1,p2);
             if (p2>p1) printf("Jogador 2 vence por %d a %d.\n",p2,p1);
             if (p1==p2)printf("Empate, %d a %d.\n",p1,p2);
             printf("Pressione qualquer tecla para retornar ao menu...");
             getch();
             opcao=0;
             cabecalho();
             menu();
         }
    }
}

/*A fun��o mostraTabuleiro imprime o tabuleiro e coloca os numeros para servir 
de guia no topo e na lateral dele. 
Os par�metros s�o o tabuleiro e o tamanho que o usu�rio escolheu. */
void mostraTabuleiro(int vetor[20][20], int tamanho){
    int i, j;
    //bota os numeros no topo da tabela
    textbackground(WHITE);
    textcolor(BLACK);
    printf("  ");
    for(i=0;i<tamanho;i++){
        if(i<9)printf("0"); //para fazer 01,02,...,09 ao inv�s de 1,2...,9
        printf("%d ",i+1);
    }
    printf("\n");
    //imprime o tabuleiro e os numeros na lateral:
     for(i=0;i<tamanho;i++){
           textcolor(BLACK);
           if (i<9) printf("0");
                printf("%d ",i+1);
            for(j=0;j<tamanho;j++){
                if(vetor[i][j]==0){
                    textcolor(CYAN);
                    printf("#  "); //casa vazia
                }
                if(vetor[i][j]==1){
                    textcolor(BLUE);
                    printf("@  "); //casa do jogador 1
                }
                if(vetor[i][j]==-1){
                    textcolor(LIGHTRED);
                    printf("O  "); //casa do jogador 2
                }
            }
            printf("\n");
     }
}


/*A fun��o jogada � a respons�vel por receber a casa onde o jogador quer colocar
sua pe�a, verifica se a jogada � v�lida (e caso n�o seja, obriga o jogador a
escolher outra casa) e converte as pe�as do inimigo.
Os par�metros s�o o tabuleiro, o jogador que est� jogando no momento e o tamanho
escolhido pelo usu�rio para o tabuleiro.*/

void jogada(int vetor[20][20], int jog, int tamanho){
    int i,j,lin,col,jogval=0;
    /*As vari�veis s�o:
        lin, col = linha e coluna; i, j = contadores;
        jogval armazena valor diferente de zero se a jogada for v�lida*/
    textbackground(WHITE);
    textcolor(BLACK);
    switch(jog){
        case (1): printf("Jogador 1, digite a linha e a coluna(sintaxe: lin,col): ");
        break;
        case (-1): printf("Jogador 2, digite a linha e a coluna(sintaxe: lin,col): ");
        break;
    }
    scanf("%d,%d",&lin,&col);
    /*A matriz � de 0 a tamanho-1, mas a guia ao redor do tabuleiro � de 1 a
    tamanho, logo, o usu�rio digitar� valores 1 unidade maiores do que os valores
    reais da matriz, ent�o h� a necessidade de ajust�-los, por isso o decremento
    abaixo*/
    lin--;  
    col--; 
    //evita que o jogador escolha casa ocupada ou cause memory leak:
    while((vetor[lin][col]!=0)||((lin>tamanho)||(col>tamanho)||(lin<-1)||col<-1)){
        printf("Jogada invalida. Jogue novamente: ");
        scanf("%d,%d",&lin,&col);
        lin--;
        col--;
    }
    /*O loop abaixo verifica a presen�a de casas inimigas nos arredores da casa
    escolhida pelo jogador. Se houver alguma, o programa verifica se h� a possibilidade 
    de converter pe�as na dire��o de cada vizinho inimigo. Se alguma
    convers�o for feita, jogval recebe valor diferente de zero. Caso contr�rio,
    o jogador � obrigado a escolher outra casa e o loop recome�a.*/
    while (jogval==0){
        if((lin>0)&&(vetor[lin-1][col]==(-jog))){
            i=lin-1;
            j=col;
            while((vetor[i][j]==-jog)&&(i>0)) i--;
            if (vetor[i][j]==jog){
                i++;
                while(i!=lin){
                    vetor[i][j]=-1*vetor[i][j];
                    i++;
                }
                jogval++;
            }
        }
        if((lin<tamanho)&&(vetor[lin+1][col]==(-jog))){
            i=lin+1;
            j=col;
            while((vetor[i][j]==-jog)&&(i<tamanho-1)) i++;
            if (vetor[i][j]==jog){
                i--;
                while(i!=lin){
                    vetor[i][j]=-1*vetor[i][j];
                    i--;
                }
                jogval++;
            }
        }
        if((col>0)&&(vetor[lin][col-1]==(-jog))){
            i=lin;
            j=col-1;
            while((vetor[i][j]==-jog)&&(j>0)) j--;
            if (vetor[i][j]==jog){
                j++;
                while(j!=col){
                    vetor[i][j]=-1*vetor[i][j];
                    j++;
                }
                jogval++;
            }
        }
        if((col<tamanho)&&(vetor[lin][col+1]==(-jog))){
            i=lin;
            j=col+1;
            while((vetor[i][j]==-jog)&&(j<tamanho-1)) j++;
            if (vetor[i][j]==jog){
                j--;
                while(j!=col){
                    vetor[i][j]=-1*vetor[i][j];
                    j--;
                }
                jogval++;
            }
        }
        if(((lin>0)&&(col>0))&&(vetor[lin-1][col-1]==(-jog))){
            i=lin-1;
            j=col-1;
            while((vetor[i][j]==-jog)&&((i>0)&&(j>0))){
                i--;
                j--;
            }
            if (vetor[i][j]==jog){
                i++;
                j++;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i++;
                    j++;
                }
                jogval++;
            }
        }
        if(((lin<tamanho)&&(col>0))&&(vetor[lin+1][col-1]==(-jog))){
            i=lin+1;
            j=col-1;
            while((vetor[i][j]==-jog)&&((i<tamanho-1)&&(j>0))){
                i++;
                j--;
            }
            if (vetor[i][j]==jog){
                i--;
                j++;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i--;
                    j++;
                }
                jogval++;
            }
        }
        if(((lin<tamanho)&&(col<tamanho))&&(vetor[lin+1][col+1]==(-jog))){
            i=lin+1;
            j=col+1;
            while((vetor[i][j]==-jog)&&((i<tamanho-1)&&(j<tamanho-1))){
                i++;
                j++;
            }
            if (vetor[i][j]==jog){
                i--;
                j--;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i--;
                    j--;
                }
                jogval++;
            }
        }
        if(((lin>0)&&(col<tamanho))&&(vetor[lin-1][col+1]==(-jog))){
            i=lin-1;
            j=col+1;
            while((vetor[i][j]==-jog)&&((i>0)&&(j<tamanho-1))){
                i--;
                j++;
            }
            if (vetor[i][j]==jog){
                i++;
                j--;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i++;
                    j--;
                }
                jogval++;
            }
        }
        //nenhuma convers�o foi feita? jogue novamente! 
        if(jogval==0){
            printf("Jogada invalida. Jogue novamente: ");
            scanf("%d,%d",&lin,&col);
            lin--;
            col--;
            while((vetor[lin][col]!=0)||
        ((lin>tamanho)||(col>tamanho)||(lin<-1)||col<-1)){
                printf("Jogada invalida. Jogue novamente: ");
                scanf("%d,%d",&lin,&col);
                lin--;
                col--;
            }
        }
    }
       /*finalmente, se o loop foi quebrado (jogada v�lida), a casa escolhida
       recebe a pe�a do jogador */
        vetor[lin][col]=jog;
}

/*A fun��o contajogadas verifica quantas jogadas v�lidas podem ser feitas pelo
jogador. Caso nenhuma jogada v�lida possa ser feita, ele encerra o programa.
O funcionamento dela � bem similar ao da fun��o jogada, a diferen�a � que ela
testa todas as casas do jogo, n�o realiza nenhuma convers�o (apenas verifica
se � poss�vel efetuar alguma) e retorna o valor de jogval.
No main, o loop do jogo � quebrado caso a fun��o contajogadas retorne 0 (0 jogadas
v�lidas poss�veis)*/
int contajogadas(int vetor[20][20],int jog,int tamanho){
    int i,j,lin,col,jogval=0,jogpos=0;
    //mesmas vari�veis da fun��o jogadas, mais a jogpos.
    //A jogval verifica se uma jogada � v�lida, e � zerada cada vez que troca de casa.
    //A jogpos recebe o n�mero de jogadas poss�veis no total.
    //la�o para percorrer a matriz toda:
    for (i=0;i<tamanho;i++){
        for(j=0;j<tamanho;j++){
            jogval=0;
            if((i>0)&&(vetor[i-1][j]==(-jog))){
                lin=i-1;
                col=j;
                while((vetor[lin][col]==-jog)&&(lin>0)) lin--;
                if (vetor[lin][col]==jog) jogval++;
            }
            if((i<tamanho)&&(vetor[i+1][j]==(-jog))){
                lin=i+1;
                col=j;
                while((vetor[lin][col]==-jog)&&(lin<tamanho-1)) lin++;
                if (vetor[lin][col]==jog)jogval++;
            }
            if((j>0)&&(vetor[i][j-1]==(-jog))){
                lin=i;
                col=j-1;
                while((vetor[lin][col]==-jog)&&(col>0)) col--;
                if (vetor[lin][col]==jog) jogval++;
            }
            if((j<tamanho)&&(vetor[i][j+1]==(-jog))){
                lin=i;
                col=j+1;
                while((vetor[lin][col]==-jog)&&(col<tamanho-1)) col++;
                if (vetor[lin][col]==jog) jogval++;
            }
            if(((i>0)&&(j>0))&&(vetor[i-1][j-1]==(-jog))){
                lin=i-1;
                col=j-1;
                while((vetor[lin][col]==-jog)&&((lin>0)&(col>0))){
                    lin--;
                    col--;
                }
                if (vetor[lin][col]==jog) jogval++;
            }
            if(((i<tamanho)&&(j>0))&&(vetor[i+1][j-1]==(-jog))){
                lin=i+1;
                col=j-1;
                while((vetor[lin][col]==-jog)&&((lin<tamanho-1)&(col>0))){
                    lin++;
                    col--;
                }
                if (vetor[lin][col]==jog) jogval++;
            }
            if(((i<tamanho)&&(j<tamanho))&&(vetor[i+1][j+1]==(-jog))){
                lin=i+1;
                col=j+1;
                while((vetor[lin][col]==-jog)&&((lin<tamanho-1)&(col<tamanho-1))){
                    lin++;
                    col++;
                }
                if (vetor[lin][col]==jog) jogval++;
            }
            if(((i>0)&&(j<tamanho))&&(vetor[i-1][j+1]==(-jog))){
                lin=i-1;
                col=j+1;
                while((vetor[lin][col]==-jog)&&((lin>0)&(col<tamanho-1))){
                    lin--;
                    col++;
                }
                if (vetor[lin][col]==jog) jogval++;
            }
            if (vetor[i][j]!=0) jogval=0; // se a casa n�o estiver vazia, a jogada n�o � v�lida.
            if (jogval>0) jogpos++; //se a jogada � v�lida, a jogpos � incrementada 
        }
    }
    return(jogpos);
}

/*a fun��o cabecalho apenas imprime o cabe�alho com o famoso E da UNIFEI e os cr�ditos*/
void cabecalho(){
    clrscr();
    textbackground(WHITE);
    textcolor(BLUE);
    printf("                                                                               \n ");
    textbackground(BLUE);
    printf("     ");
    textcolor(LIGHTRED);
    printf("/");
    textcolor(BLUE);
    printf(" ");
    textbackground(WHITE);
    printf("    Universidade Federal de Itajuba                                    \n ");
    textbackground(BLUE);
    printf("  ");
    textbackground(WHITE);
    textcolor(LIGHTRED);
    printf("  /");
    textcolor(BLUE);
    printf("      Instituto de Engenharia de Sistemas e Tecnologias da Informacao    \n ");
    textbackground(BLUE);
    printf("   ");
    textcolor(LIGHTRED);
    printf("//");
    textbackground(WHITE);
    textcolor(BLUE);
    printf("      Engenharia da Computacao                                           \n ");
    textbackground(BLUE);
    printf("  ");
    textbackground(WHITE);
    textcolor(LIGHTRED);
    printf("//");
    textcolor(BLUE);
    printf("       Rafael de Moura Moreira                                            \n ");
    textbackground(BLUE);
    printf("  ");
    textcolor(LIGHTRED);
    printf("/");
    textcolor(BLUE);
    printf("    ");
    textbackground(WHITE);
    printf("    16933                                                              \n");
    textcolor(LIGHTRED);
    printf("  /                                                                            \n");
}

/*A fun��o menu apenas imprime o menu na tela, nada mais.*/
void menu(){
    textcolor(LIGHTRED);
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    textcolor(LIGHTRED);
    printf("                                R E V E R S I\n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    textcolor(BLUE);
    printf("1. Jogar contra o computador                                                   \n");
    printf("2. Jogar contra um amigo                                                       \n");
    printf("3. Como jogar                                                                  \n");
    printf("4. Sobre o jogo                                                                \n");
    printf("5. Sair                                                                        \n");
}

/*A fun��o instrucoes imprime as instru��es do jogo na tela e espera que o jogador
aperte qualquer tecla*/
void instrucoes(){
    textcolor(BLUE);
    printf("\nAntes de tudo, escolha o tamanho do tabuleiro, que devera ser um");
    printf(" numero par \nentre 8 e 20.");
    printf("\nSera gerado um tabuleiro, e no centro dele serao posicionadas as");
    printf(" pecas de cada\njogador.");
    printf("\nNo seu turno de jogo, o jogador devera adicionar uma peca ao ");
    printf("tabuleiro, e sera \nobrigado a capturar alguma peca do adversario.");
    printf("\nA captura ocorre quando uma ou mais pecas adversarias ficam \"encurraladas\"");
    printf(" entreduas pecas, seja na horizonal, seja na vertical, seja na diagonal.");
    printf("\nQuando todas as casas estiverem ocupadas ou um jogador nao puder mais");
    printf(" capturar\nqualquer peca do adversario, o jogo sera encerrado.");
    printf("\n\nO vencedor sera aquele que possuir mais pecas ao final da partida.");
    printf("\n\n\n(Pressione qualquer tecla para retornar ao menu)");
    getch();
}

/*A fun��o sobre mostra algumas informa��es sobre o programa para o usu�rio e aguarda
que ele pressione uma tecla qualquer*/
void sobre(){
    textcolor(BLUE);
    printf("\n\n\n\nEste programa foi desenvolvido em junho de 2009 para ser apresentado");
    printf("ao final do\ncurso de Tecnicas de Programacao, ministrado pelos professores ");
    printf("Enzo Seraphim e\nThatyana de Faria Piola Seraphim, do IESTI/UNIFEI, como parte");
    printf(" do curso de gra-\nduacao em Engenharia da Computacao.");
    printf("\n\nO jogo foi desenvolvido em C, no Dev-C++ 4.9.9.2 ");
    printf("com Mingw, GCC 3.4.2, GDB 5.2.1e com o DevPak CONIO.");
    printf("\n\n\n(Pressione qualquer tecla para retornar ao menu)");
    getch();
}

/*Essa fun��o � a fun��o que efetua as jogadas do computador "sem" intelig�ncia artificial.
O funcionamento � id�ntico ao da fun��o jogada, a diferen�a � que ao inv�s de ler
valores do teclado, atribui valores aleat�rios - como um jogador iniciante que n�o sabe
jogar e se contenta em meramente efetuar uma jogada v�lida, sem se importar com sua
efici�ncia*/
void jogadacomp1(int vetor[20][20],int jog,int tamanho){
    int i,j,lin,col,jogval=0,ini,fim=0;
    //as vari�veis ini e fim s�o contadores de tempo, para "enrolar" um pouco
    printf("Jogador 2 esta jogando...");
    lin=rand()%tamanho;
    col=rand()%tamanho;
    while((vetor[lin][col]!=0)||((lin>tamanho)||(col>tamanho)||(lin<-1)||col<-1)){
            lin=rand()%tamanho;
            col=rand()%tamanho;
        }
    while (jogval==0){
        
        if((lin>0)&&(vetor[lin-1][col]==(-jog))){
            i=lin-1;
            j=col;
            while((vetor[i][j]==-jog)&&(i>0)) i--;
            if (vetor[i][j]==jog){
                i++;
                while(i!=lin){
                    vetor[i][j]=-1*vetor[i][j];
                    i++;
                }
                jogval++;
            }
        }
        if((lin<tamanho)&&(vetor[lin+1][col]==(-jog))){
            i=lin+1;
            j=col;
            while((vetor[i][j]==-jog)&&(i<tamanho-1)) i++;
            if (vetor[i][j]==jog){
                i--;
                while(i!=lin){
                    vetor[i][j]=-1*vetor[i][j];
                    i--;
                }
                jogval++;
            }
        }
        if((col>0)&&(vetor[lin][col-1]==(-jog))){
            i=lin;
            j=col-1;
            while((vetor[i][j]==-jog)&&(j>0)) j--;
            if (vetor[i][j]==jog){
                j++;
                while(j!=col){
                    vetor[i][j]=-1*vetor[i][j];
                    j++;
                }
                jogval++;
            }
        }
        if((col<tamanho)&&(vetor[lin][col+1]==(-jog))){
            i=lin;
            j=col+1;
            while((vetor[i][j]==-jog)&&(j<tamanho-1)) j++;
            if (vetor[i][j]==jog){
                j--;
                while(j!=col){
                    vetor[i][j]=-1*vetor[i][j];
                    j--;
                }
                jogval++;
            }
        }
        if(((lin>0)&&(col>0))&&(vetor[lin-1][col-1]==(-jog))){
            i=lin-1;
            j=col-1;
            while((vetor[i][j]==-jog)&&((i>0)&&(j>0))){
                i--;
                j--;
            }
            if (vetor[i][j]==jog){
                i++;
                j++;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i++;
                    j++;
                }
                jogval++;
            }
        }
        if(((lin<tamanho)&&(col>0))&&(vetor[lin+1][col-1]==(-jog))){
            i=lin+1;
            j=col-1;
            while((vetor[i][j]==-jog)&&((i<tamanho-1)&&(j>0))){
                i++;
                j--;
            }
            if (vetor[i][j]==jog){
                i--;
                j++;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i--;
                    j++;
                }
                jogval++;
            }
        }
        if(((lin<tamanho)&&(col<tamanho))&&(vetor[lin+1][col+1]==(-jog))){
            i=lin+1;
            j=col+1;
            while((vetor[i][j]==-jog)&&((i<tamanho-1)&&(j<tamanho-1))){
                i++;
                j++;
            }
            if (vetor[i][j]==jog){
                i--;
                j--;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i--;
                    j--;
                }
                jogval++;
            }
        }
        if(((lin>0)&&(col<tamanho))&&(vetor[lin-1][col+1]==(-jog))){
            i=lin-1;
            j=col+1;
            while((vetor[i][j]==-jog)&&((i>0)&&(j<tamanho-1))){
                i--;
                j++;
            }
            if (vetor[i][j]==jog){
                i++;
                j--;
                while((i!=lin)&&(j!=col)){
                    vetor[i][j]=-1*vetor[i][j];
                    i++;
                    j--;
                }
                jogval++;
            }
        }

        if(jogval==0){
            lin=rand()%tamanho;
            col=rand()%tamanho;
            while((vetor[lin][col]!=0)||((lin>tamanho)||(col>tamanho)||(lin<-1)||col<-1)){
                lin=rand()%tamanho;
                col=rand()%tamanho;
            }
        }
    }
        vetor[lin][col]=jog;
    //para dar uma "enrolada" para deixar o jogador ver o tabuleiro com a sua 
    //pr�pria jogada antes de mostrar a jogada do computador:
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<1.5) fim=clock();
}

/*Essa fun��o realiza jogadas do computador, por�m de forma mais inteligente que a fun��o
jogadacomp1. Ela verifica todas as jogadas poss�veis e conta quantas pe�as ela ganharia
em cada jogada. Ela sempre armazena o maior valor poss�vel na vari�vel melhorplacar
e as coordenadas i e j da melhor jogada nas vari�veis mi e mj. No final de todas as 
verifica��es, ela efetua a jogada e realiza as convers�es*/
void jogadacomp2(int vetor[20][20],int jog,int tamanho){
 int i,j,lin,col,jogval,placar,melhorplacar=0,mi,mj,ini,fim=0;
 printf("Jogador 2 esta jogando..."); 
 for (i=0;i<tamanho;i++){
        for(j=0;j<tamanho;j++){
            jogval=placar=0;
            if((i>0)&&(vetor[i-1][j]==(-jog))){
                lin=i-1;
                col=j;
                while((vetor[lin][col]==-jog)&&(lin>0)) lin--;
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(i-lin);
                }    
            }
            if((i<tamanho)&&(vetor[i+1][j]==(-jog))){
                lin=i+1;
                col=j;
                while((vetor[lin][col]==-jog)&&(lin<tamanho-1)) lin++;
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(lin-i);
                }
            }
            if((j>0)&&(vetor[i][j-1]==(-jog))){
                lin=i;
                col=j-1;
                while((vetor[lin][col]==-jog)&&(col>0)) col--;
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(j-col);
                }
            }
            if((j<tamanho)&&(vetor[i][j+1]==(-jog))){
                lin=i;
                col=j+1;
                while((vetor[lin][col]==-jog)&&(col<tamanho-1)) col++;
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(col-j);
                }
            }
            if(((i>0)&&(j>0))&&(vetor[i-1][j-1]==(-jog))){
                lin=i-1;
                col=i-1;
                while((vetor[lin][col]==-jog)&&((lin>0)&(col>0))){
                    lin--;
                    col--;
                }
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(i-lin)+(j-col);
                }
            }
            if(((i<tamanho)&&(j>0))&&(vetor[i+1][j-1]==(-jog))){
                lin=i+1;
                col=j-1;
                while((vetor[lin][col]==-jog)&&((lin<tamanho-1)&(col>0))){
                    lin++;
                    col--;
                }
                if (vetor[lin][col]==jog){ 
                    jogval++;
                    placar=placar+(lin-i)+(j-col);
                }
            }
            if(((i<tamanho)&&(j<tamanho))&&(vetor[i+1][j+1]==(-jog))){
                lin=i+1;
                col=j+1;
                while((vetor[lin][col]==-jog)&&((lin<tamanho-1)&(col<tamanho-1))){
                    lin++;
                    col++;
                }
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(lin-i)+(col-j);
                }

            }
            if(((i>0)&&(j<tamanho))&&(vetor[i-1][j+1]==(-jog))){
                lin=i-1;
                col=j+1;
                while((vetor[lin][col]==-jog)&&((lin>0)&(col<tamanho-1))){
                    lin--;
                    col++;
                }
                if (vetor[lin][col]==jog){
                    jogval++;
                    placar=placar+(i-lin)+(col-j);
                }
            }
            if (vetor[i][j]!=0) jogval=0;
            if (jogval>0){
                if (placar>melhorplacar){
                    melhorplacar=placar;
                    mi=i;
                    mj=j;
                }
            } 
        }
    }   
    vetor[mi][mj]=jog;
    //escolhida a melhor jogada, s�o feitas as convers�es de pe�as:   
    if (vetor[mi-1][mj]==-jog){
        i=mi-1;
        j=mj;
        while((vetor[i][j]==-jog)&&(i>0)) i--;
        if (vetor[i][j]==jog){
            i++;
            while(i!=mi){
                vetor[i][j]=-1*vetor[i][j];
                i++;
            }
        }
    }
    if (vetor[mi+1][mj]==-jog){
        i=mi+1;
        j=mj;
        while((vetor[i][j]==-jog)&&(i<tamanho)) i++;
        if (vetor[i][j]==jog){
            i--;
            while(i!=mi){
                vetor[i][j]=-1*vetor[i][j];
                i--;
            }
        }
    }
    if (vetor[mi][mj-1]==-jog){
        i=mi;
        j=mj-1;
        while((vetor[i][j]==-jog)&&(j>0)) j--;
        if (vetor[i][j]==jog){
            j++;
            while(j!=mj){
                vetor[i][j]=-1*vetor[i][j];
                j++;
            }
        }
    }
    if (vetor[mi][mj+1]==-jog){
        i=mi;
        j=mj+1;
        while((vetor[i][j]==-jog)&&(j<tamanho)) j++;
        if (vetor[i][j]==jog){
            j--;
            while(j!=mj){
                vetor[i][j]=-1*vetor[i][j];
                j--;
            }
        }
    }
    if (vetor[mi-1][mj-1]==-jog){
        i=mi-1;
        j=mj-1;
        while((vetor[i][j]==-jog)&&((j>0)&&(i>0))){ 
            i--;
            j--;
        }
        if (vetor[i][j]==jog){
            i++;
            j++;
            while((j!=mj)&&(i!=mi)){
                vetor[i][j]=-1*vetor[i][j];
                i++;
                j++;
            }
        }
    }
    if (vetor[mi+1][mj+1]==-jog){
        i=mi+1;
        j=mj+1;
        while((vetor[i][j]==-jog)&&((j<tamanho)&&(i<tamanho))){ 
            i++;
            j++;
        }
        if (vetor[i][j]==jog){
            i--;
            j--;
            while((j!=mj)&&(i!=mi)){
                vetor[i][j]=-1*vetor[i][j];
                i--;
                j--;
            }
        }
    }
    if (vetor[mi+1][mj-1]==-jog){
        i=mi+1;
        j=mj-1;
        while((vetor[i][j]==-jog)&&((j>0)&&(i<tamanho))){ 
            i++;
            j--;
        }
        if (vetor[i][j]==jog){
            i--;
            j++;
            while((j!=mj)&&(i!=mi)){
                vetor[i][j]=-1*vetor[i][j];
                i--;
                j++;
            }
        }
    }
    if (vetor[mi-1][mj+1]==-jog){
        i=mi-1;
        j=mj+1;
        while((vetor[i][j]==-jog)&&((j<tamanho)&&(i>0))){ 
            i--;
            j++;
        }
        if (vetor[i][j]==jog){
            i++;
            j--;
            while((j!=mj)&&(i!=mi)){
                vetor[i][j]=-1*vetor[i][j];
                i++;
                j--;
            }
        }
    }
    //para dar uma "enrolada" para deixar o jogador ver o tabuleiro com a sua 
    //pr�pria jogada antes de mostrar a jogada do computador:
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<1.5) fim=clock();
}

/*Anima��o de abertura do jogo - Consiste apenas em apagar e reescrever uma linha
ap�s intervalos de tempo com o uso da clock().*/
void animacao(){
    int ini,fim=0;
    textcolor(BLUE);
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("                                  E V E R S");
    textcolor(LIGHTRED);
    printf(" I\n");
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<0.5) fim=clock();
    ini=fim=0;
    gotoxy(1,14);
    delline();
    textcolor(LIGHTRED);
    printf("                                R");
    textcolor(BLUE);
    printf(" E V E R S");
    textcolor(LIGHTRED);
    printf(" I");
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<0.2) fim=clock();
    ini=fim=0;
    gotoxy(1,14);
    delline();
    printf("                                R");
    textcolor(BLUE);
    printf(" E V E R ");
    textcolor(LIGHTRED);
    printf("S I");
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<0.2) fim=clock();
    ini=fim=0;
    gotoxy(1,14);
    delline();
    printf("                                R");
    textcolor(BLUE);
    printf(" E V E ");
    textcolor(LIGHTRED);
    printf("R S I");
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<0.2) fim=clock();
    ini=fim=0;
    gotoxy(1,14);
    delline();
    printf("                                R");
    textcolor(BLUE);
    printf(" E V ");
    textcolor(LIGHTRED);
    printf("E R S I");
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<0.2) fim=clock();
    ini=fim=0;
    gotoxy(1,14);
    delline();
    printf("                                R");
    textcolor(BLUE);
    printf(" E ");
    textcolor(LIGHTRED);
    printf("V E R S I");
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<0.2) fim=clock();
    ini=fim=0;
}
