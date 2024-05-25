// Gold

#include <iostream>

using namespace std;

int n, m, board[22][22], alphabet[30], ans;

void getMax(int x, int y, int cost, int done[]) {
	int did[30];
	for (int i = 0; i < 28; i++) did[i] = done[i];
	
	bool isEnd = true;
	
	int dx[4] = {-1, 0, 1, 0};
	int dy[4] = {0, 1, 0, -1};
	for (int i = 0; i < 4; i++)
		if (x+dx[i] > 0 && x+dx[i] <= n && y+dy[i] > 0 && y+dy[i] <= m)
			if (!did[board[x+dx[i]][y+dy[i]]]) {
				did[board[x+dx[i]][y+dy[i]]] = 1;
				getMax(x+dx[i], y+dy[i], cost+1, did);
				did[board[x+dx[i]][y+dy[i]]] = 0;
				isEnd = false;
			}
	
	if (isEnd && ans < cost) ans = cost;
}

int run() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char tmp;
			cin >> tmp;
			board[i][j] = tmp-'A'+1;
		}
	
	alphabet[board[1][1]] = 1;
	getMax(1, 1, 1, alphabet);
	
	cout << ans << '\n';
	
	return 0;
}