#include <cassert>
#include <utility>
#include <iostream>

#include "ft_pair.hpp"
#include "../utils/colors.hpp" // log.hpp

//#pragma GCC diagnostic ignored "-Wdeprecated-copy"

/****** Test pair equality ****************************************************/

template <typename T1, typename T2>
void compare_pairs(const std::pair<T1,T2> & pr_1, const ft::pair<T1,T2> & pr_2)
{
    assert(pr_1.first == pr_2.first);
    assert(pr_1.second == pr_2.second);
}

/****** Custom datatype *******************************************************/

struct Foo
{
    int i;
    Foo() : i(42) { }
    Foo(int _i) : i(_i) { }
};

bool operator==(const Foo & lhs, const Foo & rhs)
{ return lhs.i == rhs.i; }

/****** pair() by default *****************************************************/

void test_pair_constructed_by_default()
{
    // with standard datatypes
    compare_pairs(std::pair<int,int>(), ft::pair<int,int>());
    compare_pairs(std::pair<char,char>(), ft::pair<char,char>());
    compare_pairs(std::pair<float,float>(), ft::pair<float,float>());
    compare_pairs(std::pair<double,double>(), ft::pair<double,double>());
    compare_pairs(std::pair<unsigned char,unsigned char>(),
                   ft::pair<unsigned char,unsigned char>());

    // with custom datatypes
    typedef int foo;
    compare_pairs(std::pair<foo,foo>(), ft::pair<foo,foo>());
    compare_pairs(std::pair<Foo,Foo>(), ft::pair<Foo,Foo>());

    log("constructor by default");
}

/****** pair() by copy ********************************************************/

void test_pair_constructed_by_copy()
{
    // copied from default with standard datatypes
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

    // copied from default with custom datatype
    compare_pairs(std::pair<Foo,Foo>(std::pair<Foo,Foo>()),
                    ft::pair<Foo,Foo>(ft::pair<Foo,Foo>()));

    // copied from fill with same types
    compare_pairs(std::pair<int,int>(std::pair<int,int>(1,42)),
                    ft::pair<int,int>(ft::pair<int,int>(1,42)));

    // it works because `Foo` is constructible from `int`
    compare_pairs(std::pair<Foo,Foo>(std::pair<int,int>()),
                   ft::pair<Foo,Foo>(ft::pair<int,int>()));

    // from const to non-const
    compare_pairs(std::pair<int,int>(std::pair<const int, const int>()),
                    ft::pair<int,int>(ft::pair<const int,const int>()));

    // from non-const to const
    compare_pairs(std::pair<const int, const int>(std::pair<int, int>()),
                    ft::pair<const int,const int>(ft::pair<int, int>()));

    // both
    compare_pairs(std::pair<const int, int>(std::pair<int, const int>()),
                    ft::pair<const int, int>(ft::pair<int, const int>()));

    // here compiler try to convert `float` to `int` in order to build Foo(int)
    // compiler warn with -Wconversion
    //compare_pairs(std::pair<Foo,Foo>(std::pair<float,float>()),
    //               ft::pair<Foo,Foo>(ft::pair<float,float>()));

    // copied from fill with different types
    // --> need to implement is_constructible to avoid warning from -Wconversion
    // compare_pairs(std::pair<int,char>(std::pair<int,double>(1,421.42)),
    //                ft::pair<int,char>(ft::pair<int,double>(1,421.42)));

    log("constructor by copy");
}

/****** pair() by init ********************************************************/

void test_pair_constructed_by_init()
{
    int i = 42;
    char c = 'a';
    double d = 0.042;
    float f = 0.042f;

    compare_pairs(std::pair<int,char>(i,c), ft::pair<int,char>(i,c));
    compare_pairs(std::pair<char,int>(c,i), ft::pair<char,int>(c,i));
    compare_pairs(std::pair<int,double>(i,d), ft::pair<int,double>(i,d));
    compare_pairs(std::pair<float,char>(f,c), ft::pair<float,char>(f,c));

    Foo foo;
    compare_pairs(std::pair<float,Foo>(f,foo), ft::pair<float,Foo>(f,foo));

    log("constructor by init");
}

/****** operator= *************************************************************/

void test_pair_assignation()
{
    /// @todo add tests ? like above, mixin' types and using user-defined ones
    {
        // ft
        ft::pair<int,int> a(42,42);
        ft::pair<int,int> b;

        assert(a != b);
        b = a;
        assert(a == b);
    }
    {
        // std
        std::pair<int,int> a(42,42);
        std::pair<int,int> b;

        assert(a != b);
        b = a;
        assert(a == b);
    }
    log("operator=");
}

/****** make_pair() ***********************************************************/

void test_make_pair()
{
    compare_pairs(std::pair<int,int>(42,42), ft::make_pair<int,int>(42,42));
    compare_pairs(std::pair<int,char>(42,'z'), ft::make_pair<int,char>(42,'z'));

    log("make_pair()");
}

/****** main ******************************************************************/

int main()
{
    test_pair_constructed_by_default();
    test_pair_constructed_by_copy();
    test_pair_constructed_by_init();
    test_pair_assignation();
    test_make_pair();

    return 0;
}
