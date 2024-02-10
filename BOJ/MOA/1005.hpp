// Gold
// MOA (My Own Answer)

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void solve() {
	// input
	int n, k, weight[1010] = {0, }, income[1010] = {0, };
	int visited[1010] = {0, };
	int dp[1010] = {0, };
	vector<int> v[1010];
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> weight[i];
	for (int i = 0; i < k; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		income[tmp2]++;
		v[tmp1].push_back(tmp2);
	}
	
	int toFind;
	cin >> toFind;
		
	queue<int > q;
	
	for (int i = 1; i <= n; i++)
		if (income[i] == 0) {
			visited[i] = 1;
			dp[i] = weight[i];
			q.push(i);
		}
	
	while(!q.empty()) {
		int curNode = q.front();
		q.pop();
		
		if (curNode == toFind) break;
		
		for (int i = 0; i < v[curNode].size(); i++) {
			int watching = v[curNode][i];
			income[watching]--;
			if (dp[watching] < dp[curNode] + weight[watching])
				dp[watching] = dp[curNode] + weight[watching];
			if (income[watching] == 0) {
				visited[watching] = 1;
				q.push(watching);
			}
		}
	}
	
	cout << dp[toFind] << '\n';
}

int run() {
	int testNum;
	cin >> testNum;
	for (int test = 0; test < testNum; test++) solve();
	
	return 0;
}


// Top-down : Memory Exceeded
/*
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void solve() {
	// input
	int n, k, weight[1010] = {0, }, income[1010] = {0, };
	vector<int> v[1010];
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> weight[i];
	for (int i = 0; i < k; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		income[tmp2]++;
		v[tmp2].push_back(tmp1);
	}
	
	int toFind;
	cin >> toFind;
	
	int ans = 0;
	
	queue<pair<int, int> > q;
	
	q.push({toFind, weight[toFind]});
	while(!q.empty()) {
		int curNode = q.front().first;
		int curTime = q.front().second;
		q.pop();
		
		if (income[curNode]) {
			int maxNode, maxTime = 0;
			for (int i = 0; i < v[curNode].size(); i++) {
				int node = v[curNode][i];
				// income[curNode]--;
				q.push({node, curTime+weight[node]});
				// cout << i << ':' << curTime << '\n';
			}
		
		}
		
		// In case of first node
		if (!income[curNode])
			if (ans < curTime) ans = curTime;
	}
	
	cout << ans << '\n';
}

int run() {
	int testNum;
	cin >> testNum;
	for (int test = 0; test < testNum; test++) solve();
	
	return 0;
}
*/