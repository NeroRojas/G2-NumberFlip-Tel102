#ifndef HEADER_H
#define HEADER_H

#define N 5
#define MAX_BOMBS_PER_LINE 3
#define MAX_TRIES 10000

class Board {
    private:
        int celda[N][N];
        int bombas_fila[N];
        int bombas_col[N];
        int suma_fila[N];
        int suma_col[N];

        void inicializar_tablero();
        void contar_bombas();
        int validar_unica_linea_cero(int es_col, int idx);
        int colocar_bombas(int linea_cero_es_col, int idx_linea_cero, int total_bombas);
        void llenar_multiplicadores(int p_x3, int p_x2);
        void sumar_filas_columnas(); 

    public:
    
        Board();
        ~Board();

        void mostrar_tablero(int mostrar_valores); 
        void mostrar_casillas(int vista[N][N]);
        int getValorCelda(int fila, int col);
    };

#endif