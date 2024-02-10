// Gold

#include <iostream>
#include <math.h>

using namespace std;

int n, queens[20], ans;

bool check(int a, int aVal) {
	for (int i = 0 ; i < n; i++) {
		if (queens[i]!=-1 && queens[i] == aVal) return false;
		if (queens[i]!=-1 && abs(a-i) == abs(aVal-queens[i])) return false;
	}
	return true;
}

void nQueen(int currentQueens) {
	if (currentQueens == n) {
		ans++;
		return;
	}
	
	for (int i = 0; i < n; i++)
		if (queens[i]==-1 && check(i, currentQueens)) {
			queens[i] = currentQueens;
			nQueen(currentQueens+1);
			queens[i] = -1;
		}
}

int run() {
	cin >> n;
	
	for (int i = 0; i < n; i++) queens[i] = -1;
	
	nQueen(0);
	
	cout << ans << '\n';
	
	return 0;
}