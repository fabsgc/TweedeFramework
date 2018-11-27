#pragma once

#include <new>
#include <limits>
#include <cstdint>
#include <utility>

#pragma once
#undef min
#undef max

#if TE_PLATFORM == TE_PLATFORM_LINUX
#  include <malloc.h>
#endif

namespace te
{
    /* ###################################################################
    *  ############# MEMORY ALLOCATOR BASE ###############################
    *  ################################################################ */

    /**
    * Memory allocator providing a generic implementation. Specialize for specific categories as needed.
    */
    template<class T>
    class MemoryAllocator
    {
    public:
        static void* Allocate(size_t bytes)
        {
            return ::malloc(bytes);
        }

        static void Deallocate(void* ptr)
        {
            ::free(ptr);
        }
    };

    /**
    * Default allocator when you want to use default os memory management
    */
    class GeneralAllocator
    {
    };

    /* ###################################################################
    *  ############# ENGINE MEMORY ALLOCATION ############################
    *  ################################################################ */

    /**
    * Allocates the specified number of bytes (custom allocator)
    */
    template<class Allocator = GeneralAllocator>
    inline void* te_allocate(uint32_t count)
    {
        return MemoryAllocator<Allocator>::Allocate(count);
    }

    /**
    * Allocates enough bytes to hold the specified type, but doesn't construct it (custom allocator).
    */
    template<class T, class Allocator = GeneralAllocator>
    inline T* te_allocate()
    {
        return (T*)MemoryAllocator<Allocator>::Allocate(sizeof(T));
    }

    /**
    * Create a new object with the specified allocator and the specified parameters (custom allocator).
    */
    template<class Type, class Allocator, class... Args>
    inline Type* te_new(Args &&...args)
    {
        return new (te_allocate<Allocator>(sizeof(Type))) Type(std::forward<Args>(args)...);
    }

    /** Create a new object with the specified allocator and the specified parameters. */
    template<class Type, class... Args>
    inline Type* te_new(Args &&...args)
    {
        return new (te_allocate<GeneralAllocator>(sizeof(Type))) Type(std::forward<Args>(args)...);
    }

    /**
    * Frees all the bytes allocated at the specified location.
    */
    template<class Allocator = GeneralAllocator>
    inline void te_deallocate(void* ptr)
    {
        MemoryAllocator<Allocator>::Deallocate(ptr);
    }

    /** Destructs and frees the specified object. */
    template<class T, class Allocator = GeneralAllocator>
    inline void te_delete(T* ptr)
    {
        (ptr)->~T();
        MemoryAllocator<Allocator>::Deallocate(ptr);
    }

    /** Frees all the bytes allocated at the specified location. */
    inline void te_free(void* ptr)
    {
        MemoryAllocator<GeneralAllocator>::Deallocate(ptr);
    }

    /* ###################################################################
    *  ############# STL ALLOCATOR WRAPPER ###############################
    *  ################################################################ */

    /** Allocator used for the standard library */
    template <class T, class Allocator = GeneralAllocator>
    class StdAllocator
    {
    public:
        using value_type = T;
        using pointer = value_type * ;
        using const_pointer = const value_type*;
        using reference = value_type & ;
        using const_reference = const value_type&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        constexpr StdAllocator() = default;
        constexpr StdAllocator(StdAllocator&&) = default;
        constexpr StdAllocator(const StdAllocator&) = default;
        template<class U, class Allocator2> constexpr StdAllocator(const StdAllocator<U, Allocator2>&) { };
        template<class U, class Allocator2> constexpr bool operator==(const StdAllocator<U, Allocator2>&) const noexcept { return true; }
        template<class U, class Allocator2> constexpr bool operator!=(const StdAllocator<U, Allocator2>&) const noexcept { return false; }

        template<class U> class rebind { public: using other = StdAllocator<U, Allocator>; };

        /** Allocate but don't initialize number elements of type T. */
        static T* allocate(const size_t num)
        {
            if (num == 0)
            {
                return nullptr;
            }

            if (num > static_cast<size_t>(-1) / sizeof(T))
            {
                return nullptr;
            }

            void* pv = te_allocate<Allocator>((uint32_t)(num * sizeof(T)));

            if (!pv)
            {
                return nullptr; // Error
            }

            return static_cast<T*>(pv);
        }

        /** Deallocate storage p of deleted elements. */
        static void deallocate(T* p, size_t num) noexcept
        {
            te_deallocate<Allocator>((void*)p);
        }

        size_t max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }
        void construct(pointer p, const_reference t) { new (p) T(t); }
        void destroy(pointer p) { p->~T(); }

        /* This version of construct() (with a varying number of parameters)
        * seems necessary in order to use some STL data structures from
        * libstdc++-4.8, but compilation fails on OS X, hence the #if. */
        template<class U, class... Args>
        void construct(U* p, Args&&... args) { new(p) U(std::forward<Args>(args)...); }
    };
}

#include "Allocator/TeBasicAllocator.h"
#include "Allocator/TeLinearAllocator.h"
#include "Allocator/TeStackAllocator.h"
#include "Allocator/TePoolAllocator.h"