#include "myLog.h"

void initialize_log_file() {
    const char* filename = FILE_NAME;
    FILE *file = fopen(filename, "w"); // Открываем файл для записи, что удаляет его содержимое, если он существует
    if (file) {
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for writing\n");
    }
}

void log_to_file(const char* format, ...) {
    FILE *file = fopen("output.log", "a"); // Открываем файл для добавления
    if (file) {
        va_list args;
        va_start(args, format);
        vfprintf(file, format, args); // Записываем в файл
        va_end(args);
        fclose(file);
    }
}