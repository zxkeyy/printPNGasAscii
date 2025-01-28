#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <core/image.h>

// ======================
// Core Assertions
// ======================
#define TEST_CASE(name) void name()
#define RUN_TEST(name) do { \
    printf("Running %-40s", #name); \
    if (name()) printf("[PASS]\n"); \
    else printf("[FAIL]\n"); \
} while(0)

#define ASSERT(cond) \
    if (!(cond)) { \
        fprintf(stderr, "\n  Assertion failed: %s:%d %s\n", __FILE__, __LINE__, #cond); \
        return false; \
    }

#define ASSERT_EQUAL(a, b) ASSERT((a) == (b))
#define ASSERT_NOT_NULL(p) ASSERT((p) != NULL)
#define ASSERT_NULL(p) ASSERT((p) == NULL)

// ======================
// Image-Specific Assertions
// ======================
static inline bool images_equal(const Image* a, const Image* b) {
    if (!a || !b) return false;
    return a->width == b->width &&
           a->height == b->height &&
           a->channels == b->channels &&
           memcmp(a->pixels, b->pixels, a->width * a->height * a->channels) == 0;
}

#define ASSERT_IMAGE_EQUAL(a, b) ASSERT(images_equal(a, b))

// ======================
// Fixture Management
// ======================
typedef struct {
    Image* test_image_rgb;
    Image* test_image_grayscale;
} TestFixtures;

TestFixtures* create_test_fixtures();
void destroy_test_fixtures(TestFixtures* fixtures);