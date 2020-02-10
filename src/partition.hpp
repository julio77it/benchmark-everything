//
// partition functions
// https://marcoarena.wordpress.com/2019/11/28/tale-of-an-insight/
//
#ifndef PARTITION_HPP
#define PARTITION_HPP
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <range/v3/all.hpp>

std::vector<int> partition_simple(std::vector<int> const& input)
{
    std::vector<int> output;

    for (auto& e : input)
        output.push_back(e * e);

    std::sort(std::begin(output), std::end(output));

    return output;
}

std::vector<int> partition_transform(std::vector<int> const& input)
{
    std::vector<int> output;

    std::transform(std::begin(input), std::end(input), std::back_insert_iterator(output), [](auto e) { return e * e; });
    std::sort(std::begin(output), std::end(output));

    return output;
}

std::vector<int> partition_multiset(std::vector<int> const& input)
{
    std::vector<int> output;
    std::multiset<int> temp;

    std::transform(std::begin(input), std::end(input), std::inserter(temp, std::end(temp)), [](auto e) { return e * e; });
    output.assign(std::begin(temp), std::end(temp));

    return output;
}

template<typename T>
T square(T input) {return input * input;}

std::vector<int> partition_sortsquares(std::vector<int>& input)
{
    std::vector<int> output(input.size());
    // locate the first positive value
    auto it  = std::find_if(std::begin(input), std::end(input), [](int i) { return i>= 0; });
    auto pos = std::distance(std::begin(input), it);
    auto neg = pos - 1;

    auto len = input.size();
    for (std::size_t i = 0; i < len; ++i)
    {
        // negative values over
        if (neg < 0)
        {
            output[i] = square(input[pos++]);
        }
        // positive values over
        else if (pos >= len)
        {
            output[i] = square(input[neg--]);
        }
        // positive value is bigger
        else if (std::abs(input[pos]) > std::abs(input[neg]))
        {
            output[i] = square(input[neg--]);
        }
        // negative value is bigger
        else
        {
            output[i] = square(input[pos++]);
        }
    }
    return output;
}

std::vector<int> partition_final_draft(std::vector<int> const& input)
{
    std::vector<int> negatives, positives, output(input.size());
    std::partition_copy(std::begin(input), std::end(input), std::back_inserter(negatives), std::back_inserter(positives), [](auto i) { return i<0; });
    std::reverse(std::begin(negatives), std::end(negatives));
    std::transform(std::begin(negatives), std::end(negatives), std::begin(negatives), [](auto i){ return i*i; });
    std::transform(std::begin(positives), std::end(positives), std::begin(positives), [](auto i){ return i*i; });
    std::merge(std::begin(negatives), std::end(negatives), std::begin(positives), std::end(positives), std::begin(output));

    return output;
}

std::vector<int> partition_final_optimized(std::vector<int> const& input)
{
    std::vector<int> v(input.size()), output(input.size());
    std::copy(std::begin(input), std::end(input), std::begin(v)); // copia per preservare originale
    auto pos = std::find_if(std::begin(v), std::end(v), [](auto i){ return i>=0; }); // find first non-negative
    std::transform(std::begin(v), std::end(v), std::begin(v), [](auto i){return i*i;}); // square them all
    std::merge(std::make_reverse_iterator(pos), std::rend(v), pos, std::end(v), std::begin(output)); // the magic is here
    return output;
}
#ifdef __cplusplus >= 201803L
std::vector<int> partition_final_cxx20(std::vector<int> const& input)
{
    std::vector<int> output(input.size());
    std::copy(std::begin(input), std::end(input), std::begin(output)); // copia per preservare originale
    auto pos = std::find_if(std::begin(output), std::end(output), [](auto i){ return i>=0; });
    std::transform(std::begin(output), std::end(output), std::begin(output), [](auto i){return i*i;});
    std::reverse(std::begin(output), pos); // needed for inplace_merge
    std::inplace_merge(std::begin(output), pos, std::end(output));
    return output;
}
#endif

std::vector<int> partition_final_range_1st(std::vector<int> const& input)
{
    std::vector<int> output(input.size());
    auto firstPos  = ranges::find_if(input, [](auto i){ return i>=0; });
    auto positives = ranges::subrange(firstPos, std::end(input));
    auto negatives = ranges::subrange(std::make_reverse_iterator(firstPos), std::rend(input));

    const auto square = [](auto i) { return i*i; };
    ranges::merge(ranges::views::transform(positives, square),
                  ranges::views::transform(negatives, square),
                  std::begin(output));
    return output;
}

std::vector<int> partition_final_range_2nd(std::vector<int> const& input)
{
    std::vector<int> output(input.size());
    auto positives = ranges::views::drop_while(input, [](auto i){ return i<0; });
    auto negatives = ranges::views::drop_while(ranges::views::reverse(input), [](auto i) { return i>=0; });

    const auto square = [](auto i) { return i*i; };
    ranges::merge(ranges::views::transform(positives, square),
                  ranges::views::transform(negatives, square),
                  std::begin(output));
    return output;
}

#endif
