// Silver

#include <iostream>
#include <queue>
using namespace std;

void run() {
	int n;
	queue<int> q;
	cin >> n;
	
	for (int i = 1; i <= n; i++) q.push(i);
	
	while(q.size() > 1) {
		q.pop();
		if(q.size() == 1) break;
		int tmp = q.front();
		q.pop();
		q.push(tmp);
	}
	cout << q.front() << '\n';
}