#include <iostream>

using namespace std;

int n, m;
int visited[110] = {0, };
int graph[110][110];

void dfs(int a) {
	visited[a] = 1;
	
	for (int i = 1; i <= n; i++)
		if (graph[a][i] && !visited[i])
			dfs(i);
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int tmp1, tmp2;
		
		cin >> tmp1 >> tmp2;
		
		graph[tmp1][tmp2] = 1;
		graph[tmp2][tmp1] = 1;
	}
	
	dfs(1);
	
	int ans = 0;
	for (int i = 1; i <= n; i++) ans += visited[i];
	
	cout << --ans << '\n';
	
	return 0;
}