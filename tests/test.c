#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <cmocka.h>

#include "arguments.h"
#include "oscillator.h"
#include "parser.h"


void test_getopt_config() {
    char* argv[] = {"test", "abcde"};
    struct ProcessOptions options = parse_command_line(2, argv);
    assert_non_null(options.command);
    assert_string_equal(options.command, argv[1]);
    assert_string_equal(options.output_filename, "out.wav");
}


void test_getopt_config_with_file() {
    char* argv[] = {"test", "-o", "test.wav", "abcde"};
    struct ProcessOptions options = parse_command_line(4, argv);
    assert_non_null(options.command);
    assert_string_equal(options.command, argv[3]);
    assert_string_equal(options.output_filename, argv[2]);
}


void test_new_buffer() {
    Buffer buffer = newBufferWithMS(1000);
    assert_non_null(buffer.data);
    assert_true(SAMPLE_RATE == buffer.length);
    deleteBuffer(&buffer);
    fprintf(stderr, "%p", buffer.data);
    assert_null(buffer.data);
    assert_true(0 == buffer.length);
}


void test_new_buffer_with_frames() {
    Buffer buffer = newBufferWithFrames(1024);
    assert_non_null(buffer.data);
    assert_true(1024 == buffer.length);
    deleteBuffer(&buffer);
    assert_null(buffer.data);
    assert_true(0 == buffer.length);
}


void test_new_oscillator() {
    BufferOperation oscillator = newSinusOscillator();
    assert_non_null(oscillator.wave.data);
    assert_true(1024 == oscillator.wave.length);

    assert_true(0.0 == oscillator.wave.data[0]);
    assert_true(1.0 == oscillator.wave.data[256]);
    assert_true(-0.01 < oscillator.wave.data[512]);
    assert_true( 0.01 > oscillator.wave.data[512]);
    assert_true(-1.0 == oscillator.wave.data[768]);

    deleteOscillator(&oscillator);
    assert_null(oscillator.wave.data);
    assert_true(0 == oscillator.wave.length);
}


void check_single_default_operation(BufferOperation *operations) {
    assert_true(operations != NULL);
    assert_true(operations[0].wave.data != NULL);
    assert_true(operations[0].length_in_ms == 1000);
    assert_true(operations[0].delete != NULL);
    assert_true(operations[0].render != NULL);

    // there should only be one operation
    assert_true(operations[1].render == NULL);
    free(operations);
}


void test_parser_with_oscillators() {
    check_single_default_operation(parse("SI1000"));
    check_single_default_operation(parse("SQ1000"));
    check_single_default_operation(parse("SQ1000a"));
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_parser_with_oscillators),
    cmocka_unit_test(test_getopt_config),
    cmocka_unit_test(test_new_oscillator),
    cmocka_unit_test(test_new_buffer_with_frames),
    cmocka_unit_test(test_new_buffer),
    cmocka_unit_test(test_getopt_config_with_file)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
