#ifndef K15_RESULT_INCLUDE
#define K15_RESULT_INCLUDE

#include "k15_base.hpp"
#include "k15_error_id.hpp"

namespace k15
{
    template < typename T >
    class result
    {
      public:
        result( T value );
        result( error_id error );

        T           getValue() const;
        error_id    getError() const;
        bool        hasError() const;
        bool        isOk() const;
        string_view getErrorString() const;

        T        m_value;
        error_id m_errorId;
    };

    template <>
    class result< void >
    {
      public:
        result( error_id error );

        error_id    getError() const;
        bool        hasError() const;
        bool        isOk() const;
        string_view getErrorString() const;

      private:
        error_id m_errorId;
    };

    template < typename T >
    static result< T > createResult( error_id error, T value );
} // namespace k15

#include "k15_result.inl"

#endif //K15_RESULT_INCLUDE