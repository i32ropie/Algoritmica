/**
 * @file matrix.hpp
 * @brief <Práctica 1> Representación del TAD matriz.
 * @author Eduardo Roldán Pijuán
 * date Octubre de 2016
 */

#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <vector>
#include "extra_functions.hpp"

/**
 * Espacio de nombres para la asignatura Algorítmica.
 */


namespace al{
    /// Clase Matrix
    template<class T>
    class Matrix{
        private:
            /// Dimensión de la matriz.
            uint _size;
            /// Vector de vectores.
            std::vector<std::vector< T > > _matrix;
        public:
            /** @name Constructor. */
            /**
             * @brief Constructor con valores por defecto.
             * @param size Dimensión de la matriz.
             * @sa set_size()
             */
            Matrix(const uint &size){
                this->set_size(size);
                _matrix = std::vector< std::vector< T > >(size, std::vector<T>(size));
                for( uint i = 0 ; i < size ; ++i ){
                    for( uint j = 0 ; j< size ; ++j ){
                        _matrix[i][j] = get_random_number();
                    }
                }
            }
            Matrix(const std::vector<std::vector< T > > &m){
                this->set_matrix(m);
                this->set_size(m.size());
            }
            /** @name Observadores. */
            /**
             * @brief Devuelve el vector de vectores.
             * @return Vector de vectores.
             */
            inline std::vector< std::vector< T > > get_matrix() const { return _matrix; }
            /**
             * @brief Devuelve la dimensión de la matriz.
             * @return Dimensión de la matriz.
             */
            inline uint get_size() const { return _size; }
            /** @name Modificadores. */
            /**
             * @brief Establece el vector de vectores.
             * @param matrix Vector de vectores.
             */
            inline void set_matrix(const std::vector< std::vector< T > > &matrix) { _matrix = matrix; }
            /**
             * @brief Establece la dimensión de la matriz.
             * @param size Dimensión de la matriz (uint).
             */
            inline void set_size(const uint &size) { _size = size; }

            #ifdef NDEBUG
                friend std::ostream &operator <<(std::ostream &output, const Matrix &m){
                    uint size = m.get_size();
                    std::vector<std::vector< T > > matrix = m.get_matrix();
                    for( uint i = 0 ; i < size ; ++i ){
                        for( uint j = 0 ; j < size ; ++j ){
                            output << matrix[i][j] << "  ";
                        }
                        output << std::endl;
                    }
                    return output;
                }
            #endif
    };
}

#endif
