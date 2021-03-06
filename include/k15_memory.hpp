#ifndef K15_MEMORY_INCLUDE
#define K15_MEMORY_INCLUDE

#if defined _M_X64 || defined _M_IX86 || defined __amd64__
#    define K15_USE_SSE_MEMCPY 0
#else
#    define K15_USE_SSE_MEMCPY 0
#endif

#if defined __arm__ || defined _M_ARM
#    define K15_USE_NANO_MEMCPY 1
#else
#    define K15_USE_NANO_MEMCPY 0
#endif

#if K15_USE_SSE_MEMCPY
#    include "immintrin.h"
#    define copyMemoryNonOverlapping( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes ) copyMemoryNonOverlappingSSE( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes )
#elif K15_USE_NANO_MEMCPY
#    define copyMemoryNonOverlapping( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes ) copyMemoryNonOverlappingNano( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes )
#else
#    define copyMemoryNonOverlapping( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes ) copyMemoryNonOverlappingWord( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes )
#endif

#define K15_CRT_ALLOCATOR K15_TRUE

namespace k15
{
    constexpr size_t default_alignment = 16;
    class memory_allocator
    {
      public:
        memory_allocator();
        ~memory_allocator();

        virtual void* allocate( size_t sizeInBytes, size_t alignmentInBytes = default_alignment ) = 0;
        virtual void  free( void* pPointer )                                                      = 0;
    };

#if K15_ENABLED( K15_CRT_ALLOCATOR )
    class crt_memory_allocator : public memory_allocator
    {
      public:
        crt_memory_allocator();
        ~crt_memory_allocator();

        virtual void* allocate( size_t sizeInBytes, size_t alignmentInBytes = default_alignment );
        virtual void  free( void* pPointer );
    };

    memory_allocator* getCrtMemoryAllocator();
#endif
    template < typename T >
    T* newObject( memory_allocator* pAllocator );

    template < typename T >
    void deleteObject( T* pObject, memory_allocator* pAllocator );

    bool8 copyMemoryNonOverlappingSSE( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes );
    bool8 copyMemoryNonOverlappingNano( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes );
    bool8 copyMemoryNonOverlappingWord( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes );
}; // namespace k15

#include "k15_memory.inl"

#endif //K15_MEMORY_INCLUDE