#include <iostream>
#include <math.h>

using namespace std;

int n, board[25][25], minAns = 1987654321;

void solve(int idx, int st[], int stIdx, int li[], int liIdx) {
	if (idx == n) {
		int stRank = 0, liRank = 0;
		for (int i = 0; i < n/2; i++)
			for (int j = 0; j < n/2; j++) {
				if (i != j) {
					stRank += board[st[i]][st[j]];
				}
			}

		for (int i = 0; i < n/2; i++)
			for (int j = 0; j < n/2; j++) {
				if (i != j) {
					liRank += board[li[i]][li[j]];
				}
			}

		int sub = abs(stRank-liRank);

		// cout << "=============\n";
		// for (int i = 0;i < n/2; i++) cout << st[i] << ' ' ;
		// cout << '\n';
		// for (int i = 0;i < n/2; i++) cout << li[i] << ' ' ;
		// cout << '\n';
		// cout << sub << '\n';
		
		if (minAns > sub) minAns = sub;

		return;
	}

	int copySt[25], copyLi[25];
	for (int i = 0; i < n/2; i++) {
		copySt[i] = st[i];
		copyLi[i] = li[i];
	}

	// idx man is start team
	if (stIdx < n/2) {
		copySt[stIdx] = idx;
		solve(idx+1, copySt, stIdx+1, copyLi, liIdx);
		copySt[stIdx] = 0;
	}
	// idx man is link team
	if (liIdx < n/2) {
		copyLi[liIdx] = idx;
		solve(idx+1, copySt, stIdx, copyLi, liIdx+1);
		copyLi[liIdx] = 0;
	}
}

int arr1[25], arr2[25];
int run() {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> board[i][j];

	solve(0, arr1, 0, arr2, 0);

	cout << minAns <<'\n';

	return 0;
}