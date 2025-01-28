#include "test_helpers.h"
#include <stdlib.h>

// Declaration of test cases
TEST_CASE(test_image_creation);
TEST_CASE(test_image_clone);
TEST_CASE(test_image_validate);
TEST_CASE(test_image_compare);

int main() {
    printf("=== Image Core Tests ===\n");
    
    RUN_TEST(test_image_creation);
    RUN_TEST(test_image_clone);
    RUN_TEST(test_image_validate);
    RUN_TEST(test_image_compare);
    
    printf("\nResults: %u/%u passed\n", 
           tests_run - tests_failed, tests_run);
    
    return tests_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}