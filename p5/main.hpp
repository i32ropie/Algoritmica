#ifndef P5_MAIN_HPP
#define P5_MAIN_HPP


#include <iostream>
#include <cstdlib>
#include <unistd.h>
//#include <string>
//#include <vector>
#include <stdint.h> // Para usar uint64_t
#include "statistical.hpp"
#include "ClaseTiempo.hpp"
#include "currency.hpp"

#ifdef __linux__
    #define cls() system("clear");
#elif _WIN32
    #define cls() system("cls");
#endif

void cabecera(){
    cls();
    std::cout << "\e[1;92m###############################" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "####       \e[96mPrograma\e[92m        ####" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "###############################\e[0m" << std::endl << std::endl;
}

void volver(const int &count = 2, const std::string &mensaje="Presiona ENTER para volver al menú."){
    std::cout << std::endl << mensaje;
    for( int i = 0 ; i < count ; ++i)
        std::cin.ignore();
}

void error(const std::string &er){
    std::cout << std::endl << "\e[31;1m[ERROR]\e[0m - " << er;
    fflush(stdout);
    sleep(2);
}

bool existe(const char *fichero){
    return (access( fichero, F_OK) != -1);
}

void despedida(){
    cabecera();
    std::cout << "Gracias por usar el programa, ¡hasta la próxima!\e[1m" << std::endl;
    std::cout << "              _ _   __      " << std::endl << "\
     /\\      | (_) /_/      " << std::endl << "\
    /  \\   __| |_  ___  ___ " << std::endl << "\
   / /\\ \\ / _` | |/ _ \\/ __|" << std::endl << "\
  / ____ \\ (_| | | (_) \\__ \\" << std::endl << "\
 /_/    \\_\\__,_|_|\\___/|___/" << std::endl << "\
                            " << std::endl << "\
                            \e[0m" << std::endl;
}

int opciones(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Problema del cambio." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Problema de la mochila." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Salir del programa." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>2){
            error("Opción no válida. Volviendo al menú principal...");
        }
    }while(opcion<0 || opcion>2);
    return opcion;
}

int opciones_cambio(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Resolver el problema de forma normal." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Cálculo de estadísticos." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Volver al menú anterior." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>2){
            error("Opción no válida...");
        }
    }while(opcion<0 || opcion>2);
    return opcion;
}

void resolver_cambio_basico(){
    cabecera();
    int euros, centimos, centimos_total;
    std::cout << "Introduce el número de euros: ";
    std::cin >> euros;
    std::cout << std::endl << "Introduce el número de céntimos: ";
    std::cin >> centimos;
    centimos_total = euros * 100 + centimos;
    al::Currency c(centimos_total);
    c.solve();
    std::cout << c;
    volver();
}

void menu_cambio(){
    int opcion;
    bool salir = false;
    do{
        opcion = opciones_cambio();
        switch(opcion){
            case 0:
                salir = true;
                break;
            case 1:
                resolver_cambio_basico();
                break;
            case 2:
//                resolver_cabio_estadistico();
                break;
        }
    }while(!salir);
}



void menu_mochila(){}

#endif
