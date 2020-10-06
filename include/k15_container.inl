namespace k15
{
    template< typename T>
    slice< T >::slice()
    {
        m_pBuffer     = nullptr;
        m_capacity    = 0u;
        m_size        = 0u;
    }

    template< typename T>
    slice< T >::~slice()
    {

    }

    template< typename T>
    const T* slice< T >::getStart() const
    {
        return m_pBuffer;
    }

    template< typename T>
    void slice< T >::clear()
    {
        if( !is_trivially_destructible< T >::value )
        {
            for( size_t index = 0u; index < m_size; ++index)
            {
                m_pBuffer[ index ].~T();
            }
        }
       
        m_size = 0u;
    }

    template< typename T>
    bool slice< T >::copyTo( slice< T >* pContainer )
    {
        T* pData = pContainer->pushBackRange( m_size );
        if( pData == nullptr )
        {
            return false;
        }

        if( !is_trivially_assignable< T >::value )
        {
            for( size_t elementIndex = 0u; elementIndex < m_size; ++elementIndex )
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

    template< typename T>
    T* slice< T >::getStart()
    {
        return m_pBuffer;
    }

    template< typename T>
    T* slice< T >::pushBack( T value )
    {
        T* pValue = pushBack();
        *pValue = value;

        return pValue;
    }

    template< typename T>
    T* slice< T >::pushBack()
    {
        return pushBackRange(1u);
    }

    template< typename T >
    T* slice< T >::pushBackRange( uint32 elementCount )
    {
        if( m_size + elementCount >= m_capacity )
        {
            if( !m_pGrowBufferFunction(this, m_size + elementCount) )
            {
                return nullptr;
            }
        }

        //K15_ASSERT(pBuffer != nullptr);

        T* pDataStart = m_pBuffer + m_size;
        m_size += elementCount;
        return pDataStart;
    }

    template< typename T >
    uint32 slice< T >::getSize() const
    {
        return m_size;
    }

    template< typename T >
    uint32 slice< T >::getCapacity() const
    {
        return m_capacity;
    }

    template< typename T >
    T& slice< T >::getElementByIndex( size_t index )
    {
       // K15_ASSERT( index < m_size );
        return m_pBuffer[ index ];
    }

    template< typename T >
    const T& slice< T >::getElementByIndex( size_t index ) const
    {
        //K15_ASSERT( index < m_size );
        return m_pBuffer[ index ];
    }

    template< typename T >
    T& slice< T >::operator[]( size_t index )
    {
        return getElementByIndex( index );
    }

    template< typename T >
    const T& slice< T >::operator[]( size_t index ) const
    {
        return getElementByIndex( index );
    }

    template< typename T, uint32 Size >
    dynamic_array< T, Size >::dynamic_array()
    {
        m_pBuffer = m_staticBuffer;
        m_capacity = Size;
        m_size = 0;
        m_pGrowBufferFunction = dynamic_array<T, Size>::growBuffer;
    }

    template< typename T, uint32 Size >
    dynamic_array< T, Size >::~dynamic_array()
    {
        freeBuffer();
    }

    template< typename T, uint32 Size >
    bool8 dynamic_array< T, Size >::create( size_t initialCapacity )
    {
        return growBuffer( this, initialCapacity );
    }

    template< typename T, uint32 Size >
    void dynamic_array< T, Size >::freeBuffer()
    {
        if( m_pBuffer != m_staticBuffer )
        {
            free(m_pBuffer);
            m_pBuffer = nullptr;
        }
    }

    template< typename T, uint32 Size >
    bool8 dynamic_array< T, Size >::growBuffer( slice< T >* pSlice, uint32 capacity )
    {
        dynamic_array<T, Size>* pArray = (dynamic_array<T, Size>*)pSlice;
        const int newCapacity = getMax( capacity, pArray->m_capacity * 2 );

        if( newCapacity < Size )
        {
            return true;
        }

        const size_t newBufferSizeInBytes = sizeof(T) * newCapacity;
        T* pNewBuffer = (T*)malloc( newBufferSizeInBytes );
        if (pNewBuffer == nullptr)
        {
            return false;
        }

        copyMemoryNonOverlapping8( pNewBuffer, newBufferSizeInBytes, pArray->m_pBuffer, pArray->m_size );
        pArray->freeBuffer();

        pArray->m_capacity  = newCapacity;
        pArray->m_pBuffer   = pNewBuffer;

        return true;
    }

    template< typename T >
    dynamic_array< T >::dynamic_array()
    {
        m_pBuffer     = nullptr;
        m_capacity    = 0u;
        m_size        = 0;
        m_pGrowBufferFunction = dynamic_array< T >::growBuffer;
    }
    
    template< typename T >
    dynamic_array< T >::~dynamic_array()
    {
        freeBuffer();
    }
    
    template< typename T >
    bool8 dynamic_array< T >::create( size_t initialCapacity )
    {
        return growBuffer( this, initialCapacity );
    }

    template< typename T >
    void dynamic_array< T >::freeBuffer()
    {
        free( m_pBuffer );
        m_pBuffer = nullptr;
    }

    template< typename T >
    bool8 dynamic_array< T >::growBuffer( slice< T >* pSlice, uint32 capacity )
    {
        dynamic_array< T >* pArray = ( dynamic_array< T >* )pSlice;
        const int newCapacity = capacity;
        const size_t newBufferSizeInBytes = sizeof(T) * newCapacity;

        T* pNewBuffer = (T*)malloc( newBufferSizeInBytes );
        if (pNewBuffer == nullptr)
        {
            return false;
        }

        copyMemoryNonOverlapping( pNewBuffer, newBufferSizeInBytes, pArray->m_pBuffer, pArray->m_size );
        pArray->freeBuffer();

        pArray->m_capacity  = newCapacity;
        pArray->m_pBuffer   = pNewBuffer;

        return true;
    }
};