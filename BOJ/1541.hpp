// Silver

#include <iostream>
#include <string>

using namespace std;
 
int main() {
    string str;
    cin >> str;
 
    int ans = 0;
    string num;
    bool flag = false;
 
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == '-' || str[i] == '+' || i == str.size()) {
            if (flag) {
                ans -= stoi(num);
                num = "";
            }
            else {
                ans += stoi(num);
                num = "";
            }
        }
        else num += str[i];
        if (str[i] == '-') flag = true;
    }
    
    cout << ans;
}


/* This problem says my logic is wrong... BUT SAME LOGIC!!!!!!
#include <iostream>

using namespace std;

void run() {
	char str[60], expressions[60];
	cin >> str;
	
	int index = 0, numbers[60];
	for (int i = 0; str[i] != '\0'; i++) {
		int num = 0;
		for(; str[i] != '+' && str[i] != '-' && str[i] != '\0'; i++) {
			num *= 10;
			num += str[i] - '0';
		}
		numbers[index] = num;
		if (str[i] != '\0') expressions[index] = str[i];
		index++;
	}
	index--;
	
	// cout << index << '\n';
	// for (int i =0 ; i < index; i++) cout << i << '\t'; cout << '\n';
	// for (int i =0 ; i < index; i++) cout << numbers[i] << '\t'; cout << '\n';
	// for (int i =0 ; i < index; i++) cout << expressions[i] << '\t'; cout << '\n';
	
	// // after '-', just sum all numbers
	int minusSum = 0, plusSum = numbers[0];
	for (int i = 1; i < index; i++) {
		if (expressions[i-1] == '-') {
			for (; i < index; i++)
				minusSum += numbers[i];
		}
		else if (expressions[i-1] == '+') {
			plusSum += numbers[i];
			cout << numbers[i] << '\n';
		}
	}
	
	cout << plusSum - minusSum << '\n';
}
*/