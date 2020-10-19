#ifndef K15_PATH_INCLUDE
#define K15_PATH_INCLUDE

#include "k15_std/include/k15_string.hpp"
#include "k15_std/include/k15_memory.hpp"
#include "k15_std/include/k15_Container.hpp"

namespace k15
{
    class path
    {
      public:
        path( memory_allocator* pAllocator );
        path( memory_allocator* pAllocator, const string_view& path );

        void setCombinedPath( const string_view& pathA, const string_view& pathB );

        bool isDirectory() const;
        bool isFile() const;

        bool isEmpty() const;

        void clear();

        bool     hasError() const;
        error_id getError() const;

      private:
        void analyzePath();
        void fixDirectorySeperators();

      private:
        memory_allocator* m_pAllocator;
        error_id          m_error;
        dynamic_string    m_path;
        size_t            m_directoryStartIndex;
        size_t            m_fileNameStartIndex;
        size_t            m_fileExtensionStartIndex;

        //FK: Only store full path + index to offsets
    };
}

#endif //K15_PATH_INCLUDE