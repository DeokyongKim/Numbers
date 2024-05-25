// Silver

#include <iostream>

using namespace std;

long long int a, b, c;

long long int getPower(long long int under, long long int over, long long int modular) {
	if (over == 0) return 1 % modular;
	if (over == 1) return under % modular;
	
	long long int tmp = getPower(under, over/2, modular);
	
	if (over % 2 == 0) return (tmp*tmp)%modular;
	if (over % 2 == 1) return (tmp*tmp)%modular*under%modular;
}

int run() {
	cin >> a >> b >> c;
	
	cout << getPower(a, b, c) << '\n';
	
	return 0;
}