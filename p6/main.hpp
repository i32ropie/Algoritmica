#ifndef P6_MAIN_HPP
#define P6_MAIN_HPP

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include "statistical.hpp"
#include "reinas.hpp"
#include "main_auxiliar.hpp"

#ifdef __linux__
    #define cls() system("clear");
#elif _WIN32
    #define cls() system("cls");
#endif
// Problema de las N-Reinas
/**
* @brief Cabecera que se mostrará durante la ejecución del programa.
*/
void cabecera(){
    cls();
    std::cout << "\e[1;92m###############################" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "####    \e[96mProblema de las\e[92m    ####" << std::endl;
    std::cout << "####       \e[96mN-Reinas\e[92m        ####" << std::endl;
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
        std::cout << "\t\e[33;1m[1]\e[0m - Resolver mediante backtracking." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Resolver mediante Las Vegas." << std::endl;
        std::cout << "\t\e[33;1m[3]\e[0m - Cálculo de estadísticos." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Salir del programa." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>3){
            error("Opción no válida...");
        }
    }while(opcion<0 || opcion>3);
    return opcion;
}

void resolver_backtracking(){
    cabecera();
    int n;
    std::string aux;
    std::cout << "Introduce el número de reinas (mayor de 3): ";
    std::cin >> n;
    std::cin.ignore();
    al::Reinas r(n);
    std::cout << "Resolviendo..." << std::endl << std::endl;
    r.resolver_backtracking();
    std::cout << r << std::endl;
    std::cout << "¿Desea ver las soluciones por pantalla? (s/n): ";
    std::getline(std::cin, aux);
    if(aux == "s"){
        mostrar_soluciones(r.get_soluciones());
    }
    aux.clear();
    std::cout << "¿Desea exportar las soluciones? (s/n): ";
    std::getline(std::cin, aux);
    if(aux == "s"){
        std::cout << std::endl << "Podrá encontrar la salida en: " << exportar_soluciones(r.get_soluciones()) << std::endl;
    }
    volver(1);
}

int opciones_las_vegas(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Solución única." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Todas las soluciones." << std::endl;
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

void las_vegas_1(){
    cabecera();
    int n;
    std::cout << "Introduce el número de reinas (mayor que 3): ";
    std::cin >> n;
    std::cin.ignore();
    al::Reinas r(n);
    r.resolver_probabilistico();
    mostrar_soluciones(r.get_soluciones());
    std::cout << "Solución obtenida en " << r.get_intentos() << " intentos." << std::endl;
    volver(1);
}

void las_vegas_2(){
    cabecera();
    std::vector<int> aux = {0, 0, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712};
    std::string aux2;
    int n;
    int pruebas = 0;
    std::cout << "Introduce el número de reinas (mayor que 3): ";
    std::cin >> n;
    std::cin.ignore();
    al::Reinas r(n);
    std::cout << std::endl << "Obteniendo las " << aux[n] << " soluciones para el problema de las " << n << " reinas." << std::endl;
    while(r.get_soluciones().size() != aux[n]){
        r.resolver_probabilistico();
        pruebas++;
    }
    std::cout << std::endl << "Soluciones obtenidas tras " << pruebas << " pruebas." << std::endl << std::endl;
    std::cout << "¿Desea ver las soluciones por pantalla? (s/n): ";
    std::getline(std::cin, aux2);
    if(aux2 == "s"){
        mostrar_soluciones(r.get_soluciones());
    }
    aux.clear();
    std::cout << "¿Desea exportar las soluciones? (s/n): ";
    std::getline(std::cin, aux2);
    if(aux2 == "s"){
        std::cout << std::endl << "Podrá encontrar la salida en: " << exportar_soluciones(r.get_soluciones()) << std::endl;
    }
    volver(1);

}

void menu_las_vegas(){
    int opcion;
    bool salir = false;
    do{
        opcion = opciones_las_vegas();
        switch(opcion){
            case 0:
                salir = true;
                break;
            case 1:
                las_vegas_1();
                break;
            case 2:
                las_vegas_2();
                break;
        }
    }while(!salir);
}

#endif //P6_MAIN_HPP
