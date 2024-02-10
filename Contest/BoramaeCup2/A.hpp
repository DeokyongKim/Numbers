#include <iostream>

using namespace std;

int n, x, sum;

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> x;
	
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		
		sum += tmp;
	}
	
	cout << (sum%x==0?1:0);
	
	return 0;
}