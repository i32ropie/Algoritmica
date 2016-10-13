#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <stdint.h> // Para usar uint64_t
#include "matrix.hpp"
#include "statistical.hpp"

#define cls() system("clear");
#define TINY 1.e-30

void cabecera(){
    cls();
    std::cout << "\e[1;92m###############################" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "####        \e[96mPrograma       \e[92m####" << std::endl;
    std::cout << "####                       ####" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "###############################\e[0m" << std::endl << std::endl;
}

void volver(){
    std::cout << std::endl << "Presiona ENTER para volver al menú.";
    std::cin.ignore();
    std::cin.ignore();
}

void error(const std::string &er){
    std::cout << std::endl << "\e[31;1m[ERROR]\e[0m - " << er;
    fflush(stdout);
    sleep(2);
}

uint64_t fibonacci(uint64_t x){
    return x > 2?fibonacci(x-1)+fibonacci(x-2):x;
}

template<class T>
void LU_decompos(std::vector< std::vector< T > > &a,int n,std::vector<uint> &indx,int &d,std::vector<T> &vv) {
        int i,imax,j,k;
        double big,sum,temp;
        d=1;
        /* search for the largest element in each row; save the scaling in the
           temporary array vv */
        for(i=0; i<n; i++) {
                big=0.;
                for(j=0; j<n; j++) if((temp=std::abs(a[i][j]))>big) big=temp;
                vv[i]=big;
        }
        /* the main loop for the Crout's algorithm */
        for(j=0; j<n; j++) {
                /* this is the part a) of the algorithm except for i==j */
                for(i=0; i<j; i++) {
                        sum=a[i][j];
                        for(k=0; k<i; k++) sum-=a[i][k]*a[k][j];
                        a[i][j]=sum;
                }
                /* initialize for the search for the largest pivot element */
                big=0.; imax=j;
                /* this is the part a) for i==j and part b) for i>j + pivot search */
                for(i=j; i<n; i++) {
                        sum=a[i][j];
                        for(k=0; k < j; k++) sum-=a[i][k]*a[k][j];
                        a[i][j]=sum;
                        /* is the figure of merit for the pivot better than the best so far? */
                        if((temp=vv[i]*fabs(sum))>=big) {big=temp; imax=i; }
                }
                /* interchange rows, if needed, change parity and the scale factor */
                if(imax!=j) {
                        for(k=0; k<n; k++) {temp=a[imax][k]; a[imax][k]=a[j][k]; a[j][k]=temp; }
                        d=-d; vv[imax]=vv[j];
                }
                /* store the index */
                indx[j]=imax;
                /* if the pivot element is zero, the matrix is singular but for some
                   applications a tiny number is desirable instead */
                if(a[j][j]==0.) a[j][j]=TINY;
                /* finally, divide by the pivot element */
                if(j<n-1) {
                        temp=1./a[j][j];
                        for(i=j+1; i<n; i++) a[i][j]*=temp;
                }
        }
}

template<class T>
T LU_determ(std::vector<std::vector< T > > &a,uint n,int &d) {
        T res= T(d);
        for( uint j = 0 ; j < n ; j++ ){
            res *= a[j][j];
        }
        return res;
}

template<class T>
T det(al::Matrix<T> &matrix){
    std::vector<std::vector< T > > m = matrix.get_matrix();
    uint size = matrix.get_size();
    int d;
    std::vector<uint> indx = std::vector<uint>(size);
    std::vector<T> vv = std::vector<T>(size);
    LU_decompos<T>(m, size, indx, d, vv);
    return LU_determ(m, size, d);
}

template<class T>
long long det_2(const al::Matrix<T> &matrix){
    std::vector<std::vector< T > > m = matrix.get_matrix();
    long long res = 1, aux1, aux2;
    int size = m.size();
    for( int k = 0 ; k < (size - 1) ; ++k ){
        for( int i = k + 1 ; i < size ; ++i ){
            if(std::abs(m[i][k])>std::abs(m[k][k])){
                m[k].swap(m[i]);
            }
        }
        aux1 = m[k][k];
        for( int i = k +1 ; i < size ; ++i ){
            aux2 = m[i][k]/aux1;
            for( int j = 0 ; j < size ; ++j ){
                m[i][j] -= m[k][j]*aux2;
            }
        }
        res *= aux1;
    }
    return res;
}


