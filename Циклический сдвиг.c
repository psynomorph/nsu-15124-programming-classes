# include <stdio.h>
# include <stdlib.h>

# define N 10

int ABS(int x) {
    if (x > 0) {
	   return x; 	
	} else {
		return -x;
	} 
}

int SGN(x) {
	return x/abs(x);
}

void print_array(int* arr, int s) {
    int i = 0;
    for (i = 0; i < s; i++) {
	    printf("%i ", arr[i]);	
	}
	printf("\n");
}

void shift_right(int* arr, int s) {
    int i, t = arr[s - 1];
    for (i = s - 1; i > 0; i--) {
	    arr[i] = arr[i-1];
	}
	arr[0] = t;
}

void shift_left(int* arr, int s) {
    int i, t = arr[0];
    for (i = 0; i < s - 1; i++) {
	    arr[i] = arr[i + 1];	
	}
	arr[s - 1] = t;
}

int main() {
    int arr[N], n, i, n_sgn;
    for (i = 0; i < N; i++) {
	    arr[i] = rand() % 100;	
	}
	print_array(arr, N);
	scanf("%i", &n);
	n_sgn = SGN(n);
	n = ABS(n);
	for (i = 0; i < n; i++) {
	    if (n_sgn == 1) {
		    shift_right(arr, N);	
		} else {
		    shift_left(arr, N);	
		}
	}
	print_array(arr, N);
	return 0;
}
