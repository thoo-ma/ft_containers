#include <map>
#include <cassert>
#include <utility> // std::pair
#include <iostream>
#include <memory> // std::allocator
#include <type_traits> // std::is_same

#include "ft_map.hpp"
#include "../utils/colors.hpp"

void stack_allocator_test()
{
    // compare with std::allocator
    assert((ft::map<int,int>().get_allocator() == std::allocator<std::pair<int,int>>()));
    assert((ft::map<float,float>().get_allocator() == std::allocator<std::pair<float,float>>()));

    // compare with std::map.get_allocator()
    assert((ft::map<int,int>().get_allocator() == std::map<int,int>().get_allocator()));
    assert((ft::map<float,float>().get_allocator() == std::map<float,float>().get_allocator()));

    assert((std::is_same<ft::map<int,int>::allocator_type::value_type,
            std::allocator<std::pair<int,int>>::value_type>::value));

    assert((std::is_same<ft::map<int,int>::allocator_type::value_type,
            std::map<int,int>::allocator_type::value_type>::value));

   // see. https://stackoverflow.com/a/40598287 about doubling brackets

    int x = 42;
    char c = x;
    std::cout << "get_allocator() " << GREEN << "OK" << RESET << std::endl;
}

int main()
{
    stack_allocator_test();
    return 0;
}
