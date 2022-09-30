#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define CRASH_TEST_SUCCESS 0
#define CRASH_TEST_FAILURE 1
#define CRASH_TEST_SKIPPED 2

/*================================== TYPES ===================================*/

struct CrashTestFrame
{
    char *name;
    struct CrashTestFrame *under;
};

struct CrashTestContext
{
    struct CrashTestFrame *top;
    int depth;

    char *out_buffer;

    int test_count;
    int success_count;
    int skipped_count;
};

#define __CTX struct CrashTestContext *__ctx

/*================================ FUNCTIONS =================================*/

void crash_display_test(__CTX, char *name, int result);
void crash_push_suite(__CTX, char *name);
void crash_pop_suite(__CTX);
void crash_display_summary(__CTX);

#define __APARAMS __CTX, char *file, int line
#define __ARET unsigned char

__ARET crash_assert_true(__APARAMS, char *val_arg, bool val);
__ARET crash_assert_false(__APARAMS, char *val_arg, bool val);
__ARET crash_assert_equal(__APARAMS, char *exp_arg, char *val_arg, intmax_t exp,
                          intmax_t val);
__ARET crash_assert_notequal(__APARAMS, char *exp_arg, char *val_arg,
                             intmax_t exp, intmax_t val);
__ARET crash_assert_almost(__APARAMS, char *exp_arg, char *val_arg,
                           long double exp, long double val);
__ARET crash_assert_notalmost(__APARAMS, char *exp_arg, char *val_arg,
                              long double exp, long double val);
__ARET crash_assert_ptr_equal(__APARAMS, char *exp_arg, char *val_arg,
                              void *exp, void *val);
__ARET crash_assert_ptr_notequal(__APARAMS, char *exp_arg, char *val_arg,
                                 void *exp, void *val);
__ARET crash_assert_ptr_null(__APARAMS, char *val_arg, void *val);
__ARET crash_assert_same(__APARAMS, char *exp_arg, char *val_arg, char *exp,
                         char *val);
__ARET crash_assert_diff(__APARAMS, char *exp_arg, char *val_arg, char *exp,
                         char *val);
__ARET crash_assert_memory(__APARAMS, char *exp_arg, char *val_arg, void *exp,
                           void *val, size_t size);

__ARET crash_skip_test(__APARAMS);
__ARET crash_user_error(__APARAMS, const char *format, ...);
void crash_user_message(__APARAMS, int level, const char *format, ...);

/*============================= TEST DEFINITIONS =============================*/

