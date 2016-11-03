/**
 * Created by i32ropie on 29/10/16.
 *
 * Clase basada en el algoritmo de karatsuba basado en el método
 * de divide y vencerás.
 */
#ifndef P3_ENTERO_HPP
#define P3_ENTERO_HPP

#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>

namespace al{

    bool is_int(const std::string & s) {
        if(s.empty() || !isdigit(s[0])) return false ;
        char * p ;
        strtol(s.c_str(), &p, 10) ;
        return (*p == 0) ;
    }
    // Sobrecargamos el operador producto para strings (número a la derecha)
    std::string operator *(const std::string &s,const size_t &count){
        std::string ret;
        for(size_t i = 0 ; i < count ; ++i){
            ret += s;
        }
        return ret;
    }
    // Sobrecargamos el operador producto para strings (número a la izquierda)
    std::string operator *(const size_t &count, const std::string &s){
        std::string ret;
        for(size_t i = 0 ; i < count ; ++i){
            ret += s;
        }
        return ret;
    }
    void split_string(const std::string &c, std::string &c1, std::string &c2){

    }

    class Entero{
    private:
        std::string _number;
        void quitar_ceros_no_significativos() {
            std::reverse(_number.begin(), _number.end());
            while(_number[_number.size()-1] == '0'){
                _number.pop_back();
            }
            if(_number.empty())
                _number = "0";
            else
                std::reverse(_number.begin(), _number.end());
        }
    public:
        Entero(const std::string &number = "0"):_number(number){
            this->quitar_ceros_no_significativos();
        }
        Entero(const Entero &entero) { this->set_number(entero.get_number()); }
        inline void set_number(const std::string &number) { _number = number; }
        inline std::string get_number() const { return _number; }
        friend std::ostream &operator <<(std::ostream &output, Entero &entero){
            entero.quitar_ceros_no_significativos();
            output << entero.get_number();
            return output;
        }
        friend std::istream &operator >>(std::istream &input, Entero &entero){
            std::string tmp;
            input >> tmp;
            if(!is_int(tmp))
                std::cout << "\e[31;1m[ERROR]\e[0m - Input not number.\n";
            else
                entero.set_number(tmp);
            return input;
        }
        Entero &operator =(const Entero &entero){
            this->set_number(entero.get_number());
            return *this;
        }
        Entero &operator +(const Entero &entero){
//            Cargamos los números en cadenas auxiliares y les damos la vuelta.
            std::string tmp1 = this->get_number();
            std::string tmp2 = entero.get_number();
            std::reverse(tmp1.begin(), tmp1.end());
            std::reverse(tmp2.begin(), tmp2.end());
            std::string res;
            int overflow = 0;
//            Añadimos ceros a la izquierda en el número más pequeño.
            if(tmp1.size() != tmp2.size()){
                if(tmp1.size() > tmp2.size())
                    tmp2 += (tmp1.size()-tmp2.size())*std::string("0");
                else
                    tmp1 += (tmp2.size()-tmp1.size())*std::string("0");
            }
            for(int i = 0 ; i < tmp1.size() ; ++i){
                char c1 = tmp1[i], c2 = tmp2[i];
                int aux = (c1 - '0') + (c2 - '0') + overflow;
                if(aux >= 10){
                    overflow = aux / 10;
                    aux %= 10;
                }
                else{
                    overflow = 0;
                }
                res += std::to_string(aux);
            }
            if(overflow != 0)
                res += std::to_string(overflow);
            std::reverse(res.begin(), res.end());
            return *(new Entero(res));
        }
        Entero &operator *(Entero &entero){
            std::string u = this->get_number();
            std::string v = entero.get_number();
            int n = u.size() > v.size() ? u.size() : v.size();
            if(n<5)
                return *(new Entero(std::to_string(atoi(u.c_str()) * atoi(v.c_str()))));
        }

    };
}

#endif //P3_ENTERO_HPP
