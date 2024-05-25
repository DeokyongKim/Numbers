// Gold

// https://kangminjun.tistory.com/entry/BOJ-1208%EB%B2%88-%EB%B6%80%EB%B6%84%EC%88%98%EC%97%B4%EC%9D%98-%ED%95%A9-2

// Sometimes, partial solution can be a solution for all.

#include <iostream>
#include <map>

using namespace std;

int n, s;
int digits[50];

map<int, int> leftMap;

long long int ans;

void leftSolve(int now, int index) {
	if (index == n/2) {
		leftMap[now] += 1;
		return;
	}
	
	leftSolve(now, index+1);
	leftSolve(now + digits[index], index+1);
}

void rightSolve(int now, int index) {
	if (index == n) {
		if (leftMap[s-now] > 0) ans += leftMap[s-now];
		else if (now == s) ans+=1;
		return;
	}
	
	rightSolve(now, index+1);
	rightSolve(now + digits[index], index+1);
}

int run() {
	cin >> n >> s;
	for (int i = 0; i < n; i++) cin >> digits[i];
	
	bool add = false;
	leftSolve(0, 0);
	rightSolve(0, n/2);
	
	if (s==0) ans-=1;
	
	cout << ans << '\n';
	
	return 0;
}

/* Timeout
#include <iostream>

#define MIN -1987654321

using namespace std;

int n, s;
int digits[50];

int ans;

void solve(int now, int index, bool flag) {
	if (index == n) {
		if (now == s && flag)
			ans++;
		return;
	}
	
	solve(now + digits[index], index+1, true);
	solve(now, index+1, flag);
}

int run() {
	cin >> n >> s;
	for (int i = 0; i < n; i++) cin >> digits[i];
	
	bool add = false;
	solve(0, 0, add);
	
	cout << ans << '\n';
	
	return 0;
}
*/