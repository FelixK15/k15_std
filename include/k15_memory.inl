namespace k15
{
    template < typename T >
    T* newObject( memory_allocator* pAllocator )
    {
        return ( T* )pAllocator->allocate( sizeof( T ) );
    }

    template < typename T >
    void deleteObject( T* pObject, memory_allocator* pAllocator )
    {
        pAllocator->free( pObject );
    }
} // namespace k15