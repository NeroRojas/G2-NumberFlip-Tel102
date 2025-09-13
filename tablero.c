#include <stdio.h>
#include <stdlib.h>
#include "header.h"

static void inicializar_tablero(Board *b){
    for(int i=0;i<N;i++){
        b->bombas_fila[i]=0;
        b->bombas_col[i]=0;
        for(int j=0;j<N;j++) b->celda[i][j]=1;
    }
}

static void contar_bombas(Board *b){
    for(int i=0;i<N;i++){ b->bombas_fila[i]=0; b->bombas_col[i]=0; }
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(b->celda[i][j]==0){ b->bombas_fila[i]++; b->bombas_col[j]++; }
}

static int validar_unica_linea_cero(const Board *b,int es_col,int idx){
    int c=0;
    for(int i=0;i<N;i++) if(b->bombas_fila[i]==0) c++;
    for(int j=0;j<N;j++) if(b->bombas_col[j]==0) c++;
    if(!es_col && b->bombas_fila[idx]==0) return c==1;
    if( es_col && b->bombas_col[idx]==0) return c==1;
    return 0;
}

static int colocar_bombas(Board *b,int linea_cero_es_col,int idx_linea_cero,int total_bombas){
    int bf[N]={0}, bc[N]={0}, puestas=0, tiros=0, max_tiros=N*N*20;
    while(puestas<total_bombas && tiros++<max_tiros){
        int i=rand()%N, j=rand()%N;
        if(b->celda[i][j]==0) continue;
        if(!linea_cero_es_col && i==idx_linea_cero) continue;
        if( linea_cero_es_col && j==idx_linea_cero) continue;
        if(bf[i]>=MAX_BOMBS_PER_LINE) continue;
        if(bc[j]>=MAX_BOMBS_PER_LINE) continue;
        b->celda[i][j]=0; bf[i]++; bc[j]++; puestas++;
    }
    if(puestas!=total_bombas) return 0;
    contar_bombas(b);
    return 1;
}

static void llenar_multiplicadores(Board *b,int p_x3,int p_x2){
    int m=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(b->celda[i][j]==0) continue;
            int r=rand()%100;
            if(r<p_x3){ b->celda[i][j]=3; m++; }
            else if(r<(p_x3+p_x2)){ b->celda[i][j]=2; m++; }
            else b->celda[i][j]=1;
        }
    }
    if(m==0){
        for(int pass=0;pass<2;pass++){
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(b->celda[i][j]!=0){ b->celda[i][j]=2; return; }
                }
            }
        }
    }
}

int crear_tablero(Board *b){
    int p3=18, p2=27;
    for(int intento=0;intento<MAX_TRIES;intento++){
        inicializar_tablero(b);
        int pick=rand()%(N*N);
        int fila0=pick/N, col0=pick%N;
        int es_col=rand()%2;
        int idx=es_col?col0:fila0;
        int total=6+(rand()%3);
        if(!colocar_bombas(b,es_col,idx,total)) continue;
        if(!validar_unica_linea_cero(b,es_col,idx)) continue;
        llenar_multiplicadores(b,p3,p2);
        return 1;
    }
    return 0;
}

void mostrar_tablero(const Board *b, int mostrar){

    printf("    ");

    for(int j = 0; j < N; j++){
        
        printf(" %c  ",'A'+j);
    }

    printf("| BombasFila | SumaFila\n"); 
    
    for(int i = 0; i < N; i++){

        printf(" %d |",i+1);

        for(int j = 0; j < N; j++){

            if(!mostrar){
                
                printf(" ?? ");
            }
            
            else{

                int v = b->celda[i][j];

                if(v == 0){
                    printf(" B  ");
                } 
                
                else{
                    printf(" x%d ",v);
                }
            }
        }
    
        printf("|     %d     |     %2d\n", b->bombas_fila[i], b->suma_fila[i]);
    }

    printf("----");
    for(int j = 0; j < N; j++){

        printf("----");
    }

    printf("|------------|---------\n"); 

    printf("B C");

    for(int j = 0; j < N; j++){
        
        printf(" %2d ",b->bombas_col[j]);
    }

    printf("|\n");
    printf("S C");

    for(int j = 0; j < N; j++){
        printf(" %2d ",b->suma_col[j]);
    }

    printf("|\n");
}


void sumar_filas_columnas(Board *b){

    for(int i = 0; i <N; i++){

        b->suma_fila[i] = 0;
        b->suma_col[i] = 0;

        for(int j = 0; j < N; j++){

            b->suma_fila[i] += b->celda[i][j];
            b->suma_col[i] += b->celda[j][i];
        }
    }
}

void mostrar_casillas(const Board *b, int vista[N][N]){

    printf("     ");

    for(int i = 0; i < N; i++){

        printf(" %c  ",'A'+i);
    }

    printf("BombasFila | SumaFila\n");

    for(int j = 0; j < N; j++){

        printf(" %d |", j+1);

        for(int k = 0; k < N; k++){

            if(!vista[j][k]){

                printf(" ?? ");
            }

            else{

                int v = b->celda[j][k];

                if(v == 0){
                    printf(" B  ");
                } 

                else{
                    printf(" x%d ",v);
                }
            }
        }

        printf("|     %d     |     %2d\n", b->bombas_fila[j], b->suma_fila[j]);
    }

    printf("----");

    for(int i = 0; i < N; i++){

        printf("----");
    }

    printf("|---------------------\n");
    printf("B.C ");

    for(int j = 0; j < N; j++){

        printf(" %2d ",b->bombas_col[j]);
    }

    printf("|\n");
    printf("S.C ");

    for(int k = 0; k < N; k++){

        printf(" %2d ",b->suma_col[k]);
    }

    printf("|\n");
}
