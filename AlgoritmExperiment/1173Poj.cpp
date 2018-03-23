#include <iostream>
#include <string>

using namespace std;

int length, bar_num, max_width, num_test, sum = 0;
// string zero("00000000000000000000000000000000000000000000000000000000000000");
// string one("1111111111111111111111111111111111111111111111111111111111111111");

void recursive_find_k(bool color, int indix, int order[], string & now_s, int left, const string test[]) {
    cout << now_s << endl;
    if (left == 0) {
        if (indix == length) {
            sum++;
            for (int i = 0; i < num_test; ++i) {
                if (test[i] == now_s) {
                    order[i] = sum;
                }
            }
            return ;
        } else {
            return ;
        }
    }
    if (color == true)
        for (int i = 0; i < max_width; ++i) {
            // update the now_s
            // now_s.replace(indix + now_s.begin(), i + 1, '1');
            for (int j = 0; j < i + 1; ++j) {
                now_s[j + indix] = '0';
            }
            now_s[i + indix] = true;
            recursive_find_k(false, i + indix + 1, order, now_s, left - 1, test);
        }
    if (color == false)
        for (int i = 0; i < max_width; ++i) {
            // update the now_s
            // now_s.replace(indix + now_s.begin(), max_width - i - 1, '0');
            for (int j = 0; j < max_width - i - 1; ++j) {
                now_s[j + indix] = '1';
            }
            // now_s[max_width - i - 1 + indix] = false;
            recursive_find_k(true, max_width - i -1 + indix, order, now_s, left - 1, test);
            // now_s[max_width]
        }
}


int main() {
    cin >> length >> bar_num >> max_width ;
    cin >> num_test ;
    string test_s[num_test] ;
    int order[num_test];
    for (int i = 0; i < num_test; ++i) {
        cin >> test_s[i];
    }
    // for (int i = 0; i < num_test; ++i) {
    //     cout << test_s[i] << endl;
    // }
    string now_s(test_s[0]);
    cout << "now_s" << endl;
    recursive_find_k(true, 0, order, now_s, bar_num, test_s);
    cout << sum << endl;
    for (int i = 0; i < num_test; ++i) {
        cout << order[i] << endl;
    }
    return 0;
}