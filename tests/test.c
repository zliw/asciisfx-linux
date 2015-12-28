#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "arguments.h"
#include "playback.h"
#include "buffer.h"

void test_getopt_config() {
    char* argv[] = {"test", "abcde"};
    struct ProcessOptions options = parse_command_line(2, argv);
    assert_non_null(options.command);
    assert_string_equal(options.command, argv[1]);
}

void test_new_buffer() {
    struct Buffer buffer = newBufferWithMS(1000);
    assert_non_null(buffer.data);
    assert_true(SAMPLE_RATE == buffer.length);
    deleteBuffer(&buffer);
    fprintf(stderr, "%p", buffer.data);
    assert_null(buffer.data);
    assert_true(0 == buffer.length);
}

int main(void) {
  const UnitTest tests[] = {
    unit_test(test_getopt_config),
    unit_test(test_new_buffer)
  };

  return run_tests(tests);
}
