// Silver

#include <iostream>

using namespace std;

int test;

void maximizeScore() {
	int n, score[2][100010], dp[2][100010];
	
	cin >> n;
	
	for (int i = 0; i < 2; i++)
		for (int j = 0; j <= n; j++) 
			dp[i][j] = 0;
	
	for (int i = 0 ; i < 2; i++)
		for (int j = 0; j < n; j++)
			cin >> score[i][j];
	
	for (int j = 0; j < n; j++)
		for (int i = 0; i < 2; i++) {
			int up = i, down = i==1?0:1;
			
			if (j==0) dp[up][j+1] = score[up][j];
			else if (j==1) dp[up][j+1] = dp[down][j]+score[up][j];
			else {
				int a = dp[up][j];
				int b = dp[down][j]+score[up][j];
				int c_a = dp[up][j-1], c_b = dp[down][j-1];
				int c = c_a>c_b?c_a:c_b + score[up][j];
				
				dp[i][j+1] = (a>b?a:b)>c?(a>b?a:b):c;
			}
		}
	
	cout << (dp[0][n]>dp[1][n]?dp[0][n]:dp[1][n]) << '\n';
}

int run() {
	cin >> test;
	
	for (int i = 0; i < test; i++) maximizeScore();
	
	return 0;
}