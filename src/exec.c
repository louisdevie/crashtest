#include "exec.h"

void crash_init_test(__CTX)
{
    __crash_context->out_buffer[0] = 0;
    __crash_context->out_size = 0;
    __crash_context->depth++;
}

void crash_display_test(__CTX, char *name, unsigned char result)
{
    __crash_context->depth--;
    indent();

    printf("%-40s", name);
    style(BOLD);
    printf(" [");

    switch (result)
    {
    case CRASH_TEST_SUCCESS:
        style(GREEN);
        printf(" OK ");
        style(RESET_COLOR);
        __crash_context->success_count++;
        break;
    case CRASH_TEST_FAILURE:
        style(RED);
        printf("FAIL");
        style(RESET_COLOR);
        break;
    case CRASH_TEST_SKIPPED:
        style(DIM);
        printf("SKIP");
        style(RESET_ALL);
        style(BOLD);
        __crash_context->skipped_count++;
        break;
    case CRASH_TEST_ABORTED:
        style(PURPLE);
        printf("ABRT");
        style(RESET_COLOR);
        break;
    }

    printf("]\n");
    style(RESET_ALL);

    printf("%s", __crash_context->out_buffer);
}

void crash_push_suite(__CTX, char *name)
{
    indent();
    printf("%s\n", name);
    __crash_context->depth++;
}

void crash_pop_suite(__CTX) { __crash_context->depth--; }

void crash_init(__CTX)
{
    __crash_context->color = true;
    char *no_color_env = getenv("NO_COLOR");
    if (no_color_env != NULL && no_color_env[0] != 0)
    {
        __crash_context->color = false;
    }

    __crash_context->depth = 0;

    __crash_context->out_buffer = malloc(100 * sizeof(char));
    __crash_context->out_buffer[0] = 0;
    __crash_context->out_size = 0;
    __crash_context->out_capacity = 100;

    __crash_context->test_count = 0;
    __crash_context->success_count = 0;
    __crash_context->skipped_count = 0;
}

void crash_display_summary(__CTX)
{
    int fail_count =
        __crash_context->test_count -
        (__crash_context->success_count + __crash_context->skipped_count);

    style(BOLD);
    if (fail_count)
    {
        style(RED);
    }
    else
    {
        style(GREEN);
    }

    printf("%d", __crash_context->success_count);
    printf(" passed, ");
    printf("%d", fail_count);
    printf(" failed, ");

    style(RESET_COLOR);

    printf("%d", __crash_context->skipped_count);
    printf(" ignored");
}
