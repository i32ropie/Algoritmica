//
// Created by i32ropie on 21/12/16.
//

#ifndef P6_REINAS_HPP
#define P6_REINAS_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace al {

    bool lugar(const int &k, const std::vector<int> &x){
        for(int i = 0 ; i < k ; ++i){
            if( x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k))
                return false;
        }
        return true;
    }

    class Reinas {
    private:
        std::vector<std::vector<int>> _soluciones;
        int _reinas;
        int _intentos;
    public:
        Reinas(const int &reinas): _reinas(reinas), _intentos(0) {}
        inline int get_numero_soluciones() const { return _soluciones.size(); }
        inline int get_intentos() const { return _intentos; }
        inline std::vector<std::vector<int>> get_soluciones() const { return _soluciones; }
        void resolver_probabilistico() {
            if( _reinas <= 3 )
                return;
            std::vector<int> aux(_reinas, -1);
            int k = 0;
            while(k < _reinas){
                aux[k] = rand()%_reinas + 1;
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
        void resolver_backtracking() {
            if( _reinas <= 3 )
                return;
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
