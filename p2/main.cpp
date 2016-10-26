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
                menu_combinatoria();
                break;
            case 2:
                menu_hanoi();
                break;
        }
    }while(!salir);
    return 0;
}
