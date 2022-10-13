#include "integer.h"

uint8_t crash_assert_equal(__APARAMS, char *exp_arg, char *val_arg,
                           uint8_t size, intmax_t exp, intmax_t val)
{
    if (val == exp)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` wasn't equal to `%s`", val_arg,
                exp_arg);

        char *exp_repr;
        char *val_repr;
        switch (size)
        {
        case 1:
            exp_repr = __crash_repr_char(exp);
            val_repr = __crash_repr_char(val);
            break;
        case 2:
            exp_repr = __crash_repr_short(exp);
            val_repr = __crash_repr_short(val);
            break;
        case 3:
            exp_repr = __crash_repr_int(exp);
            val_repr = __crash_repr_int(val);
            break;
        default:
            exp_repr = __crash_repr_long(exp);
            val_repr = __crash_repr_long(val);
            break;
        }
        println("  Expected: %s\n", exp_repr);
        println("  Actual:   %s\n", val_repr);
        free(exp_repr);
        free(val_repr);

        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

uint8_t crash_assert_notequal(__APARAMS, char *exp_arg, char *val_arg,
                              uint8_t size, intmax_t exp, intmax_t val)
{
    if (val != exp)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` was equal to `%s`", val_arg, exp_arg);

        char *val_repr;
        switch (size)
        {
        case 1:
            val_repr = __crash_repr_char(val);
            break;
        case 2:
            val_repr = __crash_repr_short(val);
            break;
        case 3:
            val_repr = __crash_repr_int(val);
            break;
        default:
            val_repr = __crash_repr_long(val);
            break;
        }
        println("  Unexpected: %s\n", val_repr);
        free(val_repr);

        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

char *__crash_repr_char(intmax_t n)
{
    char *str;

    if (0 <= n && n < 128)
    {
        if (32 <= n && n < 127)
        {
            __asprintf(&str, "%d (0x%02X, ‘%c’)", n, n & 0xffl, (char)n);
        }
        else
        {
            char escape = 0;
            if (n == 0)
            {
                escape = '0';
            }
            else if (n == 7)
            {
                escape = 'a';
            }
            else if (n == 8)
            {
                escape = 'b';
            }
            else if (n == 9)
            {
                escape = 't';
            }
            else if (n == 10)
            {
                escape = 'n';
            }
            else if (n == 11)
            {
                escape = 'v';
            }
            else if (n == 12)
            {
                escape = 'f';
            }
            else if (n == 13)
            {
                escape = 'r';
            }

            if (escape)
            {
                __asprintf(&str, "%d (0x%02X, ‘\\%c’)", n, n & 0xffl, escape);
            }
            else
            {
                __asprintf(&str, "%d (0x%02X)", n, n & 0xffl);
            }
        }
    }
    else
    {
        __asprintf(&str, "%d (0x%02X)", n, n & 0xffl);
    }

    return str;
}

char *__crash_repr_short(intmax_t n)
{
    char *str;

    __asprintf(&str, "%d (0x%04X)", n, n & 0xffffl);

    return str;
}

char *__crash_repr_int(intmax_t n)
{
    char *str;

    __asprintf(&str, "%d (0x%08X)", n, n & 0xffffffffl);

    return str;
}

char *__crash_repr_long(intmax_t n)
{
    char *str;

    __asprintf(&str, "%d (0x%016X)", n, n);

    return str;
}