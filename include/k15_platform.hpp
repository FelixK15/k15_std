#ifndef K15_PLATFORM_INCLUDE
#define K15_PLATFORM_INCLUDE

#include "k15_base.hpp"
#include "k15_time.hpp"

namespace k15
{
    result< void > printString( const string_view& text );
    timestamp      getCurrentTime();
}; // namespace k15

#endif //K15_PLATFORM_INCLUDE