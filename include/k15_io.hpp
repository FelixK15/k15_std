#ifndef K15_IO_INCLUDE
#define K15_IO_INCLUDE

#include "k15_std/include/k15_bitmask.hpp"

namespace k15
{
    enum class file_access : uint8
    {
        read,
        write
    };

    using file_handle      = handle< size_t >;
    using file_access_mask = bitmask8< file_access >;

    result< file_handle > openFile( const string_view& filePath, file_access_mask fileAccess );
    result< void >        closeFile( const file_handle& fileHandle );
    result< size_t >      readFromFile( const file_handle& fileHandle, size_t offsetInBytes, slice< char >* pTarget, size_t bytesToRead );

    class file_handle_scope
    {
      public:
        file_handle_scope( const string_view& filePath, file_access_mask fileAccess );
        ~file_handle_scope();

        file_handle getHandle() const;
        error_id    getError() const;

        bool hasError() const;
        bool isOk() const;

      private:
        error_id    m_errorId;
        file_handle m_handle;
    };
}

#endif //K15_IO_INCLUDE