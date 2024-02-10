// READ PROBLEM CAREFULLY
// YOU NEED TO PLACE ONE CHEIF VIEWER

#include <iostream>

using namespace std;

long long int n, a[1000010], b, c;

long long sumA, sumB;

int run() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> b >> c;
	
	for (int i = 0; i < n; i++) {
		int numA = a[i], numB = a[i];
		
		// Cheif viewer
		sumA++;
		numA = (numA-b>=0?numA-b:0);
				
		// Vice viewer
		sumA += (numA/c);
		sumA += (numA%c>0?1:0);
				
		sumB += (numB/c);
		sumB += (numB%c>0?1:0);
	}
	cout << sumA << '\n';
	
	return 0;
}