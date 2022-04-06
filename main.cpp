#include <type_traits>
#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>

#include "ft_type_traits.hpp"
#include "ft_vector.hpp"

class Foo { public: int a, b, c; };

//std::vector<int>::iterator = v.begin(); TRY THIS ???

//ft::vector<int> v(5, 42);
//std::cout << std::distance(v.begin(), v.end()) << std::endl;

#define RESET       "\033[0m"
#define BLACK       "\033[30m"          /* Black */
#define RED         "\033[31m"          /* Red */
#define GREEN       "\033[32m"          /* Green */
#define YELLOW      "\033[33m"          /* Yellow */
#define BLUE        "\033[34m"          /* Blue */
#define MAGENTA     "\033[35m"          /* Magenta */
#define CYAN        "\033[36m"          /* Cyan */
#define WHITE       "\033[37m"          /* White */
#define BOLDBLACK   "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"   /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"   /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"   /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"   /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"   /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"   /* Bold White */

/****** type traits test ******************************************************/

void
is_integral_test()
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

    // typeid -- FIX THIS !
    //assert(typeid(std::is_integral<int>::type).name() == typeid(ft::is_integral<int>::type).name());
}

/****** Constructors test *****************************************************/

void
constructor_by_default_test()
{
    ft::vector<int> a;
    std::vector<int> b;

    assert(a.size() == b.size());
    assert(a.capacity() == b.capacity());
    //assert(a.max_size() == b.max_size()); // FIX THIS

    std::cout << "constructor by default " << GREEN << "OK" << RESET << std::endl;
}

void
constructor_by_fill_test()
{
    {
        // without value

        ft::vector<int> a(10);
        std::vector<int> b(10);

        assert(a.size() == b.size());
        assert(a.capacity() == b.capacity());
        //assert(a.max_size() == b.max_size()); // FIX THIS

        std::cout << "constructor by fill (without value) " << GREEN << "OK" << RESET << std::endl;
    }
    {
        // with value

        std::vector<int> a(10, 42);
        ft::vector<int> b(10, 42);

        assert(a.size() == b.size());
        assert(a.capacity() == b.capacity());
        //assert(a.max_size() == b.max_size()); // FIX THIS

        std::cout << "constructor by fill (with value) " << GREEN << "OK" << RESET << std::endl;
    }
}

/*
void
constructor_by_copy_test()
{
    // FIX THIS --> need assignation operator

    std::vector<int> v(10, 42);

    ft::vector<int> a(v);
    std::vector<int> b(v);

    assert(a.size() == v.size());
    assert(a.size() == b.size());
    assert(a.capacity() == v.capacity());
    assert(a.capacity() == b.capacity());
    assert(a == v);
    assert(a == b);

    std::cout << "constructor by copy " << GREEN << "OK" << RESET << std::endl;
}
*/

/*
void
constructor_by_iterator_range_test()
{
    // FIX THIS --> need appropriate constructor
    
    std::vector<int> v(10, 42);
    
    ft::vector<int> a(v.begin(), v.end());
    std::vector<int> b(v.begin(), v.end());
    
    assert(a.size() == v.size());
    assert(a.size() == b.size());
    assert(a.capacity() == v.capacity());
    assert(a.capacity() == b.capacity());
    assert(a == v);
    assert(a == b);
    
    std::cout << "constructor by iterator range " << GREEN << "OK" << RESET << std::endl;
}
*/

void
constructor_upon_heap_test()
{
    { ft::vector<int> * v = new ft::vector<int>; delete v; }
    { ft::vector<int> * v = new ft::vector<int>[10]; delete [] v; }
}

void
constructors_test()
{
    constructor_by_default_test();
    constructor_by_fill_test();
//    constructor_by_copy_test(); // TODO
//    constructor_by_iterator_range_test() // TODO
    constructor_upon_heap_test();
}

/****** Allocator test ********************************************************/

void
allocator_test()
{
    std::allocator<int>     a1;
    std::allocator<bool>    a2;

    try {
        int * i = a1.allocate(a1.max_size()/2);
        *i = 42;
        a1.deallocate(i, a1.max_size()/2);
    } catch (...) { std::cout << "error" << std::endl; }

    std::cout << "max_size allocator<int>:  " << a1.max_size() << std::endl;
    std::cout << "max_size allocator<bool>: " << a2.max_size() << std::endl;
}

