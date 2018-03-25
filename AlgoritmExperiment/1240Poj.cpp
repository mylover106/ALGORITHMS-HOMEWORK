#include <iostream>
#include <string>
#include <map>

#define NotFind -1

using namespace std;


map <string, int> dic;

int C(int m, int k) {
    int sum = 1, ik = k;

    while(k) {
        sum *= (m - k + 1);
        k--;
    }
    while(ik) {
        sum /= ik;
        ik--;
    }

    return sum;
}

int get_num(const string & pre, const string & post, const int m) {
    int k;
    if (pre.size() == 0 || pre.size() == 1) return 1;
    else if (dic[pre]) return dic[pre];
    else {
        // there is another way need to be consider that is if the whole don't meet the two ary 
        // the left tree can also be the right tree 
        // so if there are only k sub tree respect to the m 
        // we need to multiple it with the C_m^k
        int k = 0, sum = 1;
        string sub_pre, sub_post;
        sub_pre = pre.substr(1);
        sub_post = post.substr(0, post.size() - 1);
        

        // if find the character it will return the index else it will return -1
        int index = sub_post.find(sub_pre[0]);
        while(index != NotFind) {
            k++;
            sum *= get_num(sub_pre.substr(0, index + 1), sub_post.substr(0, index + 1), m);
            sub_pre = sub_pre.substr(index + 1);
            sub_post = sub_post.substr(index + 1);
            index = sub_post.find(sub_pre[0]);
        }


        sum *= C(m, k);
        dic[pre] = sum;
    }

    return dic[pre];
}

int main() {
    string pre;
    string post;
    int m;
    cin >> m;
    while(m) {
        cin >> pre >> post;
        cout << get_num(pre, post, m) << endl;

        dic.clear();
        cin >> m;
    }
    return 0;
}