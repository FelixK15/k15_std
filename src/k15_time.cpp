#include "k15_std/include/k15_time.hpp"

namespace k15
{
    const timestamp timestamp::zero = timestamp( 0ull );

    static const uint64  secondsToNanoseconds       = 1000000000ull;
    static const uint64  milliSecondsToNanoseconds  = 1000000ull;
    static const uint64  microSecondsToNanoseconds  = 1000ull;
    static const float32 floatSecondsToMilliseconds = 1000.f;

    timestamp timestamp::createFromFloatSeconds( float32 floatSeconds )
    {
        const uint32 seconds      = ( uint32 )floatSeconds;
        const uint32 milliseconds = ( uint32 )( ( ( float32 )floatSeconds - ( float32 )seconds ) * floatSecondsToMilliseconds );

        return timestamp( ( uint64 )seconds * secondsToNanoseconds + milliseconds * milliSecondsToNanoseconds );
    }

    timestamp timestamp::createFromSeconds( uint32 seconds )
    {
        return timestamp( ( uint64 )seconds * secondsToNanoseconds );
    }

    timestamp timestamp::createFromMilliseconds( uint32 milliseconds )
    {
        return timestamp( ( uint64 )milliseconds * milliSecondsToNanoseconds );
    }

    timestamp timestamp::createFromMicroseconds( uint64 microseconds )
    {
        return timestamp( microseconds * microSecondsToNanoseconds );
    }

    timestamp timestamp::createFromNanoSeconds( uint64 nanoseconds )
    {
        return timestamp( nanoseconds );
    }

    timestamp::timestamp()
    {
        nanoseconds = 0ull;
    }

    timestamp::timestamp( const timestamp& other )
    {
        nanoseconds = other.nanoseconds;
    }

    timestamp::timestamp( uint64 nanoseconds )
    {
        this->nanoseconds = nanoseconds;
    }

    uint32 timestamp::toMicroseconds() const
    {
        return ( uint32 )( nanoseconds / microSecondsToNanoseconds );
    }

    uint32 timestamp::toMilliseconds() const
    {
        return ( uint32 )( nanoseconds / milliSecondsToNanoseconds );
    }

    uint32 timestamp::toSeconds() const
    {
        return ( uint32 )( nanoseconds / secondsToNanoseconds );
    }

    float32 timestamp::toFloatMicroseconds() const
    {
        return ( float32 )( ( float64 )nanoseconds / 1000.0 );
    }

    float32 timestamp::toFloatMilliseconds() const
    {
        return ( float32 )( ( float64 )nanoseconds / 1000000.0 );
    }

    float32 timestamp::toFloatSeconds() const
    {
        return ( float32 )( ( float64 )nanoseconds / 1000000000.0 );
    }

    timestamp& timestamp::operator=( const timestamp& other )
    {
        nanoseconds = other.nanoseconds;
        return *this;
    }

    timestamp operator+( const timestamp& first, const timestamp& second )
    {
        return timestamp( first.nanoseconds + second.nanoseconds );
    }

    timestamp operator-( const timestamp& first, const timestamp& second )
    {
        return timestamp( first.nanoseconds - second.nanoseconds );
    }

    timestamp operator+=( const timestamp& first, const timestamp& second )
    {
        return timestamp( first.nanoseconds + second.nanoseconds );
    }

    timestamp operator-=( const timestamp& first, const timestamp& second )
    {
        return timestamp( first.nanoseconds - second.nanoseconds );
    }

    bool operator==( const timestamp& first, const timestamp& second )
    {
        return first.nanoseconds == second.nanoseconds;
    }

    bool operator!=( const timestamp& first, const timestamp& second )
    {
        return first.nanoseconds != second.nanoseconds;
    }

    bool operator<=( const timestamp& first, const timestamp& second )
    {
        return first.nanoseconds <= second.nanoseconds;
    }

    bool operator>=( const timestamp& first, const timestamp& second )
    {
        return first.nanoseconds >= second.nanoseconds;
    }

    bool operator<( const timestamp& first, const timestamp& second )
    {
        return first.nanoseconds < second.nanoseconds;
    }

    bool operator>( const timestamp& first, const timestamp& second )
    {
        return first.nanoseconds > second.nanoseconds;
    }
} // namespace k15