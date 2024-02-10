#include <iostream>
#include <queue>
#include <algorithm>

#define pii pair<int, int>

using namespace std;

int n, m, board[10][10], copyBoard[10][10], virusNum, wallNum, safeNum;
int walln, safen, maxSafe;
pii virus[10];

void bfs(pii coor) {
	queue<pii > q;
	q.push(coor);
	
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x+dx[i], ny = y+dy[i];
			if (nx>=0 && nx<n && ny>=0 && ny<m) {
				if (copyBoard[nx][ny] == 0) {
					copyBoard[nx][ny] = 2;
					q.push({nx, ny});
					safen--;
				}
			}
		}
	}
}

int run() {
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) virus[virusNum++] = {i, j};
			if (board[i][j] == 1) wallNum++;
			if (board[i][j] == 0) safeNum++;
		}
	
	for (int fi = 0; fi < n; fi++)
		for (int fj = 0; fj < m; fj++)
			for (int si = 0; si < n; si++)
				for (int sj = 0; sj < m; sj++)
					for (int ti = 0; ti < n; ti++)
						for (int tj = 0; tj < m; tj++) {
							if (board[fi][fj] + board[si][sj] + board[ti][tj] > 0) continue;
							// copy board
							for (int i = 0; i < n; i++)
								for (int j = 0; j < m; j++)
									copyBoard[i][j] = board[i][j];
							walln = wallNum;
							safen = safeNum;
							
							// wall
							copyBoard[fi][fj] = 1;
							copyBoard[si][sj] = 1;
							copyBoard[ti][tj] = 1;
							walln+=3;
							safen-=3;
							
							// bfs
							for (int i = 0; i < virusNum; i++)
								bfs(virus[i]);
							
							if (maxSafe < safen)
								maxSafe = safen;
						}
	
	cout << maxSafe << '\n';
	return 0;
}