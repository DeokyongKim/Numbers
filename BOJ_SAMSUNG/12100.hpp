// Gold 2
// 1시간 좀 넘게 걸림
// 할만할듯

#include <iostream>

#define MAX_MOVE 5

using namespace std;

int n, board[22][22];

int maxNumber = 0;

void duplicate(int from[22][22], int to[22][22]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			to[i][j] = from[i][j];
}

void showMap(int arr[22][22], int move) {
	cout << move << "==============\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0 ; j < n; j++)
			cout << arr[i][j] << '\t';
		cout <<'\n';
	}
	cout << "==============\n";
	
}

void solve(int arr[22][22], int move) {
	// end case
	if (move == MAX_MOVE) return;
	
	// cout << move << '\n';
	// showMap(arr, move);
	
	int dx, dy;
	
	// move left
	int left[22][22];
	duplicate(arr, left);
	dx = 0;
	dy = -1; 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (left[i][j] <= 0) continue;
			int x = i, y = j;
			while(true) {
				bool steady = true;
				if (x+dx>=0 && x+dx<n && y+dy>=0 && y+dy<n) {
					if (left[x+dx][y+dy] == 0) {
						left[x+dx][y+dy] = left[x][y];
						left[x][y] = 0;
						x += dx;
						y += dy;
						steady = false;
					} else if (left[x+dx][y+dy] == left[x][y]) {
						left[x+dx][y+dy] *= -2;
						left[x][y] = 0;
						break;
					}
				}
				
				if (steady) break;
			}
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (left[i][j] < 0) left[i][j] *= -1;
			if (maxNumber < left[i][j]) {
				maxNumber = left[i][j];
				// showMap(left, move);
			}
		}
	solve(left, move+1);
	
	// move right
	int right[22][22];
	duplicate(arr, right);
	dx = 0;
	dy = 1; 
	for (int i = 0; i < n; i++)
		for (int j = n-1; j >= 0; j--) {
			if (right[i][j] <= 0) continue;
			int x = i, y = j;
			while(true) {
				bool steady = true;
				if (x+dx>=0 && x+dx<n && y+dy>=0 && y+dy<n) {
					if (right[x+dx][y+dy] == 0) {
						right[x+dx][y+dy] = right[x][y];
						right[x][y] = 0;
						x = x+dx;
						y = y+dy;
						steady = false;
					} else if (right[x+dx][y+dy] == right[x][y]) {
						right[x+dx][y+dy] *= -2;
						right[x][y] = 0;
						break;
					}
				}
				
				if (steady) break;
			}
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (right[i][j] < 0) right[i][j] *= -1;
			if (maxNumber < right[i][j]) {
				maxNumber = right[i][j];
				// showMap(right, move);
			}
		}
	solve(right, move+1);
	
	// move up
	int up[22][22];
	duplicate(arr, up);
	dx = -1;
	dy = 0; 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (up[i][j] <= 0) continue;
			int x = i, y = j;
			while(true) {
				bool steady = true;
				if (x+dx>=0 && x+dx<n && y+dy>=0 && y+dy<n) {
					if (up[x+dx][y+dy] == 0) {
						up[x+dx][y+dy] = up[x][y];
						up[x][y] = 0;
						x+=dx;
						y+=dy;
						steady = false;
					} else if (up[x+dx][y+dy] == up[x][y]) {
						up[x+dx][y+dy] *= -2;
						up[x][y] = 0;
						break;
					}
				}
				
				if (steady) break;
			}
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (up[i][j] < 0) up[i][j] *= -1;
			if (maxNumber < up[i][j]) {
				maxNumber = up[i][j];
				// showMap(up, move);
			}
		}
	solve(up, move+1);
	
	// move down
	int down[22][22];
	duplicate(arr, down);
	dx = 1;
	dy = 0; 
	for (int i = n-1; i >= 0; i--)
		for (int j = 0; j < n; j++) {
			if (down[i][j] <= 0) continue;
			int x = i, y = j;
			while(true) {
				bool steady = true;
				if (x+dx>=0 && x+dx<n && y+dy>=0 && y+dy<n) {
					if (down[x+dx][y+dy] == 0) {
						down[x+dx][y+dy] = down[x][y];
						down[x][y] = 0;
						x+=dx;
						y+=dy;
						steady = false;
					} else if (down[x+dx][y+dy] == down[x][y]) {
						down[x+dx][y+dy] *= -2;
						down[x][y] = 0;
						break;
					}
				}
				
				if (steady) break;
			}
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (down[i][j] < 0) down[i][j] *= -1;
			if (maxNumber < down[i][j]) {
				maxNumber = down[i][j];
				// showMap(down, move);
			}
		}
	solve(down, move+1);
}

int run() {
	cin >> n;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> board[i][j];
	
	solve(board, 0);
	
	cout << maxNumber << '\n';
	
	return 0;
}