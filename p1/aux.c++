#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math>

using namespace std;

void printMatrix(vector<vector<int> > const& mat)
{
   int n = mat.size();
   for(int row = 0; row < n; ++row) {
      for(int col = 0; col < n; ++col) {
         cout << mat[row][col] << " ";
      }
      cout << "\n";
   }
   cout << "\n";
}

int det(vector<vector<int> > mat) {
   int n = mat.size();

   for(int col = 0; col < n; ++col) {
    //   cout << "Column: " << col << "\n";
    //   printMatrix(mat);
      bool found = false;
      for(int row = col; row < n; ++row) {
         if(mat[row][col]) {
            cout << "Got non-zero value for row " << row << " and col " << col << "\n";
            if ( row != col )
            {
               cout << "(1) Swapping rows " << col << " and " << row << "\n";
               mat[row].swap(mat[col]);
               printMatrix(mat);
            }
            else
            {
               cout << "Not swapping rows\n";
            }
            found = true;
            break;
         }
      }

      if(!found) {
         cout << "Did not find a non-zero row. Column: " << col << "\n";
         return 0;
      }

      for(int row = col + 1; row < n; ++row) {
         while(true) {
            int del = mat[row][col] / mat[col][col];
            cout << "del: " << del << "\n";
            for (int j = col; j < n; ++j) {
               mat[row][j] -= del * mat[col][j];
            }
            if (mat[row][col] == 0)
            {
               break;
            }
            else
            {
               cout << "(2) Swapping rows " << col << " and " << row << "\n";
               mat[row].swap(mat[col]);
               printMatrix(mat);
            }
         }
      }
   }

   printMatrix(mat);
   long res = 1;

   for(int i = 0; i < n; ++i) {
      res *= mat[i][i];
   }
   return abs(res);
}

int main()
{
   vector<vector<int> > mat = { {4, 6, 5}, {1, 2, 3}, {8, 10, 9} };
   int r = det(mat);
   cout << "Determinant: " << r << endl;
   return 0;
}
