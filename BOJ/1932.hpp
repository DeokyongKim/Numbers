// silver

#include <iostream>

#define MIN -1987654321

using namespace std;

int n;
int triangle[510][510];
int dp[510][510];

int run() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++)
			cin >> triangle[i][j];
	}
	
	for (int i = 1; i <= n; i++) {
		if (i == 1) {
			dp[1][1] = triangle[1][1];
			continue;
		}
		
		if (i == 2) {
			for (int j = 1; j <= i; j++)
				dp[i][j] = triangle[i][j] + dp[1][1];
			continue;
		}
		
		for (int j = 1; j <= i; j++) {
			int left = MIN, right = MIN;
			if (j-1>=1) left = dp[i-1][j-1];
			if (j < i) right = dp[i-1][j];
			int max = left>right?left:right;
			dp[i][j] = triangle[i][j] + max;
		}
	}
		
	int ans = MIN;

	for (int i = 1; i <= n; i++)
		if (dp[n][i] > ans)
			ans = dp[n][i];

	cout << ans << '\n';
	
	return 0;
}