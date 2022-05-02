#include <cassert>
#include <utility>
#include <iostream>
#include "ft_pair.hpp"
#include "../utils/colors.hpp"

#pragma GCC diagnostic ignored "-Wdeprecated-copy"

template <typename T1, typename T2>
void compare_pairs(const std::pair<T1,T2> & pair_1,
                   const ft::pair<T1,T2>  & pair_2)
{
    assert(pair_1.first == pair_2.first);
    assert(pair_1.second == pair_2.second);
}

void test_pair_constructed_by_default()
{
    compare_pairs(std::pair<int,int>(), ft::pair<int,int>());
    compare_pairs(std::pair<char,char>(), ft::pair<char,char>());
    compare_pairs(std::pair<float,float>(), ft::pair<float,float>());
    compare_pairs(std::pair<double,double>(), ft::pair<double,double>());
    compare_pairs(std::pair<unsigned char,unsigned char>(),
                   ft::pair<unsigned char,unsigned char>());

    std::cout << "constructor by default " << GREEN << "OK" << RESET << std::endl;
}

void test_pair_constructed_by_copy()
{
    // copied from default
    compare_pairs(std::pair<int,int>(std::pair<int,int>()),
                    ft::pair<int,int>(ft::pair<int,int>()));
    compare_pairs(std::pair<char,char>(std::pair<char,char>()),
                    ft::pair<char,char>(ft::pair<char,char>()));
    compare_pairs(std::pair<float,float>(std::pair<float,float>()),
                    ft::pair<float,float>(ft::pair<float,float>()));
    compare_pairs(std::pair<double,double>(std::pair<double,double>()),
                    ft::pair<double,double>(ft::pair<double,double>()));
    compare_pairs(std::pair<unsigned char,unsigned char>
                 (std::pair<unsigned char,unsigned char>()),
                    ft::pair<unsigned char,unsigned char>
                    (ft::pair<unsigned char,unsigned char>()));

    // copied from non-default
    compare_pairs(std::pair<int,int>(std::pair<int,int>(1,42)),
                    ft::pair<int,int>(ft::pair<int,int>(1,42)));

    std::cout << "constructor by copy " << GREEN << "OK" << RESET << std::endl;
}

int main()
{
    test_pair_constructed_by_default();
    test_pair_constructed_by_copy();
//    test_pair_constructed_by_init();

//    test_pair_assignation();

    return 0;
}
