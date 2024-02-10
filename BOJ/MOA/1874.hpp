// Silver

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	vector<int> arr, stk;
	vector<char> ans;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	
	int scope = 0, num = 1;
	while(scope < n) {
		if (!stk.empty() && stk.back() == arr[scope]) {
			ans.push_back('-');
			stk.pop_back();
			scope++;
			continue;
		}
		
		for (; num < arr[scope]; num++) {
			ans.push_back('+');
			stk.push_back(num);
		}
		if (num != arr[scope]) {
			printf("NO\n");
			return 0;
		}
		ans.push_back('+');
		stk.push_back(num);
		num++;
		
		ans.push_back('-');
		stk.pop_back();
		scope++;
	}
	
	for(int i = 0; i < ans.size(); i++) printf("%c\n", ans[i]);
}