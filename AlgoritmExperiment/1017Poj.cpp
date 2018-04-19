#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <map>

using namespace std;
const int False = -1;

class Range {
    public:
    int start, end;
    int fill_element[2];
    int left_element;
    void init_Range(int x, int y) {
        this->start = x;
        this->end = y;
        this->fill_element[0] = -1;
        this->fill_element[1] = -1;
        this->left_element = 2;
    }
    int add_element(int num) {
        if (num < start || num > end) return False;

        if (left_element == 0) return 0;
        
        if (fill_element[0] == -1) {
            fill_element[0] = num;
        } else {
            fill_element[1] = num;
        }

        // update the element we need
        left_element--;
        return 0;
    }
    int num_can_add() {
        int ans;
        // judge ans can be add?
        if (fill_element[0]!= end && fill_element[1]!=end) {
            ans = end;
        } else {
            ans = end - 1;
        }
        return ans;
    }
};

bool compare(const Range &x, const Range &y) {
    if (x.end > y.end) return false;
    else return true;
}

void update_r(int num, int index, Range r[], int n) {
    for (int i = index+1;i < n; ++i) {
        int states = r[i].add_element(num);
        if (states == False) return; 
    }
    return;
}


int  main() {
    int n;
    cin >> n;
    Range r[n];
    int x, y;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        r[i].init_Range(x,y);
    }
    // for (int i = 0; i < n; ++i) {
    //     cout << r[i].start << endl;
    // }
    sort(r,r+n,compare);
    // for (int i = 0; i < n; ++i) {
    //     cout << r[i].start << " " << r[i].end << endl;
    // }

    // start add elements
    int count = 0;
    for (int i = 0; i < n; ++i) {
        while(r[i].left_element) {
            int num = r[i].num_can_add();
            r[i].add_element(num);
            update_r(num, i, r, n);
            count++;
        }
    }
    cout << count << endl;
    return 0;
}
