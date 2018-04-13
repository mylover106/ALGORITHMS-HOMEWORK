#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

void get_cost(int v[], int v_num);
int get_sum(int v[], int mid, int i, int j);
int get_mid(int v[], int i, int j);
int cost[3005][3005];

int dp[3005][3005];
const int inf = numeric_limits<int>::max()/2;
int v[3005];


int main() {
    // init and read the data
    int v_num;
    int o_num;
    scanf("%d",&v_num);
    scanf("%d",&o_num);

    for (int i = 0; i < v_num; ++i) {
        scanf("%d",&v[i]);
    }

    
    get_cost(v,v_num);

    for (int i = 0; i < v_num; ++i) {
        for (int j = 0; j < v_num; ++j) {
            dp[i][j] = inf;
        }
    }


    for (int i = 0; i < v_num; ++i) {
        for (int j = 1; j <= o_num && j <= i + 1; ++j) {
            if (j == 1) {
                dp[i][1] = cost[0][i];
            } else if (j == i + 1) {
                dp[i][i+1] = 0;
            } else {
                dp[i][j] = inf;
            }
        }
    }

    // start the search
    for (int i = 1; i < v_num; ++i) {
        for (int j = 2; j <= i + 1 && j <= o_num; ++j) {
            for (int k = j - 2; k < i && k >= 0; ++k) {
                dp[i][j] = min(dp[i][j], dp[k][j-1] + cost[k+1][i]);
                // cout << dp[i][j] << endl;
            }
            // cout << i << " " << j << endl;
            // cout << dp[i][j] << endl;
        }
    }

    printf("%d\n",dp[v_num-1][o_num]);



    return 0;
}


void get_cost(int v[], int v_num) {
    int mid,sum;
    for (int i = 0; i < v_num; ++i) {
        cost[i][i] = 0;
    }
    for (int i = 0; i < v_num; ++i) {
        for (int j = i + 1; j < v_num; ++j) {
            mid = get_mid(v,i,j);
            sum = get_sum(v,mid,i,j);
            cost[i][j] = sum;
        }
    }
}


int get_mid(int v[], int i, int j) {
    // float mid;
    // float sum = 0;
    // for (int t = i;t <= j; ++t) {
    //     sum += v[t];
    // }
    // mid = sum/(j-i+1);
    // float minimal = abs(v[i] - mid);
    // int min_index = i;
    // for (int t = i; t <= j; ++t) {
    //     if (minimal > abs(v[t]-mid)) {
    //         minimal = abs(v[t]-mid);
    //         min_index = t;
    //     }
    // }
    // return v[min_index];
    return v[(i+j)/2];
}

int get_sum(int v[], int mid, int i, int j) {
    int sum = 0;
    for (int t = i; t <= j; ++t) {
        sum += abs(v[t]-mid);
    }
    return sum;
}