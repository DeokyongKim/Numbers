// Silver

// Simple DP... but couldn't solve...
// More Practice!!

#include <iostream>

using namespace std;

int n, arr[310] = {0, }, score[310];

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++) cin >> arr[i];
	
	for (int i = 1; i <= n; i++) {
		if (i == 1) score[i] = arr[i];
		if (i == 2) score[i] = arr[1]+arr[2];
		if (i == 3) score[i] = arr[i] + (arr[1]>arr[2]?arr[1]:arr[2]);
		if (i > 3) score[i] = arr[i] + (score[i-2]>score[i-3]+arr[i-1]?score[i-2]:score[i-3]+arr[i-1]);
	}
	
	cout << score[n] << '\n';
	
	// for (int i = 0; i <= n; i++) cout << score[i] << ' ';
	// cout << '\n';
	
	return 0;
}