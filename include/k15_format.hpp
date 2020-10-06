#ifndef K15_FORMAT_INCLUDE
#define K15_FORMAT_INCLUDE

#include "k15_result.hpp"

namespace k15
{
    template< typename... Args >
    result< void > formatString( slice< char >* pTarget, const string_view& format, Args... args );

    template< typename... Args >
    result< void > printFormattedText( const string_view& format, Args... args );

    result< void > formatToString( slice< char >* pTarget, const string_view& value );
    result< void > formatToString( slice< char >* pTarget, const error_id& errorId);
};

#include "k15_format.inl"

#endif //K15_FORMAT_INCLUDE
    
