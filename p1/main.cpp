/**
 * @file main.cpp
 * @brief <Práctica 1> main.
 * @author Eduardo Roldán Pijuán
 * @date Octubre de 2016
 */

#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "matrix.hpp"
#include "ClaseTiempo.hpp"
#include "statistical.hpp"
#include "main.hpp"

/**
 * @name main
 * @note La práctica está comentada internamente en inglés.
 * Programa principal.
 */
int main(int argc, char *argv[]){
    srand(time(NULL));
    // Temporal variable where we store the matrix determinant.
    double det_tmp;
    // Temporal variable where we store the fibonacci result.
    uint64_t fib, fib_tmp, aux_timer;
    al::Statistical stats_matrix(/*4, */true);
    al::Statistical stats_fibo(/*2, */false);
    // Map used to store the elapsed time in each iteration.
    // Flags to check the option used when executing the program.
    bool h_flag = false, l_flag = false, u_flag = false, i_flag = false, f_flag = false, n_flag = false, o_flag = false;
    uint lower, upper, inc, n_rpt = 0, orden;
    int option, index;
    // Force only our errors to appear.
    opterr = 0;
    // Checking program options.
    while( (option = getopt(argc, argv, "hl:u:i:f:n:o:")) != -1 ){
        switch(option){
            case 'o':
                o_flag = true;
                orden = atoi(optarg);
            case 'h':
                h_flag = true;
                break;
            case 'l':
                l_flag = true;
                lower = atoi(optarg);
                break;
            case 'u':
                u_flag = true;
                upper = atoi(optarg);
                break;
            case 'i':
                i_flag = true;
                inc = atoi(optarg);
                break;
            case 'f':
                f_flag = true;
                fib = atoi(optarg);
                break;
            case 'n':
                n_flag = true;
                n_rpt = atoi(optarg);
                break;
            case '?':
                if( (optopt == 'l' ||  optopt == 'u' ||  optopt == 'i' ||  optopt == 'f' || optopt == 'n') ){
                    std::cerr << "\e[1;31m[Error]\e[m-All options required need an argument." << std::endl << std::endl;
                }
                else if( isprint(optopt) ){
                    std::cerr << "\e[1;31m[Error]\e[m-One or more options are unknown" << std::endl << std::endl;
                }
                else{
                    std::cerr << "\e[1;31m[Error]\e[m-One or more options are not supported characters." << std::endl << std::endl;
                }
                print_help();
                exit(1);
            default: // We should never reach here.
                abort();
        }
    }
    // Check unprocessed options.
    if(optind < argc){
        for( index = optind ; index < argc ; ++index ){
            std::cerr << "\e[1;31m[Error]\e[m. The following argument is not an option <" << argv[index] << ">" << std::endl << std::endl;
        }
        print_help();
        exit(1);
    }
    if( h_flag ){
        print_help();
        return 0;
    }
    // We want all of the options to be used.
    if( !l_flag || !u_flag || !i_flag || !f_flag || !n_flag ){
        std::cerr << "\e[1;31m[Error]\e[m. All options required need an argument." << std::endl << std::endl;
        print_help();
        exit(1);
    }
    // We want to go from a lower number to a higher one.
    if(lower > upper){
        lower += upper;
        upper = lower - upper;
        lower -= upper;
    }
    // I think that the increment mustn't be higher than difference between the limits given.
    if(inc > (upper-lower)){
        std::cerr << "\e[1;31m[Error]\e[m. The increment mustn't be higher than the upper number minus the lower number." << std::endl;
        exit(1);
    }
    // If the user says he want to measure things 0 times, we will still be using 1
    if(n_rpt == 0){
        n_rpt = 0;
    }
    // If the user doesn't provide the order, we will use 4
    if(!o_flag){
        orden = 4;
    }
    std::cout << "Si estas viendo este mensaje, espera un poco que la máquina está pensando.";
    fflush(stdout);
    // Timer created.
    Clock timer;

#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Determinants calculation started." << std::endl;
#endif

    for( uint i = lower ; i <= upper ; i+=inc ){
        // Here we create the random matrix
        aux_timer = 0;

#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Matrix " << i << "x" << i << " created" << std::endl;
#endif

        for( uint x = 0 ; x < n_rpt ; ++x){
            al::Matrix<double> matrix(i);
            timer.start();
            // Here we calculate the matrix determinant.
            det_tmp = det<double>(matrix);
            timer.stop();
            aux_timer += timer.elapsed();
        }

#ifdef NDEBUG
    std::cout << "\tDet calculated in " << aux_timer/n_rpt << " microseconds." << std::endl;
#endif

        // Here we save the matrix dimension and the time it took to calculate it determinant.
        stats_matrix.add_test_size(i);
        stats_matrix.add_elapsed_time(aux_timer/n_rpt);
    }

#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Determinants calculation ended." << std::endl;
#endif

#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Generating first graph." << std::endl;
#endif

    // When finished, we store store the data and generate a graph.

#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-First graph generated." << std::endl;
#endif


#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Calculating the first " << fib << " Fibonacci numbers." << std::endl;
#endif

    for( uint64_t i = 0 ; i <= fib ; ++i ){
        aux_timer = 0;
        for( uint x = 0 ; x < n_rpt ; ++x ){
            timer.start();
            fib_tmp = fibonacci(i);
            timer.stop();
            aux_timer += timer.elapsed();
        }
#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Fib " << i << " calculated in " << aux_timer/n_rpt << " microseconds." << std::endl;
#endif
        stats_fibo.add_test_size(i);
        stats_fibo.add_elapsed_time(aux_timer);
    }


#ifdef NDEBUG
    std::cout << "\e[1;33m[DEBUG]\e[m-Generating second graph." << std::endl;
#endif
    // std::cout << "Ecuación de estimación determinante (ajuste orden " << orden << "):" << std::endl << "\t";
    stats_matrix.estimate_times(orden);
    // std::cout << "Ecuación de estimación fibonacci:" << std::endl << "\t";
    stats_fibo.estimate_times(2);
    stats_matrix.dump_stats("matrix.dat");
    stats_fibo.dump_stats("fibo.dat");
    // std::cout << std::endl << "Coeficiente de determinación determinante: " << stats_matrix.get_coef() << std::endl;
    // std::cout << "Coeficiente de determinación fibo: " << stats_fibo.get_coef() << std::endl;
    bool leave = false;
    do {
        option = opciones();
        // option = 0;
        switch (option) {
            case 0:
                despedida();
                leave = true;
                break;
            case 1:
                mostrar_determinaciones(stats_fibo, stats_matrix);
                break;
            case 2:
                mostrar_ecuaciones(stats_fibo, stats_matrix, orden);
                break;
            case 3:
                mostrar_graficas();
                break;
            case 4:
                estimar_tiempos(stats_fibo, stats_matrix);
                break;
        }
    } while(!leave);
    return 0;
}
