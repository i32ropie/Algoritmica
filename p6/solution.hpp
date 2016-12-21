//
// Created by i32ropie on 19/12/16.
//

#ifndef P6_SOLUTION_HPP
#define P6_SOLUTION_HPP

#include <vector>
#include <algorithm>
#include <iostream>

namespace al{
    class Solution{
    private:
        std::vector<int> _sol;
    public:
        inline void add_solution(const int &solution) { _sol.push_back(solution); }
        inline bool is_solved() const { *std::max_element(_sol.begin(), _sol.end()) == _sol.size()-1; }
        friend std::ostream &operator <<(std::ostream &output, const Solution &sol){
            if(not sol.is_solved()){
                output << "Solución no completada." << std::endl;
            }
            else{
                output << "Solución:" << std::endl;
                for(int i = 1 ; i <= sol._sol.size() ; ++i){
                    output << "Reina " << i <<
                }
            }
        }
    };
}

#endif //P6_SOLUTION_HPP
