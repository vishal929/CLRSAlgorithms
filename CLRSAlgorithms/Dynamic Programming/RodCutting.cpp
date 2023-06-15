#include<vector>
#include <stack>

/*
    Prices is an n-dimensional array where the i-th entry is the price for a rod of i+1-inches 
        (i.e first element is the price of rod of length 1)
    rodLength is the length of the initial rod
    We return a pair of :
        1) an integer which represents the maximum revenue we can achieve by cutting up the given rod of size rodLength
        2) an array which holds the sizes of the divisions in the optimal solution
*/
std::pair<int,std::vector<int>> rodCutting(std::vector<int> prices, int rodLength){
    using namespace std;
   // idea we create an array M[i] where M[i] is the maximum profit that can be achieved for a rod using i inches 
   // entire DP solution takes O(n^2) time
   vector<int> M(rodLength+1,0);
   for (int i=1;i<rodLength;i++){
        M[i] = prices[i-1];
        for (int j=0;j<=i;j++){
            M[i] = max(M[i],M[j]+M[i-j]);
        }

   }
   // we can trace back and recover the sizes of the solution and return them as well (this will take O(n^2) time so no problem!)
   vector<int> sol;
   stack<int> dfs;

   dfs.push(rodLength);
   while (dfs.size() > 0) {
       int idx = dfs.top();
       dfs.pop();

       // we should check if this index is a terminal split (i.e the maximum profit for this size is achieved with no splitting)
       // if its not a terminal split, we push the splits back to the stack
       if (M[idx] == prices[idx - 1]) {
           // terminal split
           sol.push_back(idx - 1);
           continue;
       }

       // not a terminal split, we have to determine the splits and push them back to the stack
       for (int j = 0; j <= idx; j++) {
           if (M[idx] == M[j] + M[idx - j]) {
                // we found the split
               dfs.push(j);
               dfs.push(idx - j);
           }
       }
   }

   return make_pair(M[rodLength],sol);

}