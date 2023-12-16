// Bronze

#include <iostream>

using namespace std;

bool isPrime(int a) {
	if (a == 1) return false;
	for (int i = 2; i*i <= a; i++)
		if (a % i == 0) return false;
	return true;
}

void run() {
	int n, arr[110];
	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	int ans = 0;
	for (int i = 0; i < n; i++)
		if (isPrime(arr[i])) ans++;
	cout << ans;
}