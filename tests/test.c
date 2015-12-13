#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "arguments.h"

void test_getopt_config()
{
  const char* argv[] = {"test", "abcde"};
  struct ProcessOptions options = parse_command_line(2, argv);
  assert_non_null(options.command);
  assert_string_equal(options.command, argv[1]);
}

int main(void)
{
  const UnitTest tests[] = {
    unit_test(test_getopt_config)
  };

  return run_tests(tests);
}
