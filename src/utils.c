#include "utils.h"

void __crash_indent(__CTX)
{
    for (int i = 0; i < __crash_context->depth; i++)
    {
        printf("  ");
    }
}

int __asprintf(char **out, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    int chrs = __vasprintf(out, fmt, args);

    va_end(args);

    return chrs;
}

int __vasprintf(char **out, const char *fmt, va_list args)
{
    va_list args2;

    va_copy(args2, args);

    size_t size = vsnprintf(NULL, 0, fmt, args) + 1;

    *out = malloc(size);

    int chrs = vsnprintf(*out, size, fmt, args2);

    va_end(args2);

    return chrs;
}

void __crash_println(__CTX, const char *fmt, ...)
{
    va_list args1, args2;

    va_start(args1, fmt);
    va_copy(args2, args1);

    size_t size =
        vsnprintf(NULL, 0, fmt, args1) + (__crash_context->depth * 2) + 2;
    va_end(args1);

    if (__crash_context->out_size + size > __crash_context->out_capacity)
    {
        char *new_buffer =
            malloc((__crash_context->out_size + size) * sizeof(char));
        memcpy(new_buffer, __crash_context->out_buffer,
               __crash_context->out_capacity);
        free(__crash_context->out_buffer);
        __crash_context->out_buffer = new_buffer;
        __crash_context->out_capacity = __crash_context->out_size + size;
    }

    char *cursor = __crash_context->out_buffer + __crash_context->out_size;

    for (int i = 0; i < __crash_context->depth; i++)
    {
        cursor[0] = ' ';
        cursor[1] = ' ';
        cursor += 2;
    }

    cursor += vsnprintf(cursor, size, fmt, args2);
    va_end(args2);

    cursor[0] = '\n';
    cursor[1] = '\0';

    __crash_context->out_size += size - 1;
}

void __crash_array_view(struct __CrashArrayView *view, size_t size,
                        size_t index)
{
    if (index < 5)
    {
        view->begin = 0;
        if (size < 10)
        {
            view->end = size;
        }
        else
        {
            view->end = 10;
        }
    }

    else if (index > (size - 5))
    {
        if (size > 10)
        {
            view->begin = size - 10;
        }
        else
        {
            view->begin = 0;
        }
        view->end = size;
    }

    else
    {
        view->begin = index - 5;
        view->end = index + 5;
    }

    view->ltrim = view->begin > 0;
    view->rtrim = view->end <= size;
}