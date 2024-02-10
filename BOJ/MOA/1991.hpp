// Silver

#include <iostream>
#include <math.h>

using namespace std;

int n, maxlen;
char tree[70000000];

void front(int now) {	
	cout << tree[now];
	if (tree[now*2] != '.') front(now*2);
	if (tree[now*2+1] != '.') front(now*2+1);
}

void mid(int now) {		
	if (tree[now*2] != '.') mid(now*2);
	cout << tree[now];
	if (tree[now*2+1] != '.') mid(now*2+1);
}

void end(int now) {		
	if (tree[now*2] != '.') end(now*2);
	if (tree[now*2+1] != '.') end(now*2+1);
	cout << tree[now];
}

int run() {
	cin >> n;
	
	int number = pow(2, n);
	
	for (int i = 0; i <= number + 20; i++) tree[i] = '.';
	
	for (int i = 0; i < n; i++) {
		char parent, lchild, rchild;
		cin >> parent >> lchild >> rchild;
		
		int point = 1;
		for (; point <= maxlen; point++)
			if (tree[point] == parent) {
				break;
			}
		
		if (maxlen < point*2 + 1) maxlen = point * 2 + 1;
		tree[point] = parent;
		
		if (lchild != '.') tree[point*2] = lchild;
		if (rchild != '.') tree[point*2+1] = rchild;
	}
	
	front(1);
	cout << '\n';
	mid(1);
	cout << '\n';
	end(1);
	cout << '\n';
	
	return 0;
}