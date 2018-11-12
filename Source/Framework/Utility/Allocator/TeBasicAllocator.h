#pragma once

#include <memory>
#include <new>

namespace te
{
    /* ###################################################################
    *  ############# BASIC ALLOCATOR #####################################
    *  ################################################################ */

    class TE_UTILITY_EXPORT BasicAllocator
    {
    public:
        BasicAllocator() {}
        ~BasicAllocator() {}

        void* Allocate(size_t amount)
        {
            return malloc(amount);
        }

        void Deallocate(void* data)
        {
            free(data);
        }

    protected:
        BasicAllocator(BasicAllocator const&) = delete;
        BasicAllocator& operator=(BasicAllocator const&) = delete;
    };

    /* ###################################################################
    *  ############# ALLOCATOR METHODS ###################################
    *  ################################################################ */

    TE_UTILITY_EXPORT BasicAllocator& gBasicAllocator();

    TE_UTILITY_EXPORT void* te_basic_allocate(UINT32 numBytes);
    TE_UTILITY_EXPORT void  te_basic_deallocate(void* data);

    /* ###################################################################
    *  ############# MEMORY ALLOCATOR FOR STD ALLOCATOR ##################
    *  ################################################################ */

    /**
    * Memory allocator using BasicAllocator
    */

    template<>
    class TE_UTILITY_EXPORT MemoryAllocator<BasicAllocator>
    {
    public:
        static void* Allocate(size_t bytes)
        {
            return gBasicAllocator().Allocate((UINT32)bytes);
        }

        static void Deallocate(void* ptr)
        {
            gBasicAllocator().Deallocate(ptr);
        }
    };
}
