#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <vector>
#include "extra_functions.hpp"


namespace al{
    class Matrix{
        private:
            uint _size;
            std::vector<std::vector< double > > _matrix;
        public:
            Matrix(const uint &size){
                this->set_size(size);
                _matrix = std::vector< std::vector< double > >(size, std::vector<double>(size));
                for( uint i = 0 ; i < size ; ++i ){
                    for( uint j = 0 ; j< size ; ++j ){
                        _matrix[i][j] = get_random_number();
                    }
                }
            }
            Matrix(const std::vector< std::vector< double > > &matrix){
                this->set_matrix(matrix);
                this->set_size(matrix.size());
            }
            inline std::vector< std::vector< double > > get_matrix() const { return _matrix; }
            inline void set_matrix(const std::vector< std::vector< double > > &matrix) { _matrix = matrix; }
            inline uint get_size() const { return _size; }
            inline void set_size(const uint &size) { _size = size; }
            void print_matrix(){
                uint size = this->get_size();
                for( uint i = 0 ; i < size ; ++i ){
                    for( uint j = 0 ; j < size ; ++j ){
                        std::cout << _matrix[i][j] << "  ";
                    }
                    std::cout << std::endl;
                }
            }
    };
}

#endif
