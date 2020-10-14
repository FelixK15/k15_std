#include "k15_std/include/k15_path.hpp"
namespace k15
{
    path::path( memory_allocator* pAllocator )
    {
        m_pAllocator = pAllocator;
    }

    void path::setRoot( const string_view& root )
    {
        K15_ASSERT( root.isEmpty() );

        m_root.clear();

        copyAndCleanPath( &m_root, root );
        createFullPath();
    }

    void path::setRelativePath( const string_view& relativePath )
    {
        K15_ASSERT( relativePath.isEmpty() );

        m_path.clear();

        //FK: Only support file names with 1 extension
        size_t lastDirSeperatorIndex = relativePath.findLast( '/' );
        if ( lastDirSeperatorIndex == string_view::invalidIndex )
        {
            lastDirSeperatorIndex = relativePath.findLast( '\\' );
        }

        string_view path = relativePath;

        if ( lastDirSeperatorIndex != string_view::invalidIndex )
        {
            const string_view potentialFileName = relativePath.subString( lastDirSeperatorIndex );
            if ( potentialFileName.contains( '.' ) )
            {
                setFileNameWithExtension( potentialFileName );
                path = relativePath.subString( 0u, lastDirSeperatorIndex );
            }
        }

        copyAndCleanPath( &m_path, path );
        createFullPath();
    }

    void path::setFileNameWithExtension( const string_view& fileName )
    {
        K15_ASSERT( fileName.isEmpty() );

        m_fileName.clear();
        m_fileExtension.clear();

        const size_t      extensionIndex = fileName.findLast( '.' );
        const string_view extension      = fileName.subString( extensionIndex );

        setFileExtension( extension );

        const string_view fileNameWithoutExtension = fileName.subString( 0u, extensionIndex );
        char*             pFileName                = m_fileName.pushBackRange( fileNameWithoutExtension.getLength() );

        copyMemoryNonOverlapping( pFileName, fileNameWithoutExtension.getLength(), fileNameWithoutExtension.getStart(), fileNameWithoutExtension.getLength() );
        createFullPath();
    }

    void path::setFileNameWithoutExtensions( const string_view& fileName )
    {
        K15_ASSERT( fileName.isEmpty() );

        m_fileName.clear();
        m_fileExtension.clear();

        char* pFileName = m_fileName.pushBackRange( fileName.getLength() );

        copyMemoryNonOverlapping( pFileName, fileName.getLength(), fileName.getStart(), fileName.getLength() );
        createFullPath();
    }

    void path::setFileExtension( const string_view& fileExtensions )
    {
        K15_ASSERT( fileExtensions.isEmpty() );

        m_fileExtension.clear();

        char* pFileExtension = m_fileExtension.pushBackRange( fileExtensions.getLength() );
        copyMemoryNonOverlapping( pFileExtension, fileExtensions.getLength(), fileExtensions.getStart(), fileExtensions.getLength() );
        createFullPath();
    }

    bool path::isDirectory() const
    {
        if ( m_fullPath.isEmpty() )
        {
            return false;
        }
        return *m_fullPath.getEnd() == '/';
    }

    bool path::isFile() const
    {
        if ( m_fullPath.isEmpty() )
        {
            return false;
        }
        return !isDirectory();
    }

    void path::createFullPath()
    {
        m_fullPath.clear();

        if ( m_root.hasElements() )
        {
            char* pRoot = m_fullPath.pushBackRange( m_root.getSize() );
            copyMemoryNonOverlapping( pRoot, m_root.getSize(), m_root.getStart(), m_root.getSize() );

            if ( m_fullPath.getLast() != '/' )
            {
                m_fullPath.pushBack( '/' );
            }
        }

        if ( m_path.hasElements() )
        {
            char* pPath = m_fullPath.pushBackRange( m_path.getSize() );
            copyMemoryNonOverlapping( pPath, m_path.getSize(), m_path.getStart(), m_path.getSize() );
        }
    }

    void path::copyAndCleanPath( dynamic_string* pDestinationPath, const string_view& sourcePath )
    {
        const size_t sourcePathLength      = sourcePath.getLength();
        size_t       lastDirSeperatorIndex = ( ~0 );
        for ( size_t sourcePathIndex = 0u; sourcePathIndex < sourcePathLength; ++sourcePathIndex )
        {
            const char sourcePathCharacter = sourcePath[ sourcePathIndex ];
            if ( sourcePathCharacter == '\\' && lastDirSeperatorIndex != ( sourcePathIndex - 1u ) )
            {
                pDestinationPath->pushBack( '/' );
                lastDirSeperatorIndex = sourcePathIndex;
                continue;
            }

            pDestinationPath->pushBack( sourcePathCharacter );
        }
    }
}