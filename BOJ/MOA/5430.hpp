// Gold

#include <iostream>
#include<algorithm>
#include <string>

using namespace std;

void AC() {
	string p, arr;
	int n, digits[100010];
	bool front = true;
	
	cin >> p >> n >> arr;
	
	int sum = 0, index = 0;
	for (int i = 0; i < arr.size(); i++) {
		if ('0' <= arr[i] && arr[i] <= '9'){
			for (; !(arr[i] == '[' || arr[i] == ']' || arr[i] == ','); i++) {
				sum *= 10;
				sum += arr[i] - '0';
			}
			i--;
		}
		else if (arr[i] == ',' || arr[i] == ']') {
			digits[index++] = sum;
			sum = 0;
		}
	}
		
// 	for (int i = 0; i < n; i++) cout << digits[i] << ' ';
// 	cout << '\n' << index << '\n';
	
	int start = 0, end = n;
	
	for (int i = 0; p[i]; i++) {
		if (p[i] == 'R') front = !front;
		if (p[i] == 'D') {
			if (start >= end) {
				cout << "error" << '\n';
				return;
			}
			
			if (front) start++;
			else end--;
		}
		
	}
		
	cout << '[';
	if (front) 
		for (int i = start; i < end; i++) {
			if (i != end-1) cout << digits[i] << ',';
			else cout << digits[i];
		}
	else
		for (int i = end-1; i >= start; i--) {
			if (i != start) cout << digits[i] << ',';
			else cout << digits[i];
		}
	cout << ']' << '\n';
}

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) AC();
	
	return 0;
}