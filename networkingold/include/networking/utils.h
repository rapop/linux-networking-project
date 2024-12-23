#pragma once

#include <cstdio>
#include <stdlib.h>

namespace networking {
struct exit_with_error_config
{
    const char *msg;
    int exit_code;
};

void exit_with_error(const exit_with_error_config& exit_with_error_config);

} // namespace networking