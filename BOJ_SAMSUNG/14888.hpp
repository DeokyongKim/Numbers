// Silver

#include <iostream>

using namespace std;

int n, operatorNum[4], inputNum[15];
int minAns = 1987654321, maxAns = -1987654321;

int calculator(int a, int b, int op) {
	if (op == 0) return a+b;
	if (op == 1) return a-b;
	if (op == 2) return a*b;
	if (op == 3) return a/b;

	return 0;
}

void solve(int idx, int cur, int arr[]) {
	int copyArr[4] = {arr[0], arr[1], arr[2], arr[3]};

	for (int i = 0; i < 4; i++) {
		if (copyArr[i] > 0) {
			copyArr[i]--;
			solve(idx+1, calculator(cur, inputNum[idx+1], i), copyArr);
			copyArr[i]++;
		}
	}

	if (idx == n-1) {
		if (minAns > cur) minAns = cur;
		if (maxAns < cur) maxAns = cur;
		return;
	}
}

int run() {
	cin >> n;

	for (int i = 0; i < n; i++) cin >> inputNum[i];
	for (int i = 0; i < 4; i++) cin >> operatorNum[i];

	solve(0, inputNum[0], operatorNum);

	cout << maxAns << '\n' << minAns << '\n';

	return 0;
}