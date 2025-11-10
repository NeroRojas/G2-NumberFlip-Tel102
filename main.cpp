#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>   // MOD: se usa string para leer la coordenada completa
#include "header.h"

using namespace std;

int main(){

    int flagmenu = 1;

    while(flagmenu == 1){

        cout << "====== NUMBER-FLIP ======\n";
        cout << "\n";
        cout << "\n";
        cout << "        " << "1. Jugar\n";
        cout << "        " << "2. Salir\n";
        cout << "\n";
        cout << "Selecciona una opcion (Solo numeros): ";

        int opcion;

        if(!(cin >> opcion)){

            cin.clear();
            while(cin.get() != '\n');
            cout << "\n";
            cout << "Opcion invalida, debe ser 1 o 2.\n";
            cout << "\n";
            continue;
        }

        if(opcion == 1){

            cout << "\n";
            int visibles[N][N] = {0};
            int Casillas_Reveladas = 0;
            srand((unsigned)time(NULL));
            Board b;

            int flagjuego = 1;

            while(flagjuego == 1){

                cout << "\n";
                b.mostrar_casillas(visibles);

                string entrada; // MOD: ahora se lee la coordenada como string

                cout << "\n";
                cout << "Introduce una casilla a revelar (por ejemplo A1 o B3)\n";
                cout << "o escribe Q para volver al menú ";

                if(!(cin >> entrada)){

                    cin.clear();
                    while(cin.get() != '\n');
                    cout << "\n";
                    cout << "Entrada invalida.\n";
                    cout << "\n";
                    continue;
                }

                // MOD: se pasa todo a mayuscula para aceptar q/Q
                for(char &c : entrada){
                    if(c >= 'a' && c <= 'z'){
                        c = c - 32;
                    }
                }

                // MOD: nueva opcion para salir al menu desde la partida
                if(entrada == "Q"){

                    cout << "\n";
                    cout << "Volviendo al menu principal...\n";
                    flagjuego = 0;
                    break;
                }

                // Validacion basica de formato (ej: A1, B3)
                if(entrada.size() != 2){

                    cout << "\n";
                    cout << "Formato inválido. Usa algo como A1, B3, etc.\n";
                    cout << "\n";
                    continue;
                }

                char coord_letra = entrada[0];
                char coord_digito = entrada[1];

                if(coord_letra < 'A' || coord_letra >= 'A' + N ||
                   coord_digito < '0' || coord_digito > '9'){

                    cout << "\n";
                    cout << "Formato inválido. Usa algo como A1, B3, etc.\n";
                    cout << "\n";
                    continue;
                }

                int coord_numero = coord_digito - '0';
                int matriz_letra = coord_numero - 1;
                int matriz_numero = coord_letra - 'A';

                if(matriz_letra < 0 || matriz_letra >= N ||
                   matriz_numero < 0 || matriz_numero >= N){

                    cout << "\n";
                    cout << "Esa no es la casilla que estas buscando.\n";
                    cout << "\n";
                    continue;
                }

                if(visibles[matriz_letra][matriz_numero]){

                    cout << "\n";
                    cout << "Esa casilla ya fue revelada.\n";
                    cout << "\n";
                    continue;
                }

                visibles[matriz_letra][matriz_numero] = 1;

                if(b.getValorCelda(matriz_letra, matriz_numero) == 0){

                    cout << "\n";
                    cout << "KA-BOOM!!!! Esa casilla era una bomba.\n";
                    cout << "\n";
                    b.mostrar_tablero(1);
                    cout << "\n";
                    cout << "GAMEOVER\n";
                    flagjuego = 0;
                }
                else{

                    Casillas_Reveladas++;
                }

                if(Casillas_Reveladas == 18){

                    cout << "\n";
                    cout << "FELICIDADES!!\n";
                    cout << "Haz encontrado todos los puntos.\n";
                    cout << "\n";
                    b.mostrar_tablero(1);
                    flagjuego = 0;
                }
            }

            cout << "\n";
        }

        else if(opcion == 2){

            cout << "\n";
            cout << "Saliendo.\n";
            cout << "Gracias por jugar.\n";
            flagmenu = 0;
        }

        else{

            cout << "Opcion invalida, debe ser 1 o 2.\n";
            cout << "\n";
        }
    }

    return 0;
}
