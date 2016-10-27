#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <stdint.h> // Para usar uint64_t
#include "hanoi.hpp"
#include "statistical.hpp"
#include "ClaseTiempo.hpp"
#define cls() system("clear");


long long combinatorio_iterativo(const int &n,const int &k){
    long double fact_n = 1, fact_k = 1, fact_nk = 1;
    for( long double i = 2 ; i <= n ; ++i )
        fact_n *= i;
    for( long double i = 2 ; i <= k ; ++i )
        fact_k *= i;
    for( long double i = 2 ; i <= (n-k) ; ++i )
        fact_nk *= i;
    return fact_n/fact_k/fact_nk;
}

long long combinatorio_recursivo(const int &n, const int &k){
    if(k == 0 || k == n){
        return 1;
    }
    return combinatorio_recursivo(n-1, k-1) + combinatorio_recursivo(n-1, k);
}

long long combinatorio_recursivo_2(const int &n, const int &k, std::vector<std::vector< long long > > &aux){
    int a;
    if(k == 0 || k == n)
        return 1;
    if( aux[n-1][k-1] != -1 ){
        a = aux[n-1][k-1];
    }
    else{
        a = combinatorio_recursivo_2(n-1, k-1, aux) + combinatorio_recursivo_2(n-1, k, aux);
        aux[n-1][k-1] = a;
    }
    return a;
}

/**
* @brief Cabecera que se mostrará durante la ejecución del programa.
*/
void cabecera(){
    cls();
    std::cout << "\e[1;92m###############################" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "####       \e[96mPrograma\e[92m        ####" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "###############################\e[0m" << std::endl << std::endl;
}

/**
* @brief Mensaje que se muestra al final de cada opción del menú.
* @note En la función aplicarFloyd() se llama también para dar paso al submenú.
* @param count Número de veces a ejecutar std::cin.ignore()
* @param mensaje Mensaje a mostar. Por defecto mostrará: "Presiona ENTER para volver al menú."
*/
void volver(const int &count = 2, const std::string &mensaje="Presiona ENTER para volver al menú."){
    std::cout << std::endl << mensaje;
    for( int i = 0 ; i < count ; ++i)
        std::cin.ignore();
}

/**
* @brief Muestra un error personalizado por pantalla.
* @note Con 2 segundos de sleep da tiempo a leer los errores.
* @param er Error a mostrar.
*/
void error(const std::string &er){
    std::cout << std::endl << "\e[31;1m[ERROR]\e[0m - " << er << std::endl;
    fflush(stdout);
    sleep(2);
}

/**
* @brief Muestra las opciones del menú e interactua con el usuario.
* @return Opción del menú a ejecutar.
* @sa cabecera()
* @sa error()
*/
uint opciones(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Menú combinatoria." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Menú Hanoi." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Salir del programa." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>2){
            error("Opción no válida. Volviendo al menú principal...");
        }
    }while(opcion<0 || opcion>2);
    return opcion;
}

/**
* @brief Función para despedirse.
* @note Con el Adiós en grande mejoramos la experiencia del usuario.
* @sa cabecera()
*/
void despedida(){
    cabecera();
    std::cout << "Gracias por usar el programa, ¡hasta la próxima!\e[1m" << std::endl;
    std::cout << "              _ _   __      " << std::endl << "\
     /\\      | (_) /_/      " << std::endl << "\
    /  \\   __| |_  ___  ___ " << std::endl << "\
   / /\\ \\ / _` | |/ _ \\/ __|" << std::endl << "\
  / ____ \\ (_| | | (_) \\__ \\" << std::endl << "\
 /_/    \\_\\__,_|_|\\___/|___/" << std::endl << "\
                            " << std::endl << "\
                            \e[0m" << std::endl;
}

void mostrar_determinacion(al::Statistical &stats){
    cabecera();
    std::cout << std::endl << "Coeficiente de determinación: " << stats.get_coef() << std::endl;
    volver();
}

