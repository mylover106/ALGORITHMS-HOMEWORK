#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

const int inf = numeric_limits<int>::max()/2;

int main() {
    // read the test data
    int n;
    scanf("%d",&n);
    char s[5003];
    scanf("%s",s+1);
    int dp[3][5003];

    // init
    for (int i = 1; i < 5003; ++i) {
        dp[0][i] = inf;
        dp[1][i] = inf;
    }

    for (int i = n; i >= 1; --i) {
        for (int j = i; j <= n; ++j) {
            // cout << i << " " << j << endl;
            if (i == j) {
                dp[i%2][j] = 0;
                // cout << dp[i%2][j] << endl;
                continue;
            }
            if (j-1 == i) {
                if (s[i] == s[j]) {
                    dp[i%2][j] = 0;
                    // cout << dp[i%2][j] << endl;
                    continue;
                } else {
                    dp[i%2][j] = 1;
                    // cout << dp[i%2][j] << endl;
                    continue;
                }
            }
            if (j-1 > i) {
                if (s[i] == s[j]) {
                    dp[i%2][j] = dp[(i+1)%2][j-1];
                    // cout << dp[i%2][j] << endl;
                    continue;
                } else {
                    dp[i%2][j] = min(dp[(i+1)%2][j]+1,dp[i%2][j-1]+1);
                    // cout << dp[i%2][j] << endl;
                    continue;
                }
            }
        }
    }

    printf("%d",dp[1][n]);
    return 0;
}

// 当使用滚动数组的时候需要注意，滚动的index只能放到最外层，因为如果放到最里层，每次滚动只能保存
// 这轮循环的两个值，就会产生错误。所以只能放到外层，对每个迭代的有效数据进行保护。