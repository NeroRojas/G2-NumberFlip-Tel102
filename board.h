#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board();
    void reset();

    int rows() const;
    int cols() const;

    bool isBomb(int row, int col) const;
    int getMultiplier(int row, int col) const; // 0 if bomb

    // Returns true if safe, false if bomb (Game Over)
    bool revealCell(int row, int col);
    bool isRevealed(int row, int col) const;

    int getSafeRevealedCount() const;
    int getTotalSafeCells() const;

    // Hints
    int bombsInRow(int row) const;
    int bombsInCol(int col) const;
    int sumInRow(int row) const;
    int sumInCol(int col) const;

private:
    static const int N = 5;
    static const int MAX_BOMBS_PER_LINE = 3;
    static const int MAX_TRIES = 1000;

    int celda[N][N];
    bool revealed[N][N];
    int bombs_fila[N];
    int bombs_col[N];
    int suma_fila[N];
    int suma_col[N];
    int safeRevealedCount;
    int totalSafeCells;

    void inicializar_tablero();
    void contar_bombas();
    int validar_unica_linea_cero(int es_col, int idx);
    int colocar_bombas(int linea_cero_es_col, int idx_linea_cero, int total_bombas);
    void llenar_multiplicadores(int p_x3, int p_x2);
    void sumar_filas_columnas();
    void calculateTotalSafeCells();
};

#endif // BOARD_H
