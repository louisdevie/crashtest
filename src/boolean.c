#include "boolean.h"

uint8_t crash_assert_true(__APARAMS, char *val_arg, bool val)
{
    if (val)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` was false", val_arg);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

uint8_t crash_assert_false(__APARAMS, char *val_arg, bool val)
{
    if (!val)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` was true", val_arg);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}