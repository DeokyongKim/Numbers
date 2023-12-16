// Gold

#include <iostream>
#include <queue>

#define INF 1987654321

using namespace std;

typedef struct _node {
	int row;
	int col;
	int broke;
} node;

int n, m, map[1010][1010], cost[1010][1010][2];

queue<node> q;

int run() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char tmp;
			cin >> tmp;
			map[i][j] = tmp-'0';
		}
	
	q.push({1, 1, 0});
	cost[1][1][0] = 1;
	while(!q.empty()) {
		node now = q.front();
		q.pop();
		
		int x = now.row, y = now.col, broke = now.broke;
		
		if (x == n && y == m) {
			cout << cost[x][y][broke] << '\n';
			return 0;
		}
		
		int dx[4] = {1, 0, -1, 0};
		int dy[4] = {0, 1, 0, -1};
		
		for (int i = 0; i < 4; i++) {
			int nx = x+dx[i], ny = y+dy[i];
			if (nx > 0 && nx <= n && ny > 0 && ny <= m) {
				if (!broke && map[nx][ny] == 1) {
					q.push({nx, ny, 1});
					cost[nx][ny][1] = cost[x][y][0] + 1;
					// cout << "BROKE: " << x+dx[i] << ", " << y+dy[i] << " : " << map[x+dx[i]][y+dy[i]] <<'\n';
				} else if (map[nx][ny] == 0 && !cost[nx][ny][broke]) {
					q.push({nx, ny, now.broke});
					cost[nx][ny][broke] = cost[x][y][broke]+1;
					// cout << "WENT: " << x+dx[i] << ", " << y+dy[i] << " : " << map[x+dx[i]][y+dy[i]] <<'\n';
				}
			}
		}
	}
	
	cout << "-1\n";
	return 0;
}


// Trying DFS. Timeover.
/*
#include <iostream>

#define INF 1987654321

using namespace std;

int n, m, map[1010][1010], dp[1010][1010], ans = INF;

void getPath(int x, int y, bool broke, int cost) {
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	
	if (x==n && y==m) {
		if (ans > cost) ans = cost;
		return;
	}
	
	if (dp[x][y]!=0 && dp[x][y] < cost) {
		return;
	} else if (dp[x][y]==0 || (dp[x][y]!=0 && dp[x][y] > cost)) {
		dp[x][y] = cost;
	}
	
	int tmp = map[x][y];
	map[x][y] = 2;
	for (int i = 0; i < 4; i++)
		if (x+dx[i] > 0 && x+dx[i] <= n && y+dy[i] > 0 && y+dy[i] <= m) {
			if (!broke && map[x+dx[i]][y+dy[i]] == 1) {
				getPath(x+dx[i], y+dy[i], !broke, cost+1);
				// cout << "BROKE: " << x+dx[i] << ", " << y+dy[i] << " : " << map[x+dx[i]][y+dy[i]] <<'\n';
			}
			if (map[x+dx[i]][y+dy[i]] == 0) {
				getPath(x+dx[i], y+dy[i], broke, cost+1);
				// cout << "WENT: " << x+dx[i] << ", " << y+dy[i] << " : " << map[x+dx[i]][y+dy[i]] <<'\n';
			}
		}
	map[x][y] = tmp;
}

int run() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char tmp;
			cin >> tmp;
			map[i][j] = tmp-'0';
		}
	
	getPath(1, 1, false, 1);
	
	ans = ans==INF?-1:ans;
	
	cout << ans << '\n';
	
	return 0;
}
*/


// Trying DP. But wrong answer.
/* 
#include <iostream>

#define INF 1987654321

using namespace std;

int n, m, map[1010][1010], dp[1010][1010][2], ans = INF;

int getPath(int x, int y) {
	if (x == 1 && y == 1) {
		dp[1][1][0] = 1;	// cost
		dp[1][1][1] = 0;	// did brake
		return dp[1][1][0];
	}
	
	if (dp[x][y][0] < INF) return dp[x][y][0];
	
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

	for (int i = 0; i < 4; i++)
		if (x+dx[i] > 0 && x+dx[i] <= n && y+dy[i] > 0 && y+dy[i] <= m) {
			int planA, planB;
			
			if (!dp[x+dx[i]][y+dy[i]][1] && map[x][y] == 1) {
				planA = getPath(x+dx[i], y+dy[i]) + 1;
				if (planA < dp[x][y][0]) {
					dp[x][y][0] = planA;
					dp[x][y][1] = 1;
				}
				// cout << "BROKE: " << x+dx[i] << ", " << y+dy[i] << " : " << map[x+dx[i]][y+dy[i]] <<'\n';
			}
			if (map[x][y] == 0) {
				planB = getPath(x+dx[i], y+dy[i]) + 1;
				if (planB < dp[x][y][0]) {
					dp[x][y][0] = planB;
					dp[x][y][1] = dp[x+dx[i]][y+dy[i]][1];
				}
				// cout << "WENT: " << x+dx[i] << ", " << y+dy[i] << " : " << map[x+dx[i]][y+dy[i]] <<'\n';
			}
		}
	
	return dp[x][y][0];
}

int run() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char tmp;
			cin >> tmp;
			map[i][j] = tmp-'0';
			dp[i][j][0] = INF;
		}
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			getPath(i, j);
	
	ans = dp[n][m][0]==INF?-1:dp[n][m][0];
	
	cout << ans << '\n';
	
	
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++) {
			cout << dp[i][j] << '\t';
		}
		cout << '\n';
	}
	
	return 0;
}
*/