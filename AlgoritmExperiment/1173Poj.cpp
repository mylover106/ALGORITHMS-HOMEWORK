#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int Unsure = -1;
const int False  =  0;


int num_search(int len, int num, int width, int bc[34][34]) {
    if (len < num) return False;
    else if (len > num * width) return False;
    else if (len == 0 && num == 0) return 1;
    else if (bc[len][num] == Unsure) {
        bc[len][num] = False;
        for (int i = 1; i <= width; ++i) {
            bc[len][num] += num_search(len - i, num - 1, width, bc);
        }
    }
    return bc[len][num];
}


void normal(string s[], int ns[][34], int test_num, int num) {
    for(int i = 0; i < test_num; ++i) {
        int sum = 0;
        int indix = 0;
        for (int j = 0; j < s[i].size(); ++j) {
            // cout << sum << endl;
            if (j == 0) sum++;
            else if (s[i][j] == s[i][j-1]) sum++;
            else {
                ns[i][indix++] = sum;
                sum = 1;
            }
        }
        ns[i][indix] = sum;
    }
}
// if you want to use dynamic array use just one dimension


int main() {
    int len, num, width, test_num;
    cin >> len >> num >> width; 
    cin >> test_num;
    string s[test_num];
    for (int i = 0; i < test_num; ++i)
        cin >> s[i];
    int ns[test_num][34];
    int order_s[test_num];
    int bc[34][34];
    // init
    for (int i = 0; i < test_num; ++i) 
        for (int j = 0; j < num; ++j) 
            ns[i][j] = 0;
    for (int i = 0; i <= len; ++i) 
        for (int j = 0; j <= len; ++j)
            bc[i][j] = Unsure;
    for (int i = 0; i < test_num; ++i) 
        order_s[i] = 0;

    // start search
    int sum;
    sum = num_search(len, num, width, bc);

    // normal the input string data
    normal(s, ns, test_num, num);
    // for (int i = 0; i < test_num; ++i) {
    //     for (int j = 0; j < num; ++j) 
    //         cout << ns[i][j];
    //     cout << endl;
    // }
    int indix_sum = 0;
    for (int i = 0; i < test_num; ++i) {
        for (int t = 0; t < num; ++t) {
            indix_sum = 0;
            for (int q = 0; q < t; ++q) {
                indix_sum += ns[i][q];
            }
            if(t%2 == 0) {
                for (int k = ns[i][t] - 1; k > 0; --k) {
                    order_s[i] += num_search(len - k - indix_sum, num - t - 1, width, bc); 
                }
            }
            if (t%2 == 1) {
                for (int k = ns[i][t] + 1; k <= width; ++k) {
                    order_s[i] += num_search(len - k - indix_sum, num - t - 1, width, bc);
                }
            }
        }
    }
    // find the order 
    cout << sum << endl;
    for (int i = 0; i < test_num; ++i) 
        cout << order_s[i] << endl;
}