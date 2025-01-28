#include "test_helpers.h"

// Declare test cases
void test_image_creation();
void test_image_clone();

int main() {
    printf("=== Starting Test Suite ===\n");
    
    RUN_TEST(test_image_creation);
    RUN_TEST(test_image_clone);
    
    printf("=== Tests Complete ===\n");
    return 0;
}