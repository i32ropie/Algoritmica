/**
* @file main.cpp
* @brief <Práctica 6> main.
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#include "main.hpp"

/**
* @name Main
* Programa principal.
*/

int main(){
    int opcion;
    bool salir = false;
    do{
        opcion = opciones();
        switch(opcion){
            case 0:
                despedida();
                salir = true;
                break;
            case 1:
                resolver_backtracking();
                break;
            case 2:
                menu_las_vegas();
                break;
        }
    }while(!salir);
    return 0;
}