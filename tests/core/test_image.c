#include "test_helpers.h"
#include "core/image.h"

TEST_CASE(test_image_creation) {
    Image* img = image_create(100, 100, IMAGE_TYPE_RGB);
    ASSERT_NOT_NULL(img);
    ASSERT_EQUAL(img->width, 100);
    ASSERT_EQUAL(img->channels, 3);
    image_free(img);
    return true;
}

TEST_CASE(test_image_clone) {
    TestFixtures* fixtures = create_test_fixtures();
    Image* clone = image_clone(fixtures->test_image_rgb);
    ASSERT_IMAGE_EQUAL(clone, fixtures->test_image_rgb);
    image_free(clone);
    destroy_test_fixtures(fixtures);
    return true;
}