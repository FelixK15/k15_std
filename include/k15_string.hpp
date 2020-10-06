#ifndef K15_STRING_INCLUDE
#define K15_STRING_INCLUDE

#include "k15_base.hpp"
#include "k15_container.hpp"

namespace k15
{
    size_t getStringLength( const char* pString );

    class string_view
    {
    public:
        string_view();
        string_view( const string_view& stringView );
        string_view( const char* pString );
        string_view( const char* pString, size_t stringLength );

        size_t getLength() const;
        const char* getStart() const;
        const char* getEnd() const;
        bool8 isEmpty() const;

        char operator[](size_t index) const;

    public:
        static const string_view empty;

    private:
        const char* pData;
        size_t      length;
    };

    const string_view string_view::empty = string_view("");
};

#endif //K15_STRING_INCLUDE