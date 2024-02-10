// Gold

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> dp;

int p[4000010];

void getPrimes(int digit) {
	if (digit <= 1) return;
	
	p[1] = 1;
	for (int i = 2; i <= sqrt(digit); i++) {
		if (p[i]) continue;
		for (int j = i*i; j <= digit; j+=i) p[j] = 1;
	}
	
	dp.push_back(0);
	for (int i = 2; i <= digit; i++)
		if (!p[i]) 
			dp.push_back(i + dp[dp.size()-1]);
}

int solve(int n) {
	int ans = 0, start = 0, end = 1;
	
	while (end < dp.size()) {
		int partial = dp[end] - dp[start];
		if (partial < n) end++;
		else if (partial > n) start++;
		else if (partial == n) {ans++; start++;}
	}
	
	return ans;
}

int run() {
	int n;
	
	cin >> n;
	
	getPrimes(n);
	
	cout << solve(n) << '\n';
	
	return 0;
}