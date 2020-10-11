#ifndef K15_CONTAINER_INCLUDE
#define K15_CONTAINER_INCLUDE

#include "k15_base.hpp"
#include "k15_memory.hpp"

namespace k15
{
    template < typename T >
    class slice
    {
        typedef bool8( growBufferFunction )( slice< T >* pSlice, memory_allocator* pAllocator, uint32 capacity );

      public:
        slice();
        ~slice();

        T*       getStart();
        const T* getStart() const;

        T*       getEnd();
        const T* getEnd() const;

        void clear();

        bool swapTo( slice< T >* pContainer );
        bool copyTo( slice< T >* pContainer );

        bool swapFrom( slice< T >* pContainer );
        bool copyFrom( slice< T >* pContainer );

        T* pushBack( T value );
        T* pushBack();
        T* pushBackRange( uint32 elementCount );

        uint32 getSize() const;
        uint32 getCapacity() const;

        bool isEmpty() const;
        bool isFull() const;
        bool hasElements() const;

        bool isValid() const;
        bool isInvalid() const;

        T&       getElementByIndex( size_t index );
        const T& getElementByIndex( size_t index ) const;

        T&       operator[]( size_t index );
        const T& operator[]( size_t index ) const;

      protected:
        uint32 m_capacity;
        uint32 m_size;

        memory_allocator*   m_pAllocator;
        T*                  m_pBuffer;
        growBufferFunction* m_pGrowBufferFunction;
    };

    template < typename T, uint32 Size = 0 >
    class dynamic_array : public slice< T >
    {
      public:
        dynamic_array( memory_allocator* pAllocator = nullptr, size_t initialCapacity = 32u );
        ~dynamic_array();

        bool8 create( memory_allocator* pAllocator, size_t initialCapacity );

      private:
        void freeBuffer();

      private:
        static bool8 growBuffer( slice< T >* pSlice, memory_allocator* pAllocator, uint32 capacity );

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
        static bool8 growBuffer( slice< T >* pSlice, memory_allocator* pAllocator, uint32 capacity );

      private:
        bool8 m_isInitialized;
    };
}; // namespace k15

#include "k15_container.inl"

#endif //K15_CONTAINER_INCLUDE