#ifndef K15_BASE_INCLUDE
#define K15_BASE_INCLUDE

#define K15_BREAK __asm{ int 3 }
#define K15_ASSERT(expr) if(!(expr)) { K15_BREAK; }
    
#define K15_UNUSED_VARIABLE(var) (void)(var)

#define K15_TRUE    1
#define K15_FALSE   0

#define K15_ENABLED(var) (var==K15_TRUE)

#include "k15_base_types.hpp"
#include "k15_result.hpp"

namespace k15
{
    template< typename T >
    class slice;

    template< typename T, uint32 Size >
    class dynamic_array;

    class string_view;

    template< typename T >
    constexpr const T& getMin( const T& a, const T& b )
    {
        return a > b ? b : a;
    }

    template< typename T >
    constexpr const T& getMax( const T& a, const T& b)
    {
        return a > b ? a : b;
    }

    template< typename T >
    struct is_trivially_assignable
    {
        constexpr static bool value = __is_trivially_assignable( T, T );
    };

    template< typename T >
    struct is_trivially_destructible
    {
        constexpr static bool value = __is_trivially_destructible( T );
    };
}

#endif //K15_BASE_INCLUDE