#include "k15_profiling.hpp"
#include "k15_platform.hpp"

namespace k15
{
    const profiling_zone_handle profiling_zone_handle::invalid = profiling_zone_handle(~0);

    profiling_zone_scope::profiling_zone_scope( const string_view& zoneName )
    {
        profiling_context* pProfilingContext = getProfilingContext();
        m_profilingZoneHandle = startProfilingZone( pProfilingContext, zoneName );
    }

    profiling_zone_scope::~profiling_zone_scope()
    {
        profiling_context* pProfilingContext = getProfilingContext();
        stopProfilingZone( pProfilingContext, m_profilingZoneHandle );  
    }
}