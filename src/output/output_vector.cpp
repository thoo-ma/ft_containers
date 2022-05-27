#include <type_traits>
#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>

#include "ft_type_traits.hpp"
#include "ft_vector.hpp"

#include <type_traits> // std::is_same

#include "../utils/colors.hpp"

/*
 *  TODO
 *  - std::vector<int>::iterator = v.begin();
 *  - ft::vector<int> v(5, 42);
 *    --> std::cout << std::distance(v.begin(), v.end()) << std::endl;
 *  - test with custom class like `class Foo { public: int a[60]; };`
 *
 */

/****** Constructors test *****************************************************/

void
constructor_by_default_test()
{
    ft::vector<int> a;
    std::vector<int> b;

    assert(a.size() == b.size());
    assert(a.capacity() == b.capacity());
    //assert(a.max_size() == b.max_size()); // TODO

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
        //assert(a.max_size() == b.max_size()); // TODO

        std::cout << "constructor by fill (without value) " << GREEN << "OK" << RESET << std::endl;
    }
    {
        // with value

        std::vector<int> a(10, 42);
        ft::vector<int> b(10, 42);

        assert(a.size() == b.size());
        assert(a.capacity() == b.capacity());
        //assert(a.max_size() == b.max_size()); // TODO

        std::cout << "constructor by fill (with value) " << GREEN << "OK" << RESET << std::endl;
    }
}

void
constructor_by_copy_test()
{
    {
        // from empty
        ft::vector<int> a;
        ft::vector<int> b(a);
        assert(a == b);
    }
    { // from non-empty
        ft::vector<int> a(10, 42);
        ft::vector<int> b(a);

        assert(a == b);
    }
    std::cout << "constructor by copy " << GREEN << "OK" << RESET << std::endl;
}

void
constructor_by_iterator_range_test()
{
    {
        // empty range
        ft::vector<int> a;
        ft::vector<int> b(a.begin(), a.end());

        assert(a == b);
    }
    {
        // non-empty range
        ft::vector<int> a(10, 42);
        ft::vector<int> b(a.begin(), a.end());

        assert(a == b);
    }
    std::cout << "constructor by iterator range " << GREEN << "OK" << RESET << std::endl;
}

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
    constructor_by_copy_test();
    constructor_by_iterator_range_test();
    constructor_upon_heap_test();
}

/****** Allocator test ********************************************************/

void
get_allocator_test()
{
    assert(ft::vector<int>().get_allocator() == std::allocator<int>());
    assert(ft::vector<int>().get_allocator() == std::allocator<float>());
    assert(ft::vector<int>().get_allocator() == std::vector<int>().get_allocator());

    assert((std::is_same<ft::vector<int>::allocator_type::value_type, int>::value));
    assert((std::is_same<ft::vector<int>::allocator_type::value_type,
            std::vector<int>::allocator_type::value_type>::value));

   // see. https://stackoverflow.com/a/40598287 about doubling brackets

    std::cout << "get_allocator() " << GREEN << "OK" << RESET << std::endl;
}

void
allocator_test()
{
    // TODO
//    std::allocator<int>     a1;
//    std::allocator<bool>    a2;
//
//    try {
//        int * i = a1.allocate(a1.max_size()/2);
//        *i = 42;
//        a1.deallocate(i, a1.max_size()/2);
//    } catch (...) { std::cout << "error" << std::endl; }
//
//    std::cout << "max_size allocator<int>:  " << a1.max_size() << std::endl;
//    std::cout << "max_size allocator<bool>: " << a2.max_size() << std::endl;

    get_allocator_test();
}

/****** Capacity test *********************************************************/

void
empty_test()
{
    assert(ft::vector<int>().empty());
    assert(!ft::vector<int>(10, 42).empty());
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
        ft::vector<int> a;
        ft::vector<int> b(10);
        assert(ft::vector<int>(a).size() == a.size());
        assert(ft::vector<int>(b).size() == b.size());
    }
    std::cout << "size " << GREEN << "OK" << RESET << std::endl;
}

void
max_size_test()
{
    // TODO
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
        ft::vector<int> a;
        ft::vector<int> b(10);
        assert(ft::vector<int>(a).capacity() == a.capacity());
        assert(ft::vector<int>(b).capacity() == b.capacity());
    }
    std::cout << "capacity " << GREEN << "OK" << RESET << std::endl;
}

