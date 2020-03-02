#include <stdio.h>

int main() {
	int n;
	int k;
	scanf("%d %d", &n, &k);
	int *a = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", a[(i + k) % n]);
	}

	return 0;
}
