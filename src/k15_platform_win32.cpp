#include "k15_std/include/k15_platform.hpp"

#ifndef _WIN32
#    error This header should only be compiled when targeting the win32 operating system.
#endif

#pragma comment( lib, "kernel32.lib" )
#include <windows.h>
//#include <fileapi.h>
//#include <ProcessEnv.h>

namespace k15
{
result< void > printString( const string_view& text )
{
    const HANDLE pIoHandle = GetStdHandle( STD_OUTPUT_HANDLE );
    if ( pIoHandle == INVALID_HANDLE_VALUE )
    {
        //FK: todo: Map win32 error to error_id
        return error_id::internal;
    }

    if ( WriteFile( pIoHandle, text.getStart(), text.getLength(), nullptr, nullptr ) == FALSE )
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
}; // namespace k15
