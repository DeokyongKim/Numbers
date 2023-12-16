// Silver

#include <iostream>

using namespace std;

int n, arr[1010], memo[1010];

int getLength(int now) {
	if (memo[now]) return memo[now];
	
	if (now == 0) {
		memo[now] = 1;
		return memo[now];
	}
	
	memo[now] = 1;
	for (int i = 0; i < now; i++)
		if (arr[i] < arr[now] && memo[i] + 1 > memo[now]) {
			memo[now] = memo[i] + 1;
		}
	return memo[now];
}

int run() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	
	// for (int i = 0; i < n; i++) memo[i] = 1;
	
	for (int i = 0; i < n; i++) getLength(i);
	
	// for (int i = 0; i < n; i++) {
	// 	cout << memo[i] << '\t';
	// } cout << '\n';
	// for (int i = 0; i < n; i++) {
	// 	cout << memo[i] << '\t';
	// } cout << '\n';
	
	int ans = 0;
	for (int i = 0; i < n; i++)
		if (memo[i] > ans) ans = memo[i];
	cout << ans << '\n';
	
	return 0;
}