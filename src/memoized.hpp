//
// Memoization helper functions
// Copyright (C) 2020 Giulio Guarnone
//
#ifndef MEMOIZED_HPP
#define MEMOIZED_HPP

#include <map>
#include <mutex>
#include <tuple>
#include <type_traits>
#include <unordered_map>


template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...))
{
    // Creates a cache that maps tuples of arguments to the calculated
    // results. If you wanted to use this in a multithreaded environment,
    // you’d need to synchronize the changes to it with a mutex,
    // as in listing 6.1.
    std::map<std::tuple<Args...>, Result> cache;

    return [f, cache](Args... args) mutable -> Result
    {
        static std::recursive_mutex m_cache_mutex;

        std::unique_lock<std::recursive_mutex>
                lock{m_cache_mutex};

        // Lambda that gets the arguments and checks whether the result is
        // already cached
        const auto args_tuple =
            std::make_tuple(args...);
        const auto cached = cache.find(args_tuple);

        if (cached == cache.end()) {
            // In case of a cache miss, calls  the function and stores the
            // result to the cache
            auto result = f(args...);
            cache[args_tuple] = result;
            return result;

        } else {
            // If the result is found in the cache, returns it to the caller
            return cached->second;
        }
    };
}


class null_param {};

template <class Sig, class F>
class memoize_helper;

template <class Result, class... Args, class F>
class memoize_helper<Result(Args...), F> {
private:
    using function_type = F;
    using args_tuple_type
        = std::tuple<std::decay_t<Args>...>;

    function_type f;

    // Defines the cache, and, because it’s  mutable, synchronizes
    // all the changes
    mutable std::map<args_tuple_type, Result> m_cache;
    mutable std::recursive_mutex m_cache_mutex;

public:
    // The constructors need to initialize the wrapped function.
    // You could made copy-constructor copy the cached values as well,
    // but that’s not necessary.

    template <typename Function>
    memoize_helper(Function&& ff, null_param)
        : f(ff)
    {
    }

    memoize_helper(const memoize_helper& other)
        : f(other.f)
    {
    }

    template <class... InnerArgs>
    Result operator()(InnerArgs&&... args) const
    {
        std::unique_lock<std::recursive_mutex>
                lock{m_cache_mutex};

        // Searches for the cached value
        const auto args_tuple =
            std::make_tuple(args...);
        const auto cached = m_cache.find(args_tuple);

        //  If the cached value is found, returns it without calling f
        if (cached != m_cache.end()) {
            return cached->second;

        } else {
            // If the cached value isn’t found, calls f and stores
            // the result. Passes *this as the first argument: the
            // function to be used for the recursive call.
            auto&& result = f(
                    *this,
                    std::forward<InnerArgs>(args)...);
            m_cache[args_tuple] = result;
            return result;
        }
    }
};

template <class Sig, class F>
memoize_helper<Sig, std::decay_t<F>>
make_memoized_r(F&& f)
{
    return {std::forward<F>(f), null_param{}};
}


#endif
