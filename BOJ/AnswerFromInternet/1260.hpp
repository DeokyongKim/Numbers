// Silver

#include <iostream>
#include <queue>

using namespace std;

int n, m, start, map[1010][1010];
int visitedDfs[1010], visitedBfs[1010];

void DFS(int node) {
	visitedDfs[node] = 1;
	cout << node << ' ';
	for (int i = 1; i <= n; i++)
		if (visitedDfs[i] == 0 && map[node][i] == 1)
			DFS(i);
}

void BFS(int node) {
	queue<int> q;
	
	q.push(node);
	visitedBfs[node] = 1;

	
	while(!q.empty()) {
		int presentNode = q.front();
		q.pop();
		cout << presentNode << ' ';
		
		for (int i = 1; i <= n; i++)
			if (visitedBfs[i] == 0 && map[presentNode][i] == 1){
				q.push(i);
				visitedBfs[i] = 1;
			}
	}
}

void run() {
	cin >> n >> m >> start;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		map[a][b] = 1;
		map[b][a] = 1;
	}
	
	DFS(start);
	cout << '\n';
	BFS(start);
	cout << '\n';
}


/* wtf is wrong?
#include <queue>
#include <stack>

using namespace std;

int n, m, start;
int graph[1010][1010];

int visitedDFS[1010] = {0, }, visitedBFS[1010] = {0, }, dfs, bfs;;

void BFS() {
	queue<int> q;
	q.push(start);
	
	while(bfs != n && !q.empty()) {
		int presentNode = q.front();
		q.pop();
		visitedBFS[presentNode] = 1;
		bfs++;
		cout << presentNode << ' ';
		
		for (int i = 1; i <= n; i++) 
			if (visitedBFS[i] == 0 && graph[presentNode][i] == 1) {
				q.push(i);
			}
	}
	
	cout << '\n';
}

void DFS() {
	stack<int> st;
	st.push(start);
	while(dfs != n && !st.empty()) {
		int presentNode = st.top();
		visitedDFS[presentNode] = 1;
		dfs++;
		st.pop();
		cout << presentNode << ' ';
		
		for (int i = n; i > 0; i--)
			if (visitedDFS[i] == 0 && graph[presentNode][i] == 1) {
				st.push(i);
			}
	}
	cout << '\n';
}

void run() {
	cin >> n >> m >> start;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graph[a][b] = 1;
		graph[b][a] = 1;
	}
	
	DFS();
	BFS();
}
*/