// Silver

#include <iostream>

using namespace std;

int memo[50] = {0, }, did[50] = {0, }, cnt0[50] = {0, }, cnt1[50] = {0, };

void cleaning() {
	for (int i = 0; i < 45; i++) {
		memo[i] = 0;
		did[i] = 0;
		cnt0[i] = 0;
		cnt1[i] = 0;
	}
}

int fibo(int a) {
	if (did[a] > 0) {
		return memo[a];
	}
	
	if (a == 0) {
		cnt0[a]++;
		memo[a] = 0;
		did[a] = 1;
		return memo[a];
	}
	if (a == 1) {
		cnt1[a]++;
		memo[a] = 1;
		did[a] = 1;
		return memo[a];
	}
	
	did[a] = 1;
	memo[a] = fibo(a-1) + fibo(a-2);
	cnt0[a] += cnt0[a-1] + cnt0[a-2];
	cnt1[a] += cnt1[a-1] + cnt1[a-2];
	return memo[a];
}

void run() {
	int t;
	cin >> t;
	
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		
		cleaning();
		
		fibo(n);
		cout << cnt0[n] << ' ' << cnt1[n] << '\n'; 
	}
}



/* out of time


int cnt0 = 0, cnt1 = 0;

void cleaning() {
	cnt0 = 0;
	cnt1 = 0;
}

int fibonacci(int n) {
    if (n == 0) {
		cnt0++;
        return 0;
    } else if (n == 1) {
		cnt1++;
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

void run() {
	int t;
	cin >> t;
	
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		
		cleaning();
		
		fibonacci(n);
		
		cout << cnt0 << ' ' << cnt1 << '\n';
	}
}

*/