// Gold

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 1987654321
#define pii pair<int, int>

using namespace std;

int n, e, v1, v2;
vector<pii > graph[810];

bool isFilled(int arr[], int end) {
	for (int i = 1; i <= end; i++)
		if (arr[i] == 0) return false;
	return true;
}

int dijkstra(int start, int end) {
	priority_queue<pii , vector<pii >, greater<pii > > pq;
	int dist[810], s[810] = {0, };
	
	for (int i = 1; i <= n; i++) dist[i] = INF;

	dist[start] = 0;
	pq.push({0, start});
	
	while(!pq.empty()) {
		// Get shortest path
		int min = pq.top().first;
		int minIndex = pq.top().second;
		pq.pop();
		
		if (min > dist[minIndex]) continue;
		
		s[minIndex] = 1;
		
		for (int i = 0; i < graph[minIndex].size(); i++) {
			int nextNode = graph[minIndex][i].second;
			int nextWeight = graph[minIndex][i].first;
			
			if (dist[nextNode] > dist[minIndex] + nextWeight) {
				dist[nextNode] = dist[minIndex] + nextWeight;
				pq.push({nextWeight, nextNode});
			}
		}
	}
	
	
	if (isFilled(s, n))	return dist[end];
	return -1;
}

int run() {
	// ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> e;
	
	for (int i = 0; i < e; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		graph[from].push_back({weight, to});
		graph[to].push_back({weight, from});
	}
	
	cin >> v1 >> v2;
	
	
	int a = dijkstra(1, v1);
	int b = dijkstra(v1, v2);
	int c = dijkstra(v2, n);
	
	int d = dijkstra(1, v2);
	int e = dijkstra(v1, n);
	
	if (b == -1) {
		cout << -1 << '\n';
		return 0;
	} else if ((a == -1 || c == -1) && (d == -1 || e == -1)) {
		cout << -1 << '\n';
		return 0;
	} else {
		int routeA = a + b + c;
		int routeB = d + b + e;
		
		int ans = routeA<routeB?routeA:routeB;
		cout << ans << '\n';
	}
	
	return 0;
}