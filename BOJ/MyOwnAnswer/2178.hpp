// Silver

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, arr[101][101], did[101][101];
queue<pair<int, int> > q;

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			char tmp;
			cin >> tmp;
			arr[i][j] = tmp - '0';
		}
	
	q.push(make_pair(0, 0));
	did[0][0] = 1;
	while(!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();
		
		if (now.first == n-1 && now.second == m-1) {
			cout << did[now.first][now.second] << '\n';
			return 0;
		}
		
		int dx[4] = {-1, 0, 1, 0};
		int dy[4] = {0, -1, 0, 1};
		
		for (int i = 0; i < 4; i++) {
			int nowX = now.first + dx[i];
			int nowY = now.second + dy[i];
			
			if (nowX >= 0 && nowX < n && nowY >= 0 && nowY < m && arr[nowX][nowY] == 1 && did[nowX][nowY] == 0) {
				q.push(make_pair(nowX, nowY));
				did[nowX][nowY] = did[now.first][now.second] + 1;
			}
		}
			
		// cout << q.size() << '\n';

	}
	
	return 0;
}