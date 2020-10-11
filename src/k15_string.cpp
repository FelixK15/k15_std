#include "k15_std/include/k15_string.hpp"

namespace k15
{
    char toLower( char character )
    {
        if( character <= 'Z' && character >= 'A' )
        {
            return character - 32;
        }

        return character;
    }

    char toUpper( char character )
    {
        if( character <= 'z' && character >= 'a' )
        {
            return character + 32;
        }

        return character;
    }

    bool isAsciiWhiteSpace( char character )
    {
        return character == ' ' || character == '\t' || character == '\n';
    }

    size_t getStringLength( const char* pString )
    {
        K15_ASSERT( pString != nullptr );

        size_t length = 0u;
        while( *pString++ != 0 )
        {
            ++length;
        }

        return length;
    }

    bool compareStringNonCaseSensitive( const char* pStringA, const char* pStringB )
    {
        K15_ASSERT( pStringA != nullptr );
        K15_ASSERT( pStringB != nullptr );

        while( *pStringA != 0 && *pStringB != 0 )
        {
            if( toLower( *pStringA++ ) != toLower( *pStringB++ ) )
            {
                return false;
            }
        }

        return true;
    }

    const char* getAfterNextAsciiWhiteSpace( const char* pString )
    {
        K15_ASSERT( pString != nullptr );
        const char* pStringRunningPtr = pString;
        
        while( *pStringRunningPtr != 0 )
        {
            if( isAsciiWhiteSpace( *pStringRunningPtr++ ) )
            {
                return *pStringRunningPtr;
            }
        }

        return pString;
    }

    string_view::string_view()
    {
        *this = empty;
    }

    string_view::string_view( const string_view& stringView )
    {
        pData   = stringView.getStart();
        length  = stringView.getLength();
    }

    string_view::string_view( const char* pString )
    {
        pData = pString;
        length = getStringLength( pString );
    }
    
    string_view::string_view( const char* pString, size_t stringLength )
    {
        pData = pString;
        length = stringLength;
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

    char string_view::operator[](size_t index) const
    {
        K15_ASSERT(index < length);
        return pData[ index ];
    }
};