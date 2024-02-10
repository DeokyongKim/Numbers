#include <iostream>
#include <algorithm>

using namespace std;

int n, maxPay;
pair<int, int> work[20]; // first: t, second: p

void payday(int day, int pay) {
	if (day == n) {
		if (maxPay < pay)
			maxPay = pay;
		return;
	}
	
	if (day + work[day].first <= n) payday(day + work[day].first, pay + work[day].second);
	payday(day+1, pay);
}

int run() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> work[i].first >> work[i].second;
	
	payday(0, 0);
	
	cout << maxPay << '\n';
	
	return 0;
}