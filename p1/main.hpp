#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <vector>
#include <cmath>

#define TINY 1.e-30

void LU_decompos(std::vector< std::vector< double > > &a,int n,std::vector<uint> &indx,int &d,std::vector<double> &vv) {
        register int i,imax,j,k;
        double big,sum,temp;
        d=1;
        /* search for the largest element in each row; save the scaling in the
           temporary array vv */
        for(i=0; i<n; i++) {
                big=0.;
                for(j=0; j<n; j++) if((temp=fabs(a[i][j]))>big) big=temp;
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

double LU_determ(std::vector<std::vector< double > > &a,int n,std::vector<uint> &indx,int &d) {
        double res= double(d);
        for( uint j = 0 ; j < n ; j++ ){
            res *= a[j][j];
        }
        return res;
}

double det_rec_1(const std::vector<std::vector< double>> matrix, const uint &size){
    double res = 0, aux = 0;
    int c;
    if(size == 2){
        return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    }
    else{
        for( uint i = 0 ; i < size ; ++i ){
            std::vector<std::vector< double > > m;
            m = std::vector< std::vector< double > >(size-1, std::vector<double>(size-1));
            for( uint j = 1 ; j < size ; ++j ){
                c = 0;
                for( uint k = 0 ; k < size ; ++k ){
                    if( k != i ){
                        m[j-1][c] = matrix[j][k];
                        c++;
                    }
                }
            }
            aux = pow(-1, 2+i) * matrix[0][i] * det_rec_1(m, size-1);
            res += aux;
        }
    }
    return res;
}

double det_rec_2(const std::vector<std::vector< double>> matrix, const uint &size){
    double res = 0;
    int h, k;
    std::vector<std::vector< double > > m;
    m = std::vector< std::vector< double > >(size-1, std::vector<double>(size-1));

    if(size == 1){
        return matrix[0][0];
    }
    else if(size == 2){
        return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    }
    else{
        for( uint p = 0 ; p < size ; ++p ){
            h = 0;
            k = 0;
            for( uint i = 1 ; i < size ; ++i ){
                for( uint j = 0 ; j < size ; ++j ){
                    if( j==p ){
                        continue;
                    }
                    m[h][k] = matrix[i][j];
                    k++;
                    if( k == size-1){
                        h++;
                        k = 0;
                    }
                }
            }
            res += matrix[0][p] * pow(-1, p) * det_rec_2(m, size-1);
        }
        return res;
    }
}

double det(al::Matrix &matrix){
    std::vector<std::vector< double > > m = matrix.get_matrix();
    uint size = matrix.get_size();
    // return det_rec_1(m, size);
    // std::cout << "Determinante recursivo: " << det_rec_1(m, size) << std::endl << std::endl;
    int d;
    std::vector<uint> indx = std::vector<uint>(size);
    std::vector<double> vv = std::vector<double>(size);
    LU_decompos(m, size, indx, d, vv);
    // std::cout << "Determinante crout: " << LU_determ(m, size, indx, d) << std::endl << std::endl;
    return LU_determ(m, size, indx, d);
}

#endif
