#include "memory.h"

int crash_assert_memory(__APARAMS, char *exp_arg, char *val_arg, void *exp,
                        void *val, size_t size)
{
    unsigned char exp_array[] = exp;
    unsigned char val_array[] = val;

    bool ok = true;
    size_t offset = 0;
    for (; offset < size; offset++)
    {
        if (exp_array[offset] != val_array[offset])
        {
            ok = false;
            break;
        }
    }

    if (ok)
    {
        return CRASH_TEST_SUCCESS;
    }
    else
    {
        println("Assertion failed: `%s` was different from `%s`", val_arg,
                exp_arg);

        static const char *ELLIPSIS = "... ";
        static const char *PADDING = "    ";
        static const char *NOTHING = "";

        struct __CrashArrayView view;
        char repr[31];

        __crash_array_view(&view, size, offset);
        __crash_display_mem(&view, repr, exp_array);
        println("  Expected: %s%s%s", view.ltrim ? ELLIPSIS : NOTHING, repr,
                view.rtrim ? ELLIPSIS : NOTHING);

        __crash_display_offset(&view, repr, offset);
        println("            %s%s", view.ltrim ? PADDING : NOTHING, repr);

        __crash_display_mem(&view, repr, val_array);
        println("  Actual:   %s%s%s", view.ltrim ? ELLIPSIS : NOTHING, repr,
                view.rtrim ? ELLIPSIS : NOTHING);

        println("  (%s, line %d)", file, line);
        return CRASH_TEST_FAILURE;
    }
}

void __crash_display_mem(struct __CrashArrayView *view, char *buffer,
                         unsigned char *source)
{
    int j = 0;
    for (int i = view->begin; i < view->end; i++)
    {
        sprintf(buffer + j, "%02X ", source[i]);
        j += 3;
    }
    for (; j < 30; j++)
    {
        buffer[j] = ' ';
    }
    buffer[30] = '\0';
}

void __crash_display_mem_offset(struct __CrashArrayView *view, char *buffer,
                                size_t offset)
{
    int j = 0;
    for (int i = view->begin; i < offset; i++)
    {
        sprintf(buffer + j, "   ");
        j += 3;
    }

    sprintf(buffer + j, "~~");
}