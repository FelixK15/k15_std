#include "k15_std/include/k15_path.hpp"

namespace k15
{
    bool doesFileExist( const string_view& filePath )
    {
        WIN32_FIND_DATA findFileData;
        HANDLE          searchHandle = FindFirstFile( filePath.getStart(), &findFileData );
        if ( searchHandle != INVALID_HANDLE_VALUE )
        {
            FindClose( searchHandle );
            return true;
        }

        return false;
    }
}