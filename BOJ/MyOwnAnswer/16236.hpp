// Gold

#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

int n, sea[22][22], shark = 2, x, y, ans, eat;

bool isEnd = false;

int visit[22][22];

void meal(int A, int B) {
	int dx[4] = {0, -1, 0, 1};
	int dy[4] = {1, 0, -1, 0};
	queue<pair<pair<int, int>, int> > q;
	
	q.push({{A, B}, 0});
	visit[A][B] = 1;
	
	while(!q.empty()) {
		int a = q.front().first.first, b = q.front().first.second;
		int t = q.front().second;
		q.pop();
		
		// cout << a << ' ' << b << " : "<< sea[a][b] << '\n';
				
		for (int i = 0; i < 4; i++) {
			if (a+dx[i] > 0 && a + dx[i] <= n && b + dy[i] > 0 && b + dy[i] <= n) {
				if (!visit[a+dx[i]][b+dy[i]]) {
					if (sea[a+dx[i]][b+dy[i]] > 0 && sea[a+dx[i]][b+dy[i]] < shark) {
						isEnd = true;
						eat++;
						if (eat == shark) {
							eat = 0;
							shark++;
						}
						x = a + dx[i];
						y = b + dy[i];
						sea[x][y] *= -1;
						ans += t;
						return;
					}
					visit[a+dx[i]][b+dy[i]] = 1;
					q.push({{a+dx[i], b+dy[i]}, t+1});
				}
			}
		}
	}
}

int run() {
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> sea[i][j];
			if (sea[i][j] == 9) {
				x = i;
				y = j;
			}
		}
	
	int stopper = 0;
	while(true) {
		stopper++;
		if (stopper > 20) break;
		
		cout << x << ' ' << y << " : " << sea[x][y] << '\n';
		
		isEnd = false;
		memset(visit, 0, sizeof(visit));
		meal(x, y);
		if (!isEnd) {
			cout << 0 << '\n';
			return 0;
		}
	}
	
	cout << ans+1 << '\n';
	
	return 0;
}