#pragma once
#include "crash.h"
#include <features.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET_ALL "\x1b[0m"
#define BOLD "\x1b[1m"
#define DIM "\x1b[2m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define PURPLE "\x1b[35m"
#define RESET_COLOR "\x1b[39m"

#define style(code)                                                            \
    if (__crash_context->color)                                                \
    {                                                                          \
        printf(code);                                                          \
    }

#define indent() __crash_indent(__crash_context)

void __crash_indent(__CTX);

#define println(...) __crash_println(__crash_context, __VA_ARGS__)

void __crash_println(__CTX, const char *fmt, ...);

// portable asprintf and vasprintf
int __asprintf(char **out, const char *fmt, ...);
int __vasprintf(char **out, const char *fmt, va_list args);

struct __CrashArrayView
{
    size_t begin;
    size_t end;
    bool ltrim;
    bool rtrim;
};

void __crash_array_view(struct __CrashArrayView *view, size_t size,
                        size_t index);