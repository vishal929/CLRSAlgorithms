#include <vector>
#include <stack>
#include <iostream>


/*
    matrixDims: array of size N+1 where matrixDims[i-1],matrixDims[i] are the dimensions of the i-th matrix
    we want to return the splits in which to multiply matrices and the number of operations computed
*/
std::pair<std::vector<std::vector<int>>,int> matrixChainMultiplication(std::vector<int> &matrixDims){
    /* M[i,j] is the optimal number of multiplications required to multiply matrices i thru j
       M[i,i]=0
       M[i,i+1] = dim[i-1] * dim[i] * dim[i+1]
       M[i,j] = min_{i<=k<j}(M[i,k] + M[k+1,j] + dim[i-1] * dim[k] * dim[j])
       the pure diagonal M[i,i]=0, and we need to compute along diagonals based on the update
    */
   // we also need to keep track of which matrices to multiply to make this useful!
   // we define s[i,j]=k where we split in the dynamic programming part above (this way we can reconstruct the solution from M[1,n]) 
   using namespace std;
   // (n+1 x n+1 matrix)
   vector<vector<int>> M(matrixDims.size(),vector<int>(matrixDims.size(),0)); 
   vector<vector<int>> S(matrixDims.size(),vector<int>(matrixDims.size(),0));
   for (int j=1;j<matrixDims.size();j++){
    for (int i=0;i<matrixDims.size();i++){
       M[i][i+j] = INT_MAX; 
       for (int k=i;k<i+j;k++){
            int possibleLower = M[i][k] + M[k+1][i+j] + matrixDims[i-1] * matrixDims[k] * matrixDims[i+j];
            if (possibleLower < M[i][i+j]){
                M[i][i+j] = possibleLower;
                // set the split
                S[i][i+j] = k;
            }
       }
    }
   }
    
   // returning the splits at each optimal solution and the optimal number of operations
   return make_pair(S, M[1][matrixDims.size() - 1]);
    
}

/*
    Given saved splits, we print an order of matrix multiplications like (A1 (A2 A3) A4) which corresponds to the optimal multiplication order
*/
void printMultiplicationOrder(std::vector<std::vector<int>> &S, int i, int j ) {
    using namespace std;
    if (i == j) {
        cout << "A" << i << " ";
        return;
    }
    cout << "( ";
    printMultiplicationOrder(S, i, S[i][j]);
    printMultiplicationOrder(S, S[i][j] + 1, j);
    cout << ") ";
}