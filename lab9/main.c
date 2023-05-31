
// Вариант 24
// Дан текстовый файл f, состоящий из нескольких строк. Переписать в файл g все
// строки файла f с заменой в них символа ‘0’ на символ ‘1’ и наоборот. Переписывать
// только строки, где произведена хотя бы одна замена. В конце строки разместить через
// пробел два числа: количество замен символа ‘0’ на символ ‘1’ и количество замен
// символа ‘1’ на символ ‘0’


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000


//функция открытия входного файла
FILE* openInputFile(const char *filename) { 
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printf("file opening error\n");
        exit(1);
    }
    return f;
}


//функция создания выходного файла
FILE* createOutputFile(const char *filename) { 
    FILE *g = fopen(filename, "w+");

    if (g == NULL) {
        printf("file creating error\n");
        exit(1);
    }
    return g;
}


//функция изменения строки и записи в файл
void replaceChars(char *line, FILE* g) {
    int len = strlen(line);
    int count_0_to_1 = 0;
    int count_1_to_0 = 0;
    for (int i = 0; i < len; i++) {
        if (line[i] == '0') {
            line[i] = '1';
            count_0_to_1++;
        } else if (line[i] == '1') {
            line[i] = '0';
            count_1_to_0++;
        }
    }
    //удаляем символ перевода строки для корректного вывода
    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    if (count_0_to_1 > 0 || count_1_to_0 > 0) {
        fprintf(g, "%s %d %d\n", line, count_0_to_1, count_1_to_0);
    }
}

//чтение и вызов функций
void reading(char* line, FILE* f, FILE* g) {
    while (fgets(line, MAX_LINE_LENGTH, f) != NULL) {
        replaceChars(line, g);
    }
}


int main() {
    FILE *f, *g;
    f = openInputFile("f.txt");
    g = createOutputFile("g.txt");


    char line[MAX_LINE_LENGTH];

    reading(line, f, g);

    //закртие файлов
    fclose(f);
    fclose(g);

    return 0;
}
