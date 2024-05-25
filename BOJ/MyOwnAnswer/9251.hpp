// Gold

#include <iostream>

using namespace std;

char one[1010], two[1010];
int oneLen, twoLen;

int dp[1010][1010];

int run() {
	cin >> one >> two;
	
	for (; one[oneLen]; oneLen++);
	for (; two[twoLen]; twoLen++);
	
	for (int i = 0; i < oneLen; i++)
		for (int j = 0; j < twoLen; j++) {
			if(one[i] == two[j]) dp[i+1][j+1] = dp[i][j] + 1;
			else dp[i+1][j+1] = dp[i+1][j]>dp[i][j+1]?dp[i+1][j]:dp[i][j+1];
		}
	
	cout << dp[oneLen][twoLen] << '\n';
	
	return 0;
}