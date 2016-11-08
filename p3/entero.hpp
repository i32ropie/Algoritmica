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

        /// Cadena con el número a almacenar.
        std::string _number;
        /// Número de de dígitos máximo que puede tener un número para multiplicarlo de forma directa.
        int _margin;
        /**
         * @brief Función que quita los ceros no significativos del número.
         * @note Es privada ya que el usuario de la clase no necesita usarla pues se usa internamente.
         */
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

        /** @name Constructores */
        /**
         * @brief Constructor con valores por defecto.
         * @note Añadido iniciación del margen a 4 por si el usuario de la clase olvida inicializarlo.
         * @param number Número a almacenar dentro de la clase (std::string)
         * @sa quitar_ceros_no_significativos()
         */
        Entero(const std::string &number = "0"):_number(number), _margin(4){
            this->quitar_ceros_no_significativos();
        }

        /**
         * @brief Constructor de copia
         * @param entero Entero del que crear el nuevo Entero.
         */
        Entero(const Entero &entero): _number(entero.get_number()), _margin(entero.get_margin()) {}

        /** @name Observadores */
        /**
         * @brief Devuelve la cadena con el número.
         * @return Cadena con el número.
         */
        inline std::string get_number() const { return _number; }

        /**
         * @brief Devuelve el márgen.
         * @return Margen.
         */
        inline int get_margin() const { return _margin; }

        /** @name Modificadores */
        /**
         * @brief Establece el número.
         * @param number Número (std::string)
         */
        inline void set_number(const std::string &number) { _number = number; }

        /**
         * @brief Establece el márgen.
         * @note Para asegurar un buen funcionamiento, no aceptamos márgenes superiores a 4.
         * @param margin Margen (int)
         */
        inline void set_margin(const int &margin) { _margin = margin > 4 ? 4 : margin; }

        /** @name Sobrecarga de operadores */
        /**
         * @brief Sobrecarga del operador <<
         * @param output Flujo de salida.
         * @param entero Entero.
         * @return Flujo de salida con el Entero ya impreso.
         * @sa quitar_ceros_no_significativos()
         */
        friend std::ostream &operator <<(std::ostream &output, Entero &entero){
            entero.quitar_ceros_no_significativos();
            output << entero.get_number();
            return output;
        }

        /**
         * @brief Sobrecarga del operador >>
         * @param input Flujo de entrada.
         * @param entero Entero.
         * @return Flujo de entrada con el Entero ya leido.
         * @sa is_int()
         * @sa set_number()
         */
        friend std::istream &operator >>(std::istream &input, Entero &entero){
            std::string tmp;
            input >> tmp;
//            Asumimos que el usuario solo introducirá números positivos.
            if(is_int(tmp))
                entero.set_number(tmp);
            return input;
        }

        /**
         * @brief Sobrecarga del operador = con un Entero.
         * @param entero Entero.
         * @return Entero.
         * @sa set_number()
         * @sa set_margin()
         */
        Entero &operator =(const Entero &entero){
            this->set_number(entero.get_number());
            this->set_margin(entero.get_margin());
            return *this;
        }

        /**
         * @brief Sobrecarga del operador = con una cadena.
         * @param numero Cadena
         * @return Entero
         * @sa set_number()
         * @sa set_margin()
         */
        Entero &operator =(const std::string &numero){
            this->set_number(numero);
            this->set_margin(4);
            return *this;
        }

        /**
         * @brief Sobrecarga del operador +
         * @note Usado como margen 9 ya que suponiendo el peor de los casos, funcionará.
         * @param entero Entero.
         * @return Suma de los enteros.
         * @sa get_number()
         */
        Entero &operator +(const Entero &entero){
//            Cargamos los números en cadenas auxiliares y les damos la vuelta.
            std::string tmp1 = this->get_number();
            std::string tmp2 = entero.get_number();
//            Si son numeros de hasta 9 cifras, podemos sumarlos de la forma tradicional.
//            999999999 + 999999999 < 2147483647
            int n = tmp1.size() > tmp2.size() ? tmp1.size() : tmp2.size();
            if(n<10)
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

        /**
         * @brief Sobrecarga del operador *
         * @note Uso del algoritmo que utiliza 4 productos para evitar sobrecargar el operador de resta.
         * @param entero Entero
         * @return Producto de los enteros.
         * @sa get_number()
         * @sa get_margin()
         * @sa primera_mitad()
         * @sa segunda_mitad()
         */
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
            if(n < this->get_margin())
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

        /**
         * @brief Sobrecarga del operador +=
         * @param entero Entero
         * @return Entero
         */
        Entero &operator +=(const Entero &entero){
            *this = *this + entero;
            return *this;
        }

        /**
         * @brief Sobrecarga del operador *=
         * @param entero Entero
         * @return Entero
         */
        Entero &operator *=(const Entero &entero){
            *this = *this * entero;
            return *this;
        }
    };
}

#endif //P3_ENTERO_HPP
