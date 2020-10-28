#include "k15_std/include/k15_io.hpp"
#include <windows.h>

namespace k15
{
    error_id convertWindowsErrorCodeToErrorId( DWORD windowsErrorCode )
    {
        switch ( windowsErrorCode )
        {
        case ERROR_FILE_NOT_FOUND:
            {
                return error_id::file_not_found;
            }

        case ERROR_SUCCESS:
            {
                return error_id::success;
            }
        }

        return error_id::generic;
    }

    result< file_handle > openFile( const string_view& filePath, file_access_mask fileAccessMask )
    {
        K15_ASSERT( filePath.hasElements() );
        K15_ASSERT( !fileAccessMask.isEmpty() );

        DWORD access    = 0u;
        DWORD fileShare = 0u;
        if ( fileAccessMask.isFlagSet( file_access::read ) )
        {
            access |= GENERIC_READ;
            fileShare |= FILE_SHARE_READ;
        }

        if ( fileAccessMask.isFlagSet( file_access::write ) )
        {
            access |= GENERIC_WRITE;
            fileShare |= FILE_SHARE_WRITE;
        }

        //FK: Clear last windows error
        SetLastError( 0u );
        const HANDLE fileHandle = CreateFileA( filePath.getStart(), access, fileShare, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
        if ( fileHandle == INVALID_HANDLE_VALUE )
        {
            const DWORD errorCode = GetLastError();
            return createResult< file_handle >( convertWindowsErrorCodeToErrorId( errorCode ), file_handle::invalid );
        }

        return file_handle::create( ( size_t )fileHandle );
    }

    result< void > closeFile( const file_handle& fileHandle )
    {
        K15_ASSERT( fileHandle.isValid() );

        SetLastError( 0u );
        HANDLE handle = ( HANDLE )fileHandle.value;
        if ( CloseHandle( handle ) == 0u )
        {
            const DWORD errorCode = GetLastError();
            return convertWindowsErrorCodeToErrorId( errorCode );
        }

        return error_id::success;
    }

    result< size_t > readFromFile( const file_handle& fileHandle, size_t offsetInBytes, slice< char >* pTarget, size_t bytesToRead )
    {
        K15_ASSERT( fileHandle.isValid() );

        HANDLE handle = ( HANDLE )fileHandle.value;

        SetLastError( 0u );
        if ( SetFilePointer( handle, offsetInBytes, nullptr, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
        {
            const DWORD errorCode = GetLastError();
            return convertWindowsErrorCodeToErrorId( errorCode );
        }

        const DWORD maxBytesToRead = K15_MIN( pTarget->getRemainingCapacity(), bytesToRead );

        DWORD bytesRead = 0u;
        if ( ReadFile( handle, pTarget->getStart(), maxBytesToRead, &bytesRead, nullptr ) == 0u )
        {
            const DWORD errorCode = GetLastError();
            return convertWindowsErrorCodeToErrorId( errorCode );
        }

        pTarget->setSize( bytesRead );

        return bytesRead;
    }
}