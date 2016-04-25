# include <stdio.h>
# define N 1024
 
void reverse(FILE*, FILE*);
 
int main() {
    reverse(stdin, stdout);
    printf("\n");
    return 0;
}
 
void reverse(FILE* in, FILE* out) {
    char ch = fgetc(in);
    if (ch == '\n') return;
    reverse(in, out);
    fputc(ch, stdout);
}
