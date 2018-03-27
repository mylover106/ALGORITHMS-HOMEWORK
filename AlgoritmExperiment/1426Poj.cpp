#include <iostream>

using namespace std;

#define True   0
#define False -1

int max_step;
int FindM = False;

void search(int number, long long multiple, int step) {
    if (FindM == True) return;
    if (step == max_step) return;
    else if (multiple % number == 0 && multiple != 0) {
        cout << multiple << endl;
        FindM = True;
        return;
    } else {
        search(number, multiple*10, step + 1);
        search(number, multiple*10 + 1, step + 1);
    }
    return;
}

int main() {
    int m;
    cin >> m;

    while(m) {
        max_step = 1;
        while(FindM == False) {
            search(m,1,0);
            max_step++;
        }
        FindM = False;
        cin >> m;
    }
    return 0;
}