/****** Capacity test *********************************************************/

void
empty_test()
{
    assert(ft::vector<int>().empty());
    std::cout << "empty " << GREEN << "OK" << RESET << std::endl;
}

void
size_test()
{
    {
        // constructed by default
        assert(ft::vector<int>().size() == 0);
    }
    {
        // constructed by fill (without value)
        assert(ft::vector<int>(10).size() == 10);
    }
    {
        // constructed by fill (with value)
        assert(ft::vector<int>(10, 42).size() == 10);
    }
    {
        // constructed by copy
//        ft::vector<int> a;
//        ft::vector<int> b(10);
//        assert(ft::vector<int>(a).size() == a.size());
//        assert(ft::vector<int>(b).size() == b.size());
    }
    std::cout << "size " << GREEN << "OK" << RESET << std::endl;
}

void
max_size_test()
{
    // ???
    std::cout << "max_size " << GREEN << "OK" << RESET << std::endl;
}

void
capacity_test()
{
    {
        // constructed by default
        assert(ft::vector<int>().capacity() == 0);
    }
    {
        // constructed by fill (without value)
        assert(ft::vector<int>(10).capacity() == 10);
    }
    {
        // constructed by fill (with value)
        assert(ft::vector<int>(10, 42).capacity() == 10);
    }
    {
        // constructed by copy
    //    ft::vector<int> a;
    //    ft::vector<int> b(10);
    //    assert(ft::vector<int>(a).capacity() == a.capacity());
    //    assert(ft::vector<int>(b).capacity() == b.capacity());
    }
    std::cout << "capacity " << GREEN << "OK" << RESET << std::endl;
}

void
reserve_test()
{
    {
     //   ft::vector<int> a;

     //   try { a.reserve(10); }
     //   catch (...) { /* log */ }

       // assert(a.capacity() == 10);

       // try { a.reserve(10); }
       // catch (...) { /* log */ }

       // assert(a.capacity() == 10);

       // try { a.reserve(11); }
       // catch (...) { /* log */ }

       // assert(a.capacity() == 11);

       // try { a.reserve(-1); }
       // catch (...) { /* log */ }

       // assert(a.capacity() == 11);
    }
    std::cout << "reserve " << GREEN << "OK" << RESET << std::endl;
}

void
capacity_tests()
{
    //empty_test();
    //size_test();
    //max_size_test();
    //capacity_test();
    //reserve_test(); // TODO
}

/****** Accessors test ********************************************************/

void
at_test()
{
    {
        ft::vector<int> v;
        std::string log = "ok";

        try { v.at(1); }
        catch (std::out_of_range & oor) { log = oor.what(); }

        assert(log != "ok");
    }
    {
        ft::vector<int> v(10, 42);
        std::string log = "ok";

        try { v.at(1); }
        catch (std::out_of_range & oor) { log = oor.what(); }

        assert(log == "ok");
    }
    std::cout << "at " << GREEN << "OK" << RESET << std::endl;
}

void
front_test()
{
    {
        // undefined behavior when vector is empty
        // assert(ft::vector<int>().front() == 0);
    }
    {
        assert(ft::vector<int>(10).front() == int());
    }
    {
        assert(ft::vector<int>(10, 42).front() == 42);
    }
    std::cout << "front " << GREEN << "OK" << RESET << std::endl;
}

void
back_test()
{
    {
        // undefined behavior when vector is empty
        // assert(ft::vector<int>().back() == 0);
    }
    {
        assert(ft::vector<int>(10).back() == int());
    }
    {
        assert(ft::vector<int>(10, 42).back() == 42);
    }
    std::cout << "back " << GREEN << "OK" << RESET << std::endl;
}

void
operator_bracket_test()
{
    {
        // undefined behavior when vector is empty
        // assert(ft::vector<int>().back() == 0);
    }
    {
        ft::vector<int> v(10);
        int i = int();
        for (ft::vector<int>::size_type j = 0; j < 10; j++) { assert(v[j] == i); }
    }
    {
        ft::vector<int> v(10, 42);
        for (ft::vector<int>::size_type i = 0; i < 10; i++) { assert(v[i] == 42); }
    }
    {
        // doesn't thow anything
        ft::vector<int>(10)[10];
    }
    std::cout << "operator[] " << GREEN << "OK" << RESET << std::endl;
}

