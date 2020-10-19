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

    size_t findFirstIndexInString( const char* pString, char character )
    {
        const char* pRunningStringPtr = pString;
        while ( *pRunningStringPtr != 0 )
        {
            if ( *pRunningStringPtr == character )
            {
                return ( pRunningStringPtr - pString );
            }

            ++pRunningStringPtr;
        }

        return string_view::invalidIndex;
    }

    size_t findLastIndexInString( const char* pString, char character )
    {
        const char* pRunningStringPtr = pString;
        size_t      lastIndex         = string_view::invalidIndex;
        while ( *pRunningStringPtr != 0 )
        {
            if ( *pRunningStringPtr == character )
            {
                lastIndex = ( pRunningStringPtr - pString );
            }

            ++pRunningStringPtr;
        }

        return lastIndex;
    }

    bool doesStringContainCharacter( const char* pString, char character )
    {
        while ( *pString != 0 )
        {
            if ( *pString == character )
            {
                true;
            }

            ++pString;
        }

        return false;
    }

    string_view::string_view()
    {
        *this = empty;
    }

    string_view::string_view( const string_view& stringView )
    {
        m_pData  = stringView.getStart();
        m_length = stringView.getLength();
    }

    string_view::string_view( const char* pString )
    {
        m_pData = pString;

        //FK: TODO: Use utf8 functions
        m_length = getAsciiStringLength( pString );
    }

    string_view::string_view( const char* pString, size_t stringLength )
    {
        m_pData  = pString;
        m_length = stringLength;
    }

    string_view::string_view( const char* pStart, const char* pEnd )
    {
        K15_ASSERT( pStart < pEnd );
        m_pData  = pStart;
        m_length = pEnd - pStart;
    }

    size_t string_view::getLength() const
    {
        return m_length;
    }

    bool string_view::isEmpty() const
    {
        return m_length == 0u;
    }

    bool string_view::hasElements() const
    {
        return m_length != 0u;
    }

    const char* string_view::getStart() const
    {
        return m_pData;
    }

    const char* string_view::getEnd() const
    {
        return m_pData + m_length;
    }

    const char& string_view::getFirst() const
    {
        K15_ASSERT( m_length > 0u );
        return m_pData[ 0u ];
    }

    const char& string_view::getLast() const
    {
        K15_ASSERT( m_length > 0u );
        return m_pData[ m_length - 1u ];
    }

    size_t string_view::findLast( char character ) const
    {
        return findLastIndexInString( m_pData, character );
    }

    bool string_view::contains( char character ) const
    {
        return doesStringContainCharacter( m_pData, character );
    }

    string_view string_view::subString( size_t startIndex ) const
    {
        K15_ASSERT( startIndex < m_length );
        return string_view( m_pData + startIndex, getEnd() );
    }

    string_view string_view::subString( size_t startIndex, size_t length ) const
    {
        K15_ASSERT( startIndex + length < m_length );
        return string_view( m_pData + startIndex, m_pData + startIndex + length );
    }

    char string_view::operator[]( size_t index ) const
    {
        K15_ASSERT( index < m_length );
        return m_pData[ index ];
    }

    dynamic_string::dynamic_string( memory_allocator* pAllocator, size_t initialCapacity )
        : dynamic_array( pAllocator, initialCapacity )
    {
    }

    dynamic_string::dynamic_string( memory_allocator* pAllocator, const string_view& stringView )
        : dynamic_array( pAllocator, stringView.getLength() )
    {
        pushBackString( stringView );
    }

    char* dynamic_string::pushBackString( const char* pString )
    {
        return pushBackRange( pString, getAsciiStringLength( pString ) );
    }

    char* dynamic_string::pushBackString( const string_view& string )
    {
        return pushBackRange( string.getStart(), string.getLength() );
    }

    void dynamic_string::operator=( const string_view& stringView )
    {
        pushBackRange( stringView.getStart(), stringView.getLength() );
        pushBack( 0 );
    }

}; // namespace k15