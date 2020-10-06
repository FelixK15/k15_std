#ifndef K15_BITMASK_INCLUDE
#define K15_BITMASK_INCLUDE

#include "k15_base.hpp"

namespace k15
{
    template< typename T, T MAX >
    class bitmask
    {
        public:
            bool8   isFlagSet( T flag ) const;

            void    toggleFlag( T flag );
            void    setFlag( T flag );
            void    clearFlag( T flag );

        private:
            byte    m_bitmask[ getMax( 1u, (size_t)MAX / 8u ) ];
    };
}

#include "k15_bitmask.inl"

#endif //K15_BITMASK_INCLUDE