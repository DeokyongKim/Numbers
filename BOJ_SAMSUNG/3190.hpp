#include <iostream>
#include <algorithm>
#include <queue>

#define pii pair<int, int>

using namespace std;

int n, k, l;

int board[110][110];

void showBoard(int t) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << board[i][j] << ' ';
		cout << '\n';
	}
	cout << t << "================\n";
}

int run() {
	pii head = {0, 0};
	pii dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	
	queue<pii > q;
	q.push({head.first, head.second});
	
	// 1 means snake
	board[0][0] = 1;
	
	int dirIdx = 0;
	int time = 0;
	
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		// 2 means apple
		board[tmp1-1][tmp2-1] = 2;
	}
	
	cin >> l;
	
	for (int tryCount = 0; tryCount < l; tryCount++) {
		int changeTime;
		char direction;
		cin >> changeTime;
		cin >> direction;
		
		for (; time < changeTime; time++) {
			// move head
			head.first += dir[dirIdx].first;
			head.second += dir[dirIdx].second;
			if (head.first >= n || 
				head.first < 0 || 
				head.second >= n || 
				head.second < 0 || 
				board[head.first][head.second] == 1
			   ) {
				cout << time+1 << '\n';
				return 0;
			}
			
			if (board[head.first][head.second] == 2) {
				board[head.first][head.second] = 1;
				q.push({head.first, head.second});
				continue;
			}
			board[head.first][head.second] = 1;
			q.push({head.first, head.second});
			
			// move tail
			pii tail = {q.front().first, q.front().second};
			board[tail.first][tail.second] = 0;
			q.pop();
		}
		
		// Change direction
		if (true) {
			if (direction == 'D') {
				if (dirIdx == 3) dirIdx = 0;
				else dirIdx += 1;
			} else if (direction == 'L') {				
				if (dirIdx == 0) dirIdx = 3;
				else dirIdx -= 1;
			}
		}		
	}
	
	for (; ; time++) {
		// move head
		head.first += dir[dirIdx].first;
		head.second += dir[dirIdx].second;
		if (head.first >= n || 
			head.first < 0 || 
			head.second >= n || 
			head.second < 0 || 
			board[head.first][head.second] == 1
		   ) {
			cout << time+1 << '\n';
			return 0;
		}

		if (board[head.first][head.second] == 2) {
			board[head.first][head.second] = 1;
			q.push({head.first, head.second});
			continue;
		}
		board[head.first][head.second] = 1;
		q.push({head.first, head.second});

		// move tail
		pii tail = {q.front().first, q.front().second};
		board[tail.first][tail.second] = 0;
		q.pop();
	}
		
	return 0;
}