#include "k15_string.hpp"

namespace k15
{
    size_t getStringLength( const char* pString )
    {
        size_t length = 0u;
        while( *pString++ != 0 )
        {
            ++length;
        }

        return length;
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