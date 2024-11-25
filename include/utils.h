// utils.h
#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include <stdio.h>

// Logging levels
typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

// Logging function
void log_message(LogLevel level, const char *message, ...);

// File utility functions
int file_exists(const char *filename);
long get_file_size(const char *filename);
int create_directory(const char *path);

// Memory allocation wrappers with error checking
void* safe_malloc(size_t size);
void* safe_realloc(void *ptr, size_t size);

// String utility functions
char* string_duplicate(const char *str);
char* trim_whitespace(char *str);

// Performance and timing utilities
double get_current_time();
void sleep_milliseconds(int milliseconds);

// Progress bar for long operations
void print_progress_bar(double progress, int width);

// Error handling
void set_error_handler(void (*handler)(const char *));
void default_error_handler(const char *error_message);

#endif // UTILS_H