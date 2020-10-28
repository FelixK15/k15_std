#ifndef K15_CONTAINER_INCLUDE
#define K15_CONTAINER_INCLUDE

#include "k15_base.hpp"
#include "k15_memory.hpp"

namespace k15
{
    template < typename T >
    class slice
    {
        typedef bool8( growBufferFunction )( slice< T >* pSlice, memory_allocator* pAllocator, size_t capacity );

      public:
        slice();
        ~slice();

        T*       getStart();
        const T* getStart() const;

        T*       getEnd();
        const T* getEnd() const;

        T&       getFirst();
        const T& getFirst() const;

        T&       getLast();
        const T& getLast() const;

        void clear();

        void swapFrom( slice< T >* pContainer );
        bool copyFrom( const slice< T >* pContainer );

        T* pushBack( T value );
        T* pushBack();
        T* pushBackRange( const T* pValues, size_t elementCount );
        T* pushBackRange( size_t elementCount );

        T popBack();

        void setSize( size_t size );

        size_t getSize() const;
        size_t getCapacity() const;
        size_t getRemainingCapacity() const;

        bool reserve( size_t size );

        bool isEmpty() const;
        bool isFull() const;
        bool hasElements() const;

        bool isValid() const;
        bool isInvalid() const;

        void eraseSortedByIndex( size_t index );
        void eraseUnsortedByIndex( size_t index );

        void eraseSorted( const T& element );
        void eraseUnsorted( const T& element );

        size_t findElementIndex( const T& element );

        T&       getElementByIndex( size_t index );
        const T& getElementByIndex( size_t index ) const;

        T&       operator[]( size_t index );
        const T& operator[]( size_t index ) const;

      public:
        static constexpr size_t invalidIndex = ( ~0 );

      protected:
        size_t m_capacity;
        size_t m_size;

        memory_allocator*   m_pAllocator;
        T*                  m_pBuffer;
        growBufferFunction* m_pGrowBufferFunction;
    };

    template < typename T, size_t Size = 0 >
    class dynamic_array : public slice< T >
    {
      public:
        dynamic_array( memory_allocator* pAllocator = nullptr, size_t initialCapacity = 32u );
        ~dynamic_array();

        bool8 create( memory_allocator* pAllocator, size_t initialCapacity );

      private:
        void freeBuffer();

      private:
        static bool8 growBuffer( slice< T >* pSlice, memory_allocator* pAllocator, size_t capacity );

      private:
        bool8 m_isInitialized;
        T     m_staticBuffer[ Size ];
    };

    template < typename T >
    class dynamic_array< T, 0u > : public slice< T >
    {
      public:
        dynamic_array( memory_allocator* pAllocator = nullptr, size_t initialCapacity = 32u );
        ~dynamic_array();

        bool8 create( memory_allocator* pAllocator, size_t initialCapacity );

      private:
        void freeBuffer();

      private:
        static bool8 growBuffer( slice< T >* pSlice, memory_allocator* pAllocator, size_t capacity );

      private:
        bool8 m_isInitialized;
    };

    template < typename T >
    class array_view
    {
      public:
        array_view();
        array_view( const T* pStart, const size_t size );
        array_view( const slice< T >& slice );

        template < size_t N >
        array_view( const T ( &cArray )[ N ] );

        size_t getSize() const;
        bool   isEmpty() const;
        bool   hasElements() const;
        bool   isValid() const;
        bool   isInvalid() const;

        const T& getFirst() const;
        const T& getLast() const;

        const T* getStart() const;
        const T* getEnd() const;

      private:
        const T* m_pData;
        size_t   m_size;
    };

    template < typename T >
    array_view< T > createArrayView( const T* pStart, const size_t size );

    template < typename T >
    array_view< T > createArrayView( const slice< T >& slice );

    template < typename T >
    array_view< T > createArrayView( const T& element );

    template < typename T, size_t N >
    array_view< T > createArrayView( const T ( &cArray )[ N ] );

}; // namespace k15

#include "k15_container.inl"

#endif //K15_CONTAINER_INCLUDE