#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

#define UN_KNOWN 0

int m;
int number[200];
long order[200];
long no_order[200];


long get_num__order(int n);
long get_num_no_order(int n);


long get_num_order(int n) {
    if (order[n] != UN_KNOWN) return order[n] % m;
    else if (n == 1) return (2 * number[n] - 1) % m;
    else if (number[n] == 1) return get_num_no_order(n) % m;
    else {
        order[n] = (get_num_order(n - 1) + get_num_no_order(n - 1) * 2 + number[n] * 2) % m;
        return order[n];
    }
}

long get_num_no_order(int n) {
    if (no_order[n] != UN_KNOWN) return no_order[n] % m;
    else if (n == 1) return number[n] % m;
    else {
        no_order[n] = (get_num_no_order(n - 1) * 2 + number[n]) % m;
        return no_order[n];
    }
}

void num_output() {
    // init
    int n;
    while (scanf("%d%d",&n,&m)!=EOF) {
        for (int i = 1; i <= n; ++i) {
            // cin >> number[i];
            scanf("%d",&number[i]);
        }
        // for (int i = 1; i <= n; ++i) {
        //     if (i == 1) no_order[i] = number[i] % m;
        //     else no_order[i] =  (no_order[i - 1] * 2 + number[i]) % m;
        // }
        // for (int i = 1; i <= n; ++i) {
        //     if (i == 1) order[i] = (2 * number[i] - 1) % m;
        //     else if (number[i] == 1) order[i] = no_order[i];
        //     else order[i] = (order[i - 1] + no_order[i - 1] * 2 + number[i] * 2) % m;
        // }
        cout << (get_num_order(n) + m) % m << endl;
        // printf("%d\n",order[n]);
        
        for (int i = 1; i <= n; ++i) {
            order[i] = UN_KNOWN;
            no_order[i] = UN_KNOWN;
        }
    }
}

int main() {
    num_output();
    return 0;
}
