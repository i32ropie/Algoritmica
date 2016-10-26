#ifndef __HANOI_HPP__
#define __HANOI_HPP__

#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#define cls() system("clear");



namespace al{
    // Sobrecargamos el operador producto para strings (número a la derecha)
    std::string operator *(std::string s, size_t count){
        std::string ret;
        for(size_t i = 0 ; i < count ; ++i){
            ret += s;
        }
        return ret;
    }
    // Sobrecargamos el operador producto para strings (número a la izquierda)
    std::string operator *(size_t count, std::string s){
        std::string ret;
        for(size_t i = 0 ; i < count ; ++i){
            ret += s;
        }
        return ret;
    }
    struct characters{
        std::string horizontal = "─";
        std::string vertical = "│";
        std::string centre1 = "┼";
        std::string centre2 = "┴";
        std::string space = " ";
    };
    // Base de las torres
    std::string base(const int n){
        characters c;
        return c.horizontal * (n + 1) + c.centre2 + c.horizontal * (n + 1);
    }
    // Capas de las torres
    std::string layer(const int n, const int x){
        characters c;
        return c.space * ((x+1) - n) + c.horizontal * n + (n!=0 ? c.centre1 : c.vertical) + c.horizontal * n + c.space * ((x+1) - n);
    }
    class Hanoi{
    private:
        std::vector<std::vector<int>> _helper;
        long _moves;
        int _sticks;
        int _disks;
        int _sum;
    public:
        Hanoi(const int &disks): _moves(0), _sticks(3), _disks(disks){
            _helper = std::vector<std::vector<int>>(_sticks, std::vector<int>());
            for(int i = _disks ; i > 0 ; --i)
                _helper[0].push_back(i);
            int x = 0;
            for(int i = 1 ; i <= _sticks ; ++i)
                x += i;
            _sum = x;
        }
        inline std::vector<std::vector<int>> get_helper() const { return _helper; }
        inline int get_disks() const { return _disks; }
        inline int get_moves() const { return _moves; }
        void solve_hanoi( bool graphical = false, int m = -1, int i = -1, int j = -1){
            if(m == -1 || i == -1 || j == -1){
                m = _disks;
                i = 1;
                j = _sticks;
            }
            if(graphical && _disks > 8)
                graphical = false;
            if(m > 0){
                this->solve_hanoi(graphical, m - 1, i, _sum - i - j);
                int x = _helper[i-1].back();
                _helper[i-1].pop_back();
                _helper[j-1].push_back(x);
                if(graphical){
                    cls();
                    std::cout << std::endl << std::endl << *this << std::endl;
                    std::cout << "Movemos la pieza superior de " << i << " a " << j << std::endl;
                }

                _moves++;
                if(graphical)
                    usleep(500000);
                this->solve_hanoi(graphical, m - 1, _sum - i - j, j);
            }
        }
        friend std::ostream &operator <<(std::ostream &output, const Hanoi &h){
            if(h.get_disks() > 8){
                std::cerr << "\e[1;31m[Error]\e[m - Opción no válida para torres de más de 8 discos.";
                exit(EXIT_FAILURE);
            }
            else{
                std::vector<std::vector<int>> helper = h.get_helper();
                int height = h.get_disks();
                std::vector<std:: string> aux1;
                for(int i = 0 ; i < height ; ++i){
                    std::vector<std::string> tower;
                    std::string aux2;
                    for(int j = 0 ; j < helper.size() ; ++j){
                        tower.push_back((helper[j].size() > i? layer(helper[j][i], height) :  layer(0, height)) + "   ");
                    }
                    for(int j = 0 ; j < helper.size() ; ++j){
                        aux2 += tower[j];
                    }
                    aux2 += "\n";
                    aux1.push_back(aux2);
                }
                std::reverse(aux1.begin(), aux1.end());
                for( int i = 0 ; i < aux1.size() ; ++i ){
                    std::cout << aux1[i];
                }
                for( int i = 0 ; i < helper.size() ; ++i ){
                    std::cout << base(height) << "   ";
                }
                std::cout << std::endl;
            }
            return output;
        }

    };
}

#endif
