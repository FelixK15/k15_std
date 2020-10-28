namespace k15
{
    template < typename T >
    const handle< T > handle< T >::invalid = handle< T >::create( ( T )~0 );

    template < typename T >
    handle< T > handle< T >::create( T value )
    {
        handle< T > handle;
        handle.value = value;

        return handle;
    }

    template < typename T >
    handle< T >::handle()
    {
        value = handle< T >::invalid.value;
    }

    template < typename T >
    handle< T >::handle( T value )
    {
        this->value = value;
    }

    template < typename T >
    bool handle< T >::isInvalid() const
    {
        return value == handle< T >::invalid.value;
    }

    template < typename T >
    bool handle< T >::isValid() const
    {
        return value != handle< T >::invalid.value;
    }

    template < typename T >
    void handle< T >::setInvalid()
    {
        value = handle< T >::invalid.value;
    }
}