namespace k15
{
    template< typename T >
    result< T >::result( T value )
    {
        this->value = value;
        errorId = error_id::success;
    }

    template< typename T >
    result< T >::result( error_id error )
    {
        errorId = error;
    }

    template< typename T >
    T result< T >::getValue() const
    {
        K15_ASSERT(error == error_id::success);
        return value;
    }

    template< typename T >
    error_id result< T >::getError() const
    {
        return errorId;
    }

    template< typename T >
    bool result< T >::hasError() const
    {
        return errorId != error_id::success;
    }

    template< typename T >
    bool result< T >::isOk() const
    {
        return errorId == error_id::success;
    }

    template< typename T >
    string_view result< T >::getErrorString() const
    {
        return k15::getErrorString( errorId );
    }

    result< void >::result( error_id error )
    {
        errorId = error;
    }

    error_id result< void >::getError() const
    {
        return errorId;
    }

    bool result< void >::hasError() const
    {
        return errorId != error_id::success;
    }

    bool result< void >::isOk() const
    {
        return errorId == error_id::success;
    }

    string_view result< void >::getErrorString() const
    {
        return k15::getErrorString( errorId );
    }
};