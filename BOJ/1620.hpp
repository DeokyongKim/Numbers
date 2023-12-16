// Silver

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
	int n, m;
	
	cin >> n >> m;
	
	map<string, int> pokemon_for_name;
	vector<string> pokemon_for_index(100001);
	
	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		
		pokemon_for_name[tmp] = i+1;
		pokemon_for_index[i] = tmp;
	}
	
	for (int i = 0; i < m; i++) {
		string tmp;
		cin >> tmp;
		if ('1' <= tmp[0] && tmp[0] <= '9') {
			cout << pokemon_for_index[stoi(tmp) - 1] << '\n';
		} else {
			cout << pokemon_for_name[tmp] << '\n';
		}
	}
}

/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool comp(pair a, pair b) {
	return a.second < b.second;
}

void run() {
	int n, m;
	vector<pair<int, string>> pokemon;

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		pair<int, string> tmp;
		cin >> tmp.second;
		tmp.first = i;
		pokemon.push_back(tmp);
	}

	sort(pokemon.begin(), pokemon.end(), comp);

	for (int i = 0; i < n; i++) {
		cout << pokemon[i].second << '\n';
	}
}
*/