#ifndef HEADER_H
#define HEADER_H

#define N 5
#define MAX_BOMBS_PER_LINE 3
#define MAX_TRIES 10000

typedef struct {
    int celda[N][N];
    int bombas_fila[N];
    int bombas_col[N];
} Board;

int crear_tablero(Board *b);
void mostrar_tablero(const Board *b, int mostrar_valores);

#endif
