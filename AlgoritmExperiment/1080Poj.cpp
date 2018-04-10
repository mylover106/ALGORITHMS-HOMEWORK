#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int inf = numeric_limits<int>::max()/2;
const int max_ = 200;
int dp[max_][max_];
const int null = 4;

// encoding A:0 C:1 G:2 T:3 -:4

const int v[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};

int main() {
    int n;
    scanf("%d",&n);
    int len[2];
    char s[2][max_];
    while(n) {
        n--;
        // read and handle the data
        scanf("%d",&len[0]);
        if (len[0] != 0)scanf("%s",s[0]+1);
        scanf("%d",&len[1]);
        if (len[1] != 0)scanf("%s",s[1]+1);
        for (int i = 0; i < len[0]; ++i) {
            if (s[0][i+1] == 'A') s[0][i+1] = 0;
            if (s[0][i+1] == 'C') s[0][i+1] = 1;
            if (s[0][i+1] == 'G') s[0][i+1] = 2;
            if (s[0][i+1] == 'T') s[0][i+1] = 3;
        }
        for (int i = 0; i < len[1]; ++i) {
            if (s[1][i+1] == 'A') s[1][i+1] = 0;
            if (s[1][i+1] == 'C') s[1][i+1] = 1;
            if (s[1][i+1] == 'G') s[1][i+1] = 2;
            if (s[1][i+1] == 'T') s[1][i+1] = 3;
        }
        int lng,shrt;
        if (len[0] > len[1]) {
            lng = 0;
            shrt = 1;
        } else {
            lng = 1;
            shrt = 0;
        }
        
        int ci,cj;
        int num;
        dp[0][0] = 0;
        for (int i = 1; i <= len[lng]; ++i) {
            dp[i][0] = dp[i-1][0] + v[s[lng][i]][null];
        }
        for (int j = 1; j <= len[shrt]; ++j) {
            dp[0][j] = dp[0][j-1] + v[null][s[shrt][j]];
        }
        // // test print 
        // for (int i = 0; i <= len[lng]; ++i) {
        //     cout << dp[i][0] << endl;
        // }

        for (int i = 1; i <= len[lng]; ++i) {
            for (int j = 1; j <= len[shrt]; ++j) {
                ci = s[lng][i];
                cj = s[shrt][j];
                dp[i][j] = dp[i-1][j-1] + v[ci][cj];
                dp[i][j] = max(dp[i][j], dp[i-1][j] + v[ci][null]);
                dp[i][j] = max(dp[i][j], dp[i][j-1] + v[cj][null]);
            }
        }
        
        printf("%d\n",dp[len[lng]][len[shrt]]);
    }
    return 0;
}