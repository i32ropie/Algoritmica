//
// Created by i32ropie on 21/12/16.
//

#ifndef P6_REINAS_BONITO_HPP_HPP
#define P6_REINAS_BONITO_HPP_HPP

#include <vector>
#include <ctime>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

struct tablero{
    std::string negro = "■ ";
    std::string blanco = "□ ";
    std::string reina = "♛ ";
};

void mostrar_soluciones(const std::vector<std::vector<int>> &soluciones){
    for(int k = 0 ; k < soluciones.size() ; ++k){
        std::cout << "Solución " << k+1 << std::endl;
        std::vector<int> sol = soluciones[k];
        for(int i = 0 ; i < sol.size() ; ++i){
            for(int j = 0 ; j < sol.size() ; ++j){
                if(j == sol[i]){
                    std::cout << "\e[101m  ";
                }
                else if((i+j)%2==0){
                    std::cout << "\e[47m  ";
                }
                else{
                    std::cout << "\e[40m  ";
                }
            }
            std::cout << "\e[m" << std::endl;
        }
        std::cout << std::endl;
    }
}

std::string exportar_soluciones(const std::vector<std::vector<int>> &soluciones){
    struct stat st = {0};
    tablero t;
    if(stat("soluciones", &st) == -1){
        mkdir("soluciones", 0700);
    }
    time_t epoch = std::time(0);
    std::string carpeta_salida = "soluciones/" + std::to_string(epoch);
    mkdir(carpeta_salida.c_str(), 0700);
    for(int k = 0 ; k < soluciones.size() ; ++k){
        std::string fichero_salida = carpeta_salida + "/" + std::to_string(k) + ".sol";
        std::ofstream f(fichero_salida.c_str());
        std::vector<int> sol = soluciones[k];
        for(int i = 0 ; i < sol.size() ; ++i){
            for(int j = 0 ; j < sol.size() ; ++j){
                if(j == sol[i]){
                    f << t.reina;
                }
                else if((i+j)%2==0){
                    f << t.blanco;
                }
                else{
                    f << t.negro;
                }
            }
            f << std::endl;
        }
        f.close();
    }
    return carpeta_salida;
}

#endif //P6_REINAS_BONITO_HPP_HPP
