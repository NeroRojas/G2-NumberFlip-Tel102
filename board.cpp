#include "board.h"
#include <cstdlib>
#include <ctime>
#include <iostream> // For debug if needed, though we avoid cout for game logic

Board::Board() {
    std::srand(std::time(nullptr));
    reset();
}

void Board::reset() {
    int p3 = 18, p2 = 27;
    int intentos = 0;
    bool tablero_valido = false;

    while (intentos < MAX_TRIES && !tablero_valido) {
        intentos++;
        inicializar_tablero();
        
        int pick = rand() % (N * N);
        int fila0 = pick / N, col0 = pick % N;
        int es_col = rand() % 2;
        int idx = es_col ? col0 : fila0;
        int total = 6 + (rand() % 3); // 6 to 8 bombs

        if (!colocar_bombas(es_col, idx, total)) {
            continue;
        }

        if (!validar_unica_linea_cero(es_col, idx)) {
            continue;
        }

        llenar_multiplicadores(p3, p2);
        sumar_filas_columnas();
        
        tablero_valido = true;
    }

    if (!tablero_valido) {
        // Fallback or simple init if generation fails (unlikely)
        inicializar_tablero();
    }

    // Reset revealed state
    safeRevealedCount = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            revealed[i][j] = false;
        }
    }
    calculateTotalSafeCells();
}

int Board::rows() const { return N; }
int Board::cols() const { return N; }

bool Board::isBomb(int row, int col) const {
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    return celda[row][col] == 0;
}

int Board::getMultiplier(int row, int col) const {
    if (row < 0 || row >= N || col < 0 || col >= N) return 0;
    return celda[row][col];
}

bool Board::revealCell(int row, int col) {
    if (row < 0 || row >= N || col < 0 || col >= N) return true; // Ignore invalid
    if (revealed[row][col]) return true; // Already revealed

    revealed[row][col] = true;

    if (celda[row][col] == 0) {
        return false; // Bomb!
    } else {
        safeRevealedCount++;
        return true; // Safe
    }
}

bool Board::isRevealed(int row, int col) const {
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    return revealed[row][col];
}

int Board::getSafeRevealedCount() const {
    return safeRevealedCount;
}

int Board::getTotalSafeCells() const {
    return totalSafeCells;
}

int Board::bombsInRow(int row) const {
    if (row < 0 || row >= N) return 0;
    return bombs_fila[row];
}

int Board::bombsInCol(int col) const {
    if (col < 0 || col >= N) return 0;
    return bombs_col[col];
}

int Board::sumInRow(int row) const {
    if (row < 0 || row >= N) return 0;
    return suma_fila[row];
}

int Board::sumInCol(int col) const {
    if (col < 0 || col >= N) return 0;
    return suma_col[col];
}

// Private helpers adapted from original code

void Board::inicializar_tablero() {
    for (int i = 0; i < N; i++) {
        bombs_fila[i] = 0;
        bombs_col[i] = 0;
        for (int j = 0; j < N; j++) {
            celda[i][j] = 1;
        }
    }
}

void Board::contar_bombas() {
    for (int i = 0; i < N; i++) {
        bombs_fila[i] = 0;
        bombs_col[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (celda[i][j] == 0) {
                bombs_fila[i]++;
                bombs_col[j]++;
            }
        }
    }
}

int Board::validar_unica_linea_cero(int es_col, int idx) {
    int c = 0;
    for (int i = 0; i < N; i++) {
        if (bombs_fila[i] == 0) c++;
    }
    for (int j = 0; j < N; j++) {
        if (bombs_col[j] == 0) c++;
    }

    if (!es_col && bombs_fila[idx] == 0) return c == 1;
    if (es_col && bombs_col[idx] == 0) return c == 1;
    return 0;
}

int Board::colocar_bombas(int linea_cero_es_col, int idx_linea_cero, int total_bombas) {
    int bf[N] = {0}, bc[N] = {0}, puestas = 0, tiros = 0, max_tiros = N * N * 20;

    while (puestas < total_bombas && tiros++ < max_tiros) {
        int i = rand() % N, j = rand() % N;

        if (celda[i][j] == 0) continue;
        if (!linea_cero_es_col && i == idx_linea_cero) continue;
        if (linea_cero_es_col && j == idx_linea_cero) continue;
        if (bf[i] >= MAX_BOMBS_PER_LINE) continue;
        if (bc[j] >= MAX_BOMBS_PER_LINE) continue;

        celda[i][j] = 0;
        bf[i]++;
        bc[j]++;
        puestas++;
    }

    if (puestas != total_bombas) return 0;

    contar_bombas();
    return 1;
}

void Board::llenar_multiplicadores(int p_x3, int p_x2) {
    int m = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (celda[i][j] == 0) continue;

            int r = rand() % 100;
            if (r < p_x3) {
                celda[i][j] = 3;
                m++;
            } else if (r < (p_x3 + p_x2)) {
                celda[i][j] = 2;
                m++;
            } else {
                celda[i][j] = 1;
            }
        }
    }

    if (m == 0) {
        // Ensure at least one >1 multiplier
        for (int pass = 0; pass < 2; pass++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (celda[i][j] != 0) {
                        celda[i][j] = 2;
                        return;
                    }
                }
            }
        }
    }
}

void Board::sumar_filas_columnas() {
    for (int i = 0; i < N; i++) {
        suma_fila[i] = 0;
        suma_col[i] = 0;
        for (int j = 0; j < N; j++) {
            suma_fila[i] += celda[i][j];
            suma_col[i] += celda[j][i];
        }
    }
}

void Board::calculateTotalSafeCells() {
    totalSafeCells = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(celda[i][j] > 0) {
                totalSafeCells++;
            }
        }
    }
}
