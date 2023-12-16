// Bronze

#include <iostream>
#include <string>

void run() {
	while(true) {
		std::string str;
		std::cin >> str;
		if (str == "0") break;
		
		bool chk = true;
		for (int i = 0; i < (str.length() - str.length()%2) / 2; i++) {
			if (str[i] != str[str.length() - i - 1]) {
				std::cout << "no\n";
				chk = false;
				break;
			}
		}
		if (!chk) continue;
		std::cout << "yes\n";
	}
}