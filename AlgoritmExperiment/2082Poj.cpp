#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef struct Loc{
    long long high;
    long long loc;
}Loc;

long long now_len;
vector <Loc> high_loc;


long long get_max_merge(long long w, long long h);
void update_high_loc(long long w, long long h);


int main() {
    int n;
    long long w, h;
    long long maximal = 0;
    scanf("%d", &n);
    Loc temp_loc;
    long long temp;
    while(n != -1) {
        for (int i = 0; i < n; ++i) {
            // cin >> w >> h;
            scanf("%lld %lld", &w, &h);
            if (i == 0) {
                maximal = w*h;
                temp_loc.high = h;
                temp_loc.loc = 1;
                high_loc.push_back(temp_loc);
                now_len = w;
            } else {
                now_len += w;
                temp = get_max_merge(w, h);
                maximal = max(maximal, temp);
                update_high_loc(w,h);  
                // for (int k = 0; k < high_loc.size(); ++k){
                //     cout << "step" << endl;
                //     cout << "high" << high_loc[k].high << endl;
                //     cout << "loc " << high_loc[k].loc << endl;
                // } 
            }
        }
        printf("%lld\n",maximal);
        scanf("%d", &n);
        high_loc.clear();
        now_len = 0;
    }
    
}


long long get_max_merge(long long w, long long h) {
    long long maximal = 0;
    vector <Loc> :: iterator i;
    for (i = high_loc.begin(); i != high_loc.end(); ++i) {
         if ((*i).high <= h) {
             maximal = max(maximal, (*i).high * (now_len - (*i).loc + 1));
         } 
    }
    maximal = max(maximal, w*h);
    return maximal;
}

void update_high_loc(long long w, long long h) {
    vector <Loc> :: iterator i;
    for (i = high_loc.begin(); i != high_loc.end(); ++i) {
        if ((*i).high >= h) break;
    }
    Loc temp;
    temp.high = h;
    temp.loc = now_len - w + 1;
    if (i == high_loc.end()) {
        high_loc.push_back(temp);
    } else {
        if ((*i).high == h) high_loc.erase(i+1, high_loc.end());
        else {
            temp.loc = (*i).loc;
            high_loc.erase(i, high_loc.end());
            high_loc.push_back(temp);
        }
    }
    return ;
}