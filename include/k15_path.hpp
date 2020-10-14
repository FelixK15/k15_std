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

        void setRoot( const string_view& root );
        void setAbsolutePath( const string_view& absolutePath );
        void setRelativePath( const string_view& relativePath );
        void setFileNameWithExtension( const string_view& fileName );
        void setFileNameWithoutExtensions( const string_view& fileName );
        void setFileExtension( const string_view& fileExtensions );

        string_view getAbsolutePath() const;
        string_view getRelativePath() const;
        string_view getFileExtension() const;
        string_view getFileName() const;
        string_view getFileNameWithoutExtension() const;

        bool isDirectory() const;
        bool isFile() const;

      private:
        void createFullPath();
        void copyAndCleanPath( dynamic_string* pDestinationPath, const string_view& sourcePath );

      private:
        memory_allocator* m_pAllocator;
        dynamic_string    m_root;
        dynamic_string    m_path;
        dynamic_string    m_fileName;
        dynamic_string    m_fileExtension;
        dynamic_string    m_fullPath;

        //FK: Only store full path + index to offsets
    };
}

#endif //K15_PATH_INCLUDE