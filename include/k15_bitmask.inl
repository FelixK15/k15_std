namespace k15
{
    template < typename T, typename MASK_TYPE >
    bitmask< T, MASK_TYPE >::bitmask()
    {
        m_bitmask = 0u;
    }

    template < typename T, typename MASK_TYPE >
    bitmask< T, MASK_TYPE >::bitmask( T flag )
    {
        setFlag( flag );
    }

    template < typename T, typename MASK_TYPE >
    bitmask< T, MASK_TYPE >::bitmask( T flag1, T flag2 )
    {
        setFlag( flag1 );
        setFlag( flag2 );
    }

    template < typename T, typename MASK_TYPE >
    bitmask< T, MASK_TYPE >::bitmask( T flag1, T flag2, T flag3 )
    {
        setFlag( flag1 );
        setFlag( flag2 );
        setFlag( flag3 );
    }

    template < typename T, typename MASK_TYPE >
    bitmask< T, MASK_TYPE >::bitmask( T flag1, T flag2, T flag3, T flag4 )
    {
        setFlag( flag1 );
        setFlag( flag2 );
        setFlag( flag3 );
        setFlag( flag4 );
    }

    template < typename T, typename MASK_TYPE >
    bool bitmask< T, MASK_TYPE >::isEmpty() const
    {
        return m_bitmask == 0u;
    }

    template < typename T, typename MASK_TYPE >
    bool bitmask< T, MASK_TYPE >::isFlagSet( T flag ) const
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