namespace k15
{
    struct bitmask_index
    {
        size_t arrayIndex;
        size_t slotIndex;
    };

    bitmask_index getBitmaskIndex( size_t flagValue, size_t max )
    {
        bitmask_index index;
        index.arrayIndex = flagValue / max;
        index.slotIndex = flagValue % max;

        return index;
    }

    template< typename T, T MAX >
    bool8 bitmask< T, MAX >::isFlagSet( T flag ) const
    {
        const bitmask_index& index = getBitmaskIndex( (size_t)flag, (size_t)MAX );
        return ( m_bitmask[index.arrayIndex] & ( 1 << index.slotIndex ) ) > 0u;
    }

    template< typename T, T MAX >
    void bitmask< T, MAX >::toggleFlag( T flag )
    {
        const bitmask_index& index = getBitmaskIndex( (size_t)flag, (size_t)MAX );
        m_bitmask[index.arrayIndex] ^= ( 1 << index.slotIndex );
    }

    template< typename T, T MAX >
    void bitmask< T, MAX >::setFlag( T flag )
    {
        const bitmask_index& index = getBitmaskIndex( (size_t)flag, (size_t)MAX );
        m_bitmask[index.arrayIndex] |= ( 1 << index.slotIndex );
    }

    template< typename T, T MAX >
    void bitmask< T, MAX >::clearFlag( T flag )
    {
        const bitmask_index& index = getBitmaskIndex( (size_t)flag, (size_t)MAX );
        m_bitmask[index.arrayIndex] &= ~( 1 << index.slotIndex );
    }

}