#include "test_helpers.h"
#include "core/image.h"

TEST_CASE(test_image_creation) {
    Image* img = image_create(100, 100, IMAGE_TYPE_RGB);
    ASSERT_NOT_NULL(img);
    ASSERT_EQUAL(img->width, 100);
    ASSERT_EQUAL(img->height, 100);
    ASSERT_EQUAL(img->channels, 3);
    image_free(img);
    return true;
}

TEST_CASE(test_image_clone) {
    TestFixtures* fixtures = create_test_fixtures();
    Image* clone = image_clone(fixtures->test_image_rgb);

    ASSERT_NOT_NULL(clone);
    ASSERT_IMAGE_EQUAL(clone, fixtures->test_image_rgb);

    image_free(clone);
    destroy_test_fixtures(fixtures);
    return true;
}

TEST_CASE(test_image_validate) {
    Image* img = image_create(100, 100, IMAGE_TYPE_RGB);
    ASSERT(image_validate(img));

    img->width = 0;
    ASSERT(!image_validate(img));

    image_free(img);
    return true;
}

TEST_CASE(test_image_compare) {
    TestFixtures* fixtures = create_test_fixtures();
    Image* img1 = fixtures->test_image_rgb;
    Image* img2 = image_clone(img1);

    ASSERT_IMAGE_EQUAL(img1, img2);

    // Modify one pixel and ensure images are different
    uint8_t* pixel = image_pixel_at(img2, 0, 0);
    *pixel = 0xFF;
    ASSERT(!image_compare(img1, img2));

    image_free(img2);
    destroy_test_fixtures(fixtures);
    return true;
}