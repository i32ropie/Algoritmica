#ifndef P4_ALGORITHMS_HPP
#define P4_ALGORITHMS_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <utility>

#define inf std::numeric_limits<int>::max()

std::pair<int, std::vector<int>> viajante_comercio(std::vector<std::vector<int>> m){
    // Vector solución.
    std::vector<int> sol1;
    // Distacia recorrida
    int sol2 = 0;
    // Añadimos la ciudad principal (desde la que partimos)
    sol1.push_back(0);
    // Vector que indica qué ciudades han sido visitadas.
    std::vector<bool> visited(m.size(), false);
    // Como partimos de la primera ciudad, la ponemos a 1.
    visited[0] = true;
    // Posición de la ciudad en la que estamos.
    int cur = 0;
    // Posición de la ciudad a la que ir.
    int pos;
    // Ponemos la diagonal a "infinito" para descartarla.
    for(uint i = 0 ; i < m.size() ; ++i)
        m[i][i] = inf;
    // Recorremos las ciudades sin visitar (todas menos la primera)
    for(uint i = 0 ; i < m.size() - 1 ; ++i){
        // Variable de control para salir.
        bool fin = false;
        // Buscamos el mínimo no visitado.
        do{
            // Mínimo elemento.
            auto minimo = std::min_element(m[cur].begin(), m[cur].end());
            // Posición del elemento es decir, la ciudad a visitar.
            pos = minimo - m[cur].begin();
            // Si el minimo es una ciudad visitada, la ponemos a infinito para no hacer bucle infinito.
            if(visited[pos]){
                m[cur][pos] = inf;
            }
            else{
                // Vamos a esa ciudad (actualizamos cur)
                cur = pos;
                // La guardamos en las soluciones.
                sol1.push_back(pos);
                // Y la marcamos como visitada.
                visited[pos] = true;
                sol2 += *minimo;
                fin = true;
            }
        }while(!fin);
    }
    // Añadimos la ciudad principal otra vez, ya que hay que formar un ciclo.
    sol1.push_back(0);
    std::pair<int, std::vector<int>> sol(sol2, sol1);
    return sol;
}

#endif //P4_ALGORITHMS_HPP
