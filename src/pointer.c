#include "pointer.h"

int crash_assert_ptr_equal(__APARAMS, char *exp_arg, char *val_arg, void *exp,
                           void *val)
{
    if (val == exp)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` wasn't equal to `%s`", val_arg,
                exp_arg);
        println("  Expected: %p\n", exp);
        println("  Actual:   %p\n", val);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

int crash_assert_ptr_notequal(__APARAMS, char *exp_arg, char *val_arg,
                              void *exp, void *val)
{
    if (val != exp)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` was equal to `%s`", val_arg, exp_arg);
        println("  Unexpected: %p\n", val);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

int crash_assert_ptr_null(__APARAMS, char *val_arg, void *val)
{
    if (val == NULL)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` wasn't null", val_arg, exp_arg);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}
