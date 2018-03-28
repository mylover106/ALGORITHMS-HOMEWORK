#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


#define DONT_HAVE 0

map <int, int> number_count;
map <char, int> c_n = {
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'0', 0},
    {'A', 2},
    {'B', 2},
    {'C', 2},
    {'D', 3},
    {'E', 3},
    {'F', 3},
    {'G', 4},
    {'H', 4},
    {'I', 4},
    {'J', 5},
    {'K', 5},
    {'L', 5},
    {'M', 6},
    {'N', 6},
    {'O', 6},
    {'P', 7},
    {'R', 7},
    {'S', 7},
    {'T', 8},
    {'U', 8},
    {'V', 8},
    {'W', 9},
    {'X', 9},
    {'Y', 9}
};

vector <int> dpl_list;


int s_number(string s) {
    int sum = 0;
    string :: iterator i;
    for (i = s.begin(); i != s.end(); ++i) {
        if (c_n[*i] != DONT_HAVE || *i == '0') {
            sum = sum * 10 + c_n[*i];
        }
    }
    return sum;
}


string number_s(int number) {
    // cout << number << endl;
    string ans = to_string(number);
    ans.insert(3,"-");
    // cout << ans;
    return ans;
}


int main() {
    int number, n;
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        number = s_number(s);
        // cout << number << endl;
        if (number_count[number] == DONT_HAVE) {
            number_count[number]++;
        } else if (number_count[number] == 1) {
            dpl_list.push_back(number);
            number_count[number]++;
        } else number_count[number]++;
    }

    sort(dpl_list.begin(), dpl_list.end());

    if (dpl_list.size() == 0) cout << "No duplicates." << endl;
    else for (vector <int> :: iterator i = dpl_list.begin(); i != dpl_list.end(); ++i) {
            cout << number_s(*i) << " " << number_count[*i] << endl;
        }
    return 0;
}