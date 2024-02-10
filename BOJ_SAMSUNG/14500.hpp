#include <iostream>
#include <algorithm>

using namespace std;

int n, m, board[510][510], maxNum;

int run() {
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	
	pair<int, int> tet[5][4] = {
		{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
		{{0, 0}, {0, 1}, {1, 0}, {1, 1}},
		{{0, 0}, {0, 1}, {0, 2}, {1, 2}},
		{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
		{{0, 0}, {0, 1}, {1, 1}, {0, 2}},
	};
	
	pair<int, int> dir[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++) {
			for (int k = 0; k < 4; k++)
				for (int i = 0; i < 5; i++) {
					int sum = 0;
					for (int j = 0; j < 4; j++) {
						int nx = x+dir[k].first*tet[i][j].first;
						int ny = y+dir[k].second*tet[i][j].second;
						if (nx<0 || nx>=n || ny<0 || ny >= m) {
							sum = 0;
							break;
						}
						sum += board[nx][ny];
					}
					if (sum > maxNum) maxNum = sum;
				}
		}
	
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++) {
			for (int k = 0; k < 4; k++)
				for (int i = 0; i < 5; i++) {
					int sum = 0;
					for (int j = 0; j < 4; j++) {
						int nx = x+dir[k].first*tet[i][j].second;
						int ny = y+dir[k].second*tet[i][j].first;
						if (nx<0 || nx>=n || ny<0 || ny >= m) {
							sum = 0;
							break;
						}
						sum += board[nx][ny];
					}
					if (sum > maxNum) maxNum = sum;
				}
		}
	
	cout << maxNum << '\n';
	
	return 0;
}