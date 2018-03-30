#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define oo (1 << 4*sizeof(int))

int adjm[250][250];
int dp[250][250]; // dp[root][num]
int rootdp[250][250][250];  // rootdp[root][step][volume]
                            // volume also represent the 
                            // nodes' num
int n,p;

int get_min_cut(int root, int n);
int get_son_num(int);
int get_kth_son(int,int);

int main() {
    cin >> n >> p;
    int x,y;
    // we think x < y, then x is father the y is the son
    for (int i = 0; i < n-1; ++i) {
        scanf("%d %d", &x, &y);
        adjm[x][y] = 1;
        adjm[y][x] = 1;
    }
    // init the dp[][]
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = oo;
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k)
            rootdp[i][j][k] = oo;
        }
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][1] = get_son_num(i);
    }

    // test the get_son_num()
    // for (int i = 0; i <= n; ++i) {
    //     printf("%d \n", dp[i][1]);
    // }


    // test the get_min_cut()
    
    // start the search
    for (int num = 0; num <= p; ++num) {
        for (int root = n; root > 0; --root) {
            // get n-1 nodes from root's son
            dp[root][num] = get_min_cut(root, num-1);
            cout << dp[root][n] << endl;
        }
    }  
    cout << dp[1][p] << endl;

    // get the correct ans
    // int minimal = oo;
    // for (int i = 1; i <= n; ++i) {
    //     minimal = min(dp[i][n], minimal);
    // }
    // cout << minimal << endl;
} 

// need to test this function !!!
int get_min_cut(int root, int n) {
    // before we start the n-th search we assume the 
    // n-1 dp has been already finished
    int son_sum = get_son_num(root);
    // beause the before dp has been compute the we just
    // need to compute the (volume == n)'s case
    int temp;
    if (n == 0) {
        for (int i = 1; i <= son_sum; ++i) {
            rootdp[root][i][0] = i;
        }
    }
    for (int i = 1; i <= son_sum; ++i) {
        
        int minimal = oo;
        // v has a max and the max is not n attention
        for (int v = 0; v <= n; ++v) {
            cout << v << endl;
            temp =  rootdp[root][i-1][n-v] + 
                    dp[get_kth_son(root,i)][v];
            if (v == 0)
            temp =  rootdp[root][i-1][n-v] + 1;
            minimal = min(temp, minimal);
        }
    }
    
    return rootdp[root][son_sum][n];
}

int get_son_num(int x) {
    int sum = 0;
    for (int i = x; i <= n; ++i) {
        if (adjm[i][x]) sum++;
    }
    return sum;
}

int get_kth_son(int root, int kth) {
    int k = 0;
    for (int i = root; i <= n; ++i) {
        if (adjm[i][root] == 1) k++;
        if (k == kth) {
            k = i;
            break;
        }
    }
    return k;
}