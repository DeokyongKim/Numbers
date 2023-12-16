// Gold

// Using dfs TWICE
// I saw answer... 
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, maxDist = 0, maxVertex = 0, visited[100010];
vector<pair<int, int> > graph[100010];

bool comp(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

void dfs(int start, int dist) {
	visited[start] = 1;
	
	if (dist > maxDist) {
		maxDist = dist;
		maxVertex = start;
	}
	
	for (int i = 0; i < graph[start].size(); i++) {
		int next = graph[start][i].first, d = graph[start][i].second;
		if (!visited[next]) dfs(next, dist + d);
	}
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		
		while(true) {
			int tmp = 0;
			cin >> tmp;
			
			if (tmp == -1) break;
			
			int edge;
			cin >> edge;
			
			graph[v].push_back(make_pair(tmp, edge));
		}
	}
	
	for (int i = 1; i <= n; i++)
		sort(graph[i].begin(), graph[i].end(), comp);
	
	dfs(1, 0);
	
	for (int i = 1; i <= n; i++) visited[i] = 0;
	maxDist = 0;
	dfs(maxVertex, 0);
	
	cout << maxDist << '\n';
	
	return 0;
}

/*
// Kruskal algorithm
// Fail: Wrong algorithm. Kruskal is for MST, which means MINIMUM spanning tree, not maximum
//       I knew that but... my mistake
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct _NODE {
	int from;
	int to;
	int weight;
} NODE;

int n;
vector<NODE> graph;
int node[100010], sum[100010];

bool comp(NODE a, NODE b) {
	return a.weight > b.weight;
}

void initializeParent() {
	for (int i = 1; i <= n; i++) {
		node[i] = i;	// parent
	}
}

bool isUnion(int v1, int v2) {
	if (node[v1] == node[v2]) return true;
	return false;
}

void kruskal() {
	initializeParent();
	
	for (vector<NODE>::iterator it = graph.begin(); it != graph.end(); it++) {
		if (!isUnion(it->from, it->to)) {
			node[it->to] = node[it->from];
			sum[node[it->from]] += it->weight;
		}
		
		cout << "node:\t";
		for (int i = 0; i < n; i++) cout << node[i] << ' ';
		cout <<"\nsum:\t";
		for (int i = 0; i < n; i++) cout << sum[i] << ' ';
		cout << "\n\n";
	}
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		
		while(true) {
			int tmp = 0;
			cin >> tmp;
			
			if (tmp == -1) break;
			
			int edge;
			cin >> edge;
			
			graph.push_back({v, tmp, edge});
		}
	}
	
	sort(graph.begin(), graph.end(), comp);
	
	kruskal();
	
	cout << sum[node[graph.begin()->from]] << '\n';
	
	return 0;
}
*/


/*
// Classic graphical approach
// Fail: Time limit exceeded
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<pair<int, int> > graph[100010];

bool comp(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		
		while(true) {
			int tmp = 0;
			cin >> tmp;
			
			if (tmp == -1) break;
			
			int edge;
			cin >> edge;
			
			graph[v].push_back(make_pair(tmp, edge));
		}
	}
	
	for (int i = 1; i <= n; i++)
		sort(graph[i].begin(), graph[i].end(), comp);

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		queue<pair<int, int> > q;
		q.push(make_pair(i, 0));
		
		int visited[100010] = {0, };
		visited[i] = 1;
		
		while(!q.empty()) {
			pair<int, int> now = q.front();
			q.pop();
			
			bool did = false;
			for (vector<pair<int, int> >::iterator it = graph[now.first].begin(); it != graph[now.first].end(); it++) {
				int vertex = it->first;
				if (!visited[vertex]) {
					visited[vertex] = 1;
					q.push(make_pair(vertex, it->second + now.second));
					did = true;
				}
			}
			
			if (!did)
				if (ans < now.second) ans = now.second;
		}
	}
	
	cout << ans << '\n';
	
	return 0;
}
*/