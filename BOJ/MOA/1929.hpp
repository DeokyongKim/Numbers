// Silver

#include <iostream>

bool isPrime(int a) {
	if (a == 1) return false;
	for (int i = 2; i*i <= a; i++) {
		if (a%i == 0) return false;
	}
	return true;
}

void run() {
	int n, m;
	std::cin >> m >> n;
	for (int i = m; i <= n; i++) {
		if (isPrime(i)) std::cout << i << '\n';
	}
}