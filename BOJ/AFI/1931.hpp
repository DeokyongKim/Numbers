// Silver

// Way 3 : Using greedy algorithm in different way
// Result : Success
#include <iostream>
#include <algorithm>

using namespace std;

int n, ans = 0;

pair<int, int> meetings[100010];

bool comp(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second)
		return a.first < b.first;
	return a.second < b.second;
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++)
		cin >> meetings[i].first >> meetings[i].second;
	
	sort(meetings, meetings + n, comp);
	
	int j;
	for (int i = 0; i < n; ) {
		for (j = i+1; j < n; j++)
			if (meetings[i].second <= meetings[j].first) break;
		i = j;
		ans++;
	}
	
	// for (int i = 0; i < n; i++)
	// 	cout << meetings[i].first << ' ' << meetings[i].second << '\n';
	
	cout << ans << '\n';
	
	return 0;
}

// // Way 2 : Brute force
// // Result : Memory over
// #include <iostream>
// #include <algorithm>
// #include <queue>

// using namespace std;

// typedef struct _triple {
// 	int first;
// 	int second;
// 	int third;
// } triple;

// int n = 0, ans = 0;
// pair<int, int> meetings[100010];
// queue<triple> q;

// bool comp(pair<int, int> a, pair<int, int> b) {
// 	if (a.first == b.first) return a.second < b.second;
// 	return a.first < b.first;
// }

// int run() {
// 	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
// 	cin >> n;
	
// 	for (int i = 0; i < n; i++)
// 		cin >> meetings[i].first >> meetings[i].second;
	
// 	sort(meetings, meetings + n, comp);
	
// 	for (int i = 0; i < n; i++) q.push({meetings[i].first, meetings[i].second, 1});
	
// 	while (!q.empty()) {
// 		triple front = q.front();
// 		q.pop();
				
// 		if (front.second > meetings[n-1].first) {
// 			if (ans < front.third) ans = front.third;
// 			continue;
// 		}
		
// 		int pivot = meetings[n-1].second, flag = 0;
// 		for (int i = 0; i < n; i++) 
// 			if (meetings[i].first >= front.second && pivot >= meetings[i].first) {
// 				if (!flag) {
// 					flag = 1;
// 					pivot = meetings[i].second;
// 				}
// 				q.push({meetings[i].first, meetings[i].second, front.third + 1});
// 			}
// 	}
	
// 	cout << ans << '\n';
	
// 	return 0;
// }


// // Way 1 : Using greedy algorithm
// // Result : Fail
// #include <iostream>
// #include <algorithm>

// using namespace std;

// int n;

// typedef struct _triple {
// 	int first;	// start
// 	int second;	// end
// 	int third;	// term
// } triple;

// triple meetings[100010];

// bool comp(triple a, triple b) {
// 	if (a.third == b.third) {
// 		if (a.second == b.second)
// 			return a.first < b.first;
// 		return a.second < b.second;
// 	}
// 	return a.third < b.third;
// }

// int run() {
// 	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
// 	cin >> n;
	
// 	for (int i = 0; i < n; i++) {
// 		cin >> meetings[i].first >> meetings[i].second;
// 		meetings[i].third = meetings[i].second - meetings[i].first;
// 	}
	
// 	sort(meetings, meetings + n, comp);
	
// 	int pivot = 0, end = meetings[n-1].first, ans = 0;
	
// 	while (pivot < end) {
// 		for (int i = 0; i < n; i++) {
// 			if (meetings[i].first >= pivot) {
// 				ans++;
// 				pivot = meetings[i].second;
// 				// cout << meetings[i].first << ' ' << meetings[i].second << '\n';
// 				break;
// 			}
// 		}
// 	}
	
// 	// for (int i = 0; i < n; i++)
// 	// 	cout << meetings[i].first << ' ' << meetings[i].second << '\n';
	
// 	cout << ans << '\n';
	
// 	return 0;
// }