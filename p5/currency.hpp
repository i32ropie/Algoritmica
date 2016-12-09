/**
* @file currency.hpp
* @brief <Práctica 4> Tipo de dato Currency
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#ifndef P5_CURRENCY_HPP
#define P5_CURRENCY_HPP

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>


/**
 * @brief Espacio de nombres para la asignatura Algorítmica.
 */

namespace al{
    /// Clase Currency
    class Currency{
    private:
        /// Vector que contiene las monedas usables para la resolución del problema.
        std::vector<int> _usable_coins;
        /// Vector que contiene la cantidad de monedas usadas de cada tipo para la resolución del problema.
        std::vector<int> _solution_coins;
        /// Matriz con la cuál resolveremos dinámicamente el problema.
        std::vector<std::vector<int>> _aux;
        /// Número de filas y columnas de la matriz.
        int _fil, _col;
        /// Variable para comprobar si está resuelto o no el problema.
        bool _solved;
        /**
         * @brief Algoritmo dinámico que resuelve el problema del cambio.
         */
        void dynamic_algorithm(){
            for(int i = 0 ; i < _aux.size() ; ++i){
                _aux[i][0] = 0;
            }
            for(int i = 0 ; i < _aux.size() ; ++i){
                for(int j = 1 ; j < _aux[i].size(); ++j){
                    if( i == 0 && j < _usable_coins[i] ){
                        _aux[i][j] = 0;
                    }
                    else{
                        if( i == 0 ){
                            _aux[i][j] = 1 + _aux[i][j-_usable_coins[0]];
                        }
                        else{
                            if( j < _usable_coins[i] ){
                                _aux[i][j] = _aux[i-1][j];
                            }
                            else{
                                _aux[i][j] = std::min(_aux[i-1][j], 1 + _aux[i][j-_usable_coins[i]]);
                            }
                        }
                    }
                }
            }
        }
        /**
         * @brief Algoritmo que, una vez resuelto el problema del cambio, obtiene qué cantidad de monedas de cada tipo han sido usadas
         */
        void fill_coins() {
            int b = 0;
            int i = _fil-1, j = _col-1;
            do{
                if( i == 0 ){
                    _solution_coins[i] += 1;
                    break;
                }
                else if( _aux[i][j] == _aux[i-1][j] ){
                    --i;
                }
                else if( _aux[i][j] == 1 + _aux[i][j-_usable_coins[i]] ){
                    j -= _usable_coins[i];
                    _solution_coins[i] += 1;
                    b += _usable_coins[i];
                }
            }while(j > 0);
        }
    public:
        /** @name Constructor */
        /**
         * @brief Constructor con valores por defecto.
         * @note En el programa se usa "currency.txt" por defecto, pero en otro programa se podrá usar otro archivo.
         * @param N Cantidad de céntimos total del cambio (int)
         * @param file_name Nombre del archivo que contiene el valor de las monedas a usar (std::string)
         */
        Currency(const int &N, const std::string &file_name = "currency.txt"): _solved(false){
            std::ifstream f(file_name.c_str());
            int coin_value;
            while(f >> coin_value){
                _usable_coins.push_back(coin_value);
                _solution_coins.push_back(0);
            }
            f.close();
            _aux = std::vector<std::vector<int>>(_usable_coins.size(), std::vector<int>(N+1));
            _fil = _usable_coins.size();
            _col = N+1;
        }
        /** @name Función principal. */
        /**
         * @brief Función que resuelve el problema del cambio. Si ya está resuelto no hace nada.
         * @note Primero utiliza el algoritmo dinámico para generar la matriz y después contabiliza las monedas.
         * @sa dynamic_algorithm()
         * @sa fill_coins()
         */
        void solve(){
            if(!_solved){
                dynamic_algorithm();
                fill_coins(); // No confundir con Phil Collins
                _solved = true;
            }
        }
        /** @name Sobrecarga de operador */
        /**
         * @brief Sobrecarga del operador <<
         * @note Si se imprime un objeto sin haber sido resuelto, se informará de ello.
         * @param output Flujo de salida.
         * @param c Currency.
         * @return Flujo de salida con las monedas usadas para resolver el problema.
         */
        friend std::ostream &operator <<(std::ostream &output, const Currency &c){
            if(!c._solved){
                output << "Problema no resuelto. Debes llamar antes a la función solve()" << std::endl;
            }
            else{
                std::vector<int> usable_coins = c._usable_coins;
                std::vector<int> solution_coins = c._solution_coins;
                output << "\t̲ ̲M̲o̲n̲e̲d̲a̲/̲B̲i̲l̲l̲e̲t̲e │ ̲C̲a̲n̲t̲i̲d̲a̲d" << std::endl;
                for( int i = 0 ; i < solution_coins.size() ; ++i ){
                    if( solution_coins[i] != 0 ){
                        output << "\t" << std::setw(15) << usable_coins[i]/100.0;
                        output << " │ ";
                        output << std::setw(8) << solution_coins[i];
                        output << std::endl;
                    }
                }
            }
            return output;
        }

    };
}

#endif //P5_CURRENCY_HPP