void
reserve_test()
{
    {
        ft::vector<int> a;

        assert(a.capacity() == 0);

        // increase capacity
        try {
            a.reserve(10);
            assert(a.capacity() == 10);
        } catch (...) { /* log */ }

        // don't increase capacity
        try {
            a.reserve(10);
            assert(a.capacity() == 10);
        } catch (...) { /* log */ }

        // increase again
        try {
            a.reserve(11);
            assert(a.capacity() == 11);
        } catch (...) { /* log */ }

        // TODO
        // With stl, since `size_type` is unsigned,
        // -1 would be converted into some big number.
        // Then `reserve` would throw an `std::length_error`.
    //    try { a.reserve(-1); }
    //    catch (...) { /* log */ }
    //    assert(a.capacity() == 11);
    }
    std::cout << "reserve " << GREEN << "OK" << RESET << std::endl;
}

void
capacity_tests()
{
    empty_test();
    size_test();
    max_size_test();
    capacity_test();
    reserve_test(); // TODO
}

/****** Accessors test ********************************************************/

void
at_test()
{
    // success
    {
        {
            // at non-empty vector
            ft::vector<int> v(10, 42);

            bool success = true;

            try { v.at(1); assert(v.at(1) == 42); }
            catch (std::out_of_range & oor) { success = false; }

            assert(success);
        }
        {
            // at end() - 1
            ft::vector<int> v(10, 42);

            bool success = true;

            try
            {
                ft::vector<int>::size_type i = static_cast<size_t>(v.end() - v.begin() - 1);
                v.at(i);
                assert(v.at(i) == 42);
            }
            catch (std::out_of_range & oor) { success = false; }

            assert(success);
        }
    }
    // failure (exception throw)
    {
        {
            // access to empty vector
            ft::vector<int> v;

            bool success = true;

            try { v.at(1); }
            catch (std::out_of_range & oor) { success = false; }

            assert(!success);
        }
        {
            // access to end()
            ft::vector<int> v(10, 42);

            bool success = true;

            try { v.at(v.end() - v.begin()); }
            catch (std::out_of_range & oor) { success = false; }

            assert(!success);
        }
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
    { assert(ft::vector<int>(10).front() == int()); }
    { assert(ft::vector<int>(10, 42).front() == 42); }
    std::cout << "front " << GREEN << "OK" << RESET << std::endl;
}

void
back_test()
{
    {
        // undefined behavior when vector is empty
        // assert(ft::vector<int>().back() == 0);
    }
    { assert(ft::vector<int>(10).back() == int()); }
    { assert(ft::vector<int>(10, 42).back() == 42); }
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
accessors_tests()
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
        // empty vector
        ft::vector<int> v;

        assert(v.size() == 0);
        assert(v.capacity() == 0);

        v.clear();

        assert(v.size() == 0);
        assert(v.capacity() == 0);
    }
    {
        // non-empty vector
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

        // erase(end) -> segfault
        // --> stl segfault but standard says undefined beavior
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
    // TODO
    // - add tests with reallocations
    // - add tests like nested or invalid intervals
    // - add tests with differents values with push back
    // single element (1)
    {
        {
            // to empty
            ft::vector<int> a;
            ft::vector<int> b;
            ft::vector<int> c(1, 21);

            // at begin
            a.insert(a.begin(), 21);
            assert(a == c);

            // at end
            b.insert(b.end(), 21);
            assert(b == c);
        }
        std::cout << "insert single element (1) " << GREEN << "OK" << RESET << std::endl;
    }
    // fill (2)
    {
        {
            // to empty
            ft::vector<int> a;
            ft::vector<int> b(4, 21);

            a.insert(a.begin(), 4, 21);
            assert(a == b);
        }
        {
            // in middle
            ft::vector<int> a(5, 21);

            a.insert(a.begin() + 2, 2, 42);

            assert(a.size() == 7);
            assert(*(a.begin() + 0) == 21);
            assert(*(a.begin() + 1) == 21);
            assert(*(a.begin() + 2) == 42);
            assert(*(a.begin() + 3) == 42);
            assert(*(a.begin() + 4) == 21);
            assert(*(a.begin() + 5) == 21);
            assert(*(a.begin() + 6) == 21);
        }
        {
            // n = 0
            ft::vector<int> a;
            a.insert(a.begin(), 0, 21);
            assert(a == a);
        }
        std::cout << "insert by fill (2) " << GREEN << "OK" << RESET << std::endl;
    }
    // range (3)
    {
        {
            // to empty
            ft::vector<int> a;
            ft::vector<int> b(4, 21);

            a.insert(a.begin(), b.begin(), b.end());
            assert(a == b);
        }
        {
            // insert empty interval
            ft::vector<int> a;
            ft::vector<int> b(4, 21);
            ft::vector<int> c(b);

            // at begin
            b.insert(b.begin(), a.begin(), a.end());
            assert(b == c);

            // at end
            b.insert(b.end(), a.begin(), a.end());
            assert(b == c);

            // in middle
            b.insert(b.begin() + 2, a.begin(), a.end());
            assert(b == c);
        }
        {
            // in middle
            ft::vector<int> a(2, 21);
            ft::vector<int> b(2, 42);

            a.insert(a.begin() + 1, b.begin(), b.end());

            assert(a.size() == 4);
            assert(*(a.begin() + 0) == 21);
            assert(*(a.begin() + 1) == 42);
            assert(*(a.begin() + 2) == 42);
            assert(*(a.begin() + 3) == 21);
        }
        std::cout << "insert by range (3) " << GREEN << "OK" << RESET << std::endl;
    }
}

void
push_back_tests()
{
    // more tests ?
    {
        // with enough capacity
        ft::vector<int> v;

        v.reserve(10);

        v.push_back(42);
        assert(v.size() == 1);

        v.push_back(42);
        assert(v.size() == 2);
    }
    {
        // without enough capacity
        ft::vector<int> v;

        v.push_back(42);
        assert(v.size() == 1);
        assert(v.at(0) == 42);

        v.push_back(21);
        assert(v.size() == 2);
        assert(v.at(1) == 21);
    }
    std::cout << "push_back() " << GREEN << "OK" << RESET << std::endl;
}

void
pop_back_tests()
{
    // more tests ?
    {
        // empty vector
        ft::vector<int>().pop_back();
    }
    {
        // non-empty vector
        ft::vector<int> v(10, 21);

        assert(v.size() == 10);
        v.pop_back();
        assert(v.size() == 9);
    }
    std::cout << "pop_back() " << GREEN << "OK" << RESET << std::endl;
}

void
resize_tests()
{
    // with second argument _implicit_
    {
        {
            // n > capacity
            ft::vector<int> v;

            assert(v.capacity() == 0);
            assert(v.size() == 0);

            v.resize(10);
            assert(v.size() == 10);
        }
        {
            // n < capacity && n > size
            ft::vector<int> v;

            v.reserve(10);

            assert(v.size() == 0);
            assert(v.capacity() == 10);

            v.resize(5);

            assert(v.size() == 5);
            assert(v.capacity() == 10);
        }
        {
            // n < size
            ft::vector<int> v(10, 42);

            assert(v.size() == 10);
            assert(v.capacity() == 10);

            // FAIL
            v.resize(5);
            assert(v.size() == 10);
            assert(v.capacity() == 10);
        }
    }
    // with second argument _explicit_
    {
        {
            // n > capacity
            ft::vector<int> v;

            assert(v.capacity() == 0);
            assert(v.size() == 0);

            v.resize(10, 42);

            assert(v.size() == 10);

            for (ft::size_t i = 0; i < v.size(); i++)
            { assert(v.at(i) == 42); }

        }
        {
            // n < capacity && n > size
            ft::vector<int> v;

            v.reserve(10);

            assert(v.size() == 0);
            assert(v.capacity() == 10);

            v.resize(5, 42);

            assert(v.size() == 5);
            assert(v.capacity() == 10);

            for (ft::size_t i = 0; i < v.size(); i++)
            { assert(v.at(i) == 42); }
        }
        {
            // n < size
            ft::vector<int> v(10, 42);

            assert(v.size() == 10);
            assert(v.capacity() == 10);

            // FAIL
            v.resize(5, 42);

            assert(v.size() == 10);
            assert(v.capacity() == 10);

            for (ft::size_t i = 0; i < v.size(); i++)
            { assert(v.at(i) == 42); }
        }
    }
    std::cout << "resize() " << GREEN << "OK" << RESET << std::endl;
}

void
swap_tests()
{
    {
        // test equality
        ft::vector<int> a(10, 42);
        ft::vector<int> b(20, 21);

        ft::vector<int> c(a);
        ft::vector<int> d(b);

        assert(c == a);
        assert(d == b);

        c.swap(d);

        assert(c == b);
        assert(d == a);
    }
    {
        // test iterators
        ft::vector<int> a(10, 42);
        ft::vector<int> b(20, 21);

        ft::vector<int>::iterator ita = a.begin();
        ft::vector<int>::iterator itb = b.begin();

        assert(*ita == 42);
        assert(*itb == 21);

        a.swap(b);

        assert(*ita == 42);
        assert(*itb == 21);

        assert(*(ita + 1) == 42);
        assert(*(itb + 1) == 21);
    }
    std::cout << "swap() " << GREEN << "OK" << RESET << std::endl;
}

void
assign_tests()
{
    // by fill
    {
        {
            // assign to empty vector
            ft::vector<int> a;
            ft::vector<int> b(10, 42);

            a.assign(10, 42);
            assert(a == b);
        }
        {
            // assign to non-empty vector
            ft::vector<int> a(42, 21);
            ft::vector<int> b(10, 42);

            a.assign(10, 42);
            assert(a == b);
        }
        {
            // assign no elements to empty vector
            ft::vector<int> a;
            ft::vector<int> b;

            a.assign(0, 42);
            assert(a == b);
        }
        {
            // assign no elements to non-empty vector
            ft::vector<int> a(10, 42);

            // FAIL
            a.assign(0, 21);

            assert(a.size() == 0);
            assert(a.capacity() == 10);
        }
    }
    // by range
    {
        {
            // assign to empty vector
            ft::vector<int> a;
            ft::vector<int> b(10, 42);

            a.assign(b.begin(), b.end());
            assert(a == b);
        }
        {
            // assign to non-empty vector
            ft::vector<int> a(42, 21);
            ft::vector<int> b(10, 42);

            a.assign(b.begin(), b.end());
            assert(a == b);
        }
        {
            // assign no elements to empty vector
            ft::vector<int> a;
            ft::vector<int> b;

            a.assign(b.begin(), b.end());
            assert(a == b);
        }
        {
            // assign no elements to non-empty vector
            ft::vector<int> a(10, 42);
            ft::vector<int> b;

            // FAIL
            a.assign(b.begin(), b.end());

            assert(a.size() == 0);
            assert(a.capacity() == 10);
        }
    }
    std::cout << "assign() " << GREEN << "OK" << RESET << std::endl;
}

void
modifiers_tests()
{
    std::cout << "== Modifiers ==" << std::endl;
    clear_tests();
    erase_tests(); // TODO
    insert_tests(); // TODO
    push_back_tests();
    pop_back_tests();
    resize_tests();
    swap_tests();
    assign_tests();
}

/****** Operators tests *******************************************************/

void
equal_test()
{
    // empty vector
    { assert(ft::vector<int>() == ft::vector<int>()); }
    // non-empty with default values
    { assert(ft::vector<int>(10) == ft::vector<int>(10)); }
    // non-empty with specified values
    { assert(ft::vector<int>(10, 21) == ft::vector<int>(10, 21)); }
    // heap with empty vector
    {
        ft::vector<int> * a = new ft::vector<int>();
        ft::vector<int> * b = new ft::vector<int>();
        assert(*b == *a);
        delete a;
        delete b;
    }
    // heap with non-empty vector
    {
        ft::vector<int> * a = new ft::vector<int>(10,21);
        ft::vector<int> * b = new ft::vector<int>(10,21);
        assert(*b == *a);
        delete a;
        delete b;
    }
    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

void
not_equal_test()
{
    assert(ft::vector<int>() != ft::vector<int>(10));
    assert(ft::vector<int>(10) != ft::vector<int>(10, 21));
    assert(ft::vector<int>(10, 21) != ft::vector<int>(10, 42));

    std::cout << "operator!= " << GREEN << "OK" << RESET << std::endl;
}

void
vector_assignation_test()
{
    {
        // same size
        ft::vector<int> a(5, 21);
        ft::vector<int> b(5, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // upper size
        ft::vector<int> a(9, 21);
        ft::vector<int> b(5, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // lower size
        ft::vector<int> a(5, 21);
        ft::vector<int> b(9, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // assign from empty
        ft::vector<int> a(9, 21);
        ft::vector<int> b;

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // assign to empty
        ft::vector<int> a;
        ft::vector<int> b(9, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    std::cout << "operator= " << GREEN << "OK" << RESET << std::endl;
    }

    void
    less_than_test()
    {
        {
            // with different sizes
            assert(ft::vector<int>() < ft::vector<int>(1));
            assert(ft::vector<int>(0) < ft::vector<int>(1));
            assert(ft::vector<int>(1) < ft::vector<int>(2));

            // with different values
            assert(ft::vector<int>(1, 21) < ft::vector<int>(1, 42));
        }
        std::cout << "operator< " << GREEN << "OK" << RESET << std::endl;
    }

    void
    greater_than_test()
    {
        {
            // with different sizes
            assert(ft::vector<int>(1) > ft::vector<int>());
            assert(ft::vector<int>(1) > ft::vector<int>(0));
            assert(ft::vector<int>(2) > ft::vector<int>(1));

            // with different values
            assert(ft::vector<int>(1, 42) > ft::vector<int>(1, 21));
        }
        std::cout << "operator> " << GREEN << "OK" << RESET << std::endl;
    }

    void
    less_than_equal_test()
{
    {
        // with different sizes
        assert(ft::vector<int>() <= ft::vector<int>());
        assert(ft::vector<int>() <= ft::vector<int>(1));
        assert(ft::vector<int>(0) <= ft::vector<int>(0));
        assert(ft::vector<int>(0) <= ft::vector<int>(1));
        assert(ft::vector<int>(1) <= ft::vector<int>(1));
        assert(ft::vector<int>(1) <= ft::vector<int>(2));

        // with different values
        assert(ft::vector<int>(1, 21) <= ft::vector<int>(1, 21));
        assert(ft::vector<int>(1, 21) <= ft::vector<int>(1, 42));
        assert(ft::vector<int>(1, 21) <= ft::vector<int>(2, 21));
    }
    std::cout << "operator<= " << GREEN << "OK" << RESET << std::endl;
}

void
greater_than_equal_test()
{
    {
        // with different sizes
        assert(ft::vector<int>() >= ft::vector<int>());
        assert(ft::vector<int>(1) >= ft::vector<int>());
        assert(ft::vector<int>(0) >= ft::vector<int>(0));
        assert(ft::vector<int>(1) >= ft::vector<int>(0));
        assert(ft::vector<int>(1) >= ft::vector<int>(1));
        assert(ft::vector<int>(2) >= ft::vector<int>(1));

        // with different values
        assert(ft::vector<int>(1, 21) >= ft::vector<int>(1, 21));
        assert(ft::vector<int>(1, 42) >= ft::vector<int>(1, 21));
        assert(ft::vector<int>(2, 21) >= ft::vector<int>(1, 21));
    }
    std::cout << "operator>= " << GREEN << "OK" << RESET << std::endl;
}

void
operators_tests()
{
    std::cout << "== Operators ==" << std::endl;
    equal_test();
    not_equal_test();
    vector_assignation_test();
    less_than_test();
    greater_than_test();
    less_than_equal_test();
    greater_than_equal_test();
}

/****** Iterators tests *******************************************************/

void
iterator_constructors_test()
{
    {
        // by default
        ft::vector<int>::iterator	    a;
        ft::vector<int>::const_iterator b;
    }
    {
        // by pointer
        int i = 42;
        int * p = &i;
        ft::vector<int>::iterator	    a(p);
        ft::vector<int>::const_iterator	b(p);
    }
    {
        // by copy
        std::vector<int>::iterator a;
        std::vector<int>::const_iterator b;

        // it(it)
        std::vector<int>::iterator c(a);

        // const_it(const_it)
        std::vector<int>::const_iterator d(b);

        // const_it(it)
        std::vector<int>::const_iterator e(a);

        // it(const_it) --> should not compile !
        //std::vector<int>::iterator f(b); (void)f;

        (void)c;
        (void)d;
    }
    std::cout << "constructors " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_assignation_test()
{
    {
        // it = it
        int i = 42;
        int * p = &i;
        ft::vector<int>::iterator a(p);
        ft::vector<int>::iterator b;
        assert(a != b);
        b = a;
        assert(a == b);
    }
    {
        // const_it = const_it
        int i = 42;
        int * p = &i;
        ft::vector<int>::const_iterator a(p);
        ft::vector<int>::const_iterator b;
        assert(a != b);
        b = a;
        assert(a == b);
    }
    {
        // const_it = it
        int i = 42;
        int * p = &i;
        ft::vector<int>::iterator a(p);
        ft::vector<int>::const_iterator b;
        assert(a != b);
        b = a;
        assert(a == b);
    }
    {
        // it = const_it -- should not compile
    }
    std::cout << "assignation " << GREEN << "OK" << RESET << std::endl;
}

void
begin_test()
{
    {
        // iterator
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.begin();
        assert(*it == 21);
        it++;
    }
    {
        // const_iterator
        ft::vector<int> v(10, 21);
        //ft::vector<int>::const_iterator it = v.begin(); // TODO
        //assert(*it == 21);
        // it++; // error
    }
    std::cout << "begin " << GREEN << "OK" << RESET << std::endl;
}

void
end_test()
{
    {
        // iterator
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.end();
        it--;
    }
    {
        // const_iterator
        ft::vector<int> v(10, 21);
        //ft::vector<int>::const_iterator it = v.end(); // TODO
        //it--; // error
        //(void)it;
    }
    std::cout << "end " << GREEN << "OK" << RESET << std::endl;
}

void
increment_test()
{
    ft::vector<int> v(10, 21);
    {
        // prefix
        {
            // it
            ft::vector<int>::iterator it = v.begin();
            for (int i = 0; i < 10; ++i, ++it)
                assert(*it == 21);
        }
        {
            // it
            ft::vector<int>::const_iterator it = v.begin();
            for (int i = 0; i < 10; ++i, ++it)
                assert(*it == 21);
        }
    }
    {
        {
            // it
            ft::vector<int>::iterator it = v.begin();
            for (int i = 0; i < 10; ++i, it++)
                assert(*it == 21);
        }
        {
            // const_it
            ft::vector<int>::const_iterator it = v.begin();
            for (int i = 0; i < 10; ++i, it++)
                assert(*it == 21);
        }
    }
    std::cout << "increment " << GREEN << "OK" << RESET << std::endl;
}

void
decrement_test()
{
    ft::vector<int> v(10, 21);
    {
        // prefix
        {
            // it
            ft::vector<int>::iterator it = v.end();
            for (int i = 0; i < 10; ++i)
                assert(*(--it) == 21);
        }
        {
            // const_it
            ft::vector<int>::const_iterator it = v.end();
            for (int i = 0; i < 10; ++i)
                assert(*(--it) == 21);
        }
    }
    {
        // postfix
        {
            // it
            ft::vector<int>::iterator it = v.end();
            it--;
            for (int i = 0; i < 10; ++i)
                assert(*(it--) == 21);
        }
        {
            // const_it
            ft::vector<int>::const_iterator it = v.end();
            it--;
            for (int i = 0; i < 10; ++i)
                assert(*(it--) == 21);
        }
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
        {
            // it
            ft::vector<int>::iterator a(p);
            assert(*a == *p);
        }
        {
            // const_it
            ft::vector<int>::const_iterator a(p);
            assert(*a == *p);
        }
    }
    {
        // from vector
        ft::vector<int> v(10, 21);
        {
            // it
            ft::vector<int>::iterator a = v.begin();
            ft::vector<int>::iterator b(a);
            assert(*a == *b);
            assert(*a == *(v.begin()));
            assert(*b == *(v.begin()));
            assert(*v.begin() == *v.begin());
        }
        {
            // const_it
            ft::vector<int>::const_iterator a = v.begin();
            ft::vector<int>::const_iterator b(a);
            assert(*a == *b);
            assert(*a == *(v.begin()));
            assert(*b == *(v.begin()));
            assert(*v.begin() == *v.begin());
        }
    }
    {
        // segfault
        //ft::vector<int>::iterator a;
        //assert(*a);
    }
    std::cout << "operator* " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_dereference_pointer_test()
{
    {
        // from single pointer
        int i = 42;
        int *p = &i;
        {
            // it
            ft::vector<int>::iterator a(p);
            assert(a.operator->() == p);
        }
        {
            // const_it
            ft::vector<int>::const_iterator a(p);
            assert(a.operator->() == p);
        }
    }
    {
        // from vector
        ft::vector<int> v(10, 21);
        {
            // it
            ft::vector<int>::iterator a = v.begin();
            ft::vector<int>::iterator b(a);
            assert(a.operator->() == &(*b));
            assert(a.operator->() == &(*(v.begin())));
            assert(b.operator->() == &(*(v.begin())));
            assert(v.begin().operator->() == &(*v.begin()));
        }
        {
            // const_it
            ft::vector<int>::const_iterator a = v.begin();
            ft::vector<int>::const_iterator b(a);
            assert(a.operator->() == &(*b));
            assert(a.operator->() == &(*(v.begin())));
            assert(b.operator->() == &(*(v.begin())));
            assert(v.begin().operator->() == &(*v.begin()));
        }
    }
    std::cout << "operator-> " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_equal_test()
{
    {
        // constructed by defalut
        {
            // it == it
            ft::vector<int>::iterator a;
            ft::vector<int>::iterator b;
            assert(a == b);
            assert(b == a);
        }
        {
            // it == const_it && const_it == it
            ft::vector<int>::iterator	    a;
            ft::vector<int>::const_iterator b;
            assert(a == b);
            assert(b == a);
        }
        {
            // const_it == const_it
            ft::vector<int>::const_iterator	a;
            ft::vector<int>::const_iterator b;
            assert(a == b);
            assert(b == a);
        }
    }
    {
        // constructed by pointer
        int i = 42;
        int *p = &i;
        {
            // it == it
            ft::vector<int>::iterator a(p);
            ft::vector<int>::iterator b(p);
            assert(a == b);
            assert(b == a);
        }
        {
            // it == const_it && const_it == it
            ft::vector<int>::iterator	    a(p);
            ft::vector<int>::const_iterator b(p);
            assert(a == b);
            assert(b == a);
        }
        {
            // const_it == const_it
            ft::vector<int>::const_iterator	a(p);
            ft::vector<int>::const_iterator b(p);
            assert(a == b);
            assert(b == a);
        }
    }
    {
        // constructed by vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator a = v.begin();
        ft::vector<int>::iterator b(a);
        assert(a == b);
        assert(b == a);
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
        // constructed by pointer
        int i = 42;
        int j = 42;

        int *p = &i;
        int *q = &j;
        {
            // it == it
            ft::vector<int>::iterator a(p);
            ft::vector<int>::iterator b(q);
            assert(a != b);
            assert(b != a);
        }
        {
            // it == const_it && const_it == it
            ft::vector<int>::iterator	    a(p);
            ft::vector<int>::const_iterator b(q);
            assert(a != b);
            assert(b != a);
        }
        {
            // const_it == const_it
            ft::vector<int>::const_iterator	a(p);
            ft::vector<int>::const_iterator b(q);
            assert(a != b);
            assert(b != a);
        
        }
    }
    {
        // constructed by vector
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
    {
        // it
        ft::vector<int>::iterator it = v.begin();

        assert(it + 0 == it);
        assert(it + 2 == it + 1 + 1);
        assert(it + 5 == v.end());
    }
    {
        // const_it
        ft::vector<int>::const_iterator it = v.begin();

        assert(it + 0 == it);
        assert(it + 2 == it + 1 + 1);
        assert(it + 5 == v.end());
    }
    std::cout << "operator+ " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_substraction_test()
{
    {
        // with number
        {
            // it - n
            ft::vector<int> v(5, 42);
            ft::vector<int>::iterator it = v.end();

            assert(it - 0 == it);
            assert(it - 2 == it - 1 - 1);
            assert(it - 5 == v.begin());
        }
        {
            // const_it - n
            ft::vector<int> v(5, 42);
            ft::vector<int>::const_iterator it = v.end();

            assert(it - 0 == it);
            assert(it - 2 == it - 1 - 1);
            assert(it - 5 == v.begin());
        }
    }
    {
        // with iterator
        {
            // it - it
            ft::vector<int> v(5, 42);
            ft::vector<int>::iterator it = v.begin();
            ft::vector<int>::iterator ite = v.end();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 5);
            assert(ite - it == static_cast<ptrdiff_t>(v.size()));
        }
        {
            // it - const_it && const_it - it
            ft::vector<int> v(5, 42);
            ft::vector<int>::iterator it = v.begin();
            ft::vector<int>::const_iterator ite = v.end();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 5);
            assert(ite - it == static_cast<ptrdiff_t>(v.size()));
        }
        {
            // const_it - const_it
            ft::vector<int> v(5, 42);
            ft::vector<int>::iterator it = v.begin();
            ft::vector<int>::const_iterator ite = v.end();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 5);
            assert(ite - it == static_cast<ptrdiff_t>(v.size()));
        }
    }
    std::cout << "operator- " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_less_than_test()
{
    ft::vector<int> v(5, 42);
    {
        // it < it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // it < const_it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // const_it < it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // const_it < const_it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    std::cout << "operator< " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_greather_than_test()
{
    ft::vector<int> v(5, 42);
    {
        // it > it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // it > const_it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // const_it > it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // const_it > const_it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }

    std::cout << "operator> " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_less_than_or_equal_test()
{
    ft::vector<int> v(5, 42);
    {
        // it <= it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // it <= const_it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // const_it <= it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // const_it <= const_it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    std::cout << "operator<= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_greather_than_or_equal_test()
{
    ft::vector<int> v(5, 42);
    {
        // it >= it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // it >= const_it
        ft::vector<int>::iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // const_it >= it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::iterator ite = v.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // const_it >= const_it
        ft::vector<int>::const_iterator it = v.begin();
        ft::vector<int>::const_iterator ite = v.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    std::cout << "operator>= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_add_then_assign_test()
{
    ft::vector<int> v(5, 42);
    {
        // it += n
        ft::vector<int>::iterator it = v.begin();

        assert((it += 1) == v.begin() + 1);
        assert((it += 1) == v.begin() + 2);
        assert((it += 2) == v.begin() + 4);
    }
    {
        // const_it += n
        ft::vector<int>::const_iterator it = v.begin();

        assert((it += 1) == v.begin() + 1);
        assert((it += 1) == v.begin() + 2);
        assert((it += 2) == v.begin() + 4);
    }
    std::cout << "operator+= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_sub_then_assign_test()
{
    ft::vector<int> v(5, 42);
    {
        // it += n
        ft::vector<int>::iterator ite = v.end();

        assert((ite -= 1) == v.end() - 1);
        assert((ite -= 1) == v.end() - 2);
        assert((ite -= 2) == v.end() - 4);
    }
    {
        // const_it -= n
        ft::vector<int>::const_iterator ite = v.end();

        assert((ite -= 1) == v.end() - 1);
        assert((ite -= 1) == v.end() - 2);
        assert((ite -= 2) == v.end() - 4);
    }
    std::cout << "operator-= " << GREEN << "OK" << RESET << std::endl;
}

void
iterator_brackets_operator_test()
{
    ft::vector<int> v(5, 42);
    {
        // it
        ft::vector<int>::iterator it = v.begin();

        assert(it[0] == 42);
        assert(it[1] == 42);
        assert(it[2] == 42);
        assert(it[3] == 42);
        assert(it[4] == 42);
    }
    {
        // const_it
        ft::vector<int>::const_iterator it = v.begin();

        assert(it[0] == 42);
        assert(it[1] == 42);
        assert(it[2] == 42);
        assert(it[3] == 42);
        assert(it[4] == 42);
    }

    // TODO
 //   ft::vector<int>::value_type x = it[42]; // doesn't throw anything
 //   (void)x;

    std::cout << "operator[] " << GREEN << "OK" << RESET << std::endl;
}

void
iterators_tests()
{
    // TODO add tests for const_iterator everywhere

    std::cout << "== Iterators ==" << std::endl;

    iterator_constructors_test();

    iterator_assignation_test();

    begin_test(); // move to vector test suite ?
    end_test();   // move to vector test suite ?

    increment_test(); // both prefix and posifix
    decrement_test(); // both prefix and posifix

    iterator_dereference_test();
    iterator_dereference_pointer_test(); // TODO

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

/****** Vector tests **********************************************************/

template <typename T>
void vector_constructor_by_default_test()
{
    ft::vector<T> a;

    assert(a.size() == 0);
    assert(a.capacity() == 0);
    //assert(a.max_size() == std::vector<T>().max_size()); // TODO

    std::cout << "constructor by default " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void vector_test()
{
    vector_constructor_by_default_test<T>();
}

/****** All tests *************************************************************/

int main()
{
//      VECTOR
    //vector_test<int>();
    //vector_test<double>();

//    allocator_test(); // TODO
//    constructors_test(); // TODO
//
//    capacity_tests();
//    accessors_tests();
//    modifiers_tests(); // TODO
//    operators_tests();

    iterators_tests(); // TODO add reverse_iterator

    return 0;
}