void mostrar_ecuacion(al::Statistical &stats){
    cabecera();
    bool lineal = stats.get_lineal();
    std::vector<long double> aux = stats.get_params_value();
    std::cout << "Ecuación de estimación:" << std::endl << "\tt(n) = ";
    if(lineal){
        for (int i = 0; i < aux.size(); ++i) {
            std::cout << ((i == 0) ? aux[i] : std::abs(aux[i])) << "*n^" << i;
            if( i < (aux.size()-1))
                aux[i]>0?std::cout<<" + ":std::cout<<" - ";
        }
    }
    else{
        std::cout << aux[0] << (aux[1]>0?" + ":" - ") << std::abs(aux[1]) << "*2^n" << std::endl;
    }
    volver();
}

void mostrar_grafica(const std::string &f_name){
    cabecera();
    std::string cmd = "xdg-open " + f_name + " 2> /dev/null";
    FILE * aux = popen(cmd.c_str(), "r");
    pclose(aux);
    volver();
}

void estimar_tiempos(al::Statistical &stats, const std::string &x){
    cabecera();
    int tam;
    long double res = 0;
    std::vector<long double> params = stats.get_params_value();
    bool lineal = stats.get_lineal();
    std::cout << "Introduce el " << x << " a calcular: ";
    std::cin >> tam;
    if(lineal){
        for( int i = 0 ; i < params.size() ; ++i ){
            res += params[i] * pow(tam, i);
        }
    }
    else{
        res = params[0] + params[1] * pow(2, tam);
    }
    std::cout << std::endl << "Taradría " << (lineal?res*pow(10,-6)/(60*60):res*(pow(10, -6)/(3600*24))) << (lineal? " horas.":" años.") << std::endl;
    volver();
}

int opciones_comb(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Algoritmo recursivo." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Algoritmo recursivo con tabla de valores." << std::endl;
        std::cout << "\t\e[33;1m[3]\e[0m - Algoritmo iterativo." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Atrás." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>3){
            error("Opción no válida. Volviendo al menú...");
        }
    }while(opcion<0 || opcion>3);
    return opcion;
}

int opciones_stats(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Mostrar coeficiente de determinación." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Mostrar ecuación de estimación." << std::endl;
        std::cout << "\t\e[33;1m[3]\e[0m - Mostrar gráfico generado." << std::endl;
        std::cout << "\t\e[33;1m[4]\e[0m - Estimar tiempos." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Atrás." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>4){
            error("Opción no válida. Volviendo...");
        }
    }while(opcion<0 || opcion>4);
    return opcion;
}

void menu_combinatoria(const int &type){
    cabecera();
    int mayor, menor, incremento, n_rpt, opcion;
    Clock timer;
    std::string dat_name, eps_name;
    uint64_t aux_timer1, aux_timer2;
    al::Statistical stats(true);
    std::cout << "Introduce el menor número a calcular: ";
    std::cin >> menor;
    std::cout << "Introduce el mayor número a calcular: ";
    std::cin >> mayor;
    std::cout << "Introduce el incremento: ";
    std::cin >> incremento;
    std::cout << "Veces a repetir: ";
    std::cin >> n_rpt;
    if(menor > mayor){
        menor += mayor;
        mayor = menor - mayor;
        menor -= mayor;
    }
    if(incremento > (mayor-menor)){
        std::cerr << "\e[1;31m[Error]\e[m. The increment mustn't be higher than the upper number minus the lower number." << std::endl;
        exit(1);
    }
    std::cout << std::endl << "Procesando..." << std::endl;
    for( int i = menor ; i <= mayor ; i+=incremento ){
        aux_timer1 = 0;
        for( int j = 0 ; j <= i ; ++j ){
            aux_timer2 = 0;
            for( int k = 0 ; k < n_rpt ; ++k ){
                long long res;
                std::vector<std::vector< long long > > v = std::vector<std::vector< long long > >(i, std::vector<long long>(j));
                if(type == 2){
                    for( int z = 0 ; z < i ; ++z ){
                        for( int t = 0 ; t < j ; ++t )
                            v[z][t] = -1;
                    }
                }
                timer.start();
                switch (type){
                    case 1:
                        res = combinatorio_recursivo(i, j);
                        break;
                    case 2:
                        res = combinatorio_recursivo_2(i, j, v);
                        break;
                    case 3:
                        res = combinatorio_iterativo(i, j);
                        break;
                }
                timer.stop();
                aux_timer2 += timer.elapsed();
            }
            // t(i,0) + t(i,1) .. t(i,i)
            aux_timer1 += aux_timer2/n_rpt;
        }
        stats.add_test_size(i);
        // t(i) = (t(i,0) + t(i,1) .. t(i,i)) / (i+1)
        stats.add_elapsed_time(aux_timer1/(i+1));
    }
    stats.estimate_times(4);
    switch (type){
        case 1:
            dat_name = "comb_rec.dat";
            eps_name = "comb_rec.eps";
            break;
        case 2:
            dat_name = "comb_rec2.dat";
            eps_name = "comb_rec2.eps";
            break;
        case 3:
            dat_name = "comb_iter.dat";
            eps_name = "comb_iter.eps";
            break;
    }
    stats.dump_stats(dat_name.c_str());
    bool salir = false;
    do{
        opcion = opciones_stats();
        switch (opcion){
            case 0:
                salir = true;
                break;
            case 1:
                mostrar_determinacion(stats);
                break;
            case 2:
                mostrar_ecuacion(stats);
                break;
            case 3:
                mostrar_grafica(eps_name);
                break;
            case 4:
                estimar_tiempos(stats, "tamaño de combinatorio");
                break;
        }
    }while(!salir);
}