#define define_test(name)                                                      \
    void __test_##name##_impl(__CTX, int *__res);                              \
    void __test_##name(__CTX)                                                  \
    {                                                                          \
        int result;                                                            \
        __test_##name##_impl(__ctx, &result);                                  \
        crash_display_test(__ctx, #name, result);                              \
    }                                                                          \
    void __test_##name##_impl(__CTX, int *__res)

#define test(name) __test_##name(__ctx)

#define define_suite(name)                                                     \
    void __suite_##name##_impl(__CTX);                                         \
    void __suite_##name(__CTX)                                                 \
    {                                                                          \
        crash_push_suite(__ctx, #name);                                        \
        __suite_##name##_impl(__ctx);                                          \
        crash_pop_suite(__ctx);                                                \
    }                                                                          \
    void __suite_##name##_impl(__CTX)

#define suite(name) __suite_##name(__ctx)

#define run()                                                                  \
    void __main_suite_impl(__CTX);                                             \
    int main(int argc, char const *argv[])                                     \
    {                                                                          \
        struct CrashTestContext context;                                       \
        crash_init(&context);                                                  \
        __main_suite_impl(&context);                                           \
        crash_display_summary(&context);                                       \
    }                                                                          \
    void __main_suite_impl(__CTX)

/*============================= ASSERTION MACROS =============================*/

#define __AARGS __ctx, __FILE__, __LINE__
#define __ASSERT_BEFORE __res =
#define __ASSERT_AFTER                                                         \
    ;                                                                          \
    if (__res)                                                                 \
    {                                                                          \
        return;                                                                \
    }

#define __assert_ok(value)                                                     \
    __ASSERT_BEFORE                                                            \
    crash_assert_true(__AARGS, #value, value) __ASSERT_AFTER

#define __assert_no(value)                                                     \
    __ASSERT_BEFORE                                                            \
    crash_assert_false(__AARGS, #value, value) __ASSERT_AFTER

#define __assert_eq(expected, value)                                           \
    __ASSERT_BEFORE                                                            \
    crash_assert_equal(__AARGS, #expected, #value, expected, value)            \
        __ASSERT_AFTER

#define __assert_ne(expected, value)                                           \
    __ASSERT_BEFORE                                                            \
    crash_assert_notequal(__AARGS, #expected, #value, expected, value)         \
        __ASSERT_AFTER

#define __assert_eq_flt(expected, value, prec)                                 \
    __ASSERT_BEFORE                                                            \
    crash_assert_almost(__AARGS, #expected, #value, expected, value, prec)     \
        __ASSERT_AFTER

#define __assert_ne_flt(expected, value, prec)                                 \
    __ASSERT_BEFORE                                                            \
    crash_assert_notalmost(__AARGS, #expected, #value, expected, value, prec)  \
        __ASSERT_AFTER

#define __assert_eq_ptr(expected, value)                                       \
    __ASSERT_BEFORE                                                            \
    crash_assert_ptr_equal(__AARGS, #expected, #value, (void *)expected,       \
                           (void *)value) __ASSERT_AFTER

#define __assert_ne_ptr(expected, value)                                       \
    __ASSERT_BEFORE                                                            \
    crash_assert_ptr_notequal(__AARGS, #expected, #value, (void *)expected,    \
                              (void *)value) __ASSERT_AFTER

#define __assert_null_ptr(value)                                               \
    __ASSERT_BEFORE                                                            \
    crash_assert_ptr_null(__AARGS, #value, (void *)value) __ASSERT_AFTER

#define __assert_same(expected, value)                                         \
    __ASSERT_BEFORE                                                            \
    crash_assert_same(__AARGS, #expected, #value, expected, value)             \
        __ASSERT_AFTER

#define __assert_diff(expected, value)                                         \
    __ASSERT_BEFORE                                                            \
    crash_assert_diff(__AARGS, #expected, #value, expected, value)             \
        __ASSERT_AFTER

#define __assert_mem(expected, value, size)                                    \
    __ASSERT_BEFORE                                                            \
    crash_assert_memory(__AARGS, #expected, #value, expected, value, size)     \
        __ASSERT_AFTER

#ifdef ASSERT_PREFIX
#define assert_ok(...) __assert_ok(__VA_ARGS__)
#define assert_no(...) __assert_no(__VA_ARGS__)
#define assert_eq(...) __assert_eq(__VA_ARGS__)
#define assert_ne(...) __assert_ne(__VA_ARGS__)
#define assert_eq_flt(...) __assert_eq_flt(__VA_ARGS__)
#define assert_ne_flt(...) __assert_ne_flt(__VA_ARGS__)
#define assert_eq_ptr(...) __assert_eq_ptr(__VA_ARGS__)
#define assert_ne_ptr(...) __assert_ne_ptr(__VA_ARGS__)
#define assert_null_ptr(...) __assert_null_ptr(__VA_ARGS__)
#define assert_same(...) __assert_same(__VA_ARGS__)
#define assert_diff(...) __assert_diff(__VA_ARGS__)
#define assert_mem(...) __assert_mem(__VA_ARGS__)
#else
#define ok(...) __assert_ok(__VA_ARGS__)
#define no(...) __assert_no(__VA_ARGS__)
#define eq(...) __assert_eq(__VA_ARGS__)
#define ne(...) __assert_ne(__VA_ARGS__)
#define eq_flt(...) __assert_eq_flt(__VA_ARGS__)
#define ne_flt(...) __assert_ne_flt(__VA_ARGS__)
#define eq_ptr(...) __assert_eq_ptr(__VA_ARGS__)
#define ne_ptr(...) __assert_ne_ptr(__VA_ARGS__)
#define null_ptr(...) __assert_null_ptr(__VA_ARGS__)
#define same(...) __assert_same(__VA_ARGS__)
#define diff(...) __assert_diff(__VA_ARGS__)
#define mem(...) __assert_mem(__VA_ARGS__)
#endif

#define skip() __ASSERT_BEFORE crash_skip_test(__AARGS) __ASSERT_AFTER

#define err(...)                                                               \
    __ASSERT_BEFORE crash_user_error(__AARGS, __VA_ARGS__) __ASSERT_AFTER

#define warn(...) crash_user_message(__AARGS, 1, __VA_ARGS__)

#define info(...) crash_user_message(__AARGS, 2, __VA_ARGS__)