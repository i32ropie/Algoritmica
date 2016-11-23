//
// Created by i32ropie on 10/11/16.
//

#ifndef P4_GRAPH_HPP
#define P4_GRAPH_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace al{
    class Graph{
    private:
        std::vector<std::vector<int>> _matrix;
        int _edges;
        int _cursori, _cursorj;
    public:
        Graph(const std::vector<std::vector<int>> &matrix):_matrix(matrix), _edges(matrix.size()), _cursori(0), _cursorj(0){};
        Graph():_cursori(0), _cursorj(0){};
        Graph(const std::string &file_name): _cursori(0), _cursorj(0){
            this->load_graph(file_name);
        }
        void load_graph(const std::string &file_name){
            std::ifstream f(file_name.c_str());
            int n;
            bool dir; // No usado
            f >> n;
            _edges = n;
            f >> dir;
            _matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
            for(int i = 0 ; i < n ; ++i){
                for(int j = 0 ; j < n ; ++j){
                    f >> _matrix[i][j];
                }
            }
            f.close();
        }
        const std::vector<std::vector<int>> get_matrix() const { return _matrix; }
        bool is_loaded() const { return _matrix.size() != 0; }
        friend std::ostream &operator <<(std::ostream &output, const Graph &g){
            if(!g.is_loaded()){
                output << "Error - Empty graph." << std::endl;
            }
            else{
                std::vector<std::vector<int>> m = g.get_matrix();
                for(auto i = m.begin() ; i != m.end() ; ++i){
                    for(auto j = i->begin() ; j != i->end() ; ++j){
                        output << std::setw(5) << *j;
                    }
                    output << std::endl;
                }
            }
            return output;
        }
    };
}

#endif //P4_GRAPH_HPP
