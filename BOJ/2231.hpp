// Bronze

#include <iostream>

using namespace std;

int summer(int a) {
	int sum = a;
	while(a) {
		sum += a%10;
		a /= 10;
	}
	return sum;
}

void run() {
	int n;
	cin >> n;
	
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (summer(i) == n) {
			ans = i;
			break;
		}
	
	cout << ans << '\n';
}