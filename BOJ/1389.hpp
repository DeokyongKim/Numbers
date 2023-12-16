// Silver

#include <iostream>
#include <queue>

using namespace std;

int n, m, map[5010][5010], visited[5010], answer[5010];

void cleanVisited() {for (int i = 0; i <= n; i++) visited[i] = 0;}

void BFS(int start) {
	cleanVisited();
	
	queue<int> q;
	
	q.push(start);
	visited[start] = 1;
	
	while(!q.empty()) {
		int presentNode = q.front();
		q.pop();
		
		for (int i = 1; i <= n; i++) 
			if (visited[i] == 0 && map[presentNode][i] == 1) {
				q.push(i);
				visited[i] = visited[presentNode] + 1;
			}
	}
	
	for (int i = 1; i <= n; i++)
		answer[start] += visited[i];
	answer[start] -= 1;
}

int findMin() {
	int min = 1987654321, ans;
	
	for (int i = 1; i <= n; i++)
		if (answer[i] < min) {
			min = answer[i];
			ans = i;
		}
	return ans;
}

void run() {
	
	cin >> n >> m;
	for (int i =0 ; i < m; i++) {
		int a, b;
		cin >> a >> b;
		map[a][b] = 1;
		map[b][a] = 1;
	}
	
	for (int i = 1; i <= n; i++) BFS(i);
	
	cout << findMin() << '\n';
}