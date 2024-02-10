// Silver

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int n, max = -5000, min = 5000, sum = 0, howMany[8010] = {0, }, mid, howmax = -1;
	vector<int> arr, forSort, mostMany;
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
		forSort.push_back(tmp);
		
		if (max < tmp) max = tmp;
		if (min > tmp) min = tmp;
		
		sum += tmp;
		howMany[tmp + 4000]++;
	}
	
	sort(forSort.begin(), forSort.end());
	mid = forSort[(n-1)/2];
	
	int mean = (int)floor((float)((float)sum / (float)n) + 0.5);
	
	for (int i = min; i <= max; i++) 
		if (howmax < howMany[i + 4000]) {
			howmax = howMany[i + 4000];
		}
	
	for (int i = min; i <= max; i++) {
		if (howmax == howMany[i + 4000]) {
			mostMany.push_back(i);
		}
	}
	sort(mostMany.begin(), mostMany.end());
	
	int choi;
	if (mostMany.size() == 1) choi = mostMany.back();
	else choi = mostMany[1];
	
	cout << mean << '\n' << mid << '\n' << choi << '\n' << max-min << '\n';
}