#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


using namespace std;

#define INF (1<<6*sizeof(int))
#define MAX 10000


int dp[MAX][MAX];
int B[MAX][MAX];
int BV[MAX][MAX];
int b_n[MAX];


void get_ans();

int main() {
	int test;
	scanf("%d",&test);
	for (int i = 0; i < test; ++i) {
		get_ans();
	}	
	return 0;
} 

float max(float x1, float x2) {
	if (x1 > x2) return x1;
	else return x2;
}


void get_ans() {
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i) {
		scanf("%d",&b_n[i]);
		for (int j = 0; j < b_n[i]; ++j) {
			scanf("%d %d",&B[i][j], &BV[i][j]);
		}
	} 
	
	// init the dp
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < MAX; ++j) {
			dp[i][j] = INF;
		}
	}
	
	
	for (int b = 0; b < MAX; ++b) {
		for (int dev = 0; dev < b_n[0]; ++dev) {
			if (b == B[0][dev]) dp[0][b] = min(BV[0][dev],dp[0][b]);
		} 
	}
	
	for (int it = 1; it < n; ++it) {
		for (int b = 0; b < MAX; ++b) {
			for (int dev = 0; dev < b_n[it]; ++dev) {
				if (b <= B[it][dev]) dp[it][b] = min(dp[it][b],dp[it-1][b] + BV[it][dev]);
				else dp[it][B[it][dev]] = min(dp[it][B[it][dev]], dp[it-1][b] + BV[it][dev]);
			}
		}
	}
	
	// find the maximal
	float maximal = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < MAX; ++j) {
			maximal = max(maximal, j*1.0/dp[n-1][j]);
		}
	}
	printf("%.3f\n",maximal);
} 


