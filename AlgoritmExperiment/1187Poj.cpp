#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int Unknown = -1;
const int False = 0;

int get_num(int depth, int out, int mid, int in, int ms[40][15][15][15]) {

	if (out < 0 || mid < 0 || in < 0 || depth < 0) return 0; 
	if (out + mid + in == 0 && depth >= 0) {
		return 1;
	}
	else if (ms[depth][out][mid][in] == Unknown){
		
		ms[depth][out][mid][in] = 0;
		// divided by the out
		for (int i = 0; i <= in; ++i) {
			if (i != in)
			ms[depth][out][mid][in] += get_num(depth - 1,0,0,i,ms) *
								  get_num(depth,out,mid,in - i - 1,ms);
			ms[depth][out][mid][in] = ms[depth][out][mid][in] % 11380;
			for (int j = 0; j <= mid; ++j) {
				if (j != mid)
				ms[depth][out][mid][in] += get_num(depth - 1,
										0,j,i,ms) *
									  get_num(depth,
									  out,
									  mid - j - 1,
									  in - i,ms);
				ms[depth][out][mid][in] = ms[depth][out][mid][in] % 11380;
				for (int k = 0; k <= out; ++k) {
					if (k != out)
					ms[depth][out][mid][in] += get_num(depth,
												 out - k - 1,
												 mid - j,
												 in - i, ms) *
											   get_num(depth - 1,
											     k,j,i,ms);
					ms[depth][out][mid][in] = ms[depth][out][mid][in] % 11380;
				
				}
			}
			
		}
//		cout << depth << out << mid << in << ms[depth][out][mid][in] << endl;
	}
//	cout << ms[depth][out][mid][in] % 11380 <<endl;
	return ms[depth][out][mid][in] % 11380;
}

int main(int argc, char** argv) {
	int out, mid , in, depth;
	cin >> out >> mid >> in >> depth;
	int ms[40][15][15][15] = {};
	// init the ms
	for (int i = 0; i < 40; ++i) 
	for (int j = 0; j < 15; ++j) 
	for (int k = 0; k < 15; ++k)
	for (int t = 0; t < 15; ++t)
	ms[i][j][k][t] = Unknown;
	cout << (11380*2 + get_num(depth, out, mid, in, ms) - get_num(depth - 1, out, mid, in , ms))%11380 << endl;
	return 0;
}

