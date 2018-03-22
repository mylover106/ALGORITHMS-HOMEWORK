#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int get_inversion(const string &s) {
	int sum = 0;
	for (int i = 0; i < s.size(); ++i)
	for (int j = i + 1; j < s.size(); ++j)
	if (s[i] > s[j]) sum++; 
	return sum;
}

bool sort_way(const string &s1, const string &s2) {
	if (get_inversion(s1) < get_inversion(s2)) return true;
	else return false;
} 

int main(int argc, char** argv) {
	int length, line_num;
	cin >> length >> line_num;
	string line[line_num];
	
	// init 
	for (int i = 0; i < line_num; ++i) {
		cin >> line[i];
	}
	
	sort(line,line + line_num,sort_way);

//	cout << get_inversion(line[1]) << endl;
//	cout << "this is the answer" << endl;
	for (int i = 0; i < line_num; ++i) {
		cout << line[i] << endl;
	} 
	return 0;
}
