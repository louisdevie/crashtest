#include "user.h"

int crash_skip_test(__APARAMS, const char *fmt, ...)
{
    if (fmt[0] == 0)
    {
        println("Test ignored");
    }
    else
    {
        va_list args;
        va_start(args, fmt);

        char *msg;
        vasprintf(&msg, fmt, args);

        va_end(args);

        println("Test ignored: %s", msg);

        free(msg);
    }
    println("  (%s, line %d)", file, line);
}

void crash_user_message(__APARAMS, int level, const char *format, ...)
{
    va_list args;
    va_start(args, fmt);

    char *msg;
    vasprintf(&msg, fmt, args);

    va_end(args);

    switch (level)
    {
    case CRASH_TEST_ERROR:
        println("Error: %s", msg);
        break;
    case CRASH_TEST_WARNING:
        println("Warning: %s", msg);
        break;
    case CRASH_TEST_INFO:
        println("Info: %s", msg);
        break;
    }

    free(msg);

    println("  (%s, line %d)", file, line);
}
