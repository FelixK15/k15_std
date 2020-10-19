#include "k15_std/include/k15_path.hpp"
namespace k15
{
    bool isDirectorySeperator( char character )
    {
        return character == '\\' || character == '/';
    }

    constexpr static char directorySeperator = '/';

    path::path( memory_allocator* pAllocator )
        : m_path( pAllocator, 128u )
    {
        m_pAllocator = pAllocator;
        m_error      = error_id::success;
    }

    path::path( memory_allocator* pAllocator, const string_view& path )
        : m_path( pAllocator, path )
    {
        m_error      = error_id::success;
        m_pAllocator = pAllocator;
        analyzePath();
    }

    bool path::setCombinedPath( const string_view& pathA, const string_view& pathB )
    {
        m_path.clear();
        m_path.pushBackString( pathA );

        if ( !isDirectorySeperator( m_path.getLast() ) )
        {
            m_path.pushBack( directorySeperator );
        }

        const void* pData = m_path.pushBackString( pathB );
        if ( pData == nullptr )
        {
            return false;
        }

        fixDirectorySeperators();
        analyzePath();

        return true;
    }

    bool path::isDirectory() const
    {
        return m_fileNameStartIndex == string_view::invalidIndex;
    }

    bool path::isFile() const
    {
        return m_fileNameStartIndex != string_view::invalidIndex;
    }

    bool path::isEmpty() const
    {
        return m_path.isEmpty();
    }

    void path::clear()
    {
        m_fileExtensionStartIndex = 0u;
        m_fileNameStartIndex      = 0u;
        m_directoryStartIndex     = 0u;

        m_path.clear();
        m_error = error_id::success;
    }

    const char* path::getStart() const
    {
        return m_path.getStart();
    }

    const char* path::getEnd() const
    {
        return m_path.getEnd();
    }

    size_t path::getLength() const
    {
        return m_path.getSize();
    }

    bool path::hasError() const
    {
        return m_error != error_id::success;
    }

    error_id path::getError() const
    {
        return m_error;
    }

    void path::analyzePath()
    {
        if ( m_path.isEmpty() )
        {
            return;
        }

        m_directoryStartIndex = findFirstIndexInString( m_path.getStart(), '/' );
        m_fileNameStartIndex  = findLastIndexInString( m_path.getStart(), '/' );

        if ( m_fileNameStartIndex == m_directoryStartIndex || m_fileNameStartIndex == m_path.getSize() )
        {
            m_fileNameStartIndex      = string_view::invalidIndex;
            m_fileExtensionStartIndex = string_view::invalidIndex;
        }
        else
        {
            m_fileExtensionStartIndex = findLastIndexInString( m_path.getStart(), '.' );
        }
    }

    void path::fixDirectorySeperators()
    {
        size_t lastDirectorySeperatorIndex = string_view::invalidIndex;
        for ( size_t pathCharIndex = 0u; pathCharIndex < m_path.getSize(); ++pathCharIndex )
        {
            if ( isDirectorySeperator( m_path[ pathCharIndex ] ) )
            {
                if ( lastDirectorySeperatorIndex == ( pathCharIndex - 1 ) )
                {
                    //FK: detected 2 or more joined dir seperator - remove current seperator
                    m_path.eraseSortedByIndex( pathCharIndex );
                    --pathCharIndex;

                    continue;
                }

                m_path[ pathCharIndex ]     = directorySeperator;
                lastDirectorySeperatorIndex = pathCharIndex;
            }
        }
    }
}