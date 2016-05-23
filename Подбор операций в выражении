# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* Подсчёт значения выражения при выбранном наборе операторов */
int calc(int* nums, char* operators, int nums_count) {
    int result = nums[0];
    int i;
    for (i = 1; i < nums_count; i++) {
        if (operators[i - 1] == '+') {
            result += nums[i];
        } else {
            result -= nums[i];
        }
    }
    return result;
}

/* Распечатать выражение с выбранным набоором операторов */
int print_expr(int* nums, char* operators, int nums_count) {
    int i;
    printf("%i", nums[0]);
    for (i = 1; i < nums_count; i++) {
        printf("%c%i", operators[i - 1], nums[i]);
    }
    printf("\n");
}

/* Заполнить массив от begin до end плюсами */
void reset(char* begin, char* end) {
    while (begin < end) {
        *begin = '+';
        begin++;
    }
}

/* Следующая перестановка в массиве операторов */
/* Возращает значение, указывающее, завершёна ли генерация перестановок*/
int next_perm(char* operators, int count) {
    int i;
    /* Ищем самый правый + */
    for (i = count - 1; i >= 0; i--) {
        if (operators[i] == '+') break;
    }
    /* Если его нет, то всё, алгоритм закончен */
    if (i == -1) return 0;
    /* Если есть, то делаем его минусом */
    operators[i] = '-';
    /* И зануляем всё после него */
    reset(operators + i + 1, operators + count);
    return 1;
}

int main() {
    /* Чиселки */
    int* nums;
    /* Операторы */
    char* operators;
    /*  Искомое число, колв-во цифр, итерационная переменная, есть ли ещё перестановка, результат выражения */
    int required_number, nums_count, i, perm_exists, res;

    scanf("%i", &nums_count);

    nums = (int*) malloc(sizeof(int) * nums_count);
    operators = (char*) malloc(sizeof(char) * nums_count - 1);

    for (i = 0; i < nums_count; i++) {
        scanf("%i", &nums[i]);
    }

    reset(operators, operators + nums_count - 1);

    scanf("%i", &required_number);

    /* Делаем, пока */
    do {
        res = calc(nums, operators, nums_count);
        print_expr(nums, operators, nums_count);
        printf("%i\n", res);
        /* Либо не сойдётся результат */
        if (res == required_number) break;
        perm_exists = next_perm(operators, nums_count - 1);
    } while (perm_exists); /* Либо не кончатся пеестановки */

    if (res == required_number) {
        print_expr(nums, operators, nums_count);
    } else {
        printf("IMPOSSIBLE\n");
    }

    free(operators);
    free(nums);
    return 0;
}
