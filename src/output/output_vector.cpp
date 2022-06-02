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
 *  1. template tests upon basic arithmetic datatypes (int, char, double, etc.)
 *  2. template tests upon custom datatypes
 *  3. iterators_tests into separate file (shared with vector_test and map_test)
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

template <typename Vector>
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
        Vector a(10, typename Vector::value_type());

        assert(a.size() == 10);
        assert(a.capacity() == 10);
        //assert(a.max_size() == 0); // TODO

        log("constructor by fill (with value)");
    }
}

template <typename Vector>
void constructor_by_copy_test()
{
    {
        // from empty
        Vector a;
        Vector b(a);

        assert(a == b);
    }
    {
        // from non-empty
        Vector a(10, typename Vector::value_type());
        Vector b(a);

        assert(a == b);
    }
    log("constructor by copy");
}

template <typename Vector>
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
        Vector a(10, typename Vector::value_type());
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
void constructors_tests()
{
    constructor_by_default_test<std::vector<T>>();
    constructor_by_default_test< ft::vector<T>>();

    constructor_by_fill_test<std::vector<T>>();
    constructor_by_fill_test< ft::vector<T>>();

    constructor_by_copy_test<std::vector<T>>();
    constructor_by_copy_test< ft::vector<T>>();

    constructor_by_iterator_range_test<std::vector<T>>();
    constructor_by_iterator_range_test< ft::vector<T>>();

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
void allocator_tests()
{
    get_allocator_test<std::vector<T>>();
    get_allocator_test< ft::vector<T>>();
}

/****** Capacity test *********************************************************/

template <typename Vector>
void empty_test()
{
    assert(Vector().empty());
    assert(!Vector(10, typename Vector::value_type()).empty());
    std::cout << "empty " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
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
        assert(Vector(10, typename Vector::value_type()).size() == 10);
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

template <typename Vector>
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
        assert(Vector(10, typename Vector::value_type()).capacity() == 10);
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
void capacity_tests()
{
    empty_test<std::vector<T>>();
    empty_test< ft::vector<T>>();

    size_test<std::vector<T>>();
    size_test< ft::vector<T>>();

    max_size_test<std::vector<T>>();
    max_size_test< ft::vector<T>>();

    capacity_test<std::vector<T>>();
    capacity_test< ft::vector<T>>();

    reserve_test<std::vector<T>>(); // TODO
    reserve_test< ft::vector<T>>(); // TODO
}

/****** Accessors test ********************************************************/

template <typename Vector>
void at_test()
{
    bool success = true;
    // success
    {
        {
            // at non-empty vector
            {
                // mutable vector
                Vector v(10, 42);
                try { (void)v.at(1); assert(v.at(1) == 42); }
                catch (std::out_of_range & oor) { success = false; }
                assert(success);
            }
            {
                // const vector
                const Vector v(10, 42);
                try { (void)v.at(1); assert(v.at(1) == 42); }
                catch (std::out_of_range & oor) { success = false; }
                assert(success);
            }
        }
        {
            // at end() - 1
            {
                // mutable vector
                Vector v(10, 42);
                try
                {
                    typename Vector::size_type i;
                    i = static_cast<size_t>(v.end() - v.begin() - 1);
                    (void)v.at(i);
                    assert(v.at(i) == 42);
                }
                catch (std::out_of_range & oor) { success = false; }
                assert(success);
            }
            {
                // const vector
                const Vector v(10, 42);
                try
                {
                    typename Vector::size_type i;
                    i = static_cast<size_t>(v.end() - v.begin() - 1);
                    (void)v.at(i);
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
                    Vector v;
                    try { (void)v.at(1); }
                    catch (std::out_of_range & oor) { success = false; }
                    assert(!success);
                }
                {
                    // const vector
                    const Vector v;
                    try { (void)v.at(1); }
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

template <typename Vector>
void front_test()
{
    // undefined behavior when vector is empty
    // { assert(Vector().front() == 0); }

    // mutable vector
    { assert(Vector(10).front() == typename Vector::value_type()); }
    { assert(Vector(10, 42).front() == 42); }

    // const vector
    { const Vector v(10); assert(v.front() == typename Vector::value_type()); }
    { const Vector v(10, 42); assert(v.front() == 42); }

    std::cout << "front " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void back_test()
{
    // undefined behavior when vector is empty
    // { assert(Vector().back() == 0); }

    // mutable vector
    { assert(Vector(10).back() == typename Vector::value_type()); }
    { assert(Vector(10, 42).back() == 42); }

    // const vector
    { const Vector v(10); assert(v.back() == typename Vector::value_type()); }
    { const Vector v(10, 42); assert(v.back() == 42); }

    std::cout << "back " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void operator_bracket_test()
{
    {
        // undefined behavior when vector is empty
        // assert(Vector().back() == 0);
    }
    {
        Vector v(10);
        typename Vector::value_type i = typename Vector::value_type();
        for (typename Vector::size_type j = 0; j < 10; j++)
            assert(v[j] == i);
    }
    {
        Vector v(10, 42);
        for (typename Vector::size_type i = 0; i < 10; i++)
            assert(v[i] == 42);
    }
    {
        // doesn't thow anything
        Vector(10)[10];
    }
    {
        const Vector v(10);
        typename Vector::value_type i = typename Vector::value_type();
        for (typename Vector::size_type j = 0; j < 10; j++)
            assert(v[j] == i);
    }
    {
        const Vector v(10, 42);
        for (typename Vector::size_type i = 0; i < 10; i++)
            assert(v[i] == 42);
    }
    std::cout << "operator[] " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void accessors_tests()
{
    std::cout << "== Accessors ==" << std::endl;

    at_test<std::vector<T>>();
    at_test< ft::vector<T>>();

    front_test<std::vector<T>>();
    front_test< ft::vector<T>>();

    back_test<std::vector<T>>();
    back_test< ft::vector<T>>();

    operator_bracket_test<std::vector<T>>();
    operator_bracket_test< ft::vector<T>>();
}

/****** Modifiers tests *******************************************************/

template <typename Vector>
void clear_test()
{
    {
        // empty vector
        Vector v;

        assert(v.size() == 0);
        assert(v.capacity() == 0);

        v.clear();

        assert(v.size() == 0);
        assert(v.capacity() == 0);
    }
    {
        // non-empty vector
        Vector v(42);

        assert(v.size() == 42);
        assert(v.capacity() == 42);

        v.clear();

        assert(v.size() == 0);
        assert(v.capacity() == 42);
    }
    std::cout << "clear " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void erase_test()
{
    // TODO try with different values (fill with push back)
    // TODO maybe add some tricky cases like overflow size or capacity
    {
        // erase by position
        Vector a(21, 42);
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
        Vector a(21, 42);
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

template <typename Vector>
void insert_test()
{
    // TODO
    // - add tests with reallocations
    // - add tests like nested or invalid intervals
    // - add tests with differents values with push back
    // single element (1)
    {
        {
            // to empty
            Vector a;
            Vector b;
            Vector c(1, 21);

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
            Vector a;
            Vector b(4, 21);

            a.insert(a.begin(), 4, 21);
            assert(a == b);
        }
        {
            // in middle
            Vector a(5, 21);

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
            Vector a;
            a.insert(a.begin(), 0, 21);
            assert(a == a);
        }
        std::cout << "insert by fill (2) " << GREEN << "OK" << RESET << std::endl;
    }
    // range (3)
    {
        {
            // to empty
            Vector a;
            Vector b(4, 21);

            a.insert(a.begin(), b.begin(), b.end());
            assert(a == b);
        }
        {
            // insert empty interval
            Vector a;
            Vector b(4, 21);
            Vector c(b);

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
            Vector a(2, 21);
            Vector b(2, 42);

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

template <typename Vector>
void push_back_test()
{
    // TODO
    // more tests ?
    {
        // with enough capacity
        Vector v;

        v.reserve(10);

        v.push_back(42);
        assert(v.size() == 1);

        v.push_back(42);
        assert(v.size() == 2);
    }
    {
        // without enough capacity
        Vector v;

        v.push_back(42);
        assert(v.size() == 1);
        assert(v.at(0) == 42);

        v.push_back(21);
        assert(v.size() == 2);
        assert(v.at(1) == 21);
    }
    std::cout << "push_back() " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void pop_back_test()
{
    // TODO
    // more tests ?
    {
        // empty vector
        Vector().pop_back();
    }
    {
        // non-empty vector
        Vector v(10, 21);

        assert(v.size() == 10);
        v.pop_back();
        assert(v.size() == 9);
    }
    std::cout << "pop_back() " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void resize_test()
{
    // with second argument _implicit_
    {
        {
            // n > capacity
            Vector v;

            assert(v.capacity() == 0);
            assert(v.size() == 0);

            v.resize(10);
            assert(v.size() == 10);
        }
        {
            // n < capacity && n > size
            Vector v;

            v.reserve(10);

            assert(v.size() == 0);
            assert(v.capacity() == 10);

            v.resize(5);

            assert(v.size() == 5);
            assert(v.capacity() == 10);
        }
        {
            // n < size
            Vector v(10, 42);

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
            Vector v;

            assert(v.capacity() == 0);
            assert(v.size() == 0);

            v.resize(10, 42);

            assert(v.size() == 10);

            for (typename Vector::size_type i = 0; i < v.size(); i++)
            { assert(v.at(i) == 42); }

        }
        {
            // n < capacity && n > size
            Vector v;

            v.reserve(10);

            assert(v.size() == 0);
            assert(v.capacity() == 10);

            v.resize(5, 42);

            assert(v.size() == 5);
            assert(v.capacity() == 10);

            for (typename Vector::size_type i = 0; i < v.size(); i++)
            { assert(v.at(i) == 42); }
        }
        {
            // n < size
            Vector v(10, 42);

            assert(v.size() == 10);
            assert(v.capacity() == 10);

            v.resize(5, 42);

            assert(v.size() == 5);
            assert(v.capacity() == 10);

            for (typename Vector::size_type i = 0; i < v.size(); i++)
            { assert(v.at(i) == 42); }
        }
    }
    std::cout << "resize() " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void swap_test()
{
    {
        // test equality
        Vector a(10, 42);
        Vector b(20, 21);

        Vector c(a);
        Vector d(b);

        assert(c == a);
        assert(d == b);

        c.swap(d);

        assert(c == b);
        assert(d == a);
    }
    {
        // test iterators
        Vector a(10, 42);
        Vector b(20, 21);

        typename Vector::iterator ita = a.begin();
        typename Vector::iterator itb = b.begin();

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

template <typename Vector>
void assign_test()
{
    // by fill
    {
        {
            // assign to empty vector
            Vector a;
            Vector b(10, 42);

            a.assign(10, 42);
            assert(a == b);
        }
        {
            // assign to non-empty vector
            Vector a(42, 21);
            Vector b(10, 42);

            a.assign(10, 42);
            assert(a == b);
        }
        {
            // assign no elements to empty vector
            Vector a;
            Vector b;

            a.assign(0, 42);
            assert(a == b);
        }
        {
            // assign no elements to non-empty vector
            Vector a(10, 42);

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
            Vector a;
            Vector b(10, 42);

            a.assign(b.begin(), b.end());
            assert(a == b);
        }
        {
            // assign to non-empty vector
            Vector a(42, 21);
            Vector b(10, 42);

            a.assign(b.begin(), b.end());
            assert(a == b);
        }
        {
            // assign no elements to empty vector
            Vector a;
            Vector b;

            a.assign(b.begin(), b.end());
            assert(a == b);
        }
        {
            // assign no elements to non-empty vector
            Vector a(10, 42);
            Vector b;

            // FAIL (?)
            a.assign(b.begin(), b.end());

            assert(a.size() == 0);
            assert(a.capacity() == 10);
        }
    }
    std::cout << "assign() " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void modifiers_tests()
{
    std::cout << "== Modifiers ==" << std::endl;

    clear_test<std::vector<T>>();
    clear_test< ft::vector<T>>();

    erase_test<std::vector<T>>(); // TODO
    erase_test< ft::vector<T>>(); // TODO

    insert_test<std::vector<T>>(); // TODO
    insert_test< ft::vector<T>>(); // TODO

    push_back_test<std::vector<T>>();
    push_back_test< ft::vector<T>>();

    pop_back_test<std::vector<T>>();
    pop_back_test< ft::vector<T>>();

    resize_test<std::vector<T>>();
    resize_test< ft::vector<T>>();

    swap_test<std::vector<T>>();
    swap_test< ft::vector<T>>();

    assign_test<std::vector<T>>();
    assign_test< ft::vector<T>>();
}

/****** Operators tests *******************************************************/

template <typename Vector>
void equal_test()
{
    // empty vector
    { assert(Vector() == Vector()); }
    // non-empty with default values
    { assert(Vector(10) == Vector(10)); }
    // non-empty with specified values
    { assert(Vector(10, 21) == Vector(10, 21)); }
    // heap with empty vector
    {
        Vector * a = new Vector();
        Vector * b = new Vector();
        assert(*b == *a);
        delete a;
        delete b;
    }
    // heap with non-empty vector
    {
        Vector * a = new Vector(10,21);
        Vector * b = new Vector(10,21);
        assert(*b == *a);
        delete a;
        delete b;
    }
    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void not_equal_test()
{
    assert(Vector() != Vector(10));
    assert(Vector(10) != Vector(10, 21));
    assert(Vector(10, 21) != Vector(10, 42));

    std::cout << "operator!= " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void vector_assignation_test()
{
    {
        // same size
        Vector a(5, 21);
        Vector b(5, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // upper size
        Vector a(9, 21);
        Vector b(5, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // lower size
        Vector a(5, 21);
        Vector b(9, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // assign from empty
        Vector a(9, 21);
        Vector b;

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // assign to empty
        Vector a;
        Vector b(9, 42);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    std::cout << "operator= " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void less_than_test()
{
    {
        // with different sizes
        assert(Vector() < Vector(1));
        assert(Vector(0) < Vector(1));
        assert(Vector(1) < Vector(2));

        // with different values
        assert(Vector(1, 21) < Vector(1, 42));
    }
    std::cout << "operator< " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void greater_than_test()
{
    {
        // with different sizes
        assert(Vector(1) > Vector());
        assert(Vector(1) > Vector(0));
        assert(Vector(2) > Vector(1));

        // with different values
        assert(Vector(1, 42) > Vector(1, 21));
    }
    std::cout << "operator> " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void less_than_equal_test()
{
    {
        // with different sizes
        assert(Vector() <= Vector());
        assert(Vector() <= Vector(1));
        assert(Vector(0) <= Vector(0));
        assert(Vector(0) <= Vector(1));
        assert(Vector(1) <= Vector(1));
        assert(Vector(1) <= Vector(2));

        // with different values
        assert(Vector(1, 21) <= Vector(1, 21));
        assert(Vector(1, 21) <= Vector(1, 42));
        assert(Vector(1, 21) <= Vector(2, 21));
    }
    std::cout << "operator<= " << GREEN << "OK" << RESET << std::endl;
}

template <typename Vector>
void greater_than_equal_test()
{
    {
        // with different sizes
        assert(Vector() >= Vector());
        assert(Vector(1) >= Vector());
        assert(Vector(0) >= Vector(0));
        assert(Vector(1) >= Vector(0));
        assert(Vector(1) >= Vector(1));
        assert(Vector(2) >= Vector(1));

        // with different values
        assert(Vector(1, 21) >= Vector(1, 21));
        assert(Vector(1, 42) >= Vector(1, 21));
        assert(Vector(2, 21) >= Vector(1, 21));
    }
    std::cout << "operator>= " << GREEN << "OK" << RESET << std::endl;
}

template <typename T>
void operators_tests()
{
    std::cout << "== Operators ==" << std::endl;

    equal_test<std::vector<T>>();
    equal_test< ft::vector<T>>();

    not_equal_test<std::vector<T>>();
    not_equal_test< ft::vector<T>>();

    vector_assignation_test<std::vector<T>>();
    vector_assignation_test< ft::vector<T>>();

    less_than_test<std::vector<T>>();
    less_than_test< ft::vector<T>>();

    greater_than_test<std::vector<T>>();
    greater_than_test< ft::vector<T>>();

    less_than_equal_test<std::vector<T>>();
    less_than_equal_test< ft::vector<T>>();

    greater_than_equal_test<std::vector<T>>();
    greater_than_equal_test< ft::vector<T>>();
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

    //iterator_constructors_test(); // TODO
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
    constructors_tests<T>();
    allocator_tests<T>();
    capacity_tests<T>();
    accessors_tests<T>();
    modifiers_tests<T>(); // TODO
    operators_tests<T>();

    iterators_tests(); // TODO
}

/****** All tests *************************************************************/

int main()
{
    vector_test<int>();
    vector_test<double>();

//    vector_test<A>(); // TODO

    return 0;
}
