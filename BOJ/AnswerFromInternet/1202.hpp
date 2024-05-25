// Gold

// https://jaimemin.tistory.com/760

#include <iostream>
#include <algorithm>
#include <queue>

#define pii pair<int, int>
// first : weight, second : value

using namespace std;

int n, k;

pii jewel[300010];

int bag[300010];

long long int ans;

priority_queue<int> pq;

int run() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> jewel[i].first >> jewel[i].second;
	for (int i = 0; i < k; i++) cin >> bag[i];
	
	sort(jewel, jewel+n);
	sort(bag, bag+k);
	
	int idx = 0;
	for (int i = 0; i < k; i++) {
		while (idx < n && jewel[idx].first <= bag[i])
			pq.push(jewel[idx++].second);
		if (!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}
	
	cout << ans << '\n';
	
	return 0;
}