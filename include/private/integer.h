#pragma once
#include "crash.h"
#include "utils.h"
#include <stdlib.h>

char *__crash_repr_char(intmax_t n);

char *__crash_repr_short(intmax_t n);

char *__crash_repr_int(intmax_t n);

char *__crash_repr_long(intmax_t n);