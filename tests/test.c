#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <arguments.h>

void test_getopt_config()
{
}


int main(void)
{
  const UnitTest tests[] = {
    unit_test(test_getopt_config)
  };

  return run_tests(tests);
}
