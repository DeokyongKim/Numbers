#include <iostream>

using namespace std;

int n, m, q, t[210], map[210][210];

void dijkstra(int from, int to) {
	
}

int run() {
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) cin >> t[i];
	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		map[from][to] = weight;
		map[to][from] = weight;
	}
	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 1) t[b] += c;
		if (a == 2) dijkstra(b, c);
	}
}