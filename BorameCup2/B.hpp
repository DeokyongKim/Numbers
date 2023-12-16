#include <iostream>
#include <algorithm>

using namespace std;

long long int n, m, p, arr[510];
bool possible = true;

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> p;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> arr[j];
		
		sort(arr, arr+m);
		
		// cout << '\n';
				
		long long int floor = m;
		while(floor > 0) {
			bool win = false;
			
			for (int j = 0; j < m; j++) {
				if (arr[j] >= 0 && p >= arr[j]) {
					p += arr[j];
					arr[j] = -2;
					win = true;
					floor--;
					break;
				}
			}
			
			for (int j = 0; j < m; j++) {
				if (!win && arr[j] == -1) {
					arr[j] = -2;
					p *= 2;
					floor--;
					win = true;
					break;
				}
			}
			
			if (win == false) {
				possible = false;
				cout << 0 << '\n';
				return 0;
			}
			
			// for (int j = 0; j < m; j++) cout << arr[j] << ' ';
			// cout << " : " << p;
			// cout << '\n';
		}
	}
	
	if (possible) cout << 1 << '\n';
	
	return 0;
}