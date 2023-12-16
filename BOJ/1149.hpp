// Silver

#include <iostream>

using namespace std;

int n, color[1010][4], ans = 1987654321, dp[1010][4];

void initialize() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 3; j++)
			dp[i][j] = 198765432;
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		cin >> color[i][1] >> color[i][2] >> color[i][3];
	
	initialize();
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 3; j++) {
			if (i == 1) {
				dp[i][j] = color[i][j];
			} else {
				for (int k = 1; k <= 3; k++)
					if (j != k && dp[i][j] > dp[i-1][k] + color[i][j])
						dp[i][j] = dp[i-1][k] + color[i][j];
			}
		}
	}
	
	int low = 198765432;
	for (int i = 1; i <= 3; i++)
		if (low > dp[n][i]) low = dp[n][i];
	
	cout << low << '\n';
	
	return 0;
}

// Using DP
// FAIL: uncorrect answer
/*
#include <iostream>

using namespace std;

int n, color[1010][4], ans = 1987654321, memo[1010][2];

void initialize() {
	for (int i = 0; i <= n; i++) memo[i][0] = 1987654321;
}

void lowest(int position, int col) {
	if (position == 0) {
		memo[position][0] = 0;
	} else if (position == 1) {
		if (memo[position][0] > color[position][col]) {
			memo[position][0] = color[position][col];
			memo[position][1] = col;
		}
	} else {
		int a = 1987654322, b = 1987654322, aCol = -1, bCol = -1;

		if (memo[position-1][1] != col) {
			a = memo[position-1][0] + color[position][col];
			aCol = col;
		}
		for (int i = 1; i <= 3; i++)
			if (i != col && i != memo[position-2][1])
				if (b > memo[position-2][0] + color[position-1][i] + color[position][col]) {
					b = memo[position-2][0] + color[position-1][i] + color[position][col];
					bCol = col;
				}
		
		if (a < b) {
			if (memo[position][0] > a) {
				memo[position][0] = a;
				memo[position][1] = aCol;
			}
		} else {
			if (memo[position][0] > b) {
				memo[position][0] = b;
				memo[position][1] = bCol;
			}
		}
	}
}

int getLowest() {
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= 3; j++)
			lowest(i, j);
	return memo[n][0];
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		cin >> color[i][1] >> color[i][2] >> color[i][3];
	
	initialize();
	cout << getLowest() << '\n';
	
	// cout << '\n';
	// for (int i = 1; i <= n; i++)
	// 	cout << memo[i][0] << ' ';
	// cout << '\n';
	
	return 0;
}
*/

// Using BFS
// FAIL: memory limit exceeded
/*
#include <iostream>
#include <queue>

using namespace std;

typedef struct _PRICE {
	int position;
	int color;
	int price;
} PRICE;

int n, color[1010][3], ans = 1987654321;

queue<PRICE> q;

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		cin >> color[i][0] >> color[i][1] >> color[i][2];
	
	q.push({1, 0, color[1][0]});
	q.push({1, 1, color[1][1]});
	q.push({1, 2, color[1][2]});
	
	while(!q.empty()) {
		PRICE now = q.front();
		q.pop();
		
		if (now.price > ans) continue;
		
		if (now.position == n+1) {
			if (now.price < ans) ans = now.price;
			continue;
		}
		
		int position = now.position + 1;
		
		for (int i = 0; i < 3; i++)
			if (i != now.color)
				q.push({position, i, now.price + color[position][i]});
	}
	
	cout << ans << '\n';
	
	return 0;
}
*/