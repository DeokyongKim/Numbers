// Gold

// using bitmask
// https://velog.io/@brol2/BOJ-1562%EB%B2%88-%EA%B3%84%EB%8B%A8-%EC%88%98

#include <iostream>
#include <memory.h>

using namespace std;

long long int n, ans;

long long int dp[110][11][(1<<10) + 1]; // [now][lastNum][visit]
	
long long int capsule(int start, int visit, int lastNum, int end) {
	if (start == end-1) {
		if (visit == 1023) {
			return 1;
		}
		return 0;
	}
	
	if (dp[start][lastNum][visit] != -1) return dp[start][lastNum][visit];
	dp[start][lastNum][visit] = 0;
	
	if (lastNum-1 >= 0) {
		dp[start][lastNum][visit] += capsule(start+1, (1<<(lastNum-1)) | visit, lastNum-1, end);
	}
	if (lastNum+1 < 10) {
		dp[start][lastNum][visit] += capsule(start+1, (1<<(lastNum+1)) | visit, lastNum+1, end);
	}
	
	return dp[start][lastNum][visit]%=1000000000;
}

void cleaning() {
	memset(dp, -1, sizeof(dp));
}

void stairNum(int end) {
	cleaning();
	
	for (int i = 1; i < 10; i++) {
		ans += capsule(0, (1<<i), i, end);
	}
}

int run() {
	cin >> n;

	for (int i = 1; i <= 40; i++)
	stairNum(i);
	
	cout << ans << '\n';
	
	return 0;
}


/* bottom-up : timeover
#include <iostream>

using namespace std;

int n, ans;

int stairNum(int now, int lastNum, int visit[]) {
	if (now == 0) {
		for (int i = 0; i < 10; i++)
			if (visit[i] == 0) return 0;
		return 1;
	}
	
	int a = 0, b = 0;
	int cache = visit[lastNum];
	visit[lastNum] = 1;
	if (lastNum-1 >= 0 && !(now-1==1 && lastNum-1==0))
		a = stairNum(now-1, lastNum-1, visit);
	if (lastNum+1 < 10) 
		b = stairNum(now-1, lastNum+1, visit);
	visit[lastNum] = cache;
	
	return a + b;
}



int run() {
	cin >> n;
	
	for (int i = 0; i < 10; i++) {
		int tmp[11] = {0, };
		ans += stairNum(n, i, tmp);
		ans %= 1000000000;
	}
	
	cout << ans << '\n';
	
	return 0;
}
*/

/* timeover
#include <iostream>

using namespace std;

int n, ans;

void capsule(int start, int visit[], int lastNum, int end) {
	if (start == end) {
		for (int i = 0; i < 10; i++)
			if (visit[i] == 0) return;
		ans = (ans+1)%1000000000;
		return;
	}
	
	if (lastNum-1 >= 0) {
		int cache = visit[lastNum-1];
		visit[lastNum-1] = 1;
		capsule(start+1, visit, lastNum-1, end);
		visit[lastNum-1] = cache;
	}
	if (lastNum+1 < 10) {
		int cache = visit[lastNum+1];
		visit[lastNum+1] = 1;
		capsule(start+1, visit, lastNum+1, end);
		visit[lastNum+1] = cache;
	}
}

void stairNum(int end) {
	for (int i = 1; i < 10; i++) {
		int tmp[11] = {0, };
		tmp[i] = 1;
		capsule(1, tmp, i, end);
		tmp[i] = 0;
	}
}

int run() {
	cin >> n;

	stairNum(n);
	
	cout << ans%1000000000 << '\n';
	
	return 0;
}
*/