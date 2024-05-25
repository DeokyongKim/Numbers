#include <iostream>

using namespace std;

int n, board[130][130];

int blue = 0, white = 0;

bool isFilled(int lstart, int lend, int cstart, int cend, int color) {
	for (int i = lstart; i < lend; i++)
		for (int j = cstart; j < cend; j++)
			if (board[i][j] != color)
				return false;
	
	// cout << lstart << " / " << lend << " / " << cstart << " / " << cend << " : " << color << '\n';

	if (color) blue++;
	else white++;
	return true;
}

void getDivision(int lstart, int cstart, int length) {
	// cout << lstart << " / " << lend << " / " << cstart << " / " << cend << '\n';
	
	if (isFilled(lstart, lstart+length, cstart, cstart+length, board[lstart][cstart])) return;
	
	getDivision(lstart, cstart, length/2);
	getDivision(lstart, cstart+length/2, length/2);
	getDivision(lstart+length/2, cstart, length/2);
	getDivision(lstart+length/2, cstart+length/2, length/2);

	
	// if (cstart+cend/2 <= n) getDivision(lstart, lend/2, cstart+cend/2, cend);
	// if (lstart+lend/2 <= n)	getDivision(lstart+lend/2, lend, cstart, cend/2);
	// if (lstart+lend/2 <= n && cstart+cend/2 <= n) getDivision(lstart+lend/2, lend, cstart+cend/2, cend);
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> board[i][j];
	
	getDivision(1, 1, n);
	
	cout << white << '\n' << blue << '\n';
	
	return 0;
}