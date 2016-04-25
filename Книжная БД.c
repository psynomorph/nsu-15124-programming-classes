/*
     Предупреждаю сразу, писал для себя, потому здесь есть черная магия
*/

# include <stdlib.h>
# include <stdio.h>
# include <locale.h>
# include <string.h>

# define MAX_STRING_LENGTH 256
# define EXPANDING_STEP 5
# define forever while (1)
# define delns(s) (s[strlen(s)-1] = '\0')
# define input(...) printf("<< "); scanf(__VA_ARGS__);
# define output(...) printf(">> "  __VA_ARGS__);
# define db_not_loaded_error() printf("!! База данных ещё не выбрана!\n");

typedef struct _Book {
	unsigned int id;
	char title[MAX_STRING_LENGTH];
	char author[MAX_STRING_LENGTH];
	char ganre[MAX_STRING_LENGTH];
} Book;

typedef struct _BookDB {
	Book* books;
	int count;
	int _allocated_for;
	int saved;
} BookDB;

int id_cmp(const void* a, const void* b) {
	return ((Book*)a)->id - ((Book*)b)->id;
}

int author_cmp(const void* a, const void* b) {
	return strcmp(((Book*)a)->author, ((Book*)b)->author);
}

int title_cmp(const void* a, const void* b) {
	return strcmp(((Book*)a)->title, ((Book*)b)->title);
}

int ganre_cmp(const void* a, const void* b) {
	return strcmp(((Book*)a)->ganre, ((Book*)b)->ganre);
}
/* Создать базу данных */
BookDB* create_db(int size) {
	BookDB *db = (BookDB*) malloc(sizeof(BookDB));
	db->_allocated_for = size;
	db->count = 0;
	db->books = NULL;
	if (size > 0) {
		db->books = (Book*) malloc(sizeof(Book) * size);
		int i;
		for (i = 0; i < size; i++) {
			db->books[i].id = -1;
		}
	}
	db->saved = 0;
	return db;
}

/* Загрузить БД из файла */
BookDB* load_db(char* filename) {
	FILE* fin = fopen(filename, "r");
	if (!fin) return 0;
	int n = 0;
	fscanf(fin, "%d", &n);
	getc(fin); 
	BookDB* db = create_db(n);
	db->count = n;
	if (n > 0) {
		Book *book, *end;
		for (book = db->books, end = db->books + n; book < end; book++) {
			fscanf(fin, "%d", &(book->id)); getc(fin);
			fgets(book->title, MAX_STRING_LENGTH, fin); delns(book->title);
			fgets(book->author, MAX_STRING_LENGTH, fin); delns(book->author);
			fgets(book->ganre, MAX_STRING_LENGTH, fin); delns(book->ganre);
		}
	}
	db->saved = 1;
	fclose(fin);
	return db;
}
/* Сохранить БД в файл */
void save_db(char* filename, BookDB* db) {
	FILE* fout = fopen(filename, "w");
	fprintf(fout, "%d\n", db->count);
	Book *book, *end;
	for (book = db->books, end = db->books + db->count;  book < end; book++) {
		fprintf(fout, "%d\n", book->id);
		fprintf(fout, "%s\n", book->title);
		fprintf(fout, "%s\n", book->author);
		fprintf(fout, "%s\n", book->ganre);
	}
	db->saved = 1;
	fclose(fout);
}
/* Диалог сохранения БД*/
void save_db_dialog(BookDB* db, char* filename) {
	char tmp[MAX_STRING_LENGTH];
	if (filename[0]) {
		output("Имя файла базы данных [%s]\n", filename);
		input("%s", tmp);
		if (strlen(tmp) > 0) {
			strcpy(filename, tmp);
		} 
	} else {
		do {
			output("Имя файла базы данных\n");
			input("%s", filename);
		} while (strlen(filename) < 1);
	}
	save_db(filename, db);
}

