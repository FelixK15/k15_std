#ifndef K15_ERROR_ID_INCLUDE
#define K15_ERROR_ID_INCLUDE

#include "k15_string.hpp"

namespace k15
{
    enum class error_id
    {
        success,
        out_of_memory,
        socket_error,
        listen_error,
        parse_error,
        internal
    };

    string_view getErrorString( error_id errorId)
    {
        switch( errorId )
        {
            case error_id::success:
                return "success";

            case error_id::out_of_memory:
                return "out of memory";
            
            case error_id::internal:
                return "internal";
        }

        return string_view::empty;
    }  
};

#endif K15_ERROR_ID_INCLUDE