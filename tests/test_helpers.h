#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <core/image.h>

// ======================
// Core Assertions
// ======================
#define TEST_CASE(name) bool name(void)
#define RUN_TEST(name) do { \
    printf("Testing %-30s", #name); \
    fflush(stdout); \
    if (name()) { \
        printf("[PASS]\n"); \
    } else { \
        printf("[FAIL]\n"); \
        tests_failed++; \
    } \
    tests_run++; \
} while(0)

// Test tracking variables
extern unsigned tests_run;
extern unsigned tests_failed;

#define ASSERT(cond) \
    if (!(cond)) { \
        fprintf(stderr, "\n  FAIL: %s:%d %s\n", __FILE__, __LINE__, #cond); \
        return false; \
    }

#define ASSERT_EQUAL(a, b) ASSERT((a) == (b))
#define ASSERT_NOT_NULL(p) ASSERT((p) != NULL)
#define ASSERT_NULL(p) ASSERT((p) == NULL)

// ======================
// Image-Specific Assertions
// ======================
#define ASSERT_IMAGE_EQUAL(a, b) ASSERT(image_compare(a, b))

// ======================
// Fixture Management
// ======================
typedef struct {
    Image* test_image_rgb;
    Image* test_image_grayscale;
} TestFixtures;

TestFixtures* create_test_fixtures();
void destroy_test_fixtures(TestFixtures* fixtures);