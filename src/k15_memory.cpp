#include "k15_memory.hpp"
#include <intrin.h>

namespace k15
{
    template< typename T >
    static void copyNonOverlapping( void* pDestination, const void* pSource, size_t sourceSizeInBytes )
    {
        if (sourceSizeInBytes == 0u)
        {
            return;
        }

        T*          pDst = ( T* )pDestination;
        const T*    pSrc = ( T* )pSource;
    
        size_t elementsToCopy = sourceSizeInBytes / sizeof( T );
        K15_ASSERT( sourceSizeInBytes % sizeof( T ) == 0u );
        
        while( elementsToCopy-- != 0u )
        {
            *pDst++ = *pSrc++;
        }
    }
    
    template<>
    static void copyNonOverlapping<byte>( void* pDestination, const void* pSource, size_t sourceSizeInBytes )
    {
        __movsq( (unsigned long long*)pDestination, (const unsigned long long*)pSource, sourceSizeInBytes/sizeof(long long) );
    }

    bool8 copyMemoryNonOverlappingWord( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes )
    {
        if( destinationCapacityInBytes < sourceSizeInBytes )
        {
            return false;
        }

        if( sourceSizeInBytes == 0u)
        {
            return true;
        }

        byte* pDst = ( byte* )pDestination;
        byte* pSrc = ( byte* )pSource;

        constexpr size_t wordSizeInBytes    = sizeof( long );
        constexpr size_t wordAlignment      = alignof( long );

        const size_t destinationAlignmentOffset = ( size_t )pDestination % wordAlignment;
        const size_t sourceAlignmentOffset      = ( size_t )pSource % wordAlignment;

        const bool isDestinationAligned = destinationAlignmentOffset == 0u;
        const bool isSourceAligned      = sourceAlignmentOffset == 0u;

        bool useWordCopy = ( isDestinationAligned && isSourceAligned );
        if( !useWordCopy && destinationAlignmentOffset == sourceAlignmentOffset && sourceSizeInBytes >= wordAlignment )
        {
            const size_t byteCountToAlignment = ( wordAlignment - destinationAlignmentOffset );
            copyNonOverlapping< byte >( pDestination, pSource, byteCountToAlignment );

            sourceSizeInBytes -= byteCountToAlignment;

            pDst += byteCountToAlignment;
            pSrc += byteCountToAlignment;
            useWordCopy = true;
        }

        if ( useWordCopy )
        {
            #if 0
            const size_t wordCount = sourceSizeInBytes / wordSizeInBytes;
            copyNonOverlapping< long >( pDestination, pSource, wordCount * wordSizeInBytes );
            #else
            copyNonOverlapping< byte >( pDestination, pSource, sourceSizeInBytes );
            #endif
            const size_t numberOfBytesCopied = sourceSizeInBytes;
            sourceSizeInBytes -= numberOfBytesCopied;
            pDst += numberOfBytesCopied;
            pSrc += numberOfBytesCopied;
        }

        copyNonOverlapping< byte >( pDst, pSrc, sourceSizeInBytes );

        return true;
    }

#if K15_USE_SSE_MEMCPY
    bool8 copyMemoryNonOverlappingSSE( void* pDestination, size_t destinationCapacityInBytes, const void* pSource, size_t sourceSizeInBytes )
    {
        if( destinationCapacityInBytes < sourceSizeInBytes )
        {
            return false;
        }

        byte* pDst = ( byte* )pDestination;
        byte* pSrc = ( byte* )pSource;

        typedef __m128 sse_word_t;

        const size_t avxRegisterSizeInBytes = sizeof( sse_word_t );
        const size_t avxAlignment           = alignof( sse_word_t );

        const size_t destinationAlignmentOffset = ( size_t )pDestination % avxAlignment;
        const size_t sourceAlignmentOffset      = ( size_t )pSource % avxAlignment;

        const bool isDestinationAligned = destinationAlignmentOffset == 0u;
        const bool isSourceAligned      = sourceAlignmentOffset == 0u;

        bool useAvxCopy = isDestinationAligned && isSourceAligned;
        if( !useAvxCopy && ( destinationAlignmentOffset == sourceAlignmentOffset ) && sourceSizeInBytes >= avxAlignment )
        {
            const size_t byteCountToAlignment = ( avxAlignment - destinationAlignmentOffset );
            copyMemoryNonOverlappingWord( pDst, destinationCapacityInBytes, pSrc, byteCountToAlignment );

            sourceSizeInBytes -= byteCountToAlignment;
            destinationCapacityInBytes -= byteCountToAlignment;

            pDst += byteCountToAlignment;
            pSrc += byteCountToAlignment;
            useAvxCopy = true;
        }

        if( useAvxCopy )
        {
            const size_t avxElementCount = sourceSizeInBytes / avxRegisterSizeInBytes;
            copyNonOverlapping< sse_word_t >( pDst, pSrc, avxElementCount * avxRegisterSizeInBytes );
            
            const size_t bytesCopied = avxElementCount * avxRegisterSizeInBytes;
            sourceSizeInBytes -= bytesCopied;
            destinationCapacityInBytes -= bytesCopied;

            pDst += bytesCopied;
            pSrc += bytesCopied;
        }

        return copyMemoryNonOverlappingWord( pDst, destinationCapacityInBytes, pSrc, sourceSizeInBytes );
    }
#endif
}

