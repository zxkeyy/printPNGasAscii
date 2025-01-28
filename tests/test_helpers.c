#include "test_helpers.h"
#include "io/image_loader.h"

unsigned tests_run = 0;
unsigned tests_failed = 0;

TestFixtures* create_test_fixtures() {
    TestFixtures* fixtures = malloc(sizeof(TestFixtures));
    if (!fixtures) return NULL;

    fixtures->test_image_rgb = image_create(64, 64, IMAGE_TYPE_RGB);
    fixtures->test_image_grayscale = image_create(64, 64, IMAGE_TYPE_GRAY);
    if (!fixtures->test_image_rgb || !fixtures->test_image_grayscale) {
        destroy_test_fixtures(fixtures);
        return NULL;
    }

    // Initialize with test patterns
    memset(fixtures->test_image_rgb->pixels, 0x7F, 
           64 * 64 * 3 * sizeof(uint8_t));
    memset(fixtures->test_image_grayscale->pixels, 0xAA, 
           64 * 64 * sizeof(uint8_t));
    
    return fixtures;
}

void destroy_test_fixtures(TestFixtures* fixtures) {
    if (!fixtures) return;
    image_free(fixtures->test_image_rgb);
    image_free(fixtures->test_image_grayscale);
    free(fixtures);
}