/**
* @file extra_functions.hpp
* @brief <Práctica 6> Funciones auxiliares
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#ifndef P6_EXTRA_FUNCTIONS_HPP
#define P6_EXTRA_FUNCTIONS_HPP

#include <vector>
#include <ctime>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * @brief Estructura usada para exportar las soluciones.
 */
struct tablero{
    std::string negro = "■ ";
    std::string blanco = "□ ";
    std::string reina = "♛ ";
};

/**
 * @brief Función que dado un vector solución del problema de las N-Reinas imprime por pantalla un tablero con la solución marcando en rojo el lugar donde van las reinas.
 * @param sol Vector solución (std::vector<int>)
 */
void imprimir_tablero(const std::vector<int> &sol){
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

/**
 * @brief Función interfaz para la impresión de un vector de vectores de soluciones.
 * @param soluciones Vector de vectores de soluciones (std::vector<std::vector<int>>)
 * @sa imprimir_tablero()
 */
void mostrar_soluciones(const std::vector<std::vector<int>> &soluciones){
    for(int k = 0 ; k < soluciones.size() ; ++k){
        std::cout << "Solución " << k+1 << std::endl;
        std::vector<int> sol = soluciones[k];
        imprimir_tablero(sol);
    }
}

/**
 * @brief Función para exportar las soluciones del problema de las N-Reinas.
 * @note La idea de esta función es poder ver todas las soluciones una vez resuelto el problema, ya que si resolvemos por ejemplo el problema para 8 reinas, tendríamos 92 soluciones por ver, que si las imprimimos todas por pantalla son dificilmente visibles. De esta forma, crearemos si no existe una carpeta llamada soluciones y ahí guardaremos en una carpeta con nombre el número de segundos desde Epoch (para tener cada salida bien ordenada) y dentro guardaremos todas y cada una de las soluciones del problema separadas en archivos independientes generados mediante la estructura tablero.
 * @param soluciones Vector de vectores de soluciones (std::vector<std::vector<int>>)
 * @return Nombre de la carpeta generada que contiene las soluciones.
 */
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

#endif //P6_EXTRA_FUNCTIONS_HPP
