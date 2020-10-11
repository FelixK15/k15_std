#ifndef K15_STRING_INCLUDE
#define K15_STRING_INCLUDE

#include "k15_base.hpp"
#include "k15_container.hpp"

namespace k15
{
char   toAsciiLower( char asciiRune );
char   toAsciiUpper( char asciiRune );
bool   isAsciiWhiteSpace( char asciiRune );
size_t getAsciiStringLength( const char* pAsciiString );
bool   compareAsciiStringNonCaseSensitive( const char* pAsciiStringA, const char* pAsciiStringB );

const char* findNextAsciiWhiteSpace( const char* pAsciiString );

class string_view
{
  public:
    string_view();
    string_view( const string_view& stringView );
    string_view( const char* pString );
    string_view( const char* pString, size_t stringLength );
    string_view( const char* pStart, const char* pEnd );

    size_t      getLength() const;
    const char* getStart() const;
    const char* getEnd() const;
    bool8       isEmpty() const;

    char operator[]( size_t index ) const;

  public:
    static const string_view empty;

  private:
    const char* pData;
    size_t      length;
};

const string_view string_view::empty = string_view( "" );
}; // namespace k15

#endif //K15_STRING_INCLUDE