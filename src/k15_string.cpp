#include "k15_std/include/k15_string.hpp"

namespace k15
{
    char toAsciiLower( char asciiRune )
    {
        if ( asciiRune <= 'Z' && asciiRune >= 'A' )
        {
            return asciiRune + 32;
        }

        return asciiRune;
    }

    char toAsciiUpper( char asciiRune )
    {
        if ( asciiRune <= 'z' && asciiRune >= 'a' )
        {
            return asciiRune - 32;
        }

        return asciiRune;
    }

    bool isAsciiWhiteSpace( char asciiRune )
    {
        return asciiRune == ' ' || asciiRune == '\t' || asciiRune == '\n';
    }

    size_t getAsciiStringLength( const char* pAsciiString )
    {
        K15_ASSERT( pAsciiString != nullptr );

        size_t length = 0u;
        while ( *pAsciiString++ != 0 )
        {
            ++length;
        }

        return length;
    }

    bool compareAsciiStringNonCaseSensitive( const char* pAsciiStringA, const char* pAsciiStringB )
    {
        K15_ASSERT( pAsciiStringA != nullptr );
        K15_ASSERT( pAsciiStringB != nullptr );

        while ( *pAsciiStringA != 0 && *pAsciiStringB != 0 )
        {
            if ( toAsciiLower( *pAsciiStringA++ ) != toAsciiLower( *pAsciiStringB++ ) )
            {
                return false;
            }
        }

        return true;
    }

    const char* findNextAsciiWhiteSpace( const char* pAsciiString )
    {
        K15_ASSERT( pAsciiString != nullptr );
        const char* pAsciiStringRunningPtr = pAsciiString;

        while ( !isAsciiWhiteSpace( *pAsciiStringRunningPtr ) )
        {
            if ( *pAsciiStringRunningPtr++ == 0 )
            {
                return pAsciiString;
            }
        }

        return pAsciiStringRunningPtr;
    }

    string_view::string_view()
    {
        *this = empty;
    }

    string_view::string_view( const string_view& stringView )
    {
        pData  = stringView.getStart();
        length = stringView.getLength();
    }

    string_view::string_view( const char* pString )
    {
        pData = pString;

        //FK: TODO: Use utf8 functions
        length = getAsciiStringLength( pString );
    }

    string_view::string_view( const char* pString, size_t stringLength )
    {
        pData  = pString;
        length = stringLength;
    }

    string_view::string_view( const char* pStart, const char* pEnd )
    {
        K15_ASSERT( pStart < pEnd );
        pData  = pStart;
        length = pEnd - pStart;
    }

    size_t string_view::getLength() const
    {
        return length;
    }

    const char* string_view::getStart() const
    {
        return pData;
    }

    const char* string_view::getEnd() const
    {
        return pData + length;
    }

    bool8 string_view::isEmpty() const
    {
        return length == 0u;
    }

    char string_view::operator[]( size_t index ) const
    {
        K15_ASSERT( index < length );
        return pData[ index ];
    }
}; // namespace k15