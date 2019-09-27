#ifndef MEMOIZED_HPP
#define MEMOIZED_HPP

#include <map>

template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...))
{
    std::map<std::tuple<Args...>, Result> cache;

    return [f, cache](Args... args) mutable -> Result
    {
        const auto args_tuple = std::make_tuple(args...);

        const auto cached = cache.find(args_tuple);

        if (cached == cache.end())
        {
            auto result = f(args...);
            cache[args_tuple] = result;
            return result;

        }
        else
        {
            return cached->second;
        }
    };
}

#endif
