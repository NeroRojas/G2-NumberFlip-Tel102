#include "header.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void Board::inicializar_tablero(){

    for(int i = 0; i < N; i++){
        
        bombas_fila[i] = 0;
        bombas_col[i] = 0;

        for(int j = 0; j < N; j++){

            celda[i][j] = 1;
        }
    }
}

void Board::contar_bombas(){

    for(int i = 0; i < N; i++){
        
        bombas_fila[i] = 0;
        bombas_col[i] = 0;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){

            if(Board::celda[i][j] == 0){
                
                bombas_fila[i]++;
                bombas_col[j]++;
            }
        }
    }
}

int Board::validar_unica_linea_cero(int es_col, int idx){

    int c = 0;

    for(int i = 0; i < N; i++){

        if(bombas_fila[i] == 0){

            c++;
        }
    }

    for(int j = 0; j < N; j++){

        if(bombas_col[j] == 0){

            c++;
        }
    }

    if(!es_col && bombas_fila[idx] == 0){

        return c == 1;
    }

    if(es_col && bombas_col[idx] == 0){

        return c == 1;
    }

    return 0;
}

int Board::colocar_bombas(int linea_cero_es_col, int idx_linea_cero, int total_bombas){

    int bf[N] = {0}, bc[N]={0}, puestas=0, tiros=0, max_tiros=N*N*20;

    while(puestas < total_bombas && tiros++ < max_tiros){

        int i = rand() % N, j = rand() % N;

        if(celda[i][j] == 0){

            continue;
        }

        if(!linea_cero_es_col && i == idx_linea_cero){

            continue;
        }

        if(linea_cero_es_col && j == idx_linea_cero){

            continue;
        }

        if(bf[i] >= MAX_BOMBS_PER_LINE){

            continue;
        }

        if(bc[j] >= MAX_BOMBS_PER_LINE){

            continue;
        }

        celda[i][j] = 0;
        bf[i]++;
        bc[j]++;
        puestas++;
    }

    if(puestas != total_bombas){

        return 0;
    }

    contar_bombas();
    return 1;
}

void Board::llenar_multiplicadores(int p_x3, int p_x2){

    int m = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){

            if(celda[i][j] == 0){

                continue;
            }

            int r = rand() % 100;

            if(r<p_x3){ 
                
                celda[i][j]=3; 
                m++; 
            }
            
            else if(r<(p_x3+p_x2)){
                
                celda[i][j]=2;
                m++; 
            }

            else{
                
                celda[i][j]=1;
            }
        }
    }

    if(m == 0){

        for(int pass = 0; pass < 2; pass++){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){

                    if(celda[i][j] != 0){

                        celda[i][j]=2; 
                        return;
                    }
                }
            }
        }
    }
}

Board::Board(){

    int p3 = 18, p2 = 27;
    int intentos = 0;
    bool tablero_valido = false;

    while (intentos < MAX_TRIES && !tablero_valido){

        intentos++;
        inicializar_tablero(); 
        int pick = rand() % (N * N);
        int fila0 = pick / N, col0 = pick % N;
        int es_col = rand() % 2;
        int idx = es_col ? col0 : fila0;
        int total = 6 + (rand() % 3);

        if(!colocar_bombas(es_col, idx, total)){
            
            continue;
        }

        if(!validar_unica_linea_cero(es_col, idx)){ 
            
            continue;
        }
        
        llenar_multiplicadores(p3, p2);
        sumar_filas_columnas(); 
        
        tablero_valido = true;
    }

    if (!tablero_valido){

        cerr << "No se pudo generar un tablero válido.\n"; 
        exit(1);
    }
}

void Board::mostrar_tablero(int mostrar){
    
    cout << "    ";

    for(int j = 0; j < N; j++){

        cout << " " << (char)('A'+j) << "  ";
    }

    cout << "| BombasFila | SumaFila\n";
    
    for(int i = 0; i < N; i++){

        cout << " " << (i+1) << " |";

        for(int j = 0; j < N; j++){

            if(!mostrar){

                cout << " ?? ";

            } 
            
            else{

                int v = celda[i][j];

                if(v == 0){ 

                    cout << " B  ";
                }

                else{ 

                    cout << " " << v << " ";
                }
            }
        }
        
        cout << "|     " << bombas_fila[i] << "     |     "  << setw(2) << suma_fila[i] << "\n";
    }

    cout << "----";

    for(int j = 0; j < N; j++){ 

        cout << "----";
    }

    cout << "|------------|---------\n"; 

    cout << "B C";

    for(int j = 0; j < N; j++){

        cout << " " << setw(2) << bombas_col[j] << " ";
    }

    cout << "|\n";

    cout << "S C";

    for(int j = 0; j < N; j++){

        cout << " " << setw(2) << suma_col[j] << " ";
    }

    cout << "|\n";
}

void Board::sumar_filas_columnas(){

    for(int i = 0; i < N; i++){

        suma_fila[i] = 0;
        suma_col[i] = 0;

        for(int j = 0; j < N; j++){

            suma_fila[i] += celda[i][j];
            suma_col[i] += celda[j][i];
        }
    }
}

void Board::mostrar_casillas(int vista[N][N]){

    cout << "    ";

    for(int i = 0; i < N; i++){

        cout << " " << (char)('A'+i) << "  ";
    }

    cout << "BombasFila | SumaFila\n";

    for(int j = 0; j < N; j++){

        cout << " " << j + 1 << " |";

        for(int k = 0; k < N; k++){

            if(!vista[j][k]){

                cout << " ?? ";
            }

            else{

                int v = celda[j][k];

                if(v == 0){

                    cout << " B  ";
                }

                else{

                    cout << " " << v << " ";
                }
            }
        }

        cout << "|     " << bombas_fila[j] << "     |     "  << setw(2) << suma_fila[j] << "\n";
    }

    cout << "----";

    for(int i = 0; i < N; i++){

        cout << "----";
    }

    cout << "|---------------------\n";
    cout << "B.C ";

    for(int j = 0; j < N; j++){

        cout << " " << setw(2) << bombas_col[j] << " ";
    }

    cout << "|\n";
    cout << "S.C ";

    for(int k = 0; k < N; k++){

        cout << " " << setw(2) << suma_col[k] << " ";
    }

    cout << "|\n";
}

int Board::getValorCelda(int fila, int col){

    return celda[fila][col];
}

Board::~Board(){}