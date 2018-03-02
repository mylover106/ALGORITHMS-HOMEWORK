#include <stdio.h>
#include <stdlib.h>

# define True  1
# define False 0
# define DIVISION_VALUE 100
# define LN 16
// 100 represent the DIVISION_VALUE is 0.01

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int money_sum;
    int i, j, k;
    int luck_nums[LN] = {   60  , 66    , 600   , 660   ,
                            800 , 880   , 888   , 80    ,
                            360 , 6600  , 1600  , 1800  ,
                            500 , 2000  , 100   , 200
                        };
    int num_redp;
    scanf("%d %d", &money_sum, &num_redp); // money first
    money_sum = money_sum * DIVISION_VALUE;


    // init the search state and allocate the space
    int** dp;
    dp = (int **)malloc(sizeof(int *) * (num_redp + 1));
    for (i = 0; i <= money_sum; ++i) {
        dp[i] = (int *)malloc(sizeof(int) * (money_sum + 1));
    }
    printf("sucess allocate\n");
    // int dp[1000][1000] = {};
    // init
    for (i = 0; i <= num_redp; ++i) {
        for (j = 0; j <= money_sum; ++j) {
            dp[i][j] = False;
        }
    }
    dp[0][0] = True;


    // should keep the s-lucky_num > 0 if < 0 should allocate the False
    // start the search
    for (i = 1; i <= num_redp; ++i) {
        for (j = 1; j <= money_sum; ++j) {
            for (k = 0; k < LN; ++k) {
                // get the True or Fasle;
                if (j - luck_nums[k]>= 0 && dp[i - 1][j - luck_nums[k]]) {
                    dp[i][j] = True;
                    break;
                }
            }
        }
    }


    // collect the red bag
    if(!dp[num_redp][money_sum]){
        printf("failed!");
        return 0;
    }
    int init_sum = money_sum;
    for(i=num_redp;i>0;--i){
        for(k=0;k<LN;++k){
            if(init_sum - luck_nums[k] >= 0 && dp[i-1][init_sum - luck_nums[k]]){
                init_sum = init_sum - luck_nums[k];
                printf("%d:%.2f ",i, luck_nums[k]/100.0);
                break;
            }
        }
    }
    return 0;
}

