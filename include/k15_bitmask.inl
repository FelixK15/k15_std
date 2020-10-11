namespace k15
{

    template < typename T, typename MASK_TYPE >
    bool8 bitmask< T, MASK_TYPE >::isFlagSet( T flag ) const
    {
        return ( m_bitmask & ( 1 << ( MASK_TYPE )flag ) ) > 0u;
    }

    template < typename T, typename MASK_TYPE >
    void bitmask< T, MASK_TYPE >::toggleFlag( T flag )
    {
        m_bitmask ^= ( 1 << ( MASK_TYPE )flag );
    }

    template < typename T, typename MASK_TYPE >
    void bitmask< T, MASK_TYPE >::setFlag( T flag )
    {
        m_bitmask |= ( 1 << ( MASK_TYPE )flag );
    }

    template < typename T, typename MASK_TYPE >
    void bitmask< T, MASK_TYPE >::clearFlag( T flag )
    {
        m_bitmask &= ~( 1 << ( MASK_TYPE )flag );
    }

    template < typename T, typename MASK_TYPE >
    void bitmask< T, MASK_TYPE >::setIf( T flag, bool condition )
    {
        if ( condition )
        {
            setFlag( flag );
        }
    }

    template < typename T, typename MASK_TYPE >
    void bitmask< T, MASK_TYPE >::clearIf( T flag, bool condition )
    {
        if ( condition )
        {
            clearFlag( flag );
        }
    }

} // namespace k15