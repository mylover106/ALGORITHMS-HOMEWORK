#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define oo (1 << 4*sizeof(int))
#define NOT_COUNT -1

int adjm[250][250];
int dp[250][250]; // dp[root][num]
int rootdp[250][250][250];  // rootdp[root][step][volume]
                            // volume also represent the 
                            // nodes' num
int n,p;


int get_son_num(int);
int get_kth_son(int,int);
int DP(int root, int p);
int rootDP(int root, int ith, int p);

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
            dp[i][j] = NOT_COUNT;
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k)
            rootdp[i][j][k] = NOT_COUNT;
        }
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][1] = get_son_num(i);
    }
    
    int minimal = DP(1, p);
    for (int i = 2; i <= n; ++i) {
        minimal = min(minimal, DP(i, p)+1);
    }
    cout << minimal << endl;
} 

int DP(int root, int p) {
    if (p == 1) return get_son_num(root);
    if (get_son_num(root) == 0 && p > 1){ 
        return oo;
        }
    if (dp[root][p]!=NOT_COUNT) return dp[root][p];
    else {
        dp[root][p] = rootDP(root, get_son_num(root), p-1);
    }
    return dp[root][p];
}


int rootDP(int root, int ith, int p) {
    if (p == 0) return ith;
    if (ith == 1 ) {
        return DP(get_kth_son(root, 1), p);
    } 
    else if (rootdp[root][ith][p]!=NOT_COUNT) return rootdp[root][ith][p];
    else {
        for (int v = 0; v <= p; ++v) {
            if (v == 0) {
                rootdp[root][ith][p] =  rootDP(root,ith-1,p-v) + 1;
            } else {
                rootdp[root][ith][p] =  min(rootdp[root][ith][p], 
                                        rootDP(root,ith-1,p-v) + DP(get_kth_son(root, ith),v));
            }
        }
    }
    return rootdp[root][ith][p];
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