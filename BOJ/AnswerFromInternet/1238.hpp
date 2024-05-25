// Gold

// Use Dijkstra ; Array version
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 1987654321
#define pii pair<int, int>

using namespace std;

int n, m, x;
vector<pii > graph[1010];

bool isFilled(int arr[], int start, int end) {
	for (int i = start; i < end; i++)
		if (arr[i] == 0) return false;
	return true;
}

bool comp(pii a, pii b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

int dijkstra(int start, int end) {
	int s[1010] = {0, };
	int dist[1010] = {0, };
	priority_queue<pii , vector<pii >, greater<pii > > pq;
	
	for (int i = 0; i <= n; i++) dist[i] = INF;
	dist[start] = 0;
	
	pq.push(make_pair(0, start));
	
	while(!isFilled(s, 1, n+1)) {
		// Get shortest way
		int min = pq.top().first;
		int minIndex = pq.top().second;
		pq.pop();
		
		// cout << "MININDEX: " << minIndex << '\n';
		s[minIndex] = 1;
		
		for (int i = 0; i < graph[minIndex].size(); i++) {
			int node = graph[minIndex][i].first;
			int nodeWeight = graph[minIndex][i].second;
			
			if (!s[node])
				if (dist[node] > dist[minIndex] + nodeWeight) {
					dist[node] = dist[minIndex] + nodeWeight;
					pq.push(make_pair(dist[node], node));
					// cout << "INPUT: " << node << ' ' << dist[node] << '\n';
				}
		}
		
		// cout << "start:\n";
		// for (int i = 1; i <=n; i++) cout << i << '\t';
		// cout << '\n';
		// for (int i = 1; i <=n; i++) cout << s[i] << '\t';
		// cout << '\n';
	}
	return dist[end];
}

int getLongestTime() {
	int ans = 0;
	
	for (int i = 1; i <= n; i++) {
		int severalDist = dijkstra(i, x) + dijkstra(x, i);
		if (ans < severalDist) ans = severalDist;
	}
	
	return ans;
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> x;
	
	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		graph[from].push_back(make_pair(to, weight));
	}
	
	cout << getLongestTime() << '\n';
	
	return 0;
}


/*
// Use Dijkstra
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, x, dist[1010][1010];
vector<pair<int, int> > graph[1010];

bool comp(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

void dijkstra(int start) {
	int visited[1010] = {0, };
	
	visited[start] = 1;
	
	while(true) {
		bool isEnd = true;
		for (int i = 1; i <= n; i++)
			if (visited[i] == 0) isEnd = false;
		if(isEnd) break;
		
		int min = 1987654322, minIndex = 0;
		for (int i = 1; i <= n; i++)
			if (visited[i]) 
				for (int j = 0; j < graph[i].size(); j++) {
					int nextVertex = graph[i][j].first;
					int nextDist = graph[i][j].second;
					
					if (!visited[nextVertex])
						if (dist[i][nextVertex] + nextDist < min) {
							min = dist[i][nextVertex] + nextDist;
							minIndex = nextVertex;
							break;
						}
				}
		
		visited[minIndex] = 1;
		dist[start][minIndex] = min;
	}
}

int run() {
	cin >> n >> m >> x;
	
	memset(dist, 1987654321, sizeof(dist));
	
	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		graph[from].push_back(make_pair(to, weight));
	}
	
	for (int i = 1; i <= n; i++)
		sort(graph[i].begin(), graph[i].end(), comp);
	
	for (int i = 1; i <= n; i++) dijkstra(i);
	
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (ans < dist[i][x] + dist[x][i]) ans = dist[i][x] + dist[x][i];
	
	cout << ans << '\n';
	
	return 0;
}
*/

// Using bfs
// Fail: Time limit exceeded
/*
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, x, graph[1010][1010];

int bfs(int start, int end) {
	queue<pair<int, int> > q;
	int visited[1010] = {0, };
	int minTerm = 1987654321;
	
	visited[start] = 1;
	q.push(make_pair(start, 0));
	
	while(!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();
		
		visited[now.first] = 1;
		
		if (now.first == end) {
			if (now.second < minTerm) minTerm = now.second;
			continue;
		}
		
		for (int i = 1; i <= n; i++)
			if (!visited[i] && graph[now.first][i])
				if (now.second + graph[now.first][i] < minTerm)
					q.push(make_pair(i, now.second + graph[now.first][i]));
	}
	return minTerm;
}

int getTime(int start) {
	return bfs(start, x) + bfs(x, start);
}

int getLongestTime() {
	int max = 0;
	for (int i = 1; i <= n; i++) {
		int term = getTime(i);
		if (term > max) max = term;
	}
	return max;
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> x;
	
	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		graph[from][to] = weight;
	}
	
	cout << getLongestTime() << '\n';
	
	return 0;
}
*/