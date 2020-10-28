#include "k15_std/include/k15_io.hpp"

#ifdef _WIN32
#    include "k15_io_win32.cpp"
#else
#    error this platform has not been implemented yet
#endif

namespace k15
{
    file_handle_scope::file_handle_scope( const string_view& filePath, file_access_mask fileAccess )
    {
        const result< file_handle > openFileResult = openFile( filePath, fileAccess );

        m_handle  = openFileResult.m_value;
        m_errorId = openFileResult.m_errorId;
    }

    file_handle_scope::~file_handle_scope()
    {
        if ( m_handle.isValid() )
        {
            closeFile( m_handle );
            m_handle.setInvalid();
        }
    }

    file_handle file_handle_scope::getHandle() const
    {
        return m_handle;
    }

    error_id file_handle_scope::getError() const
    {
        return m_errorId;
    }

    bool file_handle_scope::hasError() const
    {
        return m_errorId != error_id::success;
    }

    bool file_handle_scope::isOk() const
    {
        return m_errorId == error_id::success;
    }
}