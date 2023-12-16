// Silver

#include <iostream>
#include <cmath>

using namespace std;

int order(int n, int r, int c) {
	int len = pow(2, n), divide = len / 2;
	
	if (divide == 1) return 2*r + c;
	
	//1
	if (r < divide && c < divide) 
		return order(n-1, r, c);
	//2
	if (r < divide && c >= divide) 
		return pow(divide, 2) + order(n-1, r, c - divide);
	//3
	if (r >= divide && c < divide) 
		return pow(divide, 2)*2 + order(n-1, r - divide, c);
	//4
	if (r >= divide && c >= divide) 
		return pow(divide, 2)*3 + order(n-1, r - divide, c - divide);
}

void run() {
	int n, r, c;
	
	cin >> n >> r >> c;
	
	cout << order(n, r, c) << '\n';
}