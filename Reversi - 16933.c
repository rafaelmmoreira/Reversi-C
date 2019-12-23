#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<time.h>

int contajogadas(int vetor[20][20],int jog,int tamanho); // Conta as jogadas válidas
void mostraTabuleiro(int vetor[20][20],int tamanho);     // Mostra o tabuleiro 
void jogada(int vetor[20][20],int jog, int tamanho);     // Efetua cada jogada (humano)
void jogadacomp1(int vetor[20][20],int jog,int tamanho); // Efetua cada jogada (computador - "sem" IA) 
void jogadacomp2(int vetor[20][20],int jog,int tamanho); // Efetua cada jogada (computador - com IA)
void cabecalho();   // Imprime o cabeçalho com os créditos e o logotipo na tela
void menu();        // Mostra o menu inicial na tela
void instrucoes();  // Mostra as instruções na tela
void sobre();       // Mostra detalhes sobre o programa na tela
void animacao();    // Animação de abertura :)

int main(int argc, char* argv[]){
    int tamanho,i,j,jogador,ia,p1,p2,opcao=0;
    int tabuleiro[20][20];
    /*Variáveis: tamanho = tamanho do tabuleiro; jogador = número do jogador;
    ia = grau de IA; p1 e p2 = pontuação de cada jogador; opcao = opção do menu;
    i e j são contadores.
    O vetor tabuleiro tem tamanho 20x20, mas o jogo trabalhará apenas com o 
    valor escolhido pelo jogador*/
    srand(time(NULL));  //inicializa o rand - será útil na função jogadacomp1
    textbackground(WHITE);
    cabecalho();  //faz a animação na tela, limpa a mesma e imprime o menu inicial
    animacao();
    cabecalho();
    menu();
    /*O loop abaixo põe o menu na tela e aguarda que o jogador digite uma das
    5 opções válidas:
        1 = jogar contra o PC; 2 = jogar contra humano; 3 = instruções;
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

         if(opcao==5) return 0; //usuário apertou 5? encerre o main e saia do jogo ;)
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
             //adiciona as primeiras peças; Jogador 1 tem valor "1", jogador 2 tem valor "-1":
             tabuleiro[tamanho/2-1][tamanho/2-1]=tabuleiro[tamanho/2][tamanho/2]=-1;
             tabuleiro[tamanho/2][tamanho/2-1]=tabuleiro[tamanho/2-1][tamanho/2]=1;
             //define o jogador 1 como primeiro jogador e coloca os dois pontos iniciais de cada um:
             jogador=1;
             p1=p2=2;
             textcolor(BLACK);
             textbackground(WHITE);
             /*roda o jogo até que todas as casas estejam ocupadas ou um jogador
             não possa mais fazer jogadas válidas*/
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

/*A função mostraTabuleiro imprime o tabuleiro e coloca os numeros para servir 
de guia no topo e na lateral dele. 
Os parâmetros são o tabuleiro e o tamanho que o usuário escolheu. */
void mostraTabuleiro(int vetor[20][20], int tamanho){
    int i, j;
    //bota os numeros no topo da tabela
    textbackground(WHITE);
    textcolor(BLACK);
    printf("  ");
    for(i=0;i<tamanho;i++){
        if(i<9)printf("0"); //para fazer 01,02,...,09 ao invés de 1,2...,9
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


/*A função jogada é a responsável por receber a casa onde o jogador quer colocar
sua peça, verifica se a jogada é válida (e caso não seja, obriga o jogador a
escolher outra casa) e converte as peças do inimigo.
Os parâmetros são o tabuleiro, o jogador que está jogando no momento e o tamanho
escolhido pelo usuário para o tabuleiro.*/

void jogada(int vetor[20][20], int jog, int tamanho){
    int i,j,lin,col,jogval=0;
    /*As variáveis são:
        lin, col = linha e coluna; i, j = contadores;
        jogval armazena valor diferente de zero se a jogada for válida*/
    textbackground(WHITE);
    textcolor(BLACK);
    switch(jog){
        case (1): printf("Jogador 1, digite a linha e a coluna(sintaxe: lin,col): ");
        break;
        case (-1): printf("Jogador 2, digite a linha e a coluna(sintaxe: lin,col): ");
        break;
    }
    scanf("%d,%d",&lin,&col);
    /*A matriz é de 0 a tamanho-1, mas a guia ao redor do tabuleiro é de 1 a
    tamanho, logo, o usuário digitará valores 1 unidade maiores do que os valores
    reais da matriz, então há a necessidade de ajustá-los, por isso o decremento
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
    /*O loop abaixo verifica a presença de casas inimigas nos arredores da casa
    escolhida pelo jogador. Se houver alguma, o programa verifica se há a possibilidade 
    de converter peças na direção de cada vizinho inimigo. Se alguma
    conversão for feita, jogval recebe valor diferente de zero. Caso contrário,
    o jogador é obrigado a escolher outra casa e o loop recomeça.*/
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
        //nenhuma conversão foi feita? jogue novamente! 
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
       /*finalmente, se o loop foi quebrado (jogada válida), a casa escolhida
       recebe a peça do jogador */
        vetor[lin][col]=jog;
}

/*A função contajogadas verifica quantas jogadas válidas podem ser feitas pelo
jogador. Caso nenhuma jogada válida possa ser feita, ele encerra o programa.
O funcionamento dela é bem similar ao da função jogada, a diferença é que ela
testa todas as casas do jogo, não realiza nenhuma conversão (apenas verifica
se é possível efetuar alguma) e retorna o valor de jogval.
No main, o loop do jogo é quebrado caso a função contajogadas retorne 0 (0 jogadas
válidas possíveis)*/
int contajogadas(int vetor[20][20],int jog,int tamanho){
    int i,j,lin,col,jogval=0,jogpos=0;
    //mesmas variáveis da função jogadas, mais a jogpos.
    //A jogval verifica se uma jogada é válida, e é zerada cada vez que troca de casa.
    //A jogpos recebe o número de jogadas possíveis no total.
    //laço para percorrer a matriz toda:
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
            if (vetor[i][j]!=0) jogval=0; // se a casa não estiver vazia, a jogada não é válida.
            if (jogval>0) jogpos++; //se a jogada é válida, a jogpos é incrementada 
        }
    }
    return(jogpos);
}

/*a função cabecalho apenas imprime o cabeçalho com o famoso E da UNIFEI e os créditos*/
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

/*A função menu apenas imprime o menu na tela, nada mais.*/
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

/*A função instrucoes imprime as instruções do jogo na tela e espera que o jogador
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

/*A função sobre mostra algumas informações sobre o programa para o usuário e aguarda
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

/*Essa função é a função que efetua as jogadas do computador "sem" inteligência artificial.
O funcionamento é idêntico ao da função jogada, a diferença é que ao invés de ler
valores do teclado, atribui valores aleatórios - como um jogador iniciante que não sabe
jogar e se contenta em meramente efetuar uma jogada válida, sem se importar com sua
eficiência*/
void jogadacomp1(int vetor[20][20],int jog,int tamanho){
    int i,j,lin,col,jogval=0,ini,fim=0;
    //as variáveis ini e fim são contadores de tempo, para "enrolar" um pouco
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
    //própria jogada antes de mostrar a jogada do computador:
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<1.5) fim=clock();
}

/*Essa função realiza jogadas do computador, porém de forma mais inteligente que a função
jogadacomp1. Ela verifica todas as jogadas possíveis e conta quantas peças ela ganharia
em cada jogada. Ela sempre armazena o maior valor possível na variável melhorplacar
e as coordenadas i e j da melhor jogada nas variáveis mi e mj. No final de todas as 
verificações, ela efetua a jogada e realiza as conversões*/
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
    //escolhida a melhor jogada, são feitas as conversões de peças:   
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
    //própria jogada antes de mostrar a jogada do computador:
    ini=clock();
    while((fim-ini)/CLOCKS_PER_SEC<1.5) fim=clock();
}

/*Animação de abertura do jogo - Consiste apenas em apagar e reescrever uma linha
após intervalos de tempo com o uso da clock().*/
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