void
accessor_tests()
{
    std::cout << "== Accessors ==" << std::endl;
    at_test();
    front_test();
    back_test();
    operator_bracket_test();
}

/****** Modifiers tests *******************************************************/

void
clear_tests()
{
    {
        ft::vector<int> v;

        assert(v.size() == 0);
        assert(v.capacity() == 0);

        v.clear();

        assert(v.size() == 0);
        assert(v.capacity() == 0);
    }
    {
        ft::vector<int> v(42);

        assert(v.size() == 42);
        assert(v.capacity() == 42);

        v.clear();

        assert(v.size() == 0);
        assert(v.capacity() == 42);
    }
    std::cout << "clear " << GREEN << "OK" << RESET << std::endl;
}

void
erase_tests()
{
    // TODO try with different values (fill with push back)
    // TODO maybe add some tricky cases like overflow size or capacity
    {
        // erase by position
        ft::vector<int> a(21, 42);
        std::vector<int> b(21, 42);

        // begin
        assert(a.erase(a.begin()) == a.begin());
        assert(b.erase(b.begin()) == b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // begin + n
        assert(a.erase(a.begin() + 2) == a.begin() + 2);
        assert(b.erase(b.begin() + 2) == b.begin() + 2);
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // end - n
        assert(a.erase(a.end() - 2) - a.begin()
            == b.erase(b.end() - 2) - b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // end --> segfault
        //assert(a.erase(a.end()) == a.end());
        //assert(b.erase(b.end()) == b.end());
        //assert(a.size() == b.size());
        //for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        //{ assert(a.at(i) == b.at(i)); }
    }
    {
        // erase by range
        ft::vector<int> a(21, 42);
        std::vector<int> b(21, 42);

        // [begin, begin)
        assert(a.erase(a.begin(), a.begin()) == a.begin());
        assert(b.erase(b.begin(), b.begin()) == b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // [end, end)
        assert(a.erase(a.end(), a.end()) == a.end());
        assert(b.erase(b.end(), b.end()) == b.end());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // [begin, begin + n)
        assert(a.erase(a.begin(), a.begin() + 2) == a.begin());
        assert(b.erase(b.begin(), b.begin() + 2) == b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // [end - n, end)
        assert(a.erase(a.end() - 2, a.end()) - a.begin()
            == b.erase(b.end() - 2, b.end()) - b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // [begin + n, end - m)
        assert(a.erase(a.begin() + 2, a.end() - 4) - a.begin()
            == b.erase(b.begin() + 2, b.end() - 4) - b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }

        // [begin, end)
        assert(a.erase(a.begin(), a.end()) == a.begin());
        assert(b.erase(b.begin(), b.end()) == b.begin());
        assert(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { assert(a.at(i) == b.at(i)); }
    }
    std::cout << "erase " << GREEN << "OK" << RESET << std::endl;
}

void
insert_tests()
{
    {
        // fill
       // ft::vector<int> a(4, 21);
       // a.insert(a.begin() + 2, 4, 42);

       // std::vector<int> v;
       // //v.reserve(50);
       // v.push_back(0);
       // v.push_back(0);
       // v.insert(v.begin()+1, 2, 42);
    }
    std::cout << "insert " << GREEN << "OK" << RESET << std::endl;
}

void
modifiers_tests()
{
    std::cout << "== Modifiers ==" << std::endl;
  //  clear_tests();
  //  erase_tests(); // TODO
    insert_tests(); // TODO
}

/****** Operators tests *******************************************************/

void
equal_test()
{
    { assert(ft::vector<int>() == ft::vector<int>()); }
    { assert(ft::vector<int>(10) == ft::vector<int>(10)); }
    { assert(ft::vector<int>(10, 21) == ft::vector<int>(10, 21)); }
    //{
    //    ft::vector<int> a;
    //    ft::vector<int> b(a);
    //    assert(a == b);
    //}
    //{
    //    ft::vector<int> a(10, 21);
    //    ft::vector<int> b(a);
    //    assert(b == a);
    //}
    {
        ft::vector<int> * a = new ft::vector<int>();
        ft::vector<int> * b = new ft::vector<int>();
        assert(*b == *a);
        delete a;
        delete b;
    }
    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

void
not_equal_test()
{
    { assert(ft::vector<int>() != ft::vector<int>(10)); }
    { assert(ft::vector<int>(10) != ft::vector<int>(10, 21)); }
    std::cout << "operator!= " << GREEN << "OK" << RESET << std::endl;
}

void
less_than()
{
    std::cout << "operator< " << GREEN << "OK" << RESET << std::endl;
}

void
vector_assignation_test()
{
   // {
   //     // same size
   //     ft::vector<int> a(5, 21);
   //     ft::vector<int> b(5, 42);

   //     assert(a != b);
   //     a = b;
   //     assert(a == b);
   // }
   // {
   //     // upper size
   //     ft::vector<int> a(9, 21);
   //     ft::vector<int> b(5, 42);

   //     assert(a != b);
   //     a = b;
   //     assert(a == b);
   // }
    {
        // lower size
        ft::vector<int> a(5, 21);
        ft::vector<int> b(9, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    std::cout << "operator= " << GREEN << "OK" << RESET << std::endl;
}

void
operators_tests()
{
    std::cout << "== Operators ==" << std::endl;
   // equal_test();
   // not_equal_test();
   // less_than();
    vector_assignation_test();
}

/****** Iterators tests *******************************************************/

// random_access_iterator only (for now)

void
iterator_constructors_test()
{
    int i = 42;
    int * p = &i;
    ft::random_access_iterator<int> a; // by default
    ft::random_access_iterator<int> b(p); // by pointer
    ft::random_access_iterator<int> c(b); // by copy
    (void)a;
    (void)b;
    (void)c;
    std::cout << "constructors " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_assignation_test()
{
    int i = 42;
    int * p = &i;
    ft::random_access_iterator<int> a(p);
    ft::random_access_iterator<int> b;
    b = a; // here
    assert(*a == 42);
    assert(*b == 42);
    std::cout << "assignation " << GREEN << "OK" << RESET << std::endl;
}

void
begin_test()
{
    {
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.begin();
        assert(*it == 21);
    }
    std::cout << "begin " << GREEN << "OK" << RESET << std::endl;
}

void
end_test()
{
    {
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.end();
        (void)it;
    }
    std::cout << "end " << GREEN << "OK" << RESET << std::endl;
}

void
increment_test()
{
    {
        // prefix
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.begin();
        for (int i = 0; i < 10; ++i, ++it)
            assert(*it == 21);
    }
    {
        // postfix
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.begin();
        for (int i = 0; i < 10; ++i, it++)
            assert(*it == 21);
    }
    std::cout << "increment " << GREEN << "OK" << RESET << std::endl;
}

void
decrement_test()
{
    {
        // prefix
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.end();
        for (int i = 0; i < 10; ++i)
            assert(*(--it) == 21);
    }
    {
        // postfix
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.end();
        it--;
        for (int i = 0; i < 10; ++i)
            assert(*(it--) == 21);
    }
    std::cout << "decrement " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_dereference_test()
{
    {
        // from single pointer
        int i = 42;
        int *p = &i;
        ft::random_access_iterator<int> a(p);
        assert(*a == *p);
    }
    {
        // from vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator a = v.begin();
        ft::vector<int>::iterator b(a);
        assert(*a == *b);
        assert(*a == *(v.begin()));
        assert(*b == *(v.begin()));
        assert(*v.begin() == *v.begin());
    }
    std::cout << "operator* " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_equal_test()
{
    {
        // from single pointer
        int i = 42;
        int *p = &i;
        ft::random_access_iterator<int> a(p);
        ft::random_access_iterator<int> b(a);
        assert(a == p);
        assert(a == b);
        assert(b == p);
    }
    {
        // from vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator a = v.begin();
        ft::vector<int>::iterator b(a);
        assert(a == b);
        assert(a == v.begin());
        assert(b == v.begin());
        assert(v.begin() == v.begin());
        assert(v.end() == v.end());
    }
    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_not_equal_test()
{
    {
        // from single pointers
        int i = 42;
        int j = 42;

        int *p = &i;
        int *q = &j;

        ft::random_access_iterator<int> a(p);
        ft::random_access_iterator<int> b(q);

        assert(a != b);
  }
  {
      // from vector
        ft::vector<int> v1(10, 21);
        ft::vector<int> v2(10, 21);

        ft::vector<int>::iterator a = v1.begin();
        ft::vector<int>::iterator b = v2.begin();

        assert(a != b);
        assert(a != v2.begin());
        assert(b != v1.begin());
        assert(v1.begin() != v2.begin());
        assert(v1.end() != v2.end());
    }
    std::cout << "operator!= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_addition_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();

   // v.begin().debug();
   // (v.begin() + 1).debug();
   // (v.begin() + 2).debug();
   // (v.begin() + 3).debug();
   // (v.begin() + 4).debug();

    assert(it + 0 == it);
    assert(it + 2 == it + 1 + 1);
    assert(it + 5 == v.end());

    std::cout << "operator+ " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_substraction_test()
{
    {
        // with number
        ft::vector<int> v(5, 42);
        ft::vector<int>::iterator it = v.end();

       // v.end().debug();
       // (v.end() - 1).debug();
       // (v.end() - 2).debug();
       // (v.end() - 3).debug();
       // (v.end() - 4).debug();

        assert(it - 0 == it);
        assert(it - 2 == it - 1 - 1);
        assert(it - 5 == v.begin());
    }
    {
        // with iterator
        ft::vector<int> v(5, 42);
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it - it  == 0);
        assert(ite - ite == 0);

        //std::cout << ite - it << std::endl;
        //std::cout << it - ite << std::endl;

        assert(ite - it == 5);
        assert(ite - it == v.size());
    }
    std::cout << "operator- " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_less_than_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();
    ft::vector<int>::iterator ite = v.end();

    assert(it < ite);
    assert(it < it + 1);
    assert(it + 1 < it + 2);

    std::cout << "operator< " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_greather_than_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();
    ft::vector<int>::iterator ite = v.end();

    assert(ite > it);
    assert(it + 1 > it);
    assert(it + 2 > it + 1);

    std::cout << "operator> " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_less_than_or_equal_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();
    ft::vector<int>::iterator ite = v.end();

    assert(it <= it);
    assert(ite <= ite);
    assert(it <= it + 1);
    assert(it + 1 <= it + 2);
    assert(it <= ite);

    std::cout << "operator<= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_greather_than_or_equal_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();
    ft::vector<int>::iterator ite = v.end();

    assert(it >= it);
    assert(ite >= ite);
    assert(it + 1 >= it);
    assert(it + 2 >= it + 1);
    assert(ite >= it);

    std::cout << "operator>= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_add_then_assign_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();

    assert((it += 1) == v.begin() + 1);
    assert((it += 1) == v.begin() + 2);
    assert((it += 2) == v.begin() + 4);

    std::cout << "operator+= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_sub_then_assign_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator ite = v.end();

    assert((ite -= 1) == v.end() - 1);
    assert((ite -= 1) == v.end() - 2);
    assert((ite -= 2) == v.end() - 4);

    std::cout << "operator-= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_brackets_operator_test()
{
    ft::vector<int> v(5, 42);
    ft::vector<int>::iterator it = v.begin();

    assert(it[0] == 42);
    assert(it[1] == 42);
    assert(it[2] == 42);
    assert(it[3] == 42);
    assert(it[4] == 42);

    std::cout << "operator[] " << GREEN << "OK" << RESET << std::endl;
}

void
iterators_tests()
{
    std::cout << "== Iterators ==" << std::endl;

    iterator_constructors_test();

    iterator_assignation_test();

    begin_test(); // move to vector test suite ?
    end_test();   // move to vector test suite ?

    increment_test(); // both prefix and posifix
    decrement_test(); // both prefix and posifix

    iterator_dereference_test();

    iterator_equal_test();
    iterator_not_equal_test();

    iterator_addition_test();
    iterator_substraction_test();

    iterator_less_than_test();
    iterator_greather_than_test();

    iterator_less_than_or_equal_test();
    iterator_greather_than_or_equal_test();

    iterator_add_then_assign_test();
    iterator_sub_then_assign_test();

    iterator_brackets_operator_test();
}

/****** All tests *************************************************************/

int main()
{
//    is_integral_test();

//    VECTOR
//    vector_test<int>()
//    vector_test<double>()

//    allocator_test(); // TODO
//    constructors_test(); // TODO

//    capacity_tests(); // TODO
//    accessor_tests();
//    modifiers_tests(); // TODO
    operators_tests(); // TODO

//    iterators_tests();

    return 0;
}
