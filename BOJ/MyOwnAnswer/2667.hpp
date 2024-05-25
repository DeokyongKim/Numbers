// Silver

#include <iostream>
#include <algorithm>

using namespace std;

int n, board[30][30];
int total = 1, houses[900];

void getComplex(int a, int b) {
	int x[4] = {1, 0, -1, 0};
	int y[4] = {0, 1, 0, -1};
	
	board[a][b] = -total;
	houses[total-1]++;
	
	int can = 0;
	for (int i = 0; i < 4; i++)
		if (a + x[i] >= 0 && a + x[i] < n && b + y[i] >= 0 && b + y[i] < n)
			if (board[a+x[i]][b+y[i]] > 0) can++;
	if (can == 0) return;
	
	for (int i = 0; i < 4; i++)
		if (a + x[i] >= 0 && a + x[i] < n && b + y[i] >= 0 && b + y[i] < n)
			if (board[a+x[i]][b+y[i]] > 0) getComplex(a+x[i], b+y[i]);
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++){
			char tmp;
			cin >> tmp;
			board[i][j] = tmp-'0';
		}
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 1) {
				getComplex(i, j);
				total++;
			}
		}
	total--;
	
	sort(houses, houses+total);
	
	cout << total << '\n';
	
	for (int i = 0; i < total; i++) cout << houses[i] << '\n';
	
	return 0;
}

