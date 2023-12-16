// UNSOLVED!!

// Bronze

#include <iostream>

void run() {
	char str[1000010];
	int ans = 0;
	
	scanf("%[^\n]s", str);
	
	for (int i = 0; str[i]; i++) {
		if (str[i] != ' ' && str[i] != '\n') {
			ans += 1;
			for (; str[i] != ' '; i++);
		}
	}

	printf("%d\n", ans);
}