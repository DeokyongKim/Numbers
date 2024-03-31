// Gold

#include <iostream>
#include <algorithm>

#define pii pair<int, int>

using namespace std;

int n, m, dirIdx, board[55][55], ans;
pii dir[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}, cur;

int run() {
	cin >> n >> m;

	cin >> cur.first >> cur.second;
	cin >> dirIdx;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) 
			cin >> board[i][j];

	while(true) {
		if (board[cur.first][cur.second] == 0) {
			board[cur.first][cur.second] = 2;
			ans++;
			continue;
		}

		bool did = false;
		for (int i = 1; i < 5; i++) {
			int nx = cur.first + dir[(dirIdx+8-i)%4].first;
			int ny = cur.second + dir[(dirIdx+8-i)%4].second;
			if (nx >= 0 && nx < n && ny >= 0 && ny < m)
				if (board[nx][ny] == 0) {
					cur.first = nx;
					cur.second = ny;
					dirIdx = (dirIdx+8-i)%4;
					did = true;
					break;
				}
		}

		if (!did) {
			int nx = cur.first - dir[dirIdx].first;
			int ny = cur.second - dir[dirIdx].second;
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] != 1) {
				cur.first = nx;
				cur.second = ny;
			} else {
				break;
			}
		}
	}

	cout << ans << '\n';

	return 0;
}