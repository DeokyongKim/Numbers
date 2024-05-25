// Silver

#include <iostream>
#include <algorithm>

using namespace std;

int n;
long long int m, tree[1000010];

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) cin >> tree[i];
	
	sort(tree, tree+n);
	
	int start = 0, end = tree[n-1];
	
	while(start+1 != end) {
		int mid = (start + end) / 2;
		
		long long int sum = 0;
		
		for (int i = n-1; i >= 0; i--) {
			if (tree[i] > mid) sum += (tree[i]-mid);
			else break;
		}
		
		if (sum >= m) start = mid;
		else end = mid;
	}
	
	cout << (start+end)/2 << '\n';
	
	return 0;
}