#include <networking/utils.h>

#include <cstdio>
#include <stdlib.h>

namespace networking {

void exit_with_error(const exit_with_error_config& exit_with_error_config)
{
    perror(exit_with_error_config.msg);
    exit(exit_with_error_config.exit_code);
}

} // namespace networking