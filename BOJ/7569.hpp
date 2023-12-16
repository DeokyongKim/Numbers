// Gold

#include <iostream>
#include <queue>

using namespace std;

int m, n, h, tomato[101][101][101], ans, todo;

typedef struct _COORDI {
	int x;
	int y;
	int z;
	int day;
} COORDI;

queue<COORDI> q;

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> m >> n >> h;
	
	for (int i = 0; i < h; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < m; k++) {
				cin >> tomato[i][j][k];
				if (tomato[i][j][k] == 0) todo++;
				if (tomato[i][j][k] == 1) q.push({k, j, i, 0});
			}
	
	while(!q.empty()) {
		COORDI now = q.front();
		q.pop();
		
		int dx[6] = {1, 0, 0, -1, 0, 0};
		int dy[6] = {0, 1, 0, 0, -1, 0};
		int dz[6] = {0, 0, 1, 0, 0, -1};
		for (int i = 0; i < 6; i++)
			if (now.x+dx[i] >= 0 && now.x+dx[i] < m && now.y+dy[i] >= 0 && now.y+dy[i] < n && now.z+dz[i] >= 0 && now.z+dz[i] < h)
				if (tomato[now.z+dz[i]][now.y+dy[i]][now.x+dx[i]] == 0) {
					tomato[now.z+dz[i]][now.y+dy[i]][now.x+dx[i]] = 1;
					q.push({now.x+dx[i], now.y+dy[i], now.z+dz[i], now.day+1});
					todo--;
					ans = now.day+1;
				}
	}
	
	if (todo > 0) {
		cout << -1 << '\n';
		return 0;
	}
	
	cout << ans << '\n';
	
	return 0;
}



/* Timeout
#include <iostream>

using namespace std;

int m, n, h, tomato[101][101][101];

int todo = 0, ans = 0;

int dx[6] = {1, 0, 0, -1, 0, 0};
int dy[6] = {0, 1, 0, 0, -1, 0};
int dz[6] = {0, 0, 1, 0, 0, -1};
int getRipen(int z, int y, int x) {
	int did = 0;
	for (int i = 0; i < 6; i++)
		if (x+dx[i] >= 0 && x+dx[i] < m && y+dy[i] >= 0 && y+dy[i] < n && z+dz[i] >= 0 && z+dz[i] < h)
			if (tomato[z+dz[i]][y+dy[i]][x+dx[i]] == 0) {
				did = 1;
				tomato[z+dz[i]][y+dy[i]][x+dx[i]] = ans+2;
				todo--;
			}
	return did;
}

bool isEnd() {
	for (int i = 0; i < h; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < m; k++)
				if (tomato[i][j][k] == 0) return false;
	return true;
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> m >> n >> h;
	
	for (int i = 0; i < h; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < m; k++) {
				cin >> tomato[i][j][k];
				if (tomato[i][j][k] == 0) todo++;
			}
	
	while(todo > 0) {		
		int did = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < m; k++)
					if (tomato[i][j][k] == ans +1)
						did += getRipen(i, j, k);
				
		if (!did && todo > 0) {
			cout << -1 << '\n';
			return 0;
		}
		
		ans++;
	}
	
	cout << ans << '\n';
	
	return 0;
}
*/