#include <cassert>
#include <type_traits>
#include "ft_type_traits.hpp"

void is_integral_test()
{
    // true

    // int
    assert(std::is_integral<int>::value == ft::is_integral<int>::value);
    // const int
    assert(std::is_integral<const int>::value == ft::is_integral<const int>::value);
    // ::() synonym of ::value
    assert(std::is_integral<int>() == ft::is_integral<int>());
    // signed char (is an edge case)
    assert(std::is_integral<signed char>::value == ft::is_integral<signed char>::value);

    // false

    // float
    assert(std::is_integral<float>::value == ft::is_integral<float>::value);
    // const float
    assert(std::is_integral<const float>::value == ft::is_integral<const float>::value);

    // typeid -- // TODO
    //assert(typeid(std::is_integral<int>::type).name() == typeid(ft::is_integral<int>::type).name());
}

int main()
{
    is_integral_test();
    return 0;
}
