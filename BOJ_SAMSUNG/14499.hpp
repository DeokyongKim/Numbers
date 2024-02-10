// Maintain form of dise
/*
  2
4 1 3
  5
  6

This means 1 is always upside, 6 is always downside, 
2, 4, 3, 5 is always beside. (2, 4, 3, 5 maintain it's position either)
*/

#include <iostream>

using namespace std;

int n, m, board[22][22], x, y, k;

int dise[7] = {0, };

void rollDise(int dir) {
	int tmpDise[7];
	for (int i = 0; i < 7; i++) tmpDise[i] = dise[i];
	if (dir == 1) {
		/*
		  2
		4 1 3
		  5
		  6
		  
		  goes to
		  
		  2
		6 4 1
		  5
		  3
		*/
		dise[1] = tmpDise[4];
		dise[4] = tmpDise[6];
		dise[3] = tmpDise[1];
		dise[6] = tmpDise[3];
	} else if (dir == 2) {
		dise[1] = tmpDise[3];
		dise[3] = tmpDise[6];
		dise[4] = tmpDise[1];
		dise[6] = tmpDise[4];
	} else if (dir == 3) {
		dise[2] = tmpDise[1];
		dise[1] = tmpDise[5];
		dise[5] = tmpDise[6];
		dise[6] = tmpDise[2];
	} else if (dir == 4) {
		dise[2] = tmpDise[6];
		dise[1] = tmpDise[2];
		dise[5] = tmpDise[1];
		dise[6] = tmpDise[5];
	}
}

int run() {
	cin >> n >> m;
	cin >> x >> y;
	cin >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	
	for (int i = 0; i < k; i++) {
		int dir;
		int dx[4] = {0, 0, -1, 1};
		int dy[4] = {1, -1, 0, 0};
		cin >> dir;
		
		if (x+dx[dir-1] < 0 || 
		    x+dx[dir-1] >= n ||
			y+dy[dir-1] < 0 ||
			y+dy[dir-1] >= m
		   )
			continue;
		
		rollDise(dir);
		
		x+=dx[dir-1];
		y+=dy[dir-1];
		if (board[x][y] == 0) board[x][y] = dise[6];
		else if (board[x][y] != 0) {
			dise[6] = board[x][y];
			board[x][y] = 0;
		}
		cout << dise[1] << '\n';
	}
	return 0;
}