#include <iostream>
#include <stdio.h>

using namespace std;

char map[5000][5000];

int pow(int m, int n) {
    int sum = 1;
    while(n) {
        sum = sum*m;
        n--;
    }
    return sum;
}

void B(int m, int x, int y) {
    if (map[x][y] == 'X') return;
    else if (m == 1) map[x][y] = 'X';
    else {
        B(m - 1, x, y);
        B(m - 1, x - pow(3, m - 2), y - pow(3, m - 2));
        B(m - 1, x + pow(3, m - 2), y + pow(3, m - 2));
        B(m - 1, x + pow(3, m - 2), y - pow(3, m - 2));
        B(m - 1, x - pow(3, m - 2), y + pow(3, m - 2));
    }
}

void output(int m) {
    for (int i = 1; i <= pow(3, m - 1); ++i) {
        for (int j = 1; j <= pow(3, m - 1); ++j) {
            // cout << map[i][j] ? map[i][j] == 'X' : ' ';
            if (map[i][j] == 'X') putchar('X');
            else putchar(' ');
        }
        cout << endl;
    }
    cout << '-' << endl;
}

int main() {
    int m;
    cin >> m;
    while (m != -1) {
        B(m, (pow(3, m-1) + 1) / 2, (pow(3, m-1) + 1) / 2);
        output(m);
        cin >> m;
    };
    return 0;
}