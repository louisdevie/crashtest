#include "crash.h"

void crash_display_test(__CTX, char *name, int result)
{
    __crash_print_indent(__ctx)
}

void crash_push_suite(__CTX, char *name) {}

void crash_pop_suite(__CTX) {}

void crash_init(__CTX) {}

void crash_display_summary(__CTX) {}

int crash_assert_true(__APARAMS, char *val_arg, bool val) {}

int crash_assert_false(__APARAMS, char *val_arg, bool val) {}

int crash_assert_equal(__APARAMS, char *exp_arg, char *val_arg, intmax_t exp,
                       intmax_t val)
{
}

int crash_assert_notequal(__APARAMS, char *exp_arg, char *val_arg, intmax_t exp,
                          intmax_t val)
{
}

int crash_assert_almost(__APARAMS, char *exp_arg, char *val_arg,
                        long double exp, long double val)
{
}

int crash_assert_notalmost(__APARAMS, char *exp_arg, char *val_arg,
                           long double exp, long double val)
{
}

int crash_assert_ptr_equal(__APARAMS, char *exp_arg, char *val_arg, void *exp,
                           void *val)
{
}

int crash_assert_ptr_notequal(__APARAMS, char *exp_arg, char *val_arg,
                              void *exp, void *val)
{
}

int crash_assert_ptr_null(__APARAMS, char *val_arg, void *val) {}

int crash_assert_same(__APARAMS, char *exp_arg, char *val_arg, char *exp,
                      char *val)
{
}

int crash_assert_diff(__APARAMS, char *exp_arg, char *val_arg, char *exp,
                      char *val)
{
}

int crash_assert_memory(__APARAMS, char *exp_arg, char *val_arg, void *exp,
                        void *val, size_t size)
{
}

int crash_skip_test(__APARAMS) {}

int crash_user_error(__APARAMS, const char *format, ...) {}

void crash_user_message(__APARAMS, int level, const char *format, ...) {}

void __crash_print_indent(__CTX)
{
    for (int i = 0; i < __ctx->depth; i++)
    {
        printf("  ");
    }
}