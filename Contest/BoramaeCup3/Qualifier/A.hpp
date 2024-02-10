#include <iostream>
#include <math.h>

#define MAX 641

using namespace std;

int n;
char s[5010];

int run() {
	cin >> n;
	cin >> s;
	
	int tmp = 0, ans = 0, exp = 0;
	for (int i = n-1; i >= 0; i--) {
		if (s[i] == '0' && tmp == 0) {
			exp++;
			continue;
		} else if (s[i] == '0') {
			ans++;
			exp = 0;
			tmp = 0;
			continue;
		}
		
		tmp += (s[i] - '0') * pow(10, exp);
		exp++;
		
		if (tmp > MAX) {
			ans++;
			tmp = 0;
			exp = 0;
			i++;
		}
	}
	if (tmp) ans++;
	
	cout << ans << '\n';
	
	return 0;
}