#ifndef K15_TIME_INCLUDE
#define K15_TIME_INCLUDE

#include "k15_base_types.hpp"

namespace k15
{
struct timestamp
{
    static timestamp createFromFloatSeconds( float32 seconds );
    static timestamp createFromSeconds( uint32 seconds );
    static timestamp createFromMilliseconds( uint32 milliSeconds );
    static timestamp createFromMicroseconds( uint64 microSeconds );
    static timestamp createFromNanoSeconds( uint64 nanoseconds );

    timestamp();
    timestamp( const timestamp& other );
    timestamp( uint64 nanoseconds );

    uint32 toMicroseconds() const;
    uint32 toMilliseconds() const;
    uint32 toSeconds() const;

    float32 toFloatMicroseconds() const;
    float32 toFloatMilliseconds() const;
    float32 toFloatSeconds() const;

    timestamp& operator=( const timestamp& other );

    static const timestamp zero;

    uint64 nanoseconds;
};

timestamp operator+( const timestamp& first, const timestamp& second );
timestamp operator-( const timestamp& first, const timestamp& second );
timestamp operator+=( const timestamp& first, const timestamp& second );
timestamp operator-=( const timestamp& first, const timestamp& second );

bool operator==( const timestamp& first, const timestamp& second );
bool operator!=( const timestamp& first, const timestamp& second );
bool operator<=( const timestamp& first, const timestamp& second );
bool operator>=( const timestamp& first, const timestamp& second );
bool operator<( const timestamp& first, const timestamp& second );
bool operator>( const timestamp& first, const timestamp& second );
}; // namespace k15

#endif //K15_TIME_INCLUDE