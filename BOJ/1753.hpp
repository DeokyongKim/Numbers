// Gold

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 1987654321
#define pii pair<int, int>

using namespace std;

int v, e, start, dist[20010];
vector<pii > graph[20010];

void dijkstra(int s) {
	priority_queue<pii , vector<pii >, greater<pii > > pq;
	
	for (int i = 1; i <= v; i++) dist[i] = INF;
	
	pq.push({0, s});
	dist[s] = 0;
	
	int stopper = 0;
	while (!pq.empty()) {
		int min = pq.top().first;
		int minIndex = pq.top().second;
		pq.pop();
		
		if (min > dist[minIndex]) continue;
		
		for (int i = 0; i < graph[minIndex].size(); i++) {
			int nextNode = graph[minIndex][i].second;
			int nextWeight = graph[minIndex][i].first;
			
			if (dist[nextNode] > dist[minIndex] + nextWeight) {
				dist[nextNode] = dist[minIndex] + nextWeight;
				pq.push({dist[nextNode], nextNode});
			}
		}
	}
}

int run() {
	cin >> v >> e >> start;
	
	for (int i = 0; i < e; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		graph[from].push_back({weight, to});
	}
	
	dijkstra(start);
	
	for (int i = 1; i <= v; i++) {
		if (dist[i] != INF) cout << dist[i] << '\n';
		else cout << "INF\n";
	}
	
	return 0;
}

/*
// Gold

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 1987654321
#define pii pair<int, int>

using namespace std;

int v, e, start, dist[2010];
vector<pii > graph[2010];

void dijkstra(int start) {
	priority_queue<pii , vector<pii >, greater<pii > > pq;
	
	for (int i = 1; i <= v; i++) dist[i] = INF;

	dist[start] = 0;
	pq.push({0, start});
	
	while(!pq.empty()) {
		// Get shortest path
		int min = pq.top().first;
		int minIndex = pq.top().second;
		pq.pop();
		
		if (min > dist[minIndex]) continue;
				
		for (int i = 0; i < graph[minIndex].size(); i++) {
			int nextNode = graph[minIndex][i].second;
			int nextWeight = graph[minIndex][i].first;
			
			if (dist[nextNode] > dist[minIndex] + nextWeight) {
				dist[nextNode] = dist[minIndex] + nextWeight;
				pq.push({nextWeight, nextNode});
			}
		}
	}
}

int run() {
	cin >> v >> e >> start;
	
	for (int i = 0; i < e; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		graph[from].push_back({weight, to});
	}
	
	dijkstra(start);
	
	for (int i = 1; i <= v; i++) {
		if (dist[i] != INF) cout << dist[i] << '\n';
		else cout << "INF\n";
	}
	
	return 0;
}
*/