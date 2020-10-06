#ifndef K15_CONTAINER_INCLUDE
#define K15_CONTAINER_INCLUDE

#include "k15_base.hpp"
#include "k15_memory.hpp"

namespace k15
{
    template< typename T >
    class slice
    {
        typedef bool8 (growBufferFunction)( slice< T >* pSlice, uint32 capacity  );
    
    public:
        slice();
        ~slice();

        T* getStart();
        const T* getStart() const;

        void clear();

        bool copyTo( slice< T >* pContainer );

        T* pushBack( T value );
        T* pushBack();
        T* pushBackRange(uint32 elementCount);

        uint32 getSize() const;
        uint32 getCapacity() const;

        T& getElementByIndex( size_t index );
        const T& getElementByIndex( size_t index ) const;

        T& operator[]( size_t index );
        const T& operator[]( size_t index ) const;

    protected:
        uint32 m_capacity;
        uint32 m_size;

        T*                  m_pBuffer;
        growBufferFunction* m_pGrowBufferFunction;
    };

    template< typename T, uint32 Size = 0 >
    class dynamic_array : public slice< T >
    {
    public:
        dynamic_array();
        ~dynamic_array();

        bool8 create( size_t initialCapacity );

    private:
        void freeBuffer();

    private:
        static bool8 growBuffer( slice< T >* pSlice, uint32 capacity );

        T m_staticBuffer[Size];
    };

    template< typename T >
    class dynamic_array< T, 0u > : public slice< T >
    {
    public:
        dynamic_array();
        ~dynamic_array();

        bool8 create( size_t initialCapacity );
    
    private:
        void freeBuffer();

    private:
        static bool8 growBuffer( slice< T >* pSlice, uint32 capacity );
    };
};

#include "k15_container.inl"

#endif //K15_CONTAINER_INCLUDE