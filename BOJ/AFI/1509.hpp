// Gold

// https://mangu.tistory.com/78

#include <iostream>
#include <string>

using namespace std;

bool palin[2510][2510];
int dp[2510];

int run() {
    string s; 
	cin >> s;
	
    int n = s.size();
	
	// 0부터 시작하게 조정
    s = " " + s;
	
	// Is palindrom?
    for (int i = 1; i <= n; i++) palin[i][i] = true;
    for (int i = 1; i < n; i++) palin[i][i + 1] = (s[i] == s[i + 1]);
    for (int j = 2; j < n; j++) {
        for (int i = 1; i + j <= n; i++) {
            if (s[i] == s[i + j] && palin[i + 1][i + j - 1]) palin[i][i + j] = 1;
        }
    }
	
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1987654321;
        for (int j = 1; j <= i; j++) {
            if (palin[j][i]) dp[i] = min(dp[i], dp[j - 1] + 1);
        }
    }
    cout << dp[n];
}

/*
#include <iostream>
#include <string>
#include <map>

using namespace std;

string str;

int dp[2600];

void getPalindrom(int start, int end, int color) {	
	while (true) {		
		bool did = false;
		
		if (start-1 >= 0 && end+1 < str.length()) {
			if (str[start-1] == str[end+1]) {
				did = true;
				dp[start-1] = color;
				dp[end+1] = color;
				start--;
				end++;
			}
		}
		
		if (!did) break;
	}
}

int run() {
	cin >> str;
		
	int stopper = 0;
	
	int kind = 0;
	map<string, int> m;
	while(stopper<20) {
		stopper++;
				
		bool did = false;
		for (int i = 1; i < str.length()-1; i++) {
			if (dp[i] > 0) {
				int color = dp[i];
				int start = i;
				for (; dp[i]>0; i++);
				i--;
				int end = i;
				if (start-1 >= 0 && end+1 < str.length()) 
					if (str[start-1] == str[end+1]) {
					getPalindrom(start, end, color);
					did = true;
					}
			} else {
				if (str[i-1] == str[i+1]) {
					did = true;
					
					string tmp = str.substr(i-1, i+2);
					
					if (m.find(tmp) != m.end()) {
						// Exist
						int tmpColor = m[tmp];
						dp[i] = tmpColor;
						getPalindrom(i, i, tmpColor);
					} else {
						// Nonexistence
						kind++;
						dp[i] = kind;
						getPalindrom(i, i, kind);
						m[tmp] = kind;
					}
					
				}
			}
		}
				
		if (!did) break;
	}
	
	int ans = 0;
	for (int i = 0; i < str.length(); i++) {
		if (dp[i] == 0) ans++;
		else {
			ans++;
			int col = dp[i];
			for (; dp[i] == col; i++);
			i--;
		}
	}
	
	cout << ans << '\n';
	
	for (int i = 0; i < str.length(); i++)
		cout << str[i];
	cout << '\n';
	
	for (int i = 0; i < str.length(); i++)
		cout << dp[i];
	cout << '\n';
	
	return 0;
}
*/