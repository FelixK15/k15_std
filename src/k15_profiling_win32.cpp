#include "k15_std/include/k15_profiling.hpp"
#include "k15_std/include/k15_time.hpp"
#include "k15_std/include/k15_memory.hpp"
#include <windows.h>

namespace k15
{
struct profiling_zone_win32
{
    string_view   zoneName;
    LARGE_INTEGER begin;
    LARGE_INTEGER end;
};

struct profiling_context
{
    profiling_context()
    {
        if ( QueryPerformanceFrequency( &performanceFrequency ) == 0 )
        {
            __debugbreak();
        }

        //FK: use custom allocator
        profilingZones.create( getCrtMemoryAllocator(), 128 );
    }

    LARGE_INTEGER                         performanceFrequency;
    dynamic_array< profiling_zone_win32 > profilingZones;
};

static profiling_context s_profilingContext;

profiling_context* getProfilingContext()
{
    return &s_profilingContext;
}

profiling_zone_handle startProfilingZone( profiling_context* pProfilingContext, const string_view& profilingZoneName )
{
    const uint32          handle         = ( uint32 )pProfilingContext->profilingZones.getSize();
    profiling_zone_win32* pProfilingZone = pProfilingContext->profilingZones.pushBack();
    if ( pProfilingZone == nullptr )
    {
        return profiling_zone_handle::invalid;
    }

    pProfilingZone->zoneName = profilingZoneName;
    if ( QueryPerformanceCounter( &pProfilingZone->begin ) == 0 )
    {
        __debugbreak();
    }

    return profiling_zone_handle( handle );
}

void stopProfilingZone( profiling_context* pProfilingContext, const profiling_zone_handle& profilingZoneHandle )
{
    if ( pProfilingContext->profilingZones.getSize() <= profilingZoneHandle.handle )
    {
        return;
    }

    profiling_zone_win32* pProfilingZone = &pProfilingContext->profilingZones[ profilingZoneHandle.handle ];
    if ( QueryPerformanceCounter( &pProfilingZone->end ) == 0 )
    {
        __debugbreak();
    }
}

bool getProfilingZoneInfos( profiling_context* pProfilingContext, slice< profiling_zone_info >* pOutProfilingZones )
{
    profiling_zone_info* pZoneInfos = pOutProfilingZones->pushBackRange( pProfilingContext->profilingZones.getSize() );
    if ( pZoneInfos == nullptr )
    {
        return false;
    }

    for ( size_t zoneInfoIndex = 0u; zoneInfoIndex < pOutProfilingZones->getSize(); ++zoneInfoIndex )
    {
        const profiling_zone_win32* pProfilingZone = &pProfilingContext->profilingZones[ zoneInfoIndex ];

        LARGE_INTEGER delta;
        delta.QuadPart = pProfilingZone->end.QuadPart - pProfilingZone->begin.QuadPart;
        delta.QuadPart *= 1000000000ull;
        delta.QuadPart /= pProfilingContext->performanceFrequency.QuadPart;

        pZoneInfos[ zoneInfoIndex ].zoneName = pProfilingZone->zoneName;
        pZoneInfos[ zoneInfoIndex ].delta    = timestamp::createFromNanoSeconds( delta.QuadPart );
    }

    return true;
}

void newProflingFrame( profiling_context* pProfilingContext )
{
    pProfilingContext->profilingZones.clear();
}

void newProfilingContextFrame( profiling_context* pProfilingContext )
{
    pProfilingContext->profilingZones.clear();
}
} // namespace k15