/**
* @file reinas.hpp
* @brief <Práctica 6> Tipo de dato Reinas.
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#ifndef P6_REINAS_HPP
#define P6_REINAS_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdint> // Para usar uint64_t
#include <algorithm>

/**
 * @brief Espacio de nombres para la asignatura Algorítmica.
 */

namespace al {
    /**
     * @brief Función que comprueba si la reina 'k' se puede colocar conteplando las k-1 reinas puestas anteriormente.
     * @note Se podrá colocar siempre y cuando no amenace a las reinas existentes.
     * @param k Posición de la reina k-ésima (int)
     * @param x Vector de posiciones de las reinas (std::vector<int>)
     * @return true si se puede colocar o false si no.
     */
    bool lugar(const int &k, const std::vector<int> &x){
        for(int i = 0 ; i < k ; ++i){
            if( x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k))
                return false;
        }
        return true;
    }
    /// Clase Reinas.
    class Reinas {
    private:
        /// Vector que contendrá las soluciones calculadas.
        std::vector<std::vector<int>> _soluciones;
        /// Número de reinas.
        int _reinas;
        /// Número de intentos usados para cada ejecución del algoritmo Las Vegas.
        uint64_t _intentos;
    public:
        /** @name Constructor */
        /**
         * @brief Constructor con valores por defecto.
         * @param reinas Número de reinas del problema (int)
         */
        Reinas(const int &reinas): _reinas(reinas), _intentos(0) {}
        /** @name Observadores */
        /**
         * @brief Devuelve cuántas soluciones distintas han sido calculadas.
         * @return Número de soluciones distintas calculadas.
         */
        inline int get_numero_soluciones() const { return _soluciones.size(); }
        /**
         * @brief Devue el número de intentos usados para el último uso del algoritmo Las Vegas.
         * @return Número de intentos usados en el último uso del algoritmo Las Vegas.
         */
        inline uint64_t get_intentos() const { return _intentos; }
        /**
         * @brief Devuelve el vector que contiene las soluciones.
         * @return Vector de soluciones.
         */
        inline std::vector<std::vector<int>> get_soluciones() const { return _soluciones; }
        /** @name Algoritmos */
        /**
         * @brief Algoritmo probabilístico Las Vegas.
         * @note Siempre obtiene una solución, pero solo la guarda si es nueva.
         */
        void resolver_probabilistico() {
            if( _reinas <= 3 )
                return;
            _intentos = 0;
            std::vector<int> aux(_reinas, -1);
            int k = 0;
            while(k < _reinas){
                aux[k] = rand()%_reinas;
                if(lugar(k, aux)){
                    ++k;
                }
                else{
                    k = 0;
                    aux = std::vector<int>(_reinas, -1);
                    ++_intentos;
                }
            }
            if(std::find(_soluciones.begin(), _soluciones.end(), aux) == _soluciones.end())
                _soluciones.push_back(aux);
        }
        /**
         * @brief Algoritmo backtracking.
         * @note Obtiene todas las soluciones del problema. Borra todas las soluciones obtenidas anteriormente para evitar duplicidad en caso de llamar múltiples veces a la función.
         */
        void resolver_backtracking() {
            if( _reinas <= 3 )
                return;
            _soluciones.clear();
            std::vector<int> aux(_reinas, -1);
            int k = 0;
            while( k >= 0 ){
                do{
                    aux[k]++;
                }while( aux[k] < _reinas && !lugar(k, aux));
                if( aux[k] < _reinas ){
                    if( k == _reinas-1 ){
                        _soluciones.push_back(aux);
                    }
                    else{
                        ++k;
                        aux[k] = -1;
                    }
                }
                else{
                    --k;
                }
            }
        }
        /** @name Sobre carga de operador */
        /**
         * @brief Sobrecarga del operador <<
         * @param output Flujo de salida.
         * @param r Reinas.
         * @return Flujo de salida con el número de soluciones obtenidas.
         * @sa get_numero_soluciones()
         */
        friend std::ostream &operator <<(std::ostream &output, const Reinas &r){
            if( r._reinas <= 3 ){
                output << "Error, no existe solución para 3 o menos reinas." << std::endl;
            }
            else if( r.get_numero_soluciones() == 0 ){
                output << "Error, no se ha conseguido ninguna solución. Recuerda llamar antes a la función resolver()" << std::endl;
            }
            else{
                output << "Se han obtenido " << r._soluciones.size() << " soluciones para el problema de las " << r._reinas << " reinas." << std::endl;
            }
        }
    };
}

#endif //P6_REINAS_HPP
