// Silver

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	
	int n, k, ans = 0, visited[4000010] = {0, };
	cin >> n >> k;

	queue<pair<int, int>> q;
	q.push(make_pair(n, 0));

	while(!q.empty()) {
		pair<int, int> now = q.front();
		visited[now.first] = 1;
		q.pop();

		if (now.first == k) {
			ans = now.second;
			break;
		}

		if (now.first - 1 >= 0 && !visited[now.first - 1]) q.push(make_pair(now.first - 1, now.second + 1));
		if (now.first + 1 <= k && !visited[now.first + 1]) q.push(make_pair(now.first + 1, now.second + 1));
		if (now.first < k && !visited[now.first*2]) q.push(make_pair(now.first * 2, now.second + 1));
	}

	cout << ans << "\n";
}