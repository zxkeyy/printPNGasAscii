#include "test_helpers.h"
#include "io/image_loader.h"

TestFixtures* create_test_fixtures() {
    TestFixtures* fixtures = malloc(sizeof(TestFixtures));
    fixtures->test_image_rgb = image_create(64, 64, IMAGE_TYPE_RGB);
    fixtures->test_image_grayscale = image_create(64, 64, IMAGE_TYPE_GRAY);
    // Initialize with test patterns
    return fixtures;
}

void destroy_test_fixtures(TestFixtures* fixtures) {
    if (!fixtures) return;
    image_free(fixtures->test_image_rgb);
    image_free(fixtures->test_image_grayscale);
    free(fixtures);
}