#include "main.hpp"

int main() {
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
                menu_cambio();
                break;
            case 2:
                menu_mochila();
                break;
        }
    }while(!salir);
    return 0;
}