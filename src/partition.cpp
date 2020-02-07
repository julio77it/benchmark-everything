#include <fmt/format.h>
#include "partition.hpp"

int main()
{
    std::vector<int> input    = {-4, -2,  0,  1,  5}; 
    std::vector<int> expected = { 0,  1,  4, 16, 25}; 

    fmt::print("INPUT = [{}] ; EXPECTED = [{}]\n",  fmt::join(input, " "), fmt::join(expected, " "));

    fmt::print("partition_simple\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_simple(input), " "));

    fmt::print("partition_transform\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_transform(input), " "));

    fmt::print("partition_multiset\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_multiset(input), " "));

    fmt::print("partition_sortsquares\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_sortsquares(input), " "));

    fmt::print("partition_final_draft\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_final_draft(input), " "));

    fmt::print("partition_final_optimized\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_final_optimized(input), " "));

    #ifdef __cplusplus >= 201803L
    fmt::print("partition_final_cxx20\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_final_cxx20(input), " "));
    #endif

    fmt::print("partition_final_range_1st\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_final_range_1st(input), " "));

    fmt::print("partition_final_range_2nd\n");
    fmt::print("f([{}]) = [{}]\n",  fmt::join(input, " "), fmt::join(partition_final_range_2nd(input), " "));
}