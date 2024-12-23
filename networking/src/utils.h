#pragma once

#include <cstdio>
#include <stdlib.h>

namespace networking {

struct exit_with_error_config
{
    const char *msg;
    int exit_code;
};

inline void exit_with_error(const exit_with_error_config& exit_with_error_config)
{
    // perror prints also the system error message found by the errno code.
    // when a system call fails, POSIX library will set the errno variable
    perror(exit_with_error_config.msg);
    exit(exit_with_error_config.exit_code);
}

} // namespace networking