void menu_combinatoria(){
    int opcion;
    bool salir = false;
    do{
        opcion = opciones_comb();
        switch(opcion){
            case 0:
                salir = true;
                break;
            default:
                menu_combinatoria(opcion);
        }
    }while(!salir);
}

int opciones_hanoi(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Cálculo de movimientos con n discos." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Representación gráfica." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Atrás." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>2){
            error("Opción no válida. Volviendo al menú...");
        }
    }while(opcion<0 || opcion>2);
    return opcion;
}

void calculo_hanoi(){
    cabecera();
    int tam, n_rpt, opcion;
    Clock timer;
    al::Statistical stats(false);
    uint64_t aux_timer;
    std::cout << "Introduce el tamaño máximo de discos a utilizar: ";
    std::cin >> tam;
    std::cout << "Veces a repetir: ";
    std::cin >> n_rpt;
    for(int i = 0 ; i < tam ; ++i){
        aux_timer = 0;
        for (int j = 0; j < n_rpt ; ++j) {
            al::Hanoi h(i);
            timer.start();
            h.solve_hanoi();
            timer.stop();
            aux_timer += timer.elapsed();
        }
        stats.add_test_size(i);
        stats.add_elapsed_time(aux_timer/n_rpt);
    }
    stats.estimate_times(2);
    stats.dump_stats("hanoi.dat");
    bool salir = false;
    do{
        opcion = opciones_stats();
        switch (opcion){
            case 0:
                salir = true;
                break;
            case 1:
                mostrar_determinacion(stats);
                break;
            case 2:
                mostrar_ecuacion(stats);
                break;
            case 3:
                mostrar_grafica("hanoi.eps");
                break;
            case 4:
                estimar_tiempos(stats, "número de discos de hanoi");
                break;
        }
    }while(!salir);
}

void hanoi_grafico(){
    cabecera();
    int tam;
    std::cout << "Introduce el número de discos (entre 1 y 8): ";
    std::cin >> tam;
    al::Hanoi h(tam);
    cls();
    std::cout << std::endl << std::endl << h << std::endl <<  "Estado inicial, pulsa ENTER para continuar";;
    std::cin.ignore();
    std::cin.ignore();
    usleep(500000);
    h.solve_hanoi(true);
    std::cout << std::endl << "Hanoi resuelto en " << h.get_moves() << " movimientos." << std::endl;
    volver(1);
}

void menu_hanoi(){
    int opcion;
    bool salir = false;
    do{
        opcion = opciones_hanoi();
        switch(opcion){
            case 1:
                calculo_hanoi();
                break;
            case 2:
                hanoi_grafico();
                break;
            case 3:
                break;
            case 0:
                salir = true;
                break;
        }
    }while(!salir);
}

#endif
