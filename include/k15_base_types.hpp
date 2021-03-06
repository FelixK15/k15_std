#ifndef K15_BASE_TYPES_INCLUDE
#define K15_BASE_TYPES_INCLUDE

namespace k15
{
    typedef unsigned char bool8;
    typedef unsigned int  bool32;
    typedef unsigned char byte;

    typedef signed long long sint64;
    typedef signed int       sint32;
    typedef signed short     sint16;
    typedef signed char      sint8;

    typedef unsigned long long uint64;
    typedef unsigned int       uint32;
    typedef unsigned short     uint16;
    typedef unsigned char      uint8;

    typedef float  float32;
    typedef double float64;

    template < typename T >
    struct handle
    {
        static handle< T >       create( T value );
        static const handle< T > invalid;

        handle();
        handle( T value );

        bool isInvalid() const;
        bool isValid() const;

        void setInvalid();

        T value;
    };
} // namespace k15

#include "k15_base_types.inl"

#endif //K15_BASE_TYPES_INCLUDE