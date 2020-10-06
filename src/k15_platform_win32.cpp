#include "k15_platform.hpp"

#ifndef _WIN32
#   error This header should only be compiled when targeting the win32 operating system.
#endif

#pragma comment(lib, "kernel32.lib")
#include <windows.h>
//#include <fileapi.h>
//#include <ProcessEnv.h>

namespace k15
{
    static long mapPlatformHandle( platform_io_handle handle )
    {
        switch( handle )
        {
            case platform_io_handle::stdout:
                return STD_OUTPUT_HANDLE;

            case platform_io_handle::stdin:
                return STD_INPUT_HANDLE;

            case platform_io_handle::stderr:
                return STD_ERROR_HANDLE;
        }

        K15_ASSERT( false );
        return 0u;
    }

    result< void > printString( const string_view& text, platform_io_handle targetHandle )
    {
        const DWORD handleIdentifier = mapPlatformHandle( targetHandle );
        const HANDLE pIoHandle = GetStdHandle( handleIdentifier );
        if( pIoHandle == INVALID_HANDLE_VALUE )
        {
            //FK: todo: Map win32 error to error_id
            return error_id::internal;
        }

        if( WriteFile( pIoHandle, text.getStart(), text.getLength(), nullptr, nullptr ) == FALSE )
        {
            //FK: todo: Map win32 error to error_id
            return error_id::internal;
        }

        return error_id::success;
    }

    timestamp getCurrentTime()
    {
        LARGE_INTEGER frequency;
        LARGE_INTEGER perfCounter;
        QueryPerformanceFrequency( &frequency );
        QueryPerformanceCounter( &perfCounter );

        perfCounter.QuadPart *= 100000000;
        perfCounter.QuadPart /= frequency.QuadPart;

        return timestamp::createFromMicroseconds( ( uint32 )perfCounter.QuadPart );
    }
};

