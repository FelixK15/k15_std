#ifndef K15_BITMASK_INCLUDE
#define K15_BITMASK_INCLUDE

#include "k15_base.hpp"

namespace k15
{
    template < typename T, typename MASK_TYPE >
    class bitmask
    {
      public:
        bitmask();
        bitmask( T flag );
        bitmask( T flag1, T flag2 );
        bitmask( T flag1, T flag2, T flag3 );
        bitmask( T flag1, T flag2, T flag3, T flag4 );

        bool isEmpty() const;
        bool isFlagSet( T flag ) const;

        void toggleFlag( T flag );
        void setFlag( T flag );
        void clearFlag( T flag );

        void setIf( T flag, bool condition );
        void clearIf( T flag, bool condition );

      private:
        MASK_TYPE m_bitmask;
    };

    template < typename T >
    using bitmask8 = bitmask< T, uint8 >;

    template < typename T >
    using bitmask16 = bitmask< T, uint16 >;

    template < typename T >
    using bitmask32 = bitmask< T, uint32 >;

    template < typename T >
    using bitmask64 = bitmask< T, uint64 >;

} // namespace k15

#include "k15_bitmask.inl"

#endif //K15_BITMASK_INCLUDE