# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# define true 1
# define false 0

typedef char bool;

int main() {
	int i, n, n_sqrt, j;
	bool *er;
	
	scanf("%d", &n);
	n++;
	er = (bool*) malloc(sizeof(bool) * n);
	
	for (i = 2; i < n; i++) {
		er[i] = 1;
	}
	er[0] = er[1] = 0;
	
	n_sqrt = (int) sqrt((double) n);
	
	for (i = 2; i <= n_sqrt; i++) {
		if (er[i]) {
		    for (j = i + 1; j < n; j++) {
				if (j % i == 0 && er[j] != 0) {
				    er[j] = 0;	
				}
			}	
		}
	}
	
	for (i = 2; i < n; i++)  {
		if (er[i])
			printf("%d ", i);
	}
	printf("\n");
	return 0;
}
