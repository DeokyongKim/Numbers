// Gold

#include <iostream>
#include <queue>
#include <cstring>

#define pii pair<int, int>

using namespace std;

int n, m, board[110][110], ch, t;

int visited[110][110];

queue<pii > toMelt;

void refreshing(int a, int b) {
	queue<pii > q;
	q.push({a, b});
	visited[a][b] = 1;
	
	while(!q.empty()) {
		int ca = q.front().first, cb = q.front().second;
		q.pop();
		
		board[ca][cb] = 2;
		
		int da[4] = {0, 1, 0, -1};
		int db[4] = {1, 0, -1, 0};

		for (int i = 0; i < 4; i++) {
			int na = ca+da[i], nb = cb+db[i];
			if (na >= 0 && na < n && nb >= 0 && nb < m)
				if (board[na][nb] == 0 || board[na][nb] == 2)
					if (visited[na][nb] != 1) {
						q.push({na, nb});
						visited[na][nb] = 1;
					}
		}
	}
}

int run() {
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j]==1) {
				ch++;
			}
			if (i == 0 || i == n-1 || j == 0 || j == m-1) board[i][j] = 2;
		}

	for (int i = 0; i < n; i++) {
		refreshing(i, 0);
		refreshing(i, m-1);
	}
	for (int j = 0; j < m; j++) {
		refreshing(0, j);
		refreshing(n-1, j);
	}
	
	while (ch > 0) {
		t++;
		
		memset(visited, 0, sizeof(visited));
		
		for (int i = 0; i < n; i++)
			for (int k = 0; k < m; k++)
				if (board[i][k] == 1) {
					int airs = 0;
					int dx[4] = {0, 1, 0, -1};
					int dy[4] = {1, 0, -1, 0};

					for (int j = 0; j < 4; j++) {
						int newX = i + dx[j];
						int newY = k + dy[j];

						if (newX >= 0 && newX < n && newY >= 0 && newY < m)
							if (board[newX][newY] == 2)
								airs++;
					}

					if (airs >= 2) {
						toMelt.push({i, k});
						ch--;
					}
					
				}
		
		while(!toMelt.empty()) {
			int mx = toMelt.front().first, my = toMelt.front().second;
			toMelt.pop();
			refreshing(mx, my);
		}
	}
	
	cout << t << '\n';
	
	return 0;
}



// #include <stdio.h>
// #include <queue>
// #include <algorithm>

// #define pii pair<int, int>

// using namespace std;

// int n, m, board[110][110], t, ch;

// vector<pii > cheese;

// queue<pii > air, melt; 
// void isAir(int a, int b) {
	
// 	air.push({a, b});
	
// 	while(!air.empty()) {
// 		pii now = air.front();
// 		air.pop();
		
// 		int x = now.first, y = now.second;
		
// 		board[x][y] = 2;
		
// 		int dx[4] = {0, 1, 0, -1};
// 		int dy[4] = {1, 0, -1, 0};

// 		for (int i = 0; i < 4; i++) {
// 			int nx = x+dx[i], ny = y+dy[i];
// 			if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == 0)
// 				air.push({nx, ny});
// 		}
// 	}
	
// }

// int run() {
// 	scanf("%d %d", &n, &m);
	
// 	for (int i = 0; i < n; i++)
// 		for (int j = 0; j < m; j++) {
// 			scanf("%d", &board[i][j]);
// 			if (board[i][j]) {
// 				cheese.push_back({i, j});
// 				ch++;
// 			}
// 		}
	
// 	isAir(0, 0);
	
// 	while (ch>0) {
// 		t++;
		
// 		while(!melt.empty()) {
// 			board[melt.front().first][melt.front().second] = 2;
// 			isAir(melt.front().first, melt.front().second);
// 			melt.pop();
// 		}			
		
// 		for (int k = 0; k < cheese.size(); k++) {
// 			int i = cheese[k].first, j = cheese[k].second;
// 			int isMelt = board[cheese[k].first][cheese[k].second];
			
// 			if (isMelt!=2) {
// 				int howMany = (board[i-1][j]==2)+(board[i][j-1]==2)+(board[i+1][j]==2)+(board[i][j+1]==2);
// 				if (howMany >= 2) {
// 					melt.push({i, j});
// 					cheese[k].second = 1;
// 					ch--;
// 				} 
// 			}
// 		}
		
// 		// printf("%d\n", ch);
		
// 		// printf("\n");
// 		// for (int i = 0; i < n; i++) {
// 		// 	for (int j = 0 ; j < m; j++)
// 		// 		printf("%d ", board[i][j]==2?0:board[i][j]);
// 		// 	printf("\n");
// 		// }
		
// 		// if (t > 20 ) break;
// 	}
	
// 	printf("%d\n", t);
	
// 	return 0;
// }