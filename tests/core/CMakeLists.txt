add_executable(test_core test_runner.c test_image.c)
target_link_libraries(test_core printAsciiLib test_helpers m)
add_test(NAME core_tests COMMAND test_core)