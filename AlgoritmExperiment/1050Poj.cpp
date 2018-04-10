#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>

using namespace std;

const int max_ = 200;
int dp[max_];
int sum[max_][max_][max_];
int matrix[max_][max_];
const int inf = numeric_limits<int>::max()/2;

int main() {
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) {
        scanf("%d",&matrix[i][j]);
    }
    // init the sum[][][]
    int an;
    int bfr_sum;
    for (int row = 0; row < n; ++row)
    for (int s = 0; s < n; ++s)
    sum[row][s][s] = matrix[row][s];
    

    for (int row = 0; row < n; ++row)
    for (int s = 0; s < n; ++s)
    for (int e = s+1; e < n; ++e){
        an = matrix[row][e];
        bfr_sum = sum[row][s][e-1];
        sum[row][s][e] = bfr_sum + an;
    }

    // init the dp
    int maximal = -inf;
    for (int s = 0; s < n; ++s) 
    for (int e = s; e < n; ++e)
    for (int row = 0; row < n; ++row){
        an = sum[row][s][e];
        if (row == 0){
            dp[row] = an;
        }else {
            dp[row] = max(dp[row-1]+an, an);
        }
        maximal = max(dp[row],maximal);
    }
    printf("%d\n",maximal);
    return 0;
}