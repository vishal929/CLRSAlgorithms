#include<vector>

/*
    Prices is an n-dimensional array where the i-th entry is the price for a rod of i+1-inches 
        (i.e first element is the price of rod of length 1)
    rodLength is the length of the initial rod
    We return an integer which represents the maximum revenue we can achieve by cutting up the given rod of size rodLength
*/
int rodCutting(std::vector<int> prices, int rodLength){
    using namespace std;
   // idea we create an array M[i] where M[i] is the maximum profit that can be achieved for a rod using i inches
   vector<int> M(rodLength+1,0);
   for (int i=1;i<rodLength;i++){
        M[i] = prices[i-1];
        for (int j=0;j<=i;j++){
            M[i] = max(M[i],M[j]+M[i-j]);
        }

   }
   return M[rodLength];

}