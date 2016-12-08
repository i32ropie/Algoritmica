//
// Created by i32ropie on 7/12/16.
//

#ifndef P5_CURRENCY_HPP
#define P5_CURRENCY_HPP

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace al{
    class Currency{
    private:
        std::vector<int> _usable_coins;
        std::vector<int> _solution_coins;
        std::vector<std::vector<int>> _aux;
        int _fil, _col;
        bool _solved;
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
//            for(int i = 0 ; i < _solution_coins.size() ; ++i) std::cout << _solution_coins[i] << "  ";
        }
    public:
        Currency(const int &N, const std::string &file_name = "/home/i32ropie/Dropbox/2016-2017/1ºCuatrimestre/A/Edu/p5/currency.txt"): _solved(false){
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
        void solve(){
            if(!_solved){
                dynamic_algorithm();
                fill_coins(); // No confundir con Phil Collins
                _solved = true;
            }
        }
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
