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
        internal,
        not_supported,
        not_implemented,
        not_found
    };

    string_view getErrorString( error_id errorId )
    {
        switch ( errorId )
        {
        case error_id::success:
            return "success";

        case error_id::out_of_memory:
            return "out of memory";

        case error_id::internal:
            return "internal";

        case error_id::not_supported:
            return "not supported";

        case error_id::not_implemented:
            return "not implemented";
        }

        return string_view::empty;
    }
}; // namespace k15

#endif K15_ERROR_ID_INCLUDE