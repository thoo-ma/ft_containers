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
 *
 *  - ft::vector<int> v(5, 42);
 *  --> std::cout << std::distance(v.begin(), v.end()) << std::endl;
 *
 *  - make custom datatype `class A` support all tests
 *	--> then, template all tests not templated yet
 *
 *  - log only if: std:is_same<Vector,ft::vector<Vector::value_type>>
 *
 */

/****** Custom datatype *******************************************************/

/*
 *
 * Depending on how your vector is implemented, custom datatypes
 * might require some operators/functions in order to perform all tests.
 *
 * For example, if you want to `assert(vector<T> == vector<T>)`
 * your custom datatype `T` must support `operator==`.
 *
 * To mimic the `std::vector<T>` behavior, your `ft::vector<T>` should be:
 * - copy constructible for any type `T` (especially empty class !...)
 * - ...
 *
 */

class A
{
    public:
    A() { }
    A(A const & a) { (void)a; }
};

bool operator==(const A & lhs, const A & rhs)
{ (void)lhs; (void)rhs; return true; }

bool operator!=(const A & lhs, const A & rhs)
{ (void)lhs; (void)rhs; return false; }

/****** Log *******************************************************************/

inline void log(std::string s)
{
    std::cout << s << GREEN << " OK" << RESET << std::endl;
}

/****** Constructors test *****************************************************/

template <typename Vector>
void constructor_by_default_test()
{
    Vector a;

    assert(a.empty());
    assert(a.size() == 0);
    assert(a.capacity() == 0);
    //assert(a.max_size() == 0); // TODO

    log("constructor by default");
}

template <typename Vector, typename T>
void constructor_by_fill_test()
{
    {
        // without value
        Vector a(10);

        assert(a.size() == 10);
        assert(a.capacity() == 10);
        //assert(a.max_size() == 0); // TODO

        log("constructor by fill (without value)");
    }
    {
        // with value
        Vector a(10, T());

        assert(a.size() == 10);
        assert(a.capacity() == 10);
        //assert(a.max_size() == 0); // TODO

        log("constructor by fill (with value)");
    }
}

template <typename Vector, typename T>
void constructor_by_copy_test()
{
    {
        // from empty
        Vector a;
        Vector b(a);

        assert(a == b);
    }
    {
        // TODO
        // from non-empty
   //     Vector a(10, T());
   //     Vector b(a);

   //     assert(a == b);
    }
    log("constructor by copy");
}

template <typename Vector, typename T>
void constructor_by_iterator_range_test()
{
    {
        // empty range
        Vector a;
        Vector b(a.begin(), a.end());

        assert(a == b);
    }
    {
        // non-empty range
        Vector a(10, T());
        Vector b(a.begin(), a.end());

        assert(a == b);
    }
    log("constructor by iterator range");
}

template <typename Vector>
void constructor_upon_heap_test()
{
    { Vector * v = new Vector; delete v; }
    { Vector * v = new Vector[10]; delete [] v; }
    log("constructor upon heap");
}

template <typename T>
void constructors_test()
{
    constructor_by_default_test<std::vector<T>>();
    constructor_by_default_test< ft::vector<T>>();

    constructor_by_fill_test<std::vector<T>, T>();
    constructor_by_fill_test< ft::vector<T>, T>();

    constructor_by_copy_test<std::vector<T>, T>();
    constructor_by_copy_test< ft::vector<T>, T>();

    constructor_by_iterator_range_test<std::vector<T>, T>();
    constructor_by_iterator_range_test< ft::vector<T>, T>();

    constructor_upon_heap_test<std::vector<T>>();
    constructor_upon_heap_test< ft::vector<T>>();
}

/****** Allocator test ********************************************************/

template <typename Vector>
void get_allocator_test()
{
    Vector v;
    class Foo {};

    assert(v.get_allocator() == std::allocator<typename Vector::value_type>());
    assert(v.get_allocator() == std::allocator<Foo>());

    // TODO -- move this into traits test suite
    assert((std::is_same<
                typename Vector::allocator_type::value_type,
                typename Vector::value_type
                >::value));

   // cf. https://stackoverflow.com/a/40598287 about doubling parenthesis

    log("get_allocator()");
}

template <typename T>
void allocator_test()
{
    get_allocator_test<std::vector<T>>();
    get_allocator_test< ft::vector<T>>();
}

/****** Capacity test *********************************************************/

