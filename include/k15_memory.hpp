#ifndef K15_MEMORY_INCLUDE
#define K15_MEMORY_INCLUDE

#if defined _M_X64 || defined _M_IX86 || defined __amd64__
#   define K15_USE_SSE_MEMCPY 0
#else
#   define K15_USE_SSE_MEMCPY 0
#endif 

#if defined __arm__ || defined _M_ARM
#   define K15_USE_NANO_MEMCPY 1
#else
#   define K15_USE_NANO_MEMCPY 0
#endif

#if K15_USE_SSE_MEMCPY
#   include "immintrin.h"
#   define copyMemoryNonOverlapping( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes ) copyMemoryNonOverlappingSSE( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes )
#elif K15_USE_NANO_MEMCPY
#   define copyMemoryNonOverlapping( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes ) copyMemoryNonOverlappingNano( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes )
#else
#   define copyMemoryNonOverlapping( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes ) copyMemoryNonOverlappingWord( pDestination, destinationCapacityInBytes, pSource, sourceSizeInBytes )
#endif

namespace k15
{
    bool8 copyMemoryNonOverlappingSSE( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes );
    bool8 copyMemoryNonOverlappingNano( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes );
    bool8 copyMemoryNonOverlappingWord( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes );
};

#endif //K15_MEMORY_INCLUDE