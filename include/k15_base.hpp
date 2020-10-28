#ifndef K15_BASE_INCLUDE
#define K15_BASE_INCLUDE

#define K15_BREAK __asm { int 3 }
#define K15_ASSERT( expr ) \
    if ( !( expr ) )       \
    {                      \
        K15_BREAK;         \
    }

#define K15_UNUSED_VARIABLE( var ) ( void )( var )
#define K15_NOT_IMPLEMENTED

#define K15_TRUE  1
#define K15_FALSE 0

#define K15_ENABLED( var ) ( var == K15_TRUE )

#define K15_ARRAY_SIZE( arr ) ( sizeof( arr ) / sizeof( arr[ 0 ] ) )

#define K15_MAX( a, b ) ( a ) > ( b ) ? ( a ) : ( b )
#define K15_MIN( a, b ) ( a ) < ( b ) ? ( a ) : ( b )

#define K15_KiB( n ) ( n ) * 1024
#define K15_MiB( n ) K15_KiB( n ) * 1024
#define K15_GiB( n ) K15_MiB( n ) * 1024

#include <new>
#include "k15_base_types.hpp"
#include "k15_result.hpp"

namespace k15
{
    template < typename T >
    class slice;

    template < typename T, uint32 Size >
    class dynamic_array;

    class string_view;

    template < typename T >
    constexpr const T& getMin( const T& a, const T& b )
    {
        return a > b ? b : a;
    }

    template < typename T >
    constexpr const T& getMax( const T& a, const T& b )
    {
        return a > b ? a : b;
    }

    template < typename T >
    struct is_trivially_assignable
    {
        constexpr static bool value = __is_trivially_assignable( T, T );
    };

    template < typename T >
    struct is_trivially_destructible
    {
        constexpr static bool value = __is_trivially_destructible( T );
    };

    template < typename T >
    struct is_trivially_constructible
    {
        constexpr static bool value = __is_trivially_constructible( T );
    };
} // namespace k15

#endif //K15_BASE_INCLUDE