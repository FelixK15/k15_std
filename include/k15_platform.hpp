#ifndef K15_PLATFORM_INCLUDE
#define K15_PLATFORM_INCLUDE

#include "k15_base.hpp"
#include "k15_time.hpp"

namespace k15
{
    enum class platform_io_handle : uint8
    {
        stdout,
        stdin,
        stderr
    };

    result< void > printString( const string_view& text, platform_io_handle targetHandle );
    timestamp getCurrentTime();
};

#endif //K15_PLATFORM_INCLUDE