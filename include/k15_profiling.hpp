#ifndef K15_PROFILING_INCLUDE
#define K15_PROFILING_INCLUDE

#include "k15_base_types.hpp"
#include "k15_string.hpp"
#include "k15_time.hpp"

namespace k15
{
struct profiling_zone_info
{
    string_view zoneName;
    timestamp   delta;
};

struct profiling_zone_handle
{
    static const profiling_zone_handle invalid;

    profiling_zone_handle()
    {
        handle = ~0;
    }

    profiling_zone_handle( uint32 handle )
    {
        this->handle = handle;
    }

    uint32 handle;
};

class profiling_zone_scope
{
  public:
    profiling_zone_scope( const string_view& zoneName );
    ~profiling_zone_scope();

  private:
    profiling_zone_handle m_profilingZoneHandle;
};

struct profiling_context;

profiling_context* getProfilingContext();

profiling_zone_handle startProfilingZone( profiling_context* pProfilingContext, const string_view& profilingZoneName );
void                  stopProfilingZone( profiling_context* pProfilingContext, const profiling_zone_handle& profilingZoneHandle );

bool getProfilingZoneInfos( profiling_context* pProfilingContext, slice< profiling_zone_info >* pOutProfilingZones );

void newProflingFrame( profiling_context* pProfilingContext );
} // namespace k15

#endif