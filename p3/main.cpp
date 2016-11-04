#include "main.hpp"

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