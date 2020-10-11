namespace k15
{
using FormatStringFunction = result< void > ( * )( slice< char >* pTarget, void* pData );
struct FormatStringType
{
    FormatStringFunction pFormatFunction;
    void*                pData;
};

template < typename T >
FormatStringType getFormatStringType( const T& value )
{
    FormatStringType formatStringType;
    formatStringType.pData           = ( void* )&value;
    formatStringType.pFormatFunction = formatToString
}

template < typename... Args >
result< void > formatString( slice< char >* pTarget, const string_view& format, Args... args )
{
    const FormatStringType formatTypes[] = { getFormatStringType( args )..., emptyFormatStringType };
    for ( size_t formatTypeIndex = 0u; formatTypeIndex < countof( formatTypes ); ++formatTypeIndex )
    {
    }

    const size_t formatLength    = format.getLength();
    size_t       formatCharIndex = 0u;

    while ( formatCharIndex < formatLength )
    {
        const char formatChar = format[ formatCharIndex ];
        if ( formatChar == '%' )
        {
            const format_type type = parseFormatType( format, formatCharIndex );
            if ( type.typeId == format_type_id::stringType )
            {
                const result< void > formatResult = formatToString( pTarget, args... );
                if ( formatResult.hasError() )
                {
                    return formatResult;
                }
            }

            formatCharIndex += type.formatLength;
        }
        else
        {
            if ( pTarget->pushBack( formatChar ) == nullptr )
            {
                return error_id::out_of_memory;
            }

            ++formatCharIndex;
        }
    }

    pTarget->pushBack( 0 );
    return error_id::success;
}

template < typename... Args >
result< void > printFormattedText( const string_view& format, Args... args )
{
    dynamic_array< char, 64u > tempTextBuffer;

    const size_t formatLength    = format.getLength();
    size_t       formatCharIndex = 0u;

    while ( formatCharIndex < formatLength )
    {
        const char formatChar = format[ formatCharIndex ];
        if ( formatChar == '%' )
        {
            const format_type type = parseFormatType( format, formatCharIndex );
            if ( type.typeId == format_type_id::stringType )
            {
                const result< void > formatResult = formatToString( &tempTextBuffer, args... );
                if ( formatResult.hasError() )
                {
                    return formatResult;
                }
            }

            formatCharIndex += type.formatLength;
        }
        else
        {
            if ( tempTextBuffer.pushBack( formatChar ) == nullptr )
            {
                return error_id::out_of_memory;
            }

            ++formatCharIndex;
        }
    }

    tempTextBuffer.pushBack( 0 );
    return printString( tempTextBuffer.getStart(), platform_io_handle::stdout );
}
}; // namespace k15
