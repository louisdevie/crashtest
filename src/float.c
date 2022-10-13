#include "float.h"

int crash_assert_almost(__APARAMS, char *exp_arg, char *val_arg,
                        long double exp, long double val,
                        const unsigned int prec)
{
    if (__crash_fcmp(val, exp, prec))
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` wasn't equal to `%s`", val_arg,
                exp_arg);
        println("  Expected: %0.*lf\n", prec, exp);
        println("  Actual:   %0.*lf\n", prec, val);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

int crash_assert_notalmost(__APARAMS, char *exp_arg, char *val_arg,
                           long double exp, long double val,
                           const unsigned int prec)
{
    if (!__crash_fcmp(val, exp, prec))
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` wasn't equal to `%s`", val_arg,
                exp_arg);
        println("  Expected: %0.*lf\n", prec, exp);
        println("  Actual:   %0.*lf\n", prec, val);
        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

bool __crash_fcmp(long double x, long double y, unsigned int prec)
{
    unsigned int pow = 1;
    for (; prec > 0; prec--)
    {
        pow *= 10;
    }
    long double epsilon = 1.0l / pow;
    long double delta = x - y;
    return (delta < epsilon) && (-delta < epsilon);
}