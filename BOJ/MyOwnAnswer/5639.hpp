// Gold

#include <iostream>

using namespace std;

int tree[10010];

void postOrder(int start, int end) {
	int headVal = tree[start], head = start;
	int leftStart = -1, leftEnd = -1, rightStart = -1, rightEnd = -1;
	
	for (int i = start; i < end; i++) {
		if (tree[i] < headVal) {
			if (leftEnd == -1) leftStart = i;
			leftEnd = i+1;
		}
		if (tree[i] > headVal) {
			if (rightEnd == -1) rightStart = i;
			rightEnd = i+1;
		}
	}
	
	if (leftStart != -1 && leftEnd != -1) postOrder(leftStart, leftEnd);
	if (rightStart != -1 && rightEnd != -1) postOrder(rightStart, rightEnd);
	cout << headVal << '\n';
}

int run() {
	int tmp, index = 0;
	while(cin >> tmp) {tree[index++] = tmp;}
	
	postOrder(0, index);
	
	return 0;
}