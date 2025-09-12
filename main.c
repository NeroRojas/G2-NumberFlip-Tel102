#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main(){

    int flagmenu = 1;

    while(flagmenu == 1){

        printf("====== NUMBER-FLIP ======\n");
        printf("\n");
        printf("\n");
        printf("        ");
        printf("1. Jugar\n");
        printf("        ");
        printf("2. Salir\n");
        printf("\n");
        printf("Seleciona una opcion (Solo numeros): ");

        int opcion;

        if(scanf("%d", &opcion) != 1) {

            while(getchar() != '\n');
            printf("\n");
            printf("Opcion invalida, debe ser 1 o 2.\n");
            printf("\n");
            continue;
        }


        if(opcion == 1){

            printf("\n");
            int visibles[N][N] = {0};
            int Casillas_Reveladas = 0;

            srand((unsigned)time(NULL));
            Board b;

            if(!crear_tablero(&b)){

                printf("\n");
                fprintf(stderr,"No se pudo generar un tablero válido.\n");
                printf("\n");
                return 1;
            }

            sumar_filas_columnas(&b);

            int flagjuego = 1;

            while(flagjuego == 1) {

                printf("\n");
                mostrar_casillas(&b, visibles);

                char coord_letra;
                int coord_numero;

                printf("\n");
                printf("Introduce una casilla a revelar (por ejemplo A1 o B3): ");

                if(scanf(" %c%d", &coord_letra, &coord_numero) != 2){

                    while(getchar() != '\n');
                    printf("\n");
                    printf("Opcion invalida debe ser con el formato A1, C4, etc...\n");
                    printf("\n");
                    continue;
                }

                int matriz_letra = coord_numero - 1;
                int matriz_numero = coord_letra - 'A';

                if(matriz_letra < 0 || matriz_letra >= N || matriz_numero < 0 || matriz_numero >= N){
                    
                    printf("\n");
                    printf("Esa no es la casilla que estas buscando.\n");
                    printf("\n");
                    continue;
                }

                if (visibles[matriz_letra][matriz_numero]) {

                    printf("\n");
                    printf("Esa casilla ya fue revelada.\n");
                    printf("\n");
                    continue;
                }

                visibles[matriz_letra][matriz_numero] = 1;

                if(b.celda[matriz_letra][matriz_numero] == 0){

                    printf("\n");
                    printf("KA-BOOM!!!! Esa casilla era una bomba.\n");
                    printf("\n");
                    mostrar_tablero(&b, 1);
                    printf("\n");
                    printf("GAMEOVER\n");
                    flagjuego = 0;
                } 
                
                else {
                    Casillas_Reveladas++;
                }
                
                if(Casillas_Reveladas == 18){

                    printf("\n");
                    printf("FELICIDADEZ!!!\n");
                    printf("Haz encontrado todos los puntos.\n");
                    printf("\n");
                    mostrar_tablero(&b, 1);
                    flagjuego = 0;
            }
        }

            printf("\n");
        }

        if(opcion == 2){

            printf("\n");
            printf("Saliendo.\n");
            printf("Gracias por jugar.\n");
            flagmenu = 0;
        }

        if(opcion != 1 && opcion != 2){

            printf("Opcion invalida, debe ser 1 o 2.\n");
            printf("\n");
        }
    
    }

    return 0;
}
