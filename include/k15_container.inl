namespace k15
{
    template < typename T >
    slice< T >::slice()
    {
        m_pBuffer  = nullptr;
        m_capacity = 0u;
        m_size     = 0u;
    }

    template < typename T >
    slice< T >::~slice()
    {
    }

    template < typename T >
    void slice< T >::clear()
    {
        if ( !is_trivially_destructible< T >::value )
        {
            for ( size_t index = 0u; index < m_size; ++index )
            {
                m_pBuffer[ index ].~T();
            }
        }

        m_size = 0u;
    }

    template < typename T >
    bool slice< T >::swapTo( slice< T >* pContainer )
    {
        if ( !pContainer->copyTo( this ) )
        {
            return false;
        }

        pContainer->m_capacity = 0;
        pContainer->m_size     = 0;
        pContainer->m_pBuffer  = nullptr;

        return true;
    }

    template < typename T >
    bool slice< T >::copyTo( slice< T >* pContainer )
    {
        T* pData = pContainer->pushBackRange( m_size );
        if ( pData == nullptr )
        {
            return false;
        }

        if ( !is_trivially_assignable< T >::value )
        {
            for ( size_t elementIndex = 0u; elementIndex < m_size; ++elementIndex )
            {
                pData[ elementIndex ] = m_pBuffer[ elementIndex ];
            }
        }
        else
        {
            copyMemoryNonOverlapping( pData, pContainer->m_size * sizeof( T ), m_pBuffer, m_size * sizeof( T ) );
        }

        return true;
    }

    template < typename T >
    bool slice< T >::swapFrom( slice< T >* pContainer )
    {
        return pContainer->swapTo( this );
    }

    template < typename T >
    bool slice< T >::copyFrom( slice< T >* pContainer )
    {
        return pContainer->copyTo( this );
    }

    template < typename T >
    T* slice< T >::getStart()
    {
        return m_pBuffer;
    }

    template < typename T >
    const T* slice< T >::getStart() const
    {
        return m_pBuffer;
    }

    template < typename T >
    T* slice< T >::getEnd()
    {
        return m_pBuffer + m_size;
    }

    template < typename T >
    const T* slice< T >::getEnd() const
    {
        return m_pBuffer + m_size;
    }

    template < typename T >
    T& slice< T >::getFirst()
    {
        K15_ASSERT( m_size > 0u );
        return m_pBuffer[ 0u ];
    }

    template < typename T >
    const T& slice< T >::getFirst() const
    {
        K15_ASSERT( m_size > 0u );
        return m_pBuffer[ 0u ];
    }

    template < typename T >
    T& slice< T >::getLast()
    {
        K15_ASSERT( m_size > 0u );
        return m_pBuffer[ m_size - 1 ];
    }

    template < typename T >
    const T& slice< T >::getLast() const
    {
        K15_ASSERT( m_size > 0u );
        return m_pBuffer[ m_size - 1 ];
    }

    template < typename T >
    T* slice< T >::pushBack( T value )
    {
        T* pValue = pushBack();
        *pValue   = value;

        return pValue;
    }

    template < typename T >
    T* slice< T >::pushBack()
    {
        return pushBackRange( 1u );
    }

    template < typename T >
    T* slice< T >::pushBackRange( uint32 elementCount )
    {
        if ( m_size + elementCount >= m_capacity )
        {
            if ( !m_pGrowBufferFunction( this, m_pAllocator, m_size + elementCount ) )
            {
                return nullptr;
            }
        }

        K15_ASSERT( m_pBuffer != nullptr );

        T* pDataStart = m_pBuffer + m_size;
        m_size += elementCount;
        return pDataStart;
    }

    template < typename T >
    uint32 slice< T >::getSize() const
    {
        return m_size;
    }

    template < typename T >
    uint32 slice< T >::getCapacity() const
    {
        return m_capacity;
    }

    template < typename T >
    bool slice< T >::isEmpty() const
    {
        return m_size == 0;
    }

    template < typename T >
    bool slice< T >::isFull() const
    {
        return m_size == m_capacity;
    }

    template < typename T >
    bool slice< T >::hasElements() const
    {
        return m_size > 0u;
    }

    template < typename T >
    bool slice< T >::isValid() const
    {
        return m_pBuffer != nullptr;
    }

    template < typename T >
    bool slice< T >::isInvalid() const
    {
        return m_pBuffer == nullptr;
    }

    template < typename T >
    T& slice< T >::getElementByIndex( size_t index )
    {
        K15_ASSERT( index < m_size );
        return m_pBuffer[ index ];
    }

    template < typename T >
    const T& slice< T >::getElementByIndex( size_t index ) const
    {
        K15_ASSERT( index < m_size );
        return m_pBuffer[ index ];
    }

    template < typename T >
    T& slice< T >::operator[]( size_t index )
    {
        return getElementByIndex( index );
    }

    template < typename T >
    const T& slice< T >::operator[]( size_t index ) const
    {
        return getElementByIndex( index );
    }

    template < typename T, uint32 Size >
    dynamic_array< T, Size >::dynamic_array( memory_allocator* pAllocator, size_t initialCapacity )
    {
        m_pBuffer             = m_staticBuffer;
        m_isInitialized       = false;
        m_capacity            = Size;
        m_size                = 0;
        m_pGrowBufferFunction = dynamic_array< T, Size >::growBuffer;

        if ( pAllocator != nullptr )
        {
            const bool createdSuccessfully = create( pAllocator, initialCapacity );
            K15_ASSERT( createdSuccessfully );
        }
    }

    template < typename T, uint32 Size >
    dynamic_array< T, Size >::~dynamic_array()
    {
        freeBuffer();
    }

    template < typename T, uint32 Size >
    bool8 dynamic_array< T, Size >::create( memory_allocator* pAllocator, size_t initialCapacity )
    {
        K15_ASSERT( !m_isInitialized );
        const bool8 createdSuccessfully = growBuffer( this, pAllocator, initialCapacity );
        m_isInitialized                 = true;
        m_pAllocator                    = pAllocator;

        return createdSuccessfully;
    }

    template < typename T, uint32 Size >
    void dynamic_array< T, Size >::freeBuffer()
    {
        K15_ASSERT( m_pAllocator != nullptr );
        if ( m_pBuffer != m_staticBuffer )
        {
            m_pAllocator->free( m_pBuffer );
            m_pBuffer = nullptr;
        }
    }

    template < typename T, uint32 Size >
    bool8 dynamic_array< T, Size >::growBuffer( slice< T >* pSlice, memory_allocator* pAllocator, uint32 capacity )
    {
        dynamic_array< T, Size >* pArray      = ( dynamic_array< T, Size >* )pSlice;
        const int                 newCapacity = getMax( capacity, pArray->m_capacity * 2 );

        if ( newCapacity < Size )
        {
            return true;
        }

        const size_t newBufferSizeInBytes = sizeof( T ) * newCapacity;
        T*           pNewBuffer           = ( T* )pAllocator->allocate( newBufferSizeInBytes );
        if ( pNewBuffer == nullptr )
        {
            return false;
        }

        copyMemoryNonOverlapping8( pNewBuffer, newBufferSizeInBytes, pArray->m_pBuffer, pArray->m_size );
        pArray->freeBuffer();

        pArray->m_capacity = newCapacity;
        pArray->m_pBuffer  = pNewBuffer;

        return true;
    }

    template < typename T >
    dynamic_array< T >::dynamic_array( memory_allocator* pAllocator, size_t initialCapacity )
    {
        m_pAllocator          = nullptr;
        m_pBuffer             = nullptr;
        m_capacity            = 0u;
        m_size                = 0;
        m_isInitialized       = false;
        m_pGrowBufferFunction = dynamic_array< T >::growBuffer;

        if ( pAllocator != nullptr )
        {
            const bool createdSuccessfully = create( pAllocator, initialCapacity );
            K15_ASSERT( createdSuccessfully );
        }
    }

    template < typename T >
    dynamic_array< T >::~dynamic_array()
    {
        freeBuffer();
    }

    template < typename T >
    bool8 dynamic_array< T >::create( memory_allocator* pAllocator, size_t initialCapacity )
    {
        K15_ASSERT( !m_isInitialized );
        const bool8 createdSuccessfully = growBuffer( this, pAllocator, initialCapacity );
        m_isInitialized                 = true;
        m_pAllocator                    = pAllocator;

        return createdSuccessfully;
    }

    template < typename T >
    void dynamic_array< T >::freeBuffer()
    {
        if ( m_pBuffer != nullptr )
        {
            K15_ASSERT( m_pAllocator != nullptr );
            m_pAllocator->free( m_pBuffer );
            m_pBuffer = nullptr;
        }
    }

    template < typename T >
    bool8 dynamic_array< T >::growBuffer( slice< T >* pSlice, memory_allocator* pAllocator, uint32 capacity )
    {
        dynamic_array< T >* pArray = ( dynamic_array< T >* )pSlice;

        const int    newCapacity          = capacity;
        const size_t newBufferSizeInBytes = sizeof( T ) * newCapacity;

        T* pNewBuffer = ( T* )pAllocator->allocate( newBufferSizeInBytes );
        if ( pNewBuffer == nullptr )
        {
            return false;
        }

        copyMemoryNonOverlapping( pNewBuffer, newBufferSizeInBytes, pArray->m_pBuffer, pArray->m_size );
        pArray->freeBuffer();

        pArray->m_capacity = newCapacity;
        pArray->m_pBuffer  = pNewBuffer;

        return true;
    }
}; // namespace k15