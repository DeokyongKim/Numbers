#include <iostream>

using namespace std;

int n, m, ans;
// int arr[200010][200010];
int arr[100][100];
int p = 1000000007;

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int from, to;
		cin >> from >> to;
		arr[from][to] = 1;
		arr[to][from] = 1;
	}
	
	return 0;
}

// This problem is about...

// get the number of ways that have different length

// but then {1}, {2} is out of rule!

// brute force? maybe... but it can be too many
