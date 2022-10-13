#pragma once
#include "crash.h"
#include "utils.h"

void __crash_display_mem(struct __CrashArrayView *view, char *buffer,
                         unsigned char *source);

void __crash_display_mem_offset(struct __CrashArrayView *view, char *buffer);