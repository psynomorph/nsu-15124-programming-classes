# include <stdio.h>

# define N 8 // Количество строк
# define M 8 // Количество столбцов

// Направления движения
# define RIGHT 1 // Вправо
# define DOWN 2  // Вниз
# define LEFT 3  // Влево
# define UP 4    // Вверх

int main() {
	
	int matrix[N][M];      // Собственно матрица

	int left_col  = 0;     // Текущий левый столбец
	int right_col = M - 1; // Текущий правый столбец
	
	int up_row    = 0;     // Текущая верхняя строка
	int down_row  = N - 1; // Текущая нижняя строка
	
	int value     = 0;     // Значение элемента
	int direction = RIGHT; // Направление движения
	
	int i = 0, j = 0;      // Итерационные переменные
	
	while (value < M * N) { // Пока следующий элемент не сравняет с произведением размерностей матрицы
		
		// Выбор направления движения
		switch (direction) {
			
			// Если вправо
			case RIGHT:
				// Заполняем верхнюю строку слева направо
				for (i = left_col; i <= right_col; i++) {
					matrix[up_row][i] = value++;
				}
				direction = DOWN; // Следующее направление движения вниз
				up_row++; // Свигаем текущую верхнюю строку вниз
				break;
				
			// Если вниз
			case DOWN:
				// Заполняем правый столбец сверху вниз
				for (i = up_row; i <= down_row; i++) {
				    matrix[i][right_col] =  value++;	
				}
				direction = LEFT; // Следующее направление движения влево
				right_col--; // Сдвигаем влево правый столбец
				break;
				
			// Если влево
			case LEFT:
				// Заполняем нижнюю строку справа налево
				for (i = right_col; i >= left_col; i--) {
					matrix[down_row][i] = value++;
				}
				direction = UP; // Следующее направление заполнение вверх
				down_row--; // Сдвигаем нижнюю строку вверх
				break;
			
			// Если вверх	
			case UP:
				// Заполняем левый столбец сверху вниз
				for (i = down_row; i >= up_row; i--) {
					matrix[i][left_col] = value++;
				}
				direction = RIGHT; // Следующее направление движения вправо
				left_col++;  // Сдвигаем левы столбец вправо
				break;
		}
	}
	
	// Красиво выводим матрицу
	for (i = 0; i < N; i++) {
		for (j =  0; j < M; j++) {
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
