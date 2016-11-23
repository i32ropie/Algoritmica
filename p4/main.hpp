#ifndef P4_MAIN_HPP
#define P4_MAIN_HPP

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "algorithms.hpp"
#include "graph.hpp"

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

void error(const std::string &er){
    std::cout << std::endl << "\e[31;1m[ERROR]\e[0m - " << er;
    fflush(stdout);
    sleep(2);
}

bool existe(const char *fichero){
    return (access( fichero, F_OK) != -1);
}

std::vector<std::string> cargar_nombres(const char *fichero){
    std::ifstream f(fichero);
    std::vector<std::string> res;
    std::string str;
    while(f >> str){
        res.push_back(str);
    }
    return res;
}

void funcion_principal() {
    std::string fichero_nombres, fichero_datos;
    do{
        cabecera();
        std::cout << "Introduce el nombre del fichero que contiene los datos de la matriz: ";
        std::getline(std::cin, fichero_datos);
        if(!existe(fichero_datos.c_str()))
            error("No existe el fichero, asegúrese de escribir bien el nombre del mismo.");
    }while(!existe(fichero_datos.c_str()));

    al::Graph g(fichero_datos);

    do{
        cabecera();
        std::cout << "Introduce el nombre del fichero que contiene los nombres de las ciudades: ";
        std::getline(std::cin, fichero_nombres);
        if(!existe(fichero_nombres.c_str()))
            error("No existe el fichero, asegúrese de escribir bien el nombre del mismo.");
    }while(!existe(fichero_nombres.c_str()));

    std::vector<std::string> nombres = cargar_nombres(fichero_nombres.c_str());
    std::pair<int, std::vector<int>> solucion = viajante_comercio(g.get_matrix());
    int distacia = solucion.first;
    std::vector<int> recorrido = solucion.second;
    cabecera();

    std::cout << "Recorrido: " << std::endl;

    bool principio = true;
    for(uint i = 0 ; i < recorrido.size() ; ++i){
        if(!principio){
            if(i != recorrido.size() - 1 )
                std::cout << "\t├ ";
            else
                std::cout << "\t└ ";
        }
        else{
            std::cout << "\t┌ ";
            principio = false;
        }
        std::cout << nombres[recorrido[i]] << std::endl;
    }

    std::cout << std::endl << "Distancia: " << distacia << std::endl;
}

#endif //P4_ALGORITHMS_HPP
