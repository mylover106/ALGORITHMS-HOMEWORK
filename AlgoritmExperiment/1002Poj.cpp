#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>

using namespace std;


#define DONT_HAVE 0

map <string, int> number_count;

char char_lst[34] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'};
int int_lst[34] =  { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',   '2' , '2', '2', '3',  '3', '3',   '4', '4' , '4', '5','5', '5',  '6', '6', '6', '7', '7', '7', '8','8', '8', '9', '9','9' };

map <char, char> c_n;

vector <string> dpl_list;


string s_number(string s) {
    string sum;
    string :: iterator i;
    for (i = s.begin(); i != s.end(); ++i) {
        if (c_n[*i] != DONT_HAVE || *i == '0') {
            sum += c_n[*i];
        }
    }
    sum.insert(3,"-");
    return sum;
}


int main() {
    string number;
    int n;
    scanf("%d", &n);
    string s;

    // init the map
    for (int i = 0; i < 34; ++i) {
        c_n[char_lst[i]] = int_lst[i];
    }


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
    else for (vector <string> :: iterator i = dpl_list.begin(); i != dpl_list.end(); ++i) {
            // cout << *i << " " << number_count[*i] << endl;
            printf("%s %d\n", (*i).c_str(), number_count[*i]);
        }
    return 0;
}