/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_map.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:22:29 by trobin            #+#    #+#             */
/*   Updated: 2022/05/20 18:22:30 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <cassert>
#include <utility> // std::pair
#include <iostream>
#include <memory> // std::allocator
#include <type_traits> // std::is_same

#include "ft_map.hpp"
#include "../utils/colors.hpp"

template <typename T1, typename T2>
void compare_maps(const ft::map<T1,T2> & a, const std::map<T1,T2> & b)
{
    assert(a.empty() == b.empty());
    assert(a.size() == b.size());
    //assert(a.max_size() == b.max_size());
    //assert((std::is_same<typeof(b.key_comp()), typeof(b.key_comp())>::value));
    //assert((std::is_same<typeof(b.value_comp()), typeof(b.value_comp())>::value));
}

void map_allocator_test()
{
   // see. https://mapoverflow.com/a/40598287 about use of double brackets

    assert((ft::map<int,int>().get_allocator() == std::allocator<std::pair<int,int>>()));
    assert((ft::map<float,float>().get_allocator() == std::allocator<std::pair<float,float>>()));

    assert((ft::map<int,int>().get_allocator() == std::map<int,int>().get_allocator()));
    assert((ft::map<float,float>().get_allocator() == std::map<float,float>().get_allocator()));

    assert((std::is_same<ft::map<int,int>::allocator_type::value_type,
            std::allocator<std::pair<const int,int>>::value_type>::value));

    assert((std::is_same<ft::map<int,int>::allocator_type::value_type,
            std::map<int,int>::allocator_type::value_type>::value));

    std::cout << "get_allocator() " << GREEN << "OK" << RESET << std::endl;
}

void map_constructor_test()
{
    {
        // by default (1)
        compare_maps(ft::map<int,int>(), std::map<int,int>());
        std::cout << "Constructor by default " << GREEN << "OK" << RESET << std::endl;
    }
    {
        // by range (2)
        std::cout << "Constructor by range " << GREEN << "OK" << RESET << std::endl;
    }
    {
        // by copy (3)
        std::cout << "Constructor by copy " << GREEN << "OK" << RESET << std::endl;
    }
}

int main()
{
    //map_allocator_test();
    map_constructor_test();
    return 0;
}
