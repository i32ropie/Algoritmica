/**
* @file main.cpp
* @brief <Práctica 3> main.
* @author Eduardo Roldán Pijuán
* @date Noviembre de 2016
*/

#include "main.hpp"

/**
* @name Main
* Programa principal.
*/

int main() {
    int opcion;
    bool salir = false;
    do{
        opcion = opciones();
        switch(opcion){
            case 0:
                salir = true;
                break;
            case 1:
                menu_sumas();
                break;
            case 2:
                menu_productos();
                break;
        }
    }while(!salir);
    return 0;
}