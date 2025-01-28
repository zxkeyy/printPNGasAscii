#include "test_helpers.h"
#include <stdlib.h>

// Declaration of test cases
TEST_CASE(test_image_load_valid_file);
TEST_CASE(test_image_load_invalid_file);
TEST_CASE(test_image_load_unsupported_format);
TEST_CASE(test_image_load_correct_type);

int main() {
    printf("=== Image Loader Tests ===\n");
    
    RUN_TEST(test_image_load_valid_file);
    RUN_TEST(test_image_load_invalid_file);
    RUN_TEST(test_image_load_unsupported_format);
    RUN_TEST(test_image_load_correct_type);
    
    printf("Tests run: %u\n", tests_run);
    printf("Tests failed: %u\n", tests_failed);
    
    return tests_failed == 0 ? 0 : 1;
}