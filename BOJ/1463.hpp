// Silver

#include <iostream>

using namespace std;

void run() {
	int n, arr[1000010] = {0, };
	cin >> n;
	
	for (int i = 2; i <= n; i++) {
		int min = 1987654321;
		if (i%3 == 0) min = min > (arr[i/3] + 1)? (arr[i/3]+1) : min;
		if (i%2 == 0) min = min > (arr[i/2] + 1)? (arr[i/2]+1) : min;
		min = min > (arr[i-1] + 1)? (arr[i-1]+1) : min;
		arr[i] = min;
	}
	
	cout << arr[n] << '\n';
}