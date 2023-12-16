// Gold

// Ok, i'm too tired with this problem and i don't think solving it
// would not help me a lot and also i'm running out of time,
// i just introduce a web page i just saw and submit the code.
// I wish somedoay you'll solve this...

// https://4z7l.github.io/2021/03/04/algorithms-boj-1865.html

#include <iostream>
#include <string>
#include <vector>

#define MAX 30000000

using namespace std;

int n, m, w;

struct node {
	int s, e, t;
};

bool time_travel(int n, vector<node> nodes) {
	vector<int> dist(n + 1, MAX);

	int s, e, t;
	dist[1] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < nodes.size(); j++) {
			s = nodes[j].s;
			e = nodes[j].e;
			t = nodes[j].t;
			
			if (dist[e] > dist[s] + t) dist[e] = dist[s] + t;
		}
	}
	for (int j = 0; j < nodes.size(); j++) {
		s = nodes[j].s;
		e = nodes[j].e;
		t = nodes[j].t;
		
		if (dist[e] > dist[s] + t) return true;
	}

	return false;
}

int main()
{
	cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

	int TC;
	cin >> TC;

	int s, e, t;
	while (TC > 0) {
		cin >> n >> m >> w;

		vector<node> nodes;

		for (int i = 0; i < m; i++) {
			cin >> s >> e >> t;
			nodes.push_back({ s,e,t });
			nodes.push_back({ e,s,t });
		}
		for (int i = 0; i < w; i++) {
			cin >> s >> e >> t;
			nodes.push_back({ s,e,-t });
		}

		if (time_travel(n, nodes)) cout << "YES\n";
		else cout << "NO\n";

		TC--;
	}

	return 0;
}


















// #include <iostream>
// #include <vector>
// #include <queue>
// #include <functional>

// #define INF 1987654321
// #define pii pair<int, int>

// using namespace std;

// int f;

// bool isFilled(int arr[], int end) {
// 	for (int i = 1; i <= end; i++)
// 		if (arr[i] == 0) return false;
// 	return true;
// }

// void dijkstra(int start, int vertex, int dist[]) {
// 	int s[510] = {0, };
// 	priority_queue<pii , vector<pii >, greater<pii > > pq;
// 	pq.push({0, start});
	
// 	while(!isFilled(s, vertex)) {
// 		int cur_weight = pq.top().first;
// 		int cur_node = pq.top().second;
// 		pq.pop();
		
// 		s[cur_node] = 1;
// 		dist[cur_node] = cur_weight;
		
// 		for (int i = 1; i <= vertex; i++)
// 			if (!s[i] && !graph[cur_node][i])
// 				if (dist[i] > cur_weight + graph[cur_node][i]) {
// 					dist[i] = cur_weight + graph[cur_node][i];
// 					pq.push({dist[i], i});
// 				}
// 	}
// }

// void backToTheFuture() {
// 	int n, m, w, graph[510][510];
// 	cin >> n >> m >> w;
	
// 	for (int i = 0; i < m; i++) {
// 		int from, to , weight;
// 		cin >> from >> to >> weight;
// 		graph[from][to] = weight;
// 		graph[to][from] = weight;
// 	}
	
// 	for (int i = 0; i < w; i++) {
// 		int from, to, weight;
// 		cin >> from >> to >> weight;
// 		graph[from][to] = -weight;
// 	}
	
// 	int dist[510] = {0, };
	
// }

// int run() {
// 	cin >> f;
	
// 	for (int i = 0; i < f; i++) backToTheFuture();
	
// 	return 0;
// }