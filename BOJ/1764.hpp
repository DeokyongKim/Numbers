// Silver

#include <cstdio>
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> dict;

int run() {
	ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	int n, m, ans = 0;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		dict[tmp]++;
	}
	
	for (int i = 0; i < m; i++) {
		string tmp;
		cin >> tmp;
		dict[tmp]++;
	}
	
	for (map<string, int>::iterator i = dict.begin(); i != dict.end(); i++)
		if (i -> second > 1) 
			ans++;
	
	cout << ans << '\n';
	for (map<string, int>::iterator i = dict.begin(); i != dict.end(); i++)
		if (i -> second > 1) 
			cout << i -> first << '\n';
	
	return 0;
}