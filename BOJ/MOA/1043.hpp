// Gold

#include <iostream>

using namespace std;

int n, m, kn, know[60], ans, invited[60][60]; //invited[partyNum][person]

int run() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> kn;
	
	for (int i = 0; i < kn; i++) {
		int tmp;
		cin >> tmp;
		know[tmp] = 1;
	}
	
	for (int i = 1; i <= m; i++) {
		int tmp;
		cin >> tmp;
		for (int j = 0; j < tmp; j++) {
			int ipt;
			cin >> ipt;
			invited[i][ipt] = 1;
		}
	}
	
	// find group
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			bool recognized = false;
			
			for (int k = 1; k <= n; k++)
				if (invited[j][k] && know[k]) recognized = true;
						
			if (recognized) {
				invited[j][0] = 1;
				for (int k = 1; k <= n; k++)
					if (invited[j][k]) know[k] = 1;
			}
		} 
	
	for (int i = 1; i <= m; i++)
		if (!invited[i][0]) ans++;
	
	cout << ans << '\n';
	
	// cout << '\n';
	// for (int i = 1; i <= m; i++)
	// 	cout << invited[i][0] << '\n';
	
	return 0;
}