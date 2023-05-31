
// Вариант 24
// Дан файл f, компоненты которого являются действительными числами. Найти:
// Среднее арифметическое положительных компонент файла f. Записать это значение
// перед первым положительным элементом. Если положительных элементов нет, файл
// не меняется.


#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGHT 1000

//функция открытия файла
FILE* openFile(const char *filename) { 
    FILE *f = fopen(filename, "r+");

    if (f == NULL) {
        printf("file opening error\n");
        exit(1);
    }
    return f;
}

void calculate_average_positive(FILE* f) {

    float sum = 0.0;
    int count = 0;
    float num;
    long pos = ftell(f); //позиция первого положительного
    int positive_found = 0;
    float arr[MAX_LENGHT];
    int len_arr = 0;


    // Читаем компоненты файла и вычисляем сумму и количество положительных чисел
    while (fscanf(f, "%f", &num) == 1) {
        if (num > 0) {
            sum += num;
            count++;

            if (!positive_found) {
                positive_found = 1;
                pos = ftell(f);
            }
        }
        if (positive_found) {
            arr[len_arr] = num;
            len_arr++;
        }
    }

    if (count == 0) {
        printf("there are no positive numbers in the file\n");
        return;
    }

    float average = sum / count;

    // Возвращаемся к началу файла и записываем среднее значение перед первым положительным числом
    fseek(f, pos - 1, SEEK_SET);
    fprintf(f, "%f ", average);
    for (int i = 0; i < len_arr; i++) {
        fprintf(f, "%f ", arr[i]);
    }

}

int main() {
    FILE *f;
    f = openFile("f.txt");


    calculate_average_positive(f);
    //закртие файлов
    fclose(f);

    return 0;
}
