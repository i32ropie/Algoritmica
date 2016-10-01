#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <map>
// #include <cassert>
#include "matrix.hpp"
#include "ClaseTiempo.hpp"
#include "main.hpp"


int main(int argc, char *argv[]) {
    srand(time(NULL));
    double det_tmp;
    uint64_t fib, fib_tmp;
    std::map<uint,uint64_t> time_lapse;
    bool h_flag = false, l_flag = false, u_flag = false, i_flag = false, f_flag = false;
    uint lower, upper, inc;
    int option, index;
    // Force our errors to appear only.
    opterr = 0;
    while( (option = getopt(argc, argv, "hl:u:i:f:")) != -1 ){
        switch(option){
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
            case '?':
                if( (optopt == 'l' ||  optopt == 'u' ||  optopt == 'i' ||  optopt == 'f') ){
                    fprintf(stderr, "\e[1;31m[Error]\e[m. All options are required and need an argument.\n\n");
                }
                else if( isprint(optopt) ){
                    fprintf(stderr, "\e[1;31m[Error]\e[m. One or more options are unknown\n\n");
                }
                else{
                    fprintf(stderr, "\e[1;31m[Error]\e[m. One or more options are not supported characters.\n\n");
                }
                print_help();
                exit(1);
            default:
                abort();
        }
    }
    // Check unprocesse options.
    if(optind < argc){
        for( index = optind ; index < argc ; ++index ){
            fprintf(stderr, "\e[1;31m[Error]\e[m. The following argument is not an option <%s>\n\n", argv[index]);
        }
        exit(1);
    }
    if( h_flag ){
        print_help();
        return 0;
    }
    if( !l_flag || !u_flag || !i_flag || !f_flag ){
        fprintf(stderr, "\e[1;31m[Error]\e[m. All options are required and need an argument.\n\n");
        print_help();
        exit(1);
    }
    if(lower > upper){
        lower += upper;
        upper = lower - upper;
        lower -= upper;
    }
    if(inc > (upper-lower)){
        fprintf(stderr, "\e[1;31m[Error]\e[m. The increment mustn't be higher than the upper number minus the lower number.\n");
        exit(1);
    }

    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-Options values" << std::endl;
        std::cout << "\tLower:        " << lower << std::endl;
        std::cout << "\tUpper:        " << upper << std::endl;
        std::cout << "\tIncrement:    " << inc << std::endl;
        std::cout << "\tFib:          " << fib << std::endl;
    #endif

    Clock timer;

    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-Determinants calculation started." << std::endl;
    #endif

    for( uint i = lower ; i <= upper ; i+=inc ){
        al::Matrix matrix(i);

        #ifdef NDEBUG
            std::cout << "\e[1;33m[DEBUG]\e[m-Matrix " << i << "x" << i << " created" << std::endl;
        #endif

        timer.start();
        det_tmp = det(matrix);
        timer.stop();

        #ifdef NDEBUG
            std::cout << "\tDet calculated in " << timer.elapsed() << " microseconds." << std::endl;
        #endif

        time_lapse[i] = timer.elapsed();
    }

    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-Determinants calculation ended." << std::endl;
    #endif

    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-Generating first graph." << std::endl;
    #endif

    generate_graph(time_lapse, "matrix.dat");

    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-First graph generated." << std::endl;
    #endif
    time_lapse.clear();
    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-Calculating the first " << fib << " Fibonacci numbers." << std::endl;
    #endif
    for( uint64_t i = 0 ; i <= fib ; ++i ){
        timer.start();
        fib_tmp = fibonacci(i);
        timer.stop();
        #ifdef NDEBUG
            std::cout << "\e[1;33m[DEBUG]\e[m-Fib " << i << " calculated in " << timer.elapsed() << " microseconds." << std::endl;
        #endif
        time_lapse[i] = timer.elapsed();
    }


    #ifdef NDEBUG
        std::cout << "\e[1;33m[DEBUG]\e[m-Generating second graph." << std::endl;
    #endif
    generate_graph(time_lapse, "fibo.dat");

    return 0;
}
