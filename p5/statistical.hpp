#ifndef __STATISTICAL_HPP__
#define __STATISTICAL_HPP__

#include <vector>
#include <fstream>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include "extra_functions.hpp"

namespace al{
    class Statistical{
        private:
            std::vector<uint> _test_size;
            std::vector<uint64_t> _elapsed_time;
            std::vector<long double> _estimated_time;
            std::vector<long double> _params_value;
            long double _coef;
            uint _params;
            bool _lineal;
        public:
            Statistical(const bool &lineal){
                this->set_lineal(lineal);
            }
            inline bool get_lineal() { return _lineal; }
            inline std::vector<long double> get_params_value() { return _params_value; }
            inline void set_lineal(const bool &lineal) { _lineal = lineal; }
            inline void set_params(const uint &params) { _params = params; }
            inline void add_test_size(const uint &n) { _test_size.push_back(n); }
            inline void add_elapsed_time(const uint64_t &n) { _elapsed_time.push_back(n); }
            inline void add_estimated_time(const double &n) { _estimated_time.push_back(n); }
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
            void estimate_times_lineal(){
                calculate_regression_equation();
                for( uint i = 0 ; i < _test_size.size() ; ++i ){
                    long double estimated = 0;
                    for( uint j = 0 ; j < _params ; ++j ){
                        estimated += _params_value[j] * pow(_test_size[i],j);
                    }
                    _estimated_time.push_back(estimated);
                }
            }
            void estimate_times_cuadratic(){
                calculate_regression_equation();
                if(_params_value.size() == 2){
                    for( uint i = 0 ; i < _test_size.size() ; ++i ){
                        long double estimated = _params_value[0]+_params_value[1]*pow(2,i);
                        _estimated_time.push_back(estimated);
                    }
                }
            }
            inline void set_coef(const long double &coef) { _coef = coef; }
            inline long double get_coef() { return _coef; }
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
            void estimate_times(const uint &params){
                this->set_params(params);
                _lineal?estimate_times_lineal():estimate_times_cuadratic();
                calculate_coef();
            }
    };
}

#endif
