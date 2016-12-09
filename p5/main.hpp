/**
* @file main.hpp
* @brief <Práctica 4> main.
* @author Eduardo Roldán Pijuán
* @date Diciembre de 2016
*/

#ifndef P5_MAIN_HPP
#define P5_MAIN_HPP


#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h> // Para usar uint64_t
#include "statistical.hpp"
#include "ClaseTiempo.hpp"
#include "currency.hpp"

#ifdef __linux__
    #define cls() system("clear");
#elif _WIN32
    #define cls() system("cls");
#endif

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
    std::cout << std::endl << "\e[31;1m[ERROR]\e[0m - " << er;
    fflush(stdout);
    sleep(2);
}

/**
 * @brief Función de presentación del programa donde se indica que se usa el archivo "currency.txt" para las monedas.
 * @sa cabecera()
 * @sa volver()
 */
void presentacion(){
    cabecera();
    std::cout << "Bienvenido. Con este programa podrá resolver el problema del cambio mediante" << std::endl;
    std::cout << "un algoritmo dinámico que propocionará la solución óptima." << std::endl;
    std::cout << std::endl << "Para asegurar el buen funcionamiento del programa, compruebe que el archivo " << std::endl;
    std::cout << "\e[1m'currency.txt'\e[m existe en la ruta del ejecutable y contiene el valor de las" << std::endl;
    std::cout << "monedas que serán usadas en la resolución del problema." << std::endl;

    volver(1, "Presiona ENTER para continuar.");
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


/**
* @brief Muestra las opciones del menú de estadísticos e interactua con el usuario.
* @return Opción del menú a ejecutar.
* @sa error()
* @sa cabecera()
*/
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

/**
 * @brief Muestra el coeficiente de determinación.
 * @param stats Estadísticos (al::Statistical)
 * @sa cabecera()
 * @sa volver()
 */
void mostrar_determinacion(al::Statistical &stats){
    cabecera();
    std::cout << std::endl << "Coeficiente de determinación: " << stats.get_coef() << std::endl;
    volver();
}

/**
 * Muestra la ecuación de estimación.
 * @param stats Estadísticos (al::Statistical)
 * @sa cabecera()
 * @sa volver()
 */
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

/**
 * @brief Estima cuanto tardaría una carga.
 * @param stats Estadísticos (al::Statistical)
 * @param x Mensaje a mostrar al calcular tiempos (std::string)
 * @sa cabecera()
 * @sa volver()
 */
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

/**
 * @brief Muestra la gráfica haciendo uso de xdg-open
 * @param f_name Nombre del archivo a mostrar (std::string)
 * @sa cabecera()
 * @sa volver()
 */
void mostrar_grafica(const std::string &f_name){
    cabecera();
    std::string cmd = "xdg-open " + f_name + " 2> /dev/null";
    FILE * aux = popen(cmd.c_str(), "r");
    pclose(aux);
    volver();
}

/**
* @brief Muestra las opciones del menú e interactua con el usuario.
* @return Opción del menú a ejecutar.
* @sa error()
* @sa cabecera()
*/
int opciones(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Resolver el problema de forma normal." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Cálculo de estadísticos." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Salir del programa." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>2){
            error("Opción no válida...");
        }
    }while(opcion<0 || opcion>2);
    return opcion;
}

/**
 * @brief Resuelve el problema del cambio de manera gráfica una sola vez.
 * @sa cabecera()
 * @sa volver()
 */
void resolver_cambio_basico(){
    cabecera();
    int euros, centimos, centimos_total;
    std::cout << "Introduce el número de euros: ";
    std::cin >> euros;
    std::cout << std::endl << "Introduce el número de céntimos: ";
    std::cin >> centimos;
    centimos_total = euros * 100 + centimos;
    al::Currency c(centimos_total);
    c.solve();
    cabecera();
    std::cout << c;
    volver();
}

/**
 * @brief Resuleve el problema del cambio múltiples veces y muestra el menú de estadísticos.
 * @sa cabecera()
 * @sa opciones_stats()
 * @sa mostrar_determinacion()
 * @sa mostrar_ecuacion()
 * @sa mostrar_grafica()
 * @sa estimar_tiempos()
 */
void resolver_cambio_estadistico(){
    cabecera();
    Clock timer;
    uint64_t aux_timer;
    int n_rpt = 3;
    al::Statistical stats;
    int min = 50000, max = 100000;
    int incremento;
    std::cout << "Introduce el incremento: ";
    std::cin >> incremento;
    std::cout << std::endl << "Realizando cálculos...";
    fflush(stdout);
    for(int i = min ; i <= max ; i+=incremento){
        aux_timer = 0;
        for(int j = 0 ; j < n_rpt ; ++j){
            al::Currency c(i);
            timer.start();
            c.solve();
            timer.stop();
            aux_timer += timer.elapsed();
        }
        stats.add_test_size(i);
        stats.add_elapsed_time(aux_timer/n_rpt);
    }
    stats.estimate_times(3);
    stats.dump_stats("cambio.dat");
    int opcion;
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
                mostrar_grafica("cambio.eps");
                break;
            case 4:
                estimar_tiempos(stats, "número de céntimos de cambio");
                break;
        }
    }while(!salir);
}

#endif
