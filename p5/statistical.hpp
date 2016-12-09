/**
* @file statistical.hpp
* @brief <Práctica 4> Tipo de dato Statistical
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#ifndef __STATISTICAL_HPP__
#define __STATISTICAL_HPP__

#include <vector>
#include <fstream>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include "extra_functions.hpp"

/**
 * @brief Espacio de nombres para la asignatura Algorítmica.
 */

namespace al{
    /// Clase Statistical
    class Statistical{
    private:
        /// Vector que contiene el tamaño de prueba usado para los estadísticos.
        std::vector<uint> _test_size;
        /// Vector que contiene el tiempo calculado.
        std::vector<uint64_t> _elapsed_time;
        /// Vector que contiene el tiempo estimado.
        std::vector<long double> _estimated_time;
        /// Vector que contiene los parámetros calculados.
        std::vector<long double> _params_value;
        /// Coeficiente de determinación.
        long double _coef;
        /// Número de parámetros usados en el cálculo de regresión.
        uint _params;
        /// Diferenciar el tipo de ajuste.
        bool _lineal;
    public:
        /** @name Constructores */
        /**
         * @brief Constructor con valores por defecto.
         * @param lineal Tipo de ajuste.
         * @sa set_lineal()
         */
        Statistical(const bool &lineal = true){
            this->set_lineal(lineal);
        }
        /** @name Observadores */
        /**
         * @brief Devuelve el tipo de ajuste.
         * @return false si el ajuste es exponencial, true si no.
         */
        inline bool get_lineal() { return _lineal; }
        /**
         * @brief Devuelve el vector de parámetros.
         * @return Vector de parámetros.
         */
        inline std::vector<long double> get_params_value() { return _params_value; }
        /**
         * @brief Devuelve el coeficiente de determinación.
         * @return Coeficiente de determinación (long double)
         */
        inline long double get_coef() { return _coef; }
        /** @name Modificadores */
        /**
         * @brief Establece el tipo de ajuste.
         * @param lineal Tipo de ajuste (bool)
         */
        inline void set_lineal(const bool &lineal) { _lineal = lineal; }
        /**
         * @brief Establece el número de parámetros.
         * @param params Número de parámetros (uint)
         */
        inline void set_params(const uint &params) { _params = params; }
        /**
         * @brief Establece el coeficiente de determinación.
         * @param coef Coeficiente de determinación (long double)
         */
        inline void set_coef(const long double &coef) { _coef = coef; }
        /** @name Funciones extra */
        /**
         * @brief Añade un elemento al vector de tamaño de prueba.
         * @param n Elemento a añadir (uint)
         */
        inline void add_test_size(const uint &n) { _test_size.push_back(n); }
        /**
         * @brief Añade un elemento al vector de tiempo calculado.
         * @param n Elemento a añadir (uint64_t)
         */
        inline void add_elapsed_time(const uint64_t &n) { _elapsed_time.push_back(n); }
        /**
         * @brief Añade un elemento al vector de tiempos estimados.
         * @param n Elemento a añadir (double)
         */
        inline void add_estimated_time(const double &n) { _estimated_time.push_back(n); }
        /**
         * @brief Guarda en un archivo pasado como parámetro los datos calculados y genera un gráfico con el mismo.
         * @param output Nombre del archivo donde guardar los datos (char *)
         */
        void dump_stats(const char *output){
            std::ofstream f(output);
            for( uint i = 0 ; i < _test_size.size() ; ++i ){
                f << _test_size[i] << " " << _elapsed_time[i] << " " << _estimated_time[i] << std::endl;
            }
            f.close();
            std::string cmd = "./graph_maker.sh " + std::string(output);
            FILE * aux = popen(cmd.c_str(), "r");
            pclose(aux);
        }
        /**
         * @brief Función que calcula la ecuación de regresión.
         */
        void calculate_regression_equation(){
            std::vector<std::vector< long double > > aux(_params, std::vector< long double >(_params+1));
            std::vector< long double > aux2(_params);
            std::vector<uint> test_size_transformed = transform_test_size(_test_size, _lineal);
            // Calculamos http://i.imgur.com/RmlCGMW.jpg
            indep_terms(_params, test_size_transformed, aux);
            // Calculamos http://i.imgur.com/OrxfUG6.jpg
            dep_terms(_params, test_size_transformed, _elapsed_time, aux2);
            // Hacemos cramer para sacar el valor de los parametros.
            _params_value = cramer(_params, aux, aux2);
        }
        /**
         * @brief Función que estima los tiempos para regresiones no exponenciales.
         */
        void estimate_times_lineal(){
            for( uint i = 0 ; i < _test_size.size() ; ++i ){
                long double estimated = 0;
                for( uint j = 0 ; j < _params ; ++j ){
                    estimated += _params_value[j] * pow(_test_size[i],j);
                }
                _estimated_time.push_back(estimated);
            }
        }
        /**
         * @brief Función que estima los tiempos para regresiones exponenciales.
         */
        void estimate_times_cuadratic(){
            if(_params_value.size() == 2){
                for( uint i = 0 ; i < _test_size.size() ; ++i ){
                    long double estimated = _params_value[0]+_params_value[1]*pow(2,i);
                    _estimated_time.push_back(estimated);
                }
            }
        }
        /**
         * @brief Función que calcula el coeficiente de determinación.
         */
        void calculate_coef(){
            int size = _estimated_time.size();
            long double var1 = 0, var2 = 0 , med1 = 0, med2 = 0;
            for( int i = 0 ; i < size ; ++i ){
                med1 += _elapsed_time[i];
                med2 += _estimated_time[i];
            }
            med1 /= size;
            med2 /= size;
            for( int i = 0 ; i < size ; ++i ){
                var1 += pow(_elapsed_time[i]-med1, 2);
                var2 += pow(_estimated_time[i]-med2, 2);
            }
            var1 /= size;
            var2 /= size;
            this->set_coef(var2/var1);
        }
        /**
         * @brief Función interfaz para estimar tiempos.
         * @param params Número de parámetros a usar en la regresión (uint)
         * @sa set_params()
         * @sa estimate_times_lineal()
         * @sa estimate_times_cuadratic()
         * @sa calculate_coef()
         */
        void estimate_times(const uint &params){
            this->set_params(params);
            calculate_regression_equation();
            _lineal?estimate_times_lineal():estimate_times_cuadratic();
            calculate_coef();
        }
    };
}

#endif
