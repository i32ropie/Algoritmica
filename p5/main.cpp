/**
* @file main.cpp
* @brief <Práctica 4> main.
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#include "main.hpp"

/**
* @name Main
* Programa principal.
*/

int main() {
    int opcion;
    bool salir = false;
    presentacion();
    do{
        opcion = opciones();
        switch(opcion){
            case 0:
                despedida();
                salir = true;
                break;
            case 1:
                resolver_cambio_basico();
                break;
            case 2:
                resolver_cambio_estadistico();
                break;
        }
    }while(!salir);
    return 0;
}