/* Закрывает базу данных */
void close_db(BookDB* db, char* filename) {
	if (!db->saved) {
		output("База данных не сохранена. Желаете сохранить? (yes/no)\n");
		char answer[MAX_STRING_LENGTH];
		input("%s", answer);
		if (!strcmp(answer, "y") || !strcmp(answer, "yes")) {
			save_db_dialog(db, filename);
		}
	}
	free(db);
}
/* Распечатать информацию о книге */
void print_book(Book* book) {
	printf("####################################################\n");
	printf("Книга номер: %d\n", book->id);
	printf("Название: %s\n", book->title);
	printf("Автор: %s\n", book->author);
	printf("Жанр: %s\n", book->ganre);
	printf("####################################################\n");
}
/* Распечатать содержимое БД */
void list_db(BookDB* db) {
	Book *book, *end;
	for (book = db->books, end = db->books + db->count; book < end; book++) {
		print_book(book);
	}
}
/* Получить книгу по её номеру */
Book* get_by_id(BookDB* db, int id) {
	Book *book, *end;
	for (book = db->books, end = db->books + db->count; book < end; book++) {
		if (book->id == id)
			return book;
	}
	return NULL;
}
/* Удалить книгу */
void delete_book(BookDB* db, Book* book) {
	while (++book < db->books + db->count) {
		*(book-1) = *book;
	}
	db->count--;
}
/* Диалог удаления */
void delete_dialog(BookDB* db) {
	int id;
	output("Введите номер книги\n");
	input("%i", &id);
	Book *book = get_by_id(db, id);
	if (!book) {
		output("Книга с id: %d не найдена!\n", id);
		return; 
	}
	output("Вы точно хотите удалить книгу %s? (yes/no)\n", book->title);
	char answer[MAX_STRING_LENGTH];
	input("%s", answer);
	if (!strcmp(answer, "y") || !strcmp(answer, "yes")) {
		delete_book(db, book);
		db->saved = 0;
		output("Книга удалена!\n");
	}
}
/* Создать книгу */
Book* new_book(BookDB* db) {
	if (db->count == db->_allocated_for) {
		Book* old_ptr = db->books;
		if ((db->books = (Book*) realloc(old_ptr, (db->count + EXPANDING_STEP) * sizeof(Book))) != NULL) {
			db->_allocated_for++;
		} else {
			printf("!! Не удалось выделить память под новую запись!\n");
			db->books = old_ptr;
			return NULL;
		}
	}
	return db->books + (db->count++);
}
/* Диалог создания записи о книге */
void new_dialog(BookDB* db) {
	Book* book =  new_book(db);
	int id;
	if (!book) return;
	output("Введите данные новой книги\n");
	output("ID: \n");
	input("%d", &id);
	getc(stdin);
	book->id = id;
	output("Название\n<< ");
	fgets(book->title, MAX_STRING_LENGTH, stdin); delns(book->title);
	output("Автор\n<< ");
	fgets(book->author, MAX_STRING_LENGTH, stdin); delns(book->author);
	output("Жанр\n<< ");
	fgets(book->ganre, MAX_STRING_LENGTH, stdin); delns(book->ganre);
	db->saved = 0;
}
/* Распечатать справку */
void print_help() {
	output("Библиотечная база данных V0.0001\n");
	printf("Маркер <! обозначает, что программа ждёт ввода команды из нижеприведённого списка\n");
	printf("С помощью маркера << программа демонстрирует, что ждёт пользовательского ввода\n");
	printf("С помащью маркера >> программа выделяет свой вывод, а спомощью !! предупреждения!\n");
	printf("Список используемых комманд:\n");
	printf("\t%s\n", "create - создать бызу данных");
	printf("\t%s\n", "load - загрузить базу из файла");
	printf("\t%s\n", "close - закрыть базу данных");
	printf("\t%s\n", "save - сохранить базу данных в файл");
	printf("\t%s\n", "size - отобразить размер базы данных");
	printf("\t%s\n", "list - распечатать базу данных");
	printf("\t%s\n", "new - добавить книгу в базу данных");
	printf("\t%s\n", "delete - удалить книгу из базы данных");
	printf("\t%s\n", "find - найти книгу в базе данных");
	printf("\t%s\n", "sort - отсортировать базу данных");
	printf("\t%s\n", "exit - завершить программу");
}
/* Диалог поиска */
void find_dialog(BookDB* db) {
	# define FIELD(s) if(!strcmp(#s, field)) 
	char field[MAX_STRING_LENGTH];
	output("По какому полю будем искать?\n");
	printf("\t%s\n", "id - номер книги в каталоге");
	printf("\t%s\n", "title - название");
	printf("\t%s\n", "author - имя автора");
	printf("\t%s\n", "ganre - жанр");
	input("%s", field);
	getc(stdin);
	
	FIELD(id) {
		int id;
		output("Введите номер книги\n<< ");
		input("%d", &id);
		getc(stdin);
		Book* book = get_by_id(db, id);
		if (book) {
			print_book(book);
		} else {
			output("Книги с таким номером не найдено!\n");
		}
		return;
	}
	
	Book *book, *end;
	
	FIELD(title) {
		output("Название книги\n<< ");
		fgets(field, MAX_STRING_LENGTH, stdin);
		delns(field);
		for (book = db->books, end = db->books + db->count; book < end; book++) {
			if (!(strcmp(field, book->title)))
				print_book(book);
		}
		return;
	}
	
	FIELD(ganre) {
		output("Жанр книги\n<< ");
		fgets(field, MAX_STRING_LENGTH, stdin);
		delns(field);
		for (book = db->books, end = db->books + db->count; book < end; book++) {
			if (!(strcmp(field, book->ganre)))
				print_book(book);
		}
		return;
	}
	
	FIELD(author) {
		output("Автор книги\n<< ");
		fgets(field, MAX_STRING_LENGTH, stdin);
		delns(field);
		for (book = db->books, end = db->books + db->count; book < end; book++) {
			if (!(strcmp(field, book->author)))
				print_book(book);
		}
		return;
	}
	
	printf("!! Неизвестная поле для поиска \"%s\"\n", field);
	# undef FIELD
}
/* Диалог сортировки */
void sort_dialog(BookDB* db) {
	# define FIELD(s) if(!strcmp(#s, field)) 
	char field[MAX_STRING_LENGTH];
	output("По какому полю будем сортировать?\n");
	printf("\t%s\n", "id - номер книги в каталоге");
	printf("\t%s\n", "title - название");
	printf("\t%s\n", "author - имя автора");
	printf("\t%s\n", "ganre - жанр");
	input("%s", field);
	getc(stdin);
	
	FIELD(id) {
		qsort(db->books, db->count, sizeof(Book), id_cmp);
		db->saved = 0;
		return;
	}
	
	FIELD(title) {
		qsort(db->books, db->count, sizeof(Book), title_cmp);
		db->saved = 0;
		return;
	}
	
	FIELD(author) {
		qsort(db->books, db->count, sizeof(Book), author_cmp);
		db->saved = 0;
		return;
	}
	
	FIELD(ganre) {
		qsort(db->books, db->count, sizeof(Book), ganre_cmp);
		db->saved = 0;
		return;
	}
	
	printf("!! Неизвестная поле для сортировки \"%s\"\n", field);
	# undef FIELD
}
/* Привествие */
void print_hello() {
	output("Вас приветствует библиотечная база данных V0.0001\n");
	output("Для получения помощи введите help\n");
}
/* Основная функция */
int main() {
	# define ACTION(str) if (!strcmp(#str, action))
	setlocale(LC_ALL, "Ru");
	BookDB* db = NULL;
	char filename[MAX_STRING_LENGTH] = "\0";
	char action[MAX_STRING_LENGTH];
	print_hello();
	/* Цикл обработки событий */
	forever {
		printf("<! ");
		scanf("%s", action);
		
		ACTION(help) {
			print_help();
			continue;
		}
		
		ACTION(exit) {
			if (db) {
				close_db(db, filename);
				db = NULL;
				filename[0] = '\0';
			}
			break;
		}
		
		ACTION(close) {
			if (db) {
				close_db(db, filename);
				db = NULL;
				filename[0] = '\0';
				output("База данных закрыта!\n");
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(create) {
			if (db) {
				close_db(db, filename);
				filename[0] = '\0';
				db = NULL;
			}
			int n = 0;
			output("Предполагаемая размерность Базы Данных\n");
			input("%d", &n);
			db = create_db(n);
			output("База данных для %i элементов создана!\n", n);
			continue;
		}
		
		ACTION(load) {
			if (db) {
				close_db(db, filename);
				filename[0] = '\0';
				db = NULL;
			}
			do {
				output("Имя файла базы данных\n");
				input("%s", filename);
			} while (strlen(filename) < 1);
			db = load_db(filename);
			if (!db) {
				output("Неверное имя файла!\n");
				filename[0] = '\0';
			} else {
				output(">> База данных успешно загружена!\n");
			}
			continue;
		}
		
		ACTION(save) {
			if (db) {
				save_db_dialog(db, filename);
				output(">> База данных успешно сохранена!\n");
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(list) {
			if (db != 0) {
				list_db(db);
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(find) {
			if (db) {
				find_dialog(db);
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(new) {
			if (db) {
				new_dialog(db);
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(delete) {
			if (db) {
				delete_dialog(db);
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(size) {
			if (db) {
				output("Книг в базе данных - %d\n", db->count);
			} else db_not_loaded_error();
			continue;
		}
		
		ACTION(sort) {
			if (db) {
				sort_dialog(db);
			} else db_not_loaded_error();
			continue;
		}
		
		printf("!! Неизвестная команда \"%s\"\n", action);
	}
	# undef ACTION
	return 0;
}
