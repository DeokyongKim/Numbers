// Gold

#include <iostream>
#include <vector>
#include <queue>

#define MAXMOVE 10
#define pii pair<int, int>

using namespace std;

int n, m;

int ctoi(char a) {
	switch(a) {
		case '.':
			return 0;
		case '#':
			return 1;
		case 'O':
			return 2;
		case 'R':
			return 3;
		case 'B':
			return 4;
	}
	return -1;
}

char itoc(int a) {
	switch(a) {
		case 0:
			return '.';
		case 1:
			return '#';
		case 2:
			return 'O';
		case 3:
			return 'R';
		case 4:
			return 'B';
	}
	return ' ';
}

pii red, blue, goal;

int dp[13][13][13][13];

bool check(pii a) {
	if (a.first == goal.first && a.second == goal.second)
		return true;
	return false;
}

int map[13][13], did;

pii rans, bans;

queue<pair<pair<pii, pii >, int> > q;

void showMAP(pii r, pii b, int t) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == r.first && j == r.second) cout << 'R' << ' ' ;
			else if (i == b.first && j == b.second) cout << 'B' << ' ';
			else if (i == goal.first && j == goal.second) cout << 'O' << ' ';
			else cout << itoc(map[i][j]) << ' ';
		}
		cout << '\n';
	}
	cout << t << "======================\n";
}

void solve() {
	q.push({{red,blue}, 0});
	dp[red.first][red.second][blue.first][blue.second] = 1;
	
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};
	
	while(!q.empty()) {
		
		pii r = q.front().first.first, b = q.front().first.second;
		int t = q.front().second;
		q.pop();
		
		// showMAP(r, b, t);
		
		if (t>=MAXMOVE) {
			cout << -1 << '\n';
			return;
		}
				
		for (int i = 0; i < 4; i++) {
			pii tmpR, tmpB;
			tmpR.first = r.first;
			tmpR.second = r.second;
			tmpB.first = b.first;
			tmpB.second = b.second;
			
			bool rend = false, bend = false;
			while(true) {
				bool moved = false;
				if (!bend && 
					!(!rend && tmpB.second+dy[i]==tmpR.second && tmpB.first+dx[i] == tmpR.first)
				   )
					if (map[tmpB.first+dx[i]][tmpB.second+dy[i]]==ctoi('.')){
						tmpB.first+=dx[i];
						tmpB.second+=dy[i];
						bend = check(tmpB);
						if (bend) break;
						moved = true;
					}
				if (!rend && 
					!(tmpR.second+dy[i]==tmpB.second && tmpR.first+dx[i] == tmpB.first)
				   )
					if (map[tmpR.first+dx[i]][tmpR.second+dy[i]]==ctoi('.')){
						tmpR.first+=dx[i];
						tmpR.second+=dy[i];
						rend = check(tmpR);
						// if (rend) {tmpR.first = -10; tmpR.second = -10;}
						moved = true;
					}
				if (!moved) break;
			}
			if (bend) continue;
			if (!bend && rend) {
				// showMAP(tmpR, tmpB, t);
				
				cout << t+1 << '\n';
				return;
			}
			if (!dp[tmpR.first][tmpR.second][tmpB.first][tmpB.second]) {
				dp[tmpR.first][tmpR.second][tmpB.first][tmpB.second] = 1;
				q.push({{tmpR, tmpB}, t+1});
			}
		}
	}
	
	cout << -1 << '\n';
}

int run() {
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			char tmp;
			cin >> tmp;
			
			if (tmp == 'R') {
				red.first = i;
				red.second = j;
				tmp = '.';
			}
			if (tmp == 'B') {
				blue.first = i;
				blue.second = j;
				tmp = '.';
			}
			if (tmp == 'O') {
				goal.first = i;
				goal.second = j;
				tmp = '.';
			}
			
			map[i][j] = ctoi(tmp);
		}
	
	// showMAP(red, blue, 111);
	
	solve();
	
	return 0;
}