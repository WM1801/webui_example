#include <stdio.h>
#include <stdarg.h>

#define FILE_NAME "output.log"
// создает или очищает файл для лога 
void initialize_log_file(); 
// добавляет строку в файл 
void log_to_file(const char* format, ...); 