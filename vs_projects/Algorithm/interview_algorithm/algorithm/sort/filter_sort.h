#include<stdio.h>

int solve() {

	int m;
	
	while (~scanf_s("%d", &m)) {
		int filterArray[1001] = {};
		while (m) {
			int x = 0;
			scanf_s("%d", &x);
			filterArray[x] = 1;
			m--;
		}

		for (int j = 0; j < 1001; j++) {
			if (filterArray[j] == 1) {
				printf("%d\n", j);
			}
		}
	}
	
	return 0;
}