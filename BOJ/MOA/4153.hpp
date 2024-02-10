// Bronze

#include <iostream>

using namespace std;

void run() {
	int a = 1, b = 1, c = 1;
	while(a + b + c) {
		cin >> a >> b >> c;
		if (a + b + c == 0) break;
		
		int arr[5], min = 30010, max = -1;
		arr[0] = a, arr[1] = b, arr[2] = c;
		for (int i =0; i<3; i++) {
			if (min > arr[i]) min = arr[i];
			if (max < arr[i]) max = arr[i];
		}
		int mid = a + b + c - min - max;
		
		if (max*max == mid*mid + min*min) cout << "right\n";
		else cout << "wrong\n";
	}
}