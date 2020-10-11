#include "k15_std/include/k15_format.hpp"
#include "k15_std/include/k15_container.hpp"
#include "k15_std/include/k15_memory.hpp"

namespace k15
{
    enum class format_type_id
    {
        decimalType,
        floatType,
        stringType,

        invalidType
    };

    struct format_type
    {
        format_type_id typeId;
        size_t         formatLength;

        static format_type create( format_type_id id, size_t formatLength )
        {
            format_type formatType;
            formatType.typeId       = id;
            formatType.formatLength = formatLength;

            return formatType;
        }

        const static format_type invalid;
    };

    const format_type format_type::invalid = format_type::create( format_type_id::invalidType, 0u );

    static format_type parseFormatType( const string_view& format, size_t offsetInChars )
    {
        if ( format[ offsetInChars ] != '%' )
        {
            return format_type::invalid;
        }

        if ( format[ offsetInChars + 1 ] == 's' )
        {
            return format_type::create( format_type_id::stringType, 2u );
        }

        return format_type::invalid;
    }

    result< void > formatToString( slice< char >* pTarget, const string_view& value )
    {
        char* pBuffer = pTarget->pushBackRange( value.getLength() );
        if ( pBuffer == nullptr )
        {
            return error_id::out_of_memory;
        }
        const size_t bytesCopied = copyMemoryNonOverlapping( pBuffer, value.getLength(), value.getStart(), value.getLength() );
        return bytesCopied == value.getLength() ? error_id::success : error_id::internal;
    }

    result< void > formatToString( slice< char >* pTarget, const error_id& errorId )
    {
        return formatString( pTarget, getErrorString( errorId ) );
    }
}; // namespace k15