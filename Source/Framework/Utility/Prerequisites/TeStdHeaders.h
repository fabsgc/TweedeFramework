#pragma once

#ifdef __BORLANDC__
#   define __STD_ALGORITHM
#endif

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <atomic>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <chrono>
#include <ctime>
#include <memory>
#include <string>
#include <cstdio>
#include <new>
#include <string>

// STL containers
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>
#include <random>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

extern "C" {
#   include <sys/types.h>
#   include <sys/stat.h>
}

#if TE_PLATFORM == TE_PLATFORM_WIN32
#  undef min
#  undef max
#	if !defined(NOMINMAX) && defined(_MSC_VER)
#		define NOMINMAX // required to stop windows.h messing up std::min
#	endif
#  if defined( __MINGW32__ )
#    include <unistd.h>
#  endif
#endif

#if TE_PLATFORM == TE_PLATFORM_LINUX
extern "C" {
#   include <unistd.h>
#   include <dlfcn.h>
}
#endif

#if TE_PLATFORM == TE_PLATFORM_OSX
extern "C" {
#   include <unistd.h>
#   include <sys/param.h>
#   include <CoreFoundation/CoreFoundation.h>
}
#endif

#if TE_PLATFORM == TE_PLATFORM_WIN32
#   include <Windows.h>
#   include <fcntl.h>
#   include <io.h>

#   ifndef UNICODE
#       define UNICODE
#   endif

#   ifndef _UNICODE
#       define _UNICODE
#   endif
#endif

#if TE_PLATFORM == TE_PLATFORM_WIN32
#   define TE_SLEEP(ms) Sleep(ms)
#elif TE_PLATFORM == TE_PLATFORM_LINUX
#   define TE_SLEEP(ms) usleep(ms)
#else
#   define TE_SLEEP(ms) usleep(ms)
#endif

namespace te
{
    /**
     * Hash for enum types, to be used instead of std::hash<T> when T is an enum.
     *
     * Until C++14, std::hash<T> is not defined if T is a enum (see
     * http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#2148).  But
     * even with C++14, as of october 2016, std::hash for enums is not widely
     * implemented by compilers, so here when T is a enum, we use EnumClassHash
     * instead of std::hash. (For instance, in bs::hash_combine(), or
     * bs::UnorderedMap.)
     */
    struct EnumClassHash
    {
        template <typename T>
        constexpr std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    /* ###################################################################
    *  ############# STL CONTAINER SNIPPETS ##############################
    *  ################################################################ */

    template <typename T>
    using SPtr = std::shared_ptr<T>;

    template <typename T, typename A = StdAllocator<T>>
    using UPtr = std::unique_ptr<T, decltype(&te_delete<T, A>)>;

    /** Hasher that handles custom enums automatically. */
    template <typename Key>
    using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

    /** Double ended queue. Allows for fast insertion and removal at both its beggining and end. */
    template <typename T, typename A = StdAllocator<T>>
    using Deque = std::deque<T, A>;

    /** Dynamically sized array that stores element contigously. */
    template <typename T, typename A = StdAllocator<T>>
    using Vector = std::vector<T, A>;

    /**
     * Container that supports constant time insertion and removal for elements with known locations, but without fast
     * random access to elements. Internally implemented as a doubly linked list. Use ForwardList if you do not need
     * reverse iteration.
     */
    template <typename T, typename A = StdAllocator<T>>
    using List = std::list<T, A>;

    /**
     * Container that supports constant time insertion and removal for elements with known locations, but without fast
     * random access to elements. Internally implemented as a singly linked list that doesn't support reverse iteration.
     */
    template <typename T, typename A = StdAllocator<T>>
    using ForwardList = std::forward_list<T, A>;

    /** First-in, last-out data structure. */
    template <typename T, typename A = StdAllocator<T>>
    using Stack = std::stack<T, std::deque<T, A>>;

    /** First-in, first-out data structure. */
    template <typename T, typename A = StdAllocator<T>>
    using Queue = std::queue<T, std::deque<T, A>>;

    /** An associative container containing an ordered set of elements. */
    template <typename T, typename A = StdAllocator<T>>
    using Set = std::set<T, A>;

    /** A combination of two elements. */
    template <typename L, typename R>
    using Pair = std::pair<L, R>;

    /** An associative container containing an ordered set of key-value pairs. */
    template <typename K, typename V, typename P = std::less<K>, typename A = StdAllocator<Pair<const K, V>>>
    using Map = std::map<K, V, P, A>;

    /** An associative container containing an ordered set of elements where multiple elements can have the same key. */
    template <typename T, typename P = std::less<T>, typename A = StdAllocator<T>>
    using MultiSet = std::multiset<T, P, A>;

    /** An associative container containing an ordered set of key-value pairs where multiple elements can have the same key. */
    template <typename K, typename V, typename P = std::less<K>, typename A = StdAllocator<Pair<const K, V>>>
    using MultiMap = std::multimap<K, V, P, A>;

    /** An associative container containing an unordered set of elements. Usually faster than Set for larger data sets. */
    template <typename T, typename H = HashType<T>, typename C = std::equal_to<T>, typename A = StdAllocator<T>>
    using UnorderedSet = std::unordered_set<T, H, C, A>;

    /** An associative container containing an ordered set of key-value pairs. Usually faster than Map for larger data sets. */
    template <typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>, typename A = StdAllocator<Pair<const K, V>>>
    using UnorderedMap = std::unordered_map<K, V, H, C, A>;

    /**
     * An associative container containing an ordered set of key-value pairs where multiple elements can have the same key.
     * Usually faster than MultiMap for larger data sets.
     */
    template <typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>, typename A = StdAllocator<Pair<const K, V>>>
    using UnorderedMultimap = std::unordered_multimap<K, V, H, C, A>;

    /* ###################################################################
    *  ############# SHARED PTR INSTANTIATION ############################
    *  ################################################################ */

    /**
    * \brief Create a new shared pointer using a custom allocator category.
    */
    template<class Type, class Allocator = BasicAllocator, class... Args>
    SPtr<Type> te_shared_ptr_new(Args &&... args)
    {
        return std::allocate_shared<Type>(StdAllocator<Type, Allocator>(), std::forward<Args>(args)...);
    }

    /* ###################################################################
    *  ############# UNIQUE PTR INSTANTIATION ############################
    *  ################################################################ */

    /**
    * \brief Create a new unique pointer using a custom allocator category.
    */
    template<class Type, class Allocator = GeneralAllocator, class... Args>
    UPtr<Type> te_unique_ptr_new(Args &&... args)
    {
        Type*rawPtr = (Type*)te_allocate<Type, Allocator>(std::forward<Args>(args)...);
        return te_unique_ptr<Type, Allocator>(rawPtr);
    }
}