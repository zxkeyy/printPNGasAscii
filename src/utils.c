#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

// Global error handler function pointer
static void (*g_error_handler)(const char *) = default_error_handler;

// Default error handler implementation
void default_error_handler(const char *error_message) {
    fprintf(stderr, "Error: %s\n", error_message);
    exit(EXIT_FAILURE);
}

// Set custom error handler
void set_error_handler(void (*handler)(const char *)) {
    g_error_handler = handler ? handler : default_error_handler;
}

// Logging function implementation
void log_message(LogLevel level, const char *message, ...) {
    const char *level_strings[] = {
        "ERROR", 
        "WARNING", 
        "INFO", 
        "DEBUG"
    };
    
    // Check if level is within valid range
    if (level < LOG_ERROR || level > LOG_DEBUG) {
        g_error_handler("Invalid log level");
        return;
    }
    
    va_list args;
    va_start(args, message);
    
    // Print log message with level
    fprintf(stderr, "[%s] ", level_strings[level]);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    
    va_end(args);
}

// Check if file exists
int file_exists(const char *filename) {
    if (!filename) {
        g_error_handler("Null filename provided");
        return 0;
    }
    
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Get file size
long get_file_size(const char *filename) {
    if (!filename) {
        g_error_handler("Null filename provided");
        return -1;
    }
    
    struct stat buffer;
    if (stat(filename, &buffer) != 0) {
        g_error_handler("Unable to get file size");
        return -1;
    }
    
    return buffer.st_size;
}

// Create directory
int create_directory(const char *path) {
    if (!path) {
        g_error_handler("Null path provided");
        return -1;
    }
    
    // Mode 0755: rwxr-xr-x 
    // Owner can read, write, execute
    // Group and others can read and execute
    int result = mkdir(path, 0755);
    
    if (result != 0 && errno != EEXIST) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Failed to create directory: %s", path);
        g_error_handler(error_msg);
        return -1;
    }
    
    return 0;
}

// Safe memory allocation wrappers
void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        g_error_handler("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* safe_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        g_error_handler("Memory reallocation failed");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

// String duplication with error checking
char* string_duplicate(const char *str) {
    if (!str) {
        g_error_handler("Null string provided for duplication");
        return NULL;
    }
    
    char *new_str = strdup(str);
    if (!new_str) {
        g_error_handler("String duplication failed");
        return NULL;
    }
    
    return new_str;
}

// Trim whitespace from a string
char* trim_whitespace(char *str) {
    if (!str) {
        g_error_handler("Null string provided");
        return NULL;
    }
    
    // Trim leading whitespace
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n')) {
        str++;
    }
    
    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end = '\0';
        end--;
    }
    
    return str;
}

// Get current time (seconds with microsecond precision)
double get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

// Sleep for specified milliseconds
void sleep_milliseconds(int milliseconds) {
    if (milliseconds < 0) {
        g_error_handler("Negative sleep duration");
        return;
    }
    
    // Use usleep for microsecond precision sleep
    usleep(milliseconds * 1000);
}

// Print progress bar
void print_progress_bar(double progress, int width) {
    // Validate inputs
    if (progress < 0.0) progress = 0.0;
    if (progress > 1.0) progress = 1.0;
    if (width <= 0) width = 50;  // Default width
    
    int filled_width = (int)(progress * width);
    
    printf("[");
    for (int i = 0; i < width; i++) {
        if (i < filled_width) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %.1f%%\r", progress * 100.0);
    fflush(stdout);
}