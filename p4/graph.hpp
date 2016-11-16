//
// Created by i32ropie on 10/11/16.
//

#ifndef P4_GRAPH_HPP
#define P4_GRAPH_HPP

#include <vector>
#include <iostream>
#include <iomanip>

namespace al{
    class Graph{
    private:
        std::vector<std::vector<int>> _matrix;
        int _edges;
        int _cursori, _cursorj;
    public:
//        Graph(const int &size):_matrix(*(new std::vector<std::vector<int>>(size, std::vector<int>(size)))), _edges(size), _cursori(0), _cursorj(0){};
        Graph(const std::vector<std::vector<int>> &matrix):_matrix(matrix), _edges(matrix.size()), _cursori(0), _cursorj(0){};
        Graph():_cursori(0), _cursorj(0){};
        void load_graph(const std::vector<std::vector<int>> &matrix){
            _matrix = matrix;
            _edges = matrix.size();
        }
        bool is_loaded() const { return _matrix.size() != 0; }
        friend std::ostream &operator <<(const std::ostream &output, const Graph &g){
            if(!g.is_loaded()){
                output << "Error - Empty graph." << std::endl;
            }
            else{
                m = g.get_matrix();
                for(auto i = m.begin() ; i != m.end() ; ++i){
                    for(auto j = (*i).begin() ; +j != (*j).end() ; ++j){
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
