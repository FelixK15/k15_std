namespace k15
{
    template < typename T >
    result< T >::result( T value )
    {
        m_value   = value;
        m_errorId = error_id::success;
    }

    template < typename T >
    result< T >::result( error_id error )
    {
        m_errorId = error;
    }

    template < typename T >
    T result< T >::getValue() const
    {
        K15_ASSERT( m_errorId == error_id::success );
        return m_value;
    }

    template < typename T >
    error_id result< T >::getError() const
    {
        return m_errorId;
    }

    template < typename T >
    bool result< T >::hasError() const
    {
        return m_errorId != error_id::success;
    }

    template < typename T >
    bool result< T >::isOk() const
    {
        return m_errorId == error_id::success;
    }

    template < typename T >
    string_view result< T >::getErrorString() const
    {
        return k15::getErrorString( m_errorId );
    }

    result< void >::result( error_id error )
    {
        m_errorId = error;
    }

    error_id result< void >::getError() const
    {
        return m_errorId;
    }

    bool result< void >::hasError() const
    {
        return m_errorId != error_id::success;
    }

    bool result< void >::isOk() const
    {
        return m_errorId == error_id::success;
    }

    string_view result< void >::getErrorString() const
    {
        return k15::getErrorString( m_errorId );
    }
}; // namespace k15