void print_help(){
    std::cout << "The program syntax is:" << std::endl << std::endl;
    std::cout << "   \e[1m./main -l <uint> -u <uint> -i <uint> -f <uint> -n <uint> -o <uint>\e[m" << std::endl << std::endl;
    std::cout << "\e[1m-l <uint>\e[m  : Lower number to create the matrix.      (\e[4;1mRequired\e[m)" << std::endl;
    std::cout << "\e[1m-u <uint>\e[m  : Upper number to create the matrix.      (\e[4;1mRequired\e[m)" << std::endl;
    std::cout << "\e[1m-i <uint>\e[m  : Increment size while creating matrices. (\e[4;1mRequired\e[m)" << std::endl;
    std::cout << "\e[1m-f <uint>\e[m  : Fibonacci number to calculate.          (\e[4;1mRequired\e[m)" << std::endl;
    std::cout << "\e[1m-n <uint>\e[m  : Number of repetitions.                  (\e[4;1mRequired\e[m)" << std::endl;
    std::cout << "\e[1m-o <uint>\e[m  : Order of the adjustment.                (\e[4;1mOptional\e[m)" << std::endl;
    std::cout << "\e[1m-h\e[m         : Displays the help." << std::endl << std::endl;
}

uint opciones(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Mostrar los coeficientes de determinación." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Mostrar las ecuaciones de estimación." << std::endl;
        std::cout << "\t\e[33;1m[3]\e[0m - Mostrar las matrices generadas. (Uso de xdg-open)" << std::endl;
        std::cout << "\t\e[33;1m[4]\e[0m - Estimar tiempos." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Salir del programa." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>4){
            error("Opción no válida. Volviendo al menú principal...");
        }
    }while(opcion<0 || opcion>4);
    return opcion;
}

uint opciones2(){
    int opcion;
    do{
        cabecera();
        std::cout << "Estas son las opciones disponibles:" << std::endl;
        std::cout << "\t\e[33;1m[1]\e[0m - Estimar cuanto tardaría un determinante." << std::endl;
        std::cout << "\t\e[33;1m[2]\e[0m - Estimar cuanto tardaría un término de fibonacci." << std::endl;
        std::cout << "\t\e[33;1m[0]\e[0m - Volver al menú principal." << std::endl;
        std::cout << "Introduce tu opción: \e[33;1m";
        std::cin >> opcion;
        std::cout << "\e[0m";
        if(opcion<0 || opcion>4){
            error("Opción no válida.");
        }
    }while(opcion<0 || opcion>4);
    return opcion;
}

void mostrar_determinaciones(al::Statistical &stats_fibo,al::Statistical &stats_matrix){
    cabecera();
    std::cout << std::endl << "Coeficiente de determinación determinante: " << stats_matrix.get_coef() << std::endl;
    std::cout << "Coeficiente de determinación fibo: " << stats_fibo.get_coef() << std::endl;
    volver();
}

void mostrar_ecuaciones(al::Statistical &stats_fibo, al::Statistical &stats_matrix, uint &orden){
    cabecera();
    std::vector<long double> aux1 = stats_matrix.get_params_value();
    std::vector<long double> aux2 = stats_fibo.get_params_value();
    std::cout << "Ecuación de estimación determinante (ajuste orden " << orden << "):" << std::endl << "\tt(n) = ";
    for( uint i = 0 ; i < aux1.size() ; ++i ){
        std::cout << std::abs(aux1[i]) << "*n^" << i;
        if( i < (aux1.size()-1))
            aux1[i]>0?std::cout<<" + ":std::cout<<" - ";
    }
    std::cout << std::endl << std::endl << "Ecuación de estimación fibonacci:" << std::endl << "\tt(n) = ";
    std::cout << aux2[0] << (aux2[1]>0?" + ":" - ") << std::abs(aux2[1]) << "*2^n" << std::endl;
    volver();
}

void mostrar_graficas(){
    cabecera();
    std::string cmd1 = "xdg-open matrix.eps  2> /dev/null";
    std::string cmd2 = "xdg-open fibo.eps  2> /dev/null";
    FILE * aux1 = popen(cmd1.c_str(), "r"), * aux2 = popen(cmd2.c_str(), "r");
    pclose(aux1);
    pclose(aux2);
    volver();
}

void estimar(al::Statistical &stats,const std::string &x){
    cabecera();
    uint tam;
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
    if(!lineal)
        std::cout << std::endl << "Tardaría " << res*(pow(10, -6)/(3600*24)) << " años." << std::endl;
    else
        std::cout << std::endl << "Tardaría " << res*pow(10,-6)/(60*60) << " horas." << std::endl;
    volver();
}

void estimar_tiempos(al::Statistical &stats_fibo, al::Statistical &stats_matrix){
    cabecera();
    bool leave = false;
    int opcion;
    do {
        opcion = opciones2();
        switch (opcion) {
            case 0:
                leave = true;
                break;
            case 1:
                estimar(stats_matrix, "orden de la matriz");
                break;
            case 2:
                estimar(stats_fibo, "número de fibonacci");
                break;
        }
    } while(!leave);
    volver();
}

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

#endif
