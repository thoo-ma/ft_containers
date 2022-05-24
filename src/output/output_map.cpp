/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_map.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:22:29 by trobin            #+#    #+#             */
/*   Updated: 2022/05/24 15:51:05 by trobin           ###   ########.fr       */
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
   // assert(typeid(a.key_comp()).name() == typeid(b.key_comp()).name());
   // assert(typeid(a.value_comp()).name() == typeid(b.value_comp()).name());
}

void map_allocator_test()
{
    // TODO
    // result may change whether we use ft::pair or std::pair
    //
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
        // TODO
        // by range (2)
        std::cout << "Constructor by range " << GREEN << "OK" << RESET << std::endl;
    }
    {
        // by copy (3)
        compare_maps(ft::map<int,int>(ft::map<int,int>()), std::map<int,int>(std::map<int,int>()));
        std::cout << "Constructor by copy " << GREEN << "OK" << RESET << std::endl;
    }
}

void map_key_comp_test()
{
    // verify default type of key_compare with std::map
     assert((std::is_same<std::less<int>, std::map<int,char>::key_compare>::value));
     assert((std::is_same<std::less<char>,std::map<char,int>::key_compare>::value));
    
     // compare default type of key_compare
     assert((std::is_same<std::less<int>, ft::map<int,char>::key_compare>::value));
     assert((std::is_same<std::less<char>,ft::map<char,int>::key_compare>::value));
    
     // compare default 
     assert((typeid(std::map<int,int>().key_comp()).name() == typeid(ft::map<int,int>().key_comp()).name()));
     assert((typeid(std::map<char,int>().key_comp()).name() == typeid(ft::map<char,int>().key_comp()).name()));
     assert((typeid(std::map<const char,int>().key_comp()).name() == typeid(ft::map<const char,int>().key_comp()).name()));
    
     // 3rd template arg modified by hand
     assert((typeid(ft::map<int,int,std::less<char>>().key_comp()).name() == typeid(std::less<char>).name()));
     assert((typeid(ft::map<int,int,std::less<char>>().key_comp()).name() == typeid(std::map<char,int>().key_comp()).name()));
    
     std::cout << "key_comp() " << GREEN << "OK" << RESET << std::endl;
}

void map_value_comp_test()
{
    // TODO
     std::cout << "value_comp() " << GREEN << "OK" << RESET << std::endl;
}

int main()
{
    map_allocator_test();
    //map_constructor_test();
    //map_key_comp_test();
    //map_value_comp_test();

    return 0;
}