template <typename Vector, typename T>
void empty_test()
{
    assert(Vector().empty());
    assert(!Vector(10, T()).empty());
    std::cout << "empty " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector, typename T>
void size_test()
{
    {
        // constructed by default
        assert(Vector().size() == 0);
    }
    {
        // constructed by fill (without value)
        assert(Vector(10).size() == 10);
    }
    {
        // constructed by fill (with value)
        assert(Vector(10, T()).size() == 10);
    }
    {
        // constructed by copy
        Vector a;
        Vector b(10);
        assert(Vector(a).size() == a.size());
        assert(Vector(b).size() == b.size());
    }
    std::cout << "size " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void max_size_test()
{
    // TODO
    std::cout << "max_size " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector, typename T>
void capacity_test()
{
    {
        // constructed by default
        assert(Vector().capacity() == 0);
    }
    {
        // constructed by fill (without value)
        assert(Vector(10).capacity() == 10);
    }
    {
        // constructed by fill (with value)
        assert(Vector(10, T()).capacity() == 10);
    }
    {
        // constructed by copy
        Vector a;
        Vector b(10);
        assert(Vector(a).capacity() == a.capacity());
        assert(Vector(b).capacity() == b.capacity());
    }
    std::cout << "capacity " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void reserve_test()
{
    {
        Vector a;

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

template <typename T>
void capacity_test()
{
    empty_test<std::vector<T>, T>();
    empty_test< ft::vector<T>, T>();

    size_test<std::vector<T>, T>();
    size_test< ft::vector<T>, T>();

    max_size_test<std::vector<T>>();
    max_size_test< ft::vector<T>>();

    capacity_test<std::vector<T>, T>();
    capacity_test< ft::vector<T>, T>();

    reserve_test<std::vector<T>>(); // TODO
    reserve_test< ft::vector<T>>(); // TODO
}

/****** Accessors test ********************************************************/

void
at_test()
{
    bool success = true;
    // success
    {
        {
            // at non-empty vector
            {
                // mutable vector
                ft::vector<int> v(10, 42);

                try { v.at(1); assert(v.at(1) == 42); }
                catch (std::out_of_range & oor) { success = false; }

                assert(success);
            }
            {
                // const vector
                const ft::vector<int> v(10, 42);

                try { v.at(1); assert(v.at(1) == 42); }
                catch (std::out_of_range & oor) { success = false; }

                assert(success);
            }
        }
        {
            // at end() - 1
            {
                // mutable vector
                ft::vector<int> v(10, 42);

                try
                {
                    ft::vector<int>::size_type i = static_cast<size_t>(v.end() - v.begin() - 1);
                    v.at(i);
                    assert(v.at(i) == 42);
                }
                catch (std::out_of_range & oor) { success = false; }

                assert(success);
            }
            {
                // const vector
                const ft::vector<int> v(10, 42);

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
    }
    // failure (exception throw)
    {
        {
            // access to empty vector
            {
                // mutable vector
                {
                    ft::vector<int> v;

                    try { v.at(1); }
                    catch (std::out_of_range & oor) { success = false; }

                    assert(!success);
                }
                {
                    // const vector
                    const ft::vector<int> v;

                    try { v.at(1); }
                    catch (std::out_of_range & oor) { success = false; }

                    assert(!success);
                }
            }
        }
        {
            // access to end()
            {
                // mutable vector
                ft::vector<int> v(10, 42);

                try { v.at(v.end() - v.begin()); }
                catch (std::out_of_range & oor) { success = false; }

                assert(!success);
            }
            {
                // const vector
                const ft::vector<int> v(10, 42);

                try { v.at(v.end() - v.begin()); }
                catch (std::out_of_range & oor) { success = false; }

                assert(!success);
            }
        }
    }
    std::cout << "at " << GREEN << "OK" << RESET << std::endl;
}

void
front_test()
{
    // undefined behavior when vector is empty
    // { assert(ft::vector<int>().front() == 0); }

    // mutable vector
    { assert(ft::vector<int>(10).front() == int()); }
    { assert(ft::vector<int>(10, 42).front() == 42); }

    // const vector
    { const ft::vector<int> v(10); assert(v.front() == int()); }
    { const ft::vector<int> v(10, 42); assert(v.front() == 42); }

    std::cout << "front " << GREEN << "OK" << RESET << std::endl;
}

void
back_test()
{
    // undefined behavior when vector is empty
    // { assert(ft::vector<int>().back() == 0); }

    // mutable vector
    { assert(ft::vector<int>(10).back() == int()); }
    { assert(ft::vector<int>(10, 42).back() == 42); }

    // const vector
    { const ft::vector<int> v(10); assert(v.back() == int()); }
    { const ft::vector<int> v(10, 42); assert(v.back() == 42); }

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
    {
        const ft::vector<int> v(10);
        int i = int();
        for (ft::vector<int>::size_type j = 0; j < 10; j++) { assert(v[j] == i); }
    }
    {
        const ft::vector<int> v(10, 42);
        for (ft::vector<int>::size_type i = 0; i < 10; i++) { assert(v[i] == 42); }
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

            v.resize(5);
            assert(v.size() == 5);
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

            v.resize(5, 42);

            assert(v.size() == 5);
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

            // FAIL (?)
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

            // FAIL (?)
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
        ft::vector<int>::iterator		                a;
        ft::vector<int>::const_iterator	                b;
        ft::vector<int>::reverse_iterator	            c;
        ft::vector<int>::const_reverse_iterator	        d;
        const ft::vector<int>::iterator		            e;
        const ft::vector<int>::const_iterator	        f;
        const ft::vector<int>::reverse_iterator	        g;
        const ft::vector<int>::const_reverse_iterator	h;
    }
    {
        // by pointer
        int i = 42;
        int * p = &i;
        ft::vector<int>::iterator	            a(p);
        ft::vector<int>::const_iterator	        b(p);

        // the following should not compile -- we get this behavior by
        // adding `explicit` qualifier to iterator_base constructor by pointer

        // ft::vector<int>::reverse_iterator	    c(p);
        // ft::vector<int>::const_reverse_iterator	d(p);
    }
    {
        // by copy
        ft::vector<int>::iterator               a;
        ft::vector<int>::const_iterator         b;
        ft::vector<int>::reverse_iterator	    c;
        ft::vector<int>::const_reverse_iterator	d;

        // it(it)
        ft::vector<int>::iterator e(a);

        // it(const_it) --> should not compile !
        // ft::vector<int>::iterator x(b); (void)x;

        // const_it(it)
        ft::vector<int>::const_iterator f(a);

        // const_it(const_it)
        ft::vector<int>::const_iterator g(b);

        // rev_it(it)
        ft::vector<int>::reverse_iterator h(a);

        // rev_it(const_it) --> should not compile !
        // ft::vector<int>::reverse_iterator y(b); (void)y;

        // rev_it(rev_it)
        ft::vector<int>::reverse_iterator i(c);

        // rev_it(const_rev_it) --> should not compile !
        // ft::vector<int>::reverse_iterator z(d); (void)z;

        // const_rev_it(it)
        ft::vector<int>::const_reverse_iterator j(a);

        // const_rev_it(const_it)
        ft::vector<int>::const_reverse_iterator k(b);

        // const_rev_it(rev_it)
        ft::vector<int>::const_reverse_iterator l(c);

        // const_rev_it(const_rev_it)
        ft::vector<int>::const_reverse_iterator m(d);

        (void)e;
        (void)f;
        (void)g;
        (void)h;
        (void)i;
        (void)j;
        (void)k;
        (void)l;
        (void)m;
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
        ft::vector<int>::iterator a;
        ft::vector<int>::iterator b(p);
        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // const_it = const_it
        int i = 42;
        int * p = &i;
        ft::vector<int>::const_iterator a;
        ft::vector<int>::const_iterator b(p);
        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // const_it = it
        int i = 42;
        int * p = &i;
        ft::vector<int>::const_iterator a;
        ft::vector<int>::iterator	    b(p);
        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // it = const_it -- should not compile
        // ft::vector<int>::iterator	    a;
        // ft::vector<int>::const_iterator	b;
        // a = b;
    }
    {
        // rev_it = it -- should not compile
        // ft::vector<int>::reverse_iterator	a;
        // ft::vector<int>::iterator	        b;
        // a = b;
    }
    {
        // rev_it = const_it -- should not compile
        // ft::vector<int>::reverse_iterator	a;
        // ft::vector<int>::const_iterator	    b;
        // a = b;
    }
    {
        // rev_it = rev_it
        ft::vector<int> v(2,42);
        ft::vector<int>::reverse_iterator a;
        ft::vector<int>::reverse_iterator b = v.rbegin();
        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // rev_it = const_rev_it -- should not compile
        // std::vector<int>::reverse_iterator	    a;
        // std::vector<int>::const_reverse_iterator	b;
        // a = b;
    }
    {
        // const_rev_it = it -- should not compile
        // ft::vector<int>::const_reverse_iterator	a;
        // ft::vector<int>::iterator	            b;
        // a = b;
    }
    {
        // const_rev_it = const_it -- should not compile
        // ft::vector<int>::const_reverse_iterator	a;
        // ft::vector<int>::const_iterator	        b;
        // a = b;
    }
    {
        // const_rev_it = rev_it
        ft::vector<int> v(2,42);
        ft::vector<int>::const_reverse_iterator	a = v.rbegin();
        ft::vector<int>::reverse_iterator	        b;
        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // const_rev_it = const_rev_it
        ft::vector<int> v(2,42);
        ft::vector<int>::const_reverse_iterator	a = v.rbegin();
        ft::vector<int>::const_reverse_iterator	b;
        assert(a != b);
        a = b;
        assert(a == b);
    }
    std::cout << "assignation " << GREEN << "OK" << RESET << std::endl;
}

void
begin_test()
{
    {
        // iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.begin();
        assert(*it == 21);
        it++;
    }
    {
        // const_iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::const_iterator it = v.begin();
        assert(*it == 21);
        it++;
    }
    {
        // iterator from const vector -- sould not compile
     //   const ft::vector<int> v(10, 21);
     //   ft::vector<int>::iterator it = v.begin();
     //   (void)it;
    }
    {
        // const_iterator from const vector
        const ft::vector<int> v(10, 21);
        ft::vector<int>::const_iterator it = v.begin();
        assert(*it == 21);
        it++;
    }
    std::cout << "begin " << GREEN << "OK" << RESET << std::endl;
}

void
end_test()
{
    {
        // iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::iterator it = v.end();
        it--;
    }
    {
        // const_iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::const_iterator it = v.end();
        it--;
    }
    {
        // iterator from const vector -- should not compile
     //   const ft::vector<int> v(10, 21);
     //   ft::vector<int>::iterator it = v.end();
     //   it--;
    }
    {
        // const_iterator from const vector
        const ft::vector<int> v(10, 21);
        ft::vector<int>::const_iterator it = v.end();
        it--;
    }
    std::cout << "end " << GREEN << "OK" << RESET << std::endl;
}

void
rbegin_test()
{
    {
        // reverse_iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::reverse_iterator it = v.rbegin();
        assert(it.base() == v.end());
        it++;
        assert(*it == 21);
    }
    {
        // const_reverse_iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::const_reverse_iterator it = v.rbegin();
        assert(it.base() == v.end());
        it++;
        assert(*it == 21);
    }
    {
        // reverse_iterator from const vector -- should not compile
     //   const ft::vector<int> v(10, 21);
     //   ft::vector<int>::reverse_iterator it = v.rbegin();
     //   assert(it.base() == v.end());
     //   it++;
     //   assert(*it == 21);
    }
    {
        // const_reverse_iterator from const vector
        const ft::vector<int> v(10, 21);
        ft::vector<int>::const_reverse_iterator it = v.rbegin();
        assert(it.base() == v.end());
        it++;
        assert(*it == 21);
    }
    std::cout << "rbegin " << GREEN << "OK" << RESET << std::endl;
}

void
rend_test()
{
    {
        // reverse_iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::reverse_iterator it = v.rend();
        it--;
    }
    {
        // const_reverse_iterator from mutable vector
        ft::vector<int> v(10, 21);
        ft::vector<int>::const_reverse_iterator it = v.rend();
        it--;
    }
    {
        // reverse_iterator from const vector -- should not compile
     //   const ft::vector<int> v(10, 21);
     //   ft::vector<int>::reverse_iterator it = v.rend();
     //   it--;
    }
    {
        // const_reverse_iterator from const vector
        const ft::vector<int> v(10, 21);
        ft::vector<int>::const_reverse_iterator it = v.rend();
        it--;
    }
    std::cout << "rend " << GREEN << "OK" << RESET << std::endl;
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
            // const_it
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
    // TODO
    // - reverse_iterator_base_test();
    // - add reverse_iterator and const_reverse_iterator to all tests below

    std::cout << "== Iterators ==" << std::endl;

    //iterator_constructors_test();
    iterator_assignation_test();

    begin_test(); // move to vector test suite ?
    end_test();   // move to vector test suite ?

    rbegin_test(); // move to vector test suite ?
    rend_test();   // move to vector test suite ?

    increment_test(); // both prefix and posifix
    decrement_test(); // both prefix and posifix

    iterator_dereference_test();
    iterator_dereference_pointer_test();

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
void vector_test()
{
    constructors_test<T>();
    allocator_test<T>();
    capacity_test<T>();
}

/****** All tests *************************************************************/


int main()
{
//    vector_test<int>();
//    vector_test<double>();
//    vector_test<A>();

//    accessors_tests();
//    modifiers_tests(); // TODO
//    operators_tests();
//
//    iterators_tests();

    return 0;
}
