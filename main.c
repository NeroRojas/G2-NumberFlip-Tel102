#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main(void){
    srand((unsigned)time(NULL));
    Board b;
    if(!crear_tablero(&b)){
        fprintf(stderr,"No se pudo generar un tablero válido.\n");
        return 1;
    }
    puts("\n=============== OCULTO ==============");
    mostrar_tablero(&b,0);
    puts("\n============== REVELADO =============");
    mostrar_tablero(&b,1);
    return 0;
}
