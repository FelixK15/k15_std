#ifndef K15_PATH_INCLUDE
#define K15_PATH_INCLUDE

#include "k15_std/include/k15_string.hpp"
#include "k15_std/include/k15_memory.hpp"
#include "k15_std/include/k15_container.hpp"

namespace k15
{
    class path
    {
      public:
        path( memory_allocator* pAllocator );
        path( memory_allocator* pAllocator, const string_view& path );

        bool setCombinedPath( const string_view& pathA, const string_view& pathB );

        bool isDirectory() const;
        bool isFile() const;

        bool isEmpty() const;

        void clear();

        bool copyFrom( const path& other );

        const char* getStart() const;
        const char* getEnd() const;

        size_t getLength() const;

        bool     hasError() const;
        error_id getError() const;

        path& operator=( const path& other );

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

    bool doesFileExist( const string_view& filePath );
}

#endif //K15_PATH_INCLUDE