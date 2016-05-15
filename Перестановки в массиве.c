# include <stdio.h>

# define N 5
# define false 0
# define true 1

/* Обмен элементов */
void swap(int *i, int *j) {
    int tmp = *i;
    *i = *j;
    *j = tmp;	
}

/* Quick sort */
void _qsort(int* arr, int i, int j) {
	int m = *(arr + (i + j)/2);
	int l = i, r = j;
	do {
	    while (arr[l] < m) l++;
	    while (arr[r] > m) r--;
		swap(&arr[l], &arr[r]);
	    l++; r--;
	} while (l < r);
	if (l < j)
	    _qsort(arr, l, j);
	if (r > i)
		_qsort(arr, i, r);
}

/* Печать массива */
void print_array(int* arr, int s) {
    int i = 0;
    for (i = 0; i < s;  i++) {
	    printf("%i ", arr[i]);	
	}	
	printf("\n");
}

/* Инициализация массива */
void init_array(int* arr, int s) {
	int i;
	for (i = 0; i < s; i++) {
		arr[i] = i + 1;	
	}
}

/* Следуующая перестановка */
int next_permutation(int* arr, int s) {
    int i = 0;
    /* находим такой элемент, что arr[i] < arr[i + 1] */
    for (i = s - 2; i >= 0 && arr[i] > arr[i + 1]; i--); 
    /* Если такого нет, то массив упорядочен в обратном порядке */
    if (i < 0) return false;
    int a_i = i, a_v = arr[i], min_v = arr[i + 1], min_i = i + 1;
    /* Ищем наименьший эллемент, больший чем arr[i] */
    for (i = i + 1; i < s; i++) {
	    if (arr[i] < min_v && a_v < arr[i]) {
		    min_i = i;
		    min_v = arr[i];	
		}
	}
	/* Меняем их местами */
	swap(&arr[a_i], &arr[min_i]);
	/* Сортируем хвост */
	_qsort(arr, a_i + 1, s - 1);
	return true;
}

int main() {
    int arr[N];
    init_array(arr, N);
	print_array(arr, N);
	while (next_permutation(arr, N)) {
	    print_array(arr, N);	
	}
	return 0;
}
