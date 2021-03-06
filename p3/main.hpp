/**
* @file main.hpp
* @brief <Práctica 3> main.
* @author Eduardo Roldán Pijuán
* @date Noviembre de 2016
*/

#ifndef P3_MAIN_HPP
#define P3_MAIN_HPP

#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include "entero.hpp"
#define cls() system("clear");

/**
* @brief Cabecera que se mostrará durante la ejecución del programa.
*/
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

/**
* @brief Mensaje que se muestra al final de cada opción del menú.
*/
void volver(){
    std::cout << std::endl << "Presiona ENTER para volver al menú.";
    std::cin.ignore();
    std::cin.ignore();
}

/**
* @brief Muestra un error personalizado por pantalla.
* @note Con 2 segundos de sleep da tiempo a leer los errores.
* @param er Error a mostrar.
*/
void error(const std::string &er){
    std::cout << std::endl << "\e[31;1m[ERROR]\e[0m - " << er;
    fflush(stdout);
    sleep(2);
}

/**
* @brief Muestra las opciones del menú e interactua con el usuario.
* @return Opción del menú a ejecutar.
* @sa error()
* @sa cabecera()
*/
int opciones(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Sumar números." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Multiplicar números." << std::endl;
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

/**
* @brief Opción sumas.
* @sa cabecera()
* @sa volver()
*/
void menu_sumas(){
    cabecera();
    int n;
    std::vector<al::Entero> numeros;
    std::cout << "Introduce cuántos números quieres sumar: ";
    std::cin >> n;
    std::cout << std::endl;
    cabecera();
    for(int i = 0 ; i < n ; ++i){
        al::Entero tmp;
        std::cout << "[" << i+1 << "] - Introduce el número: ";
        std::cin >> tmp;
        numeros.push_back(tmp);
    }
    cabecera();
//    res no inicializado porque por defecto la clase lo inicializa a 0;
    al::Entero res;
    for(int i = 0 ; i < n ; ++i){
        if(i!=0)
            std::cout << " + ";
        std::cout << numeros[i];
        res += numeros[i];
    }
    std::cout << " = " << res << std::endl;
    volver();
}

/**
* @brief Opción productos.
* @sa cabecera()
* @sa volver()
*/
void menu_productos(){
    cabecera();
    int n, margin;
    std::vector<al::Entero> numeros;
    std::cout << "Introduce cuántos números quieres multiplicar: ";
    std::cin >> n;
    std::cout << std::endl;
    std::cout << "Introduce el número máximo de dígitos que pueden tener los números para " << std::endl;
    std::cout << "multiplicarlos de forma directa: ";
    std::cin >> margin;
    fflush(stdout);
    cabecera();
    for(int i = 0 ; i < n ; ++i){
        al::Entero tmp;
        tmp.set_margin(margin);
        std::cout << "[" << i+1 << "] - Introduce el número: ";
        std::cin >> tmp;
        numeros.push_back(tmp);
    }
    cabecera();
    al::Entero res("1");
    for(int i = 0 ; i < n ; ++i){
        if(i!=0)
            std::cout << " * ";
        std::cout << numeros[i];
        res *= numeros[i];
    }
    std::cout << " = " << res << std::endl;
    volver();
}



#endif //P3_MAIN_HPP
