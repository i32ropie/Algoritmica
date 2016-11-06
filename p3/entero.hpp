/**
* @file entero.hpp
* @brief <Práctica 3> Tipo de dato Entero.
* @author Eduardo Roldán Pijuán
* @date Noviembre de 2016
*/

#ifndef P3_ENTERO_HPP
#define P3_ENTERO_HPP

#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>

/**
 * @brief Espacio de nombres para la asignatura Algorítmica.
 */

namespace al{
    /**
     * @brief Functión que recibe una cadena y devuelve la primera mitad de esta.
     * @param cad Cadena a dividir (std::string)
     * @return Primera mitad de la cadena recibida como parámetro.
     */
    inline std::string primera_mitad(const std::string &cad) { return cad.substr(0, cad.size() / 2); }
    /**
     * @brief Functión que recibe una cadena y devuelve la segunda mitad de esta.
     * @param cad Cadena a dividir (std::string)
     * @return Segunda mitad de la cadena recibida como parámetro.
     */
    inline std::string segunda_mitad(const std::string &cad) { return cad.substr(cad.size() / 2); }
    /**
     * @brief Función que comprueba que una cadena se pueda transformar a un entero sin signo.
     * @note Función adaptada de http://stackoverflow.com/a/2845275
     * @param s Cadena a comprobar.
     * @return true si s puede ser un entero sin signo false si no.
     */
    bool is_int(const std::string & s) {
        if(s.empty() || !isdigit(s[0])) return false ;
        char * p ;
        strtol(s.c_str(), &p, 10) ;
        return (*p == 0) ;
    }
    /// Clase Entero.
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
            // Asumimos que el usuario solo introducirá números positivos.
            if(is_int(tmp))
                entero.set_number(tmp);
            return input;
        }
        Entero &operator =(const Entero &entero){
            this->set_number(entero.get_number());
            return *this;
        }
        Entero &operator =(const std::string &numero){
            this->set_number(numero);
            return *this;
        }
        Entero &operator +(const Entero &entero){
//            Cargamos los números en cadenas auxiliares y les damos la vuelta.
            std::string tmp1 = this->get_number();
            std::string tmp2 = entero.get_number();
//            Si son numeros de hasta 8 cifras, podemos sumarlos de la forma tradicional.
            int n = tmp1.size() > tmp2.size() ? tmp1.size() : tmp2.size();
            if(n<8)
                return *(new Entero(std::to_string(atoi(tmp1.c_str()) + atoi(tmp2.c_str()))));
            std::reverse(tmp1.begin(), tmp1.end());
            std::reverse(tmp2.begin(), tmp2.end());
            std::string res;
            int overflow = 0;
//            Añadimos ceros a la izquierda (derecha realmente porque hemos invertido la cadena) en el número más pequeño.
//            Para ello, usamos la sexta versión del constructor de std::string -> http://www.cplusplus.com/reference/string/string/string/
            if(tmp1.size() != tmp2.size()){
                if(tmp1.size() > tmp2.size())
                    tmp2 += std::string(tmp1.size()-tmp2.size(), '0');
                else
                    tmp1 += std::string(tmp2.size()-tmp1.size(), '0');
            }
            for(uint i = 0 ; i < tmp1.size() ; ++i){
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
//        Uso de 4 productos y no 3 por no implementar resta.
        Entero &operator *(const Entero &entero){
            std::string u = this->get_number();
            std::string v = entero.get_number();
//            Añadimos ceros a la izquierda en el número más pequeño.
            if(u.size() != v.size()){
                if(u.size() > v.size())
                    v = std::string(u.size()-v.size(), '0') + v;
                else
                    u = std::string(v.size()-u.size(), '0') + u;
            }
//            Tanto u.size() como v.size() devuelve lo mismo ya que arriba hemos llenado con 0 el numero que tuviera menos tamaño
            int n = u.size();
            if(n<5)
                return *(new Entero(std::to_string(atoi(u.c_str()) * atoi(v.c_str()))));
            int s = n%2 == 0? n/2 : n/2+1;
            Entero w = primera_mitad(u);
            Entero x = segunda_mitad(u);
            Entero y = primera_mitad(v);
            Entero z = segunda_mitad(v);
            std::string exp1 = std::string(2*s, '0');
            std::string exp2 = std::string(s, '0');
            Entero a = w * y;
            Entero b = x * y + w * z;
            Entero c = x * z;
            a = a.get_number() + exp1;
            b = b.get_number() + exp2;
            Entero res = a + b + c;
            return *(new Entero(res));
        }
        Entero &operator +=(const Entero &entero){
            *this = *this + entero;
            return *this;
        }
        Entero &operator *=(const Entero &entero){
            *this = *this * entero;
            return *this;
        }
        // TODO: Hacer sobrecarga del operador de resta e implementar algoritmo de multiplicación con tres productos.
    };
}

#endif //P3_ENTERO_HPP
