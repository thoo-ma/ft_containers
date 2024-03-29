#include <vector>
#include <type_traits> // std::is_same
#include <list>
#include <deque>

#include "utils.hpp"
#include "ft_vector.hpp"
#include "output_iterator.hpp"

/****** Constructors test *****************************************************/

template <typename Vector>
void constructor_by_default_test()
{
    Vector a;

    expect(a.empty());
    expect(a.size() == 0);
    expect(a.capacity() == 0);
    expect(a.max_size() == a.get_allocator().max_size());

    log("constructor by default (1)");
}

template <typename Vector>
void constructor_by_fill_test()
{
    {
        // without value
        Vector a(10);

        expect(a.size() == 10);
        expect(a.capacity() == 10);
        expect(a.max_size() == a.get_allocator().max_size());
    }
    {
        // with value
        Vector a(10, typename Vector::value_type());

        expect(a.size() == 10);
        expect(a.capacity() == 10);
        expect(a.max_size() == a.get_allocator().max_size());
    }
    log("constructor by fill (2)");
}

/// @todo InputIterator
template <typename Vector, typename Value>
void constructor_by_iterator_range_test()
{
    Value i(1);
    Value j(2);
    Value k(3);

    {
        // vector(vector)
        {
            // empty range
            Vector a;
            Vector b(a.begin(), a.end());
            expect(a == b);
        }
        {
            // non-empty range
            Vector a;
            a.insert(a.begin(), k);
            a.insert(a.begin(), i);
            a.insert(a.begin(), j);
            Vector b(a.begin(), a.end());
            expect(a == b);
        }
    }
    {
        // vector(const vector)
        {
            // empty range
            Vector const a;
            Vector b(a.begin(), a.end());
            expect(a == b);
        }
        {
            // non-empty range
            Vector a;
            a.insert(a.begin(), k);
            a.insert(a.begin(), i);
            a.insert(a.begin(), j);
            Vector const b(a.begin(), a.end()); // yes, we need this first ...
            Vector c(b.begin(), b.end()); // ... to finally test this !
            expect(c == b);
        }
    }
    {
        // const vector(vector)
        {
            // empty range
            Vector a;
            Vector const b(a.begin(), a.end());
            expect(a == b);
        }
        {
            // non-empty range
            Vector a;
            a.insert(a.begin(), k);
            a.insert(a.begin(), i);
            a.insert(a.begin(), j);
            Vector const b(a.begin(), a.end());
            expect(a == b);
        }
    }
    {
        // const vector(const vector)
        {
            // empty range
            Vector const a;
            Vector const b(a.begin(), a.end());
            expect(a == b);
        }
        {
            // non-empty range
            Vector a;
            a.insert(a.begin(), k);
            a.insert(a.begin(), i);
            a.insert(a.begin(), j);
            Vector const b(a.begin(), a.end()); // yes, we need this first ...
            Vector const c(b.begin(), b.end()); // ... to finally test this !
            expect(c == b);
        }
    }
    {
        // From bidirectionnal iterators.
        // Could also be (multi)set, but not (multi)map.
        std::list<Value> l;
        l.insert(l.begin(), i);
        l.insert(l.begin(), j);
        l.insert(l.begin(), k);

        Vector v;
        v.insert(v.begin(), i);
        v.insert(v.begin(), j);
        v.insert(v.begin(), k);

        expect(Vector(l.begin(), l.end()) == v);
    }
    {
        // From random access iterators.
        // Other than vector itself, only stands deque.
        std::deque<Value> d;
        d.insert(d.begin(), i);
        d.insert(d.begin(), j);
        d.insert(d.begin(), k);

        Vector v;
        v.insert(v.begin(), i);
        v.insert(v.begin(), j);
        v.insert(v.begin(), k);

        expect(Vector(d.begin(), d.end()) == v);
    }
    log("constructor by iterator range (3)");
}

template <typename Vector>
void constructor_by_copy_test()
{
    {
        // from empty
        Vector a;
        Vector b(a);

        expect(a == b);
    }
    {
        // from non-empty
        Vector a(10, typename Vector::value_type());
        Vector b(a);

        expect(a == b);
    }
    log("constructor by copy (4)");
}

template <typename T>
void constructors_tests()
{
    std::cout << "== Constructors ==" << std::endl;

    typedef typename std::vector<T>::value_type std_value;
    typedef typename  ft::vector<T>::value_type  ft_value;

    constructor_by_default_test<std::vector<T>>();
    constructor_by_default_test< ft::vector<T>>();

    constructor_by_fill_test<std::vector<T>>();
    constructor_by_fill_test< ft::vector<T>>();

    constructor_by_copy_test<std::vector<T>>();
    constructor_by_copy_test< ft::vector<T>>();

    constructor_by_iterator_range_test<std::vector<T>,std_value>();
    constructor_by_iterator_range_test< ft::vector<T>, ft_value>();
}

/****** Allocator test ********************************************************/

/// @todo (?)
template <typename Vector>
void get_allocator_test()
{
    Vector v;
    class Foo {};

    expect(v.get_allocator() == std::allocator<typename Vector::value_type>());
    expect(v.get_allocator() == std::allocator<Foo>());

    /// @todo move this into traits test suite
    expect((std::is_same<
                typename Vector::allocator_type::value_type,
                typename Vector::value_type
                >::value));

   // cf. https://stackoverflow.com/a/40598287 about doubling parenthesis

    log("get_allocator()");
}

template <typename T>
void allocator_tests()
{
    std::cout << "== Allocator ==" << std::endl;

    get_allocator_test<std::vector<T>>();
    get_allocator_test< ft::vector<T>>();
}

/****** Capacity test *********************************************************/

template <typename Vector>
void empty_test()
{
    Vector v;
    {
        // by default
        expect(v.empty());
    }
    {
        // by copy
        expect(Vector(v).empty());
    }
    {
        // by iterator range
        expect(Vector(v.begin(), v.end()).empty());
    }
    log("empty()");
}

template <typename Vector>
void size_test()
{
    {
        // constructed by default
        expect(Vector().size() == 0);
    }
    {
        // constructed by fill (without value)
        expect(Vector(10).size() == 10);
    }
    {
        // constructed by fill (with value)
        expect(Vector(10, typename Vector::value_type()).size() == 10);
    }
    {
        // constructed by copy
        Vector a;
        Vector b(10);
        expect(Vector(a).size() == a.size());
        expect(Vector(b).size() == b.size());
    }
    log("size()");
}

template <typename Vector>
void max_size_test()
{
    {
        // constructed by default
        Vector v;
        expect(v.max_size() == v.get_allocator().max_size());
    }
    {
        // constructed by fill (without value)
        Vector v(99);
        expect(v.max_size() == v.get_allocator().max_size());
    }
    {
        // constructed by fill (with value)
        Vector v(99, typename Vector::value_type());
        expect(v.max_size() == v.get_allocator().max_size());
    }
    {
        // constructed by copy
        Vector a;
        Vector b(10);
        {
            Vector v(a);
            expect(v.max_size() == a.max_size());
            expect(v.max_size() == a.get_allocator().max_size());
        }
        {
            Vector v(b);
            expect(v.max_size() == a.max_size());
            expect(v.max_size() == a.get_allocator().max_size());
        }
    }
    log("max_size()");
}

template <typename Vector>
void capacity_test()
{
    {
        // constructed by default
        expect(Vector().capacity() == 0);
    }
    {
        // constructed by fill (without value)
        expect(Vector(10).capacity() == 10);
    }
    {
        // constructed by fill (with value)
        expect(Vector(10, typename Vector::value_type()).capacity() == 10);
    }
    {
        // constructed by copy
        Vector a;
        Vector b(10);
        expect(Vector(a).capacity() == a.capacity());
        expect(Vector(b).capacity() == b.capacity());
    }
    log("capacity()");
}

/// @todo (?)
template <typename Vector>
void reserve_test()
{
    {
        Vector a;

        expect(a.capacity() == 0);

        // increase capacity
        try {
            a.reserve(10);
            expect(a.capacity() == 10);
        } catch (...) { /* log */ }

        // don't increase capacity
        try {
            a.reserve(10);
            expect(a.capacity() == 10);
        } catch (...) { /* log */ }

        // increase again
        try {
            a.reserve(11);
            expect(a.capacity() == 11);
        } catch (...) { /* log */ }

        /// @note with stl, since `size_type` is unsigned, -1 would be converted
        /// into some big number. Then `reserve` would throw `std::length_error`
    //    try { a.reserve(-1); }
    //    catch (...) { /* log */ }
    //    expect(a.capacity() == 11);
    }
    log("reserve()");
}

template <typename T>
void capacity_tests()
{
    std::cout << "== Capacity ==" << std::endl;

    empty_test<std::vector<T>>();
    empty_test< ft::vector<T>>();

    size_test<std::vector<T>>();
    size_test< ft::vector<T>>();

    max_size_test<std::vector<T>>();
    max_size_test< ft::vector<T>>();

    capacity_test<std::vector<T>>();
    capacity_test< ft::vector<T>>();

    reserve_test<std::vector<T>>();
    reserve_test< ft::vector<T>>();
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
                try { (void)v.at(1); expect(v.at(1) == 42); }
                catch (std::out_of_range & oor) { success = false; }
                expect(success);
            }
            {
                // const vector
                const Vector v(10, 42);
                try { (void)v.at(1); expect(v.at(1) == 42); }
                catch (std::out_of_range & oor) { success = false; }
                expect(success);
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
                    expect(v.at(i) == 42);
                }
                catch (std::out_of_range & oor) { success = false; }
                expect(success);
            }
            {
                // const vector
                const Vector v(10, 42);
                try
                {
                    typename Vector::size_type i;
                    i = static_cast<size_t>(v.end() - v.begin() - 1);
                    (void)v.at(i);
                    expect(v.at(i) == 42);
                }
                catch (std::out_of_range & oor) { success = false; }
                expect(success);
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
                    expect(!success);
                }
                {
                    // const vector
                    const Vector v;
                    try { (void)v.at(1); }
                    catch (std::out_of_range & oor) { success = false; }
                    expect(!success);
                }
            }
        }
        {
            // access to end()
            {
                // mutable vector
                ft::vector<int> v(10, 42);
                try { v.at(static_cast<typename ft::vector<int>::size_type>(v.end() - v.begin())); }
                catch (std::out_of_range & oor) { success = false; }
                expect(!success);
            }
            {
                // const vector
                const ft::vector<int> v(10, 42);
                try { v.at(static_cast<typename ft::vector<int>::size_type>(v.end() - v.begin())); }
                catch (std::out_of_range & oor) { success = false; }
                expect(!success);
            }
        }
    }
    log("at()");
}

template <typename Vector>
void front_test()
{
    /// @note undefined behavior when vector is empty.
    ///       both std and ft implementations will segfault.
    // { expect(Vector().front() == 0); }

    // mutable vector
    { expect(Vector(10).front() == typename Vector::value_type()); }
    { expect(Vector(10, 42).front() == 42); }

    // const vector
    { const Vector v(10); expect(v.front() == typename Vector::value_type()); }
    { const Vector v(10, 42); expect(v.front() == 42); }

    log("front()");
}

template <typename Vector>
void back_test()
{
    // undefined behavior when vector is empty
    // { expect(Vector().back() == 0); }

    // mutable vector
    { expect(Vector(10).back() == typename Vector::value_type()); }
    { expect(Vector(10, 42).back() == 42); }

    // const vector
    { const Vector v(10); expect(v.back() == typename Vector::value_type()); }
    { const Vector v(10, 42); expect(v.back() == 42); }

    log("back()");
}

template <typename Vector>
void operator_bracket_test()
{
    {
        // undefined behavior when vector is empty
        // expect(Vector().back() == 0);
    }
    {
        Vector v(10);
        typename Vector::value_type i = typename Vector::value_type();
        for (typename Vector::size_type j = 0; j < 10; j++)
            expect(v[j] == i);
    }
    {
        Vector v(10, 42);
        for (typename Vector::size_type i = 0; i < 10; i++)
            expect(v[i] == 42);
    }
    {
        // doesn't thow anything
        Vector(10)[10];
    }
    {
        const Vector v(10);
        typename Vector::value_type i = typename Vector::value_type();
        for (typename Vector::size_type j = 0; j < 10; j++)
            expect(v[j] == i);
    }
    {
        const Vector v(10, 42);
        for (typename Vector::size_type i = 0; i < 10; i++)
            expect(v[i] == 42);
    }
    log("operator[]");
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

        expect(v.size() == 0);
        expect(v.capacity() == 0);

        v.clear();

        expect(v.size() == 0);
        expect(v.capacity() == 0);
    }
    {
        // non-empty vector
        Vector v(42);

        expect(v.size() == 42);
        expect(v.capacity() == 42);

        v.clear();

        expect(v.size() == 0);
        expect(v.capacity() == 42);
    }
    log("clear()");
}

/// @todo try with different values (fill with push back)
/// @todo add some tricky cases like overflow size or capacity
template <typename Vector>
void erase_test()
{
    {
        // erase by position
        Vector a(21, 42);
        std::vector<int> b(21, 42);

        // begin
        expect(a.erase(a.begin()) == a.begin());
        expect(b.erase(b.begin()) == b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // begin + n
        expect(a.erase(a.begin() + 2) == a.begin() + 2);
        expect(b.erase(b.begin() + 2) == b.begin() + 2);
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // end - n
        expect(a.erase(a.end() - 2) - a.begin()
            == b.erase(b.end() - 2) - b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // erase(end) -> segfault
        // --> stl segfault but standard says undefined beavior
        //expect(a.erase(a.end()) == a.end());
        //expect(b.erase(b.end()) == b.end());
        //expect(a.size() == b.size());
        //for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        //{ expect(a.at(i) == b.at(i)); }
    }
    {
        // erase by range
        Vector a(21, 42);
        std::vector<int> b(21, 42);

        // [begin, begin)
        expect(a.erase(a.begin(), a.begin()) == a.begin());
        expect(b.erase(b.begin(), b.begin()) == b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // [end, end)
        expect(a.erase(a.end(), a.end()) == a.end());
        expect(b.erase(b.end(), b.end()) == b.end());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // [begin, begin + n)
        expect(a.erase(a.begin(), a.begin() + 2) == a.begin());
        expect(b.erase(b.begin(), b.begin() + 2) == b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // [end - n, end)
        expect(a.erase(a.end() - 2, a.end()) - a.begin()
            == b.erase(b.end() - 2, b.end()) - b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // [begin + n, end - m)
        expect(a.erase(a.begin() + 2, a.end() - 4) - a.begin()
            == b.erase(b.begin() + 2, b.end() - 4) - b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }

        // [begin, end)
        expect(a.erase(a.begin(), a.end()) == a.begin());
        expect(b.erase(b.begin(), b.end()) == b.begin());
        expect(a.size() == b.size());
        for (std::vector<int>::size_type i = 0; i < b.size(); i++)
        { expect(a.at(i) == b.at(i)); }
    }
    log("erase()");
}

/// @todo add tests with reallocations
/// @todo add tests like nested or invalid intervals
/// @todo add tests with differents values with push back
template <typename Vector, typename Value>
void insert_test()
{
    // single element (1)
    {
        {
            // to empty
            Vector a;
            Vector b;
            Vector c(1, 21);

            // at begin
            a.insert(a.begin(), 21);
            expect(a == c);

            // at end
            b.insert(b.end(), 21);
            expect(b == c);
        }
        log("insert single element (1)");
    }
    // fill (2)
    {
        {
            // to empty
            Vector a;
            Vector b(4, 21);

            a.insert(a.begin(), 4, 21);
            expect(a == b);
        }
        {
            // in middle
            Vector a(5, 21);

            a.insert(a.begin() + 2, 2, 42);

            expect(a.size() == 7);
            expect(*(a.begin() + 0) == 21);
            expect(*(a.begin() + 1) == 21);
            expect(*(a.begin() + 2) == 42);
            expect(*(a.begin() + 3) == 42);
            expect(*(a.begin() + 4) == 21);
            expect(*(a.begin() + 5) == 21);
            expect(*(a.begin() + 6) == 21);
        }
        {
            // n = 0
            Vector a;
            a.insert(a.begin(), 0, 21);
            expect(a == a);
        }
        log("insert by fill (2)");
    }
    // range (3)
    {
        {
            // to empty
            Vector a;
            Vector b(4, 21);

            a.insert(a.begin(), b.begin(), b.end());
            expect(a == b);
        }
        {
            // insert empty interval
            Vector a;
            Vector b(4, 21);
            Vector c(b);

            // at begin
            b.insert(b.begin(), a.begin(), a.end());
            expect(b == c);

            // at end
            b.insert(b.end(), a.begin(), a.end());
            expect(b == c);

            // in middle
            b.insert(b.begin() + 2, a.begin(), a.end());
            expect(b == c);
        }
        {
            // in middle
            Vector a(2, 21);
            Vector b(2, 42);

            a.insert(a.begin() + 1, b.begin(), b.end());

            expect(a.size() == 4);
            expect(*(a.begin() + 0) == 21);
            expect(*(a.begin() + 1) == 42);
            expect(*(a.begin() + 2) == 42);
            expect(*(a.begin() + 3) == 21);
        }
        {
            // From bidirectionnal iterators.
            // Could also be (multi)set, but not (multi)map.
            std::list<Value> l;
            l.insert(l.begin(), Value(1));
            l.insert(l.begin(), Value(3));
            l.insert(l.begin(), Value(2));

            // just to compare
            Vector v;
            v.insert(v.begin(), Value(1));
            v.insert(v.begin(), Value(3));
            v.insert(v.begin(), Value(2));

            Vector a;
            a.insert(a.begin(), l.begin(), l.end());
            expect(a == v);
        }
        {
            // From random access iterators.
            // Other than vector itself, only stands deque.
            std::deque<Value> d;
            d.insert(d.begin(), Value(2));
            d.insert(d.begin(), Value(1));
            d.insert(d.begin(), Value(3));

            // just to compare
            Vector v;
            v.insert(v.begin(), Value(2));
            v.insert(v.begin(), Value(1));
            v.insert(v.begin(), Value(3));

            Vector a;
            a.insert(a.begin(), d.begin(), d.end());
            expect(a == v);
        }
        log("insert by range (3)");
    }
}

/// @todo (?) add more tests
template <typename Vector>
void push_back_test()
{
    {
        // with enough capacity
        Vector v;

        v.reserve(10);

        v.push_back(42);
        expect(v.size() == 1);

        v.push_back(42);
        expect(v.size() == 2);
    }
    {
        // without enough capacity
        Vector v;

        v.push_back(42);
        expect(v.size() == 1);
        expect(v.at(0) == 42);

        v.push_back(21);
        expect(v.size() == 2);
        expect(v.at(1) == 21);
    }
    log("push_back()");
}

/// @todo (?) add more tests
template <typename Vector>
void pop_back_test()
{
    {
        // empty vector
        Vector().pop_back();
    }
    {
        // non-empty vector
        Vector v(10, 21);

        expect(v.size() == 10);
        v.pop_back();
        expect(v.size() == 9);
    }
    log("pop_back()");
}

template <typename Vector>
void resize_test()
{
    // with second argument _implicit_
    {
        {
            // n > capacity
            Vector v;

            expect(v.capacity() == 0);
            expect(v.size() == 0);

            v.resize(10);
            expect(v.size() == 10);
        }
        {
            // n < capacity && n > size
            Vector v;

            v.reserve(10);

            expect(v.size() == 0);
            expect(v.capacity() == 10);

            v.resize(5);

            expect(v.size() == 5);
            expect(v.capacity() == 10);
        }
        {
            // n < size
            Vector v(10, 42);

            expect(v.size() == 10);
            expect(v.capacity() == 10);

            v.resize(5);
            expect(v.size() == 5);
            expect(v.capacity() == 10);
        }
    }
    // with second argument _explicit_
    {
        {
            // n > capacity
            Vector v;

            expect(v.capacity() == 0);
            expect(v.size() == 0);

            v.resize(10, 42);

            expect(v.size() == 10);

            for (typename Vector::size_type i = 0; i < v.size(); i++)
            { expect(v.at(i) == 42); }

        }
        {
            // n < capacity && n > size
            Vector v;

            v.reserve(10);

            expect(v.size() == 0);
            expect(v.capacity() == 10);

            v.resize(5, 42);

            expect(v.size() == 5);
            expect(v.capacity() == 10);

            for (typename Vector::size_type i = 0; i < v.size(); i++)
            { expect(v.at(i) == 42); }
        }
        {
            // n < size
            Vector v(10, 42);

            expect(v.size() == 10);
            expect(v.capacity() == 10);

            v.resize(5, 42);

            expect(v.size() == 5);
            expect(v.capacity() == 10);

            for (typename Vector::size_type i = 0; i < v.size(); i++)
            { expect(v.at(i) == 42); }
        }
    }
    log("resize()");
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

        expect(c == a);
        expect(d == b);

        c.swap(d);

        expect(c == b);
        expect(d == a);
    }
    {
        // test iterators
        Vector a(10, 42);
        Vector b(20, 21);

        typename Vector::iterator ita = a.begin();
        typename Vector::iterator itb = b.begin();

        expect(*ita == 42);
        expect(*itb == 21);

        a.swap(b);

        expect(*ita == 42);
        expect(*itb == 21);

        expect(*(ita + 1) == 42);
        expect(*(itb + 1) == 21);
    }
    log("swap()");
}

template <typename Vector, typename Value>
void assign_test()
{
    // by range (1)
    {
        {
            // assign to empty vector
            Vector a;
            Vector b(10, 42);

            a.assign(b.begin(), b.end());
            expect(a == b);
        }
        {
            // assign to non-empty vector
            Vector a(42, 21);
            Vector b(10, 42);

            a.assign(b.begin(), b.end());
            expect(a == b);
        }
        {
            // assign no elements to empty vector
            Vector a;
            Vector b;

            a.assign(b.begin(), b.end());
            expect(a == b);
        }
        {
            // assign no elements to non-empty vector
            Vector a(10, 42);
            Vector b;

            // FAIL (?)
            a.assign(b.begin(), b.end());

            expect(a.size() == 0);
            expect(a.capacity() == 10);
        }
        {
            // From bidirectionnal iterators.
            // Could also be (multi)set, but not (multi)map.
            std::list<Value> l;
            l.insert(l.begin(), Value(1));
            l.insert(l.begin(), Value(3));
            l.insert(l.begin(), Value(2));

            // just to compare
            Vector v;
            v.insert(v.begin(), Value(1));
            v.insert(v.begin(), Value(3));
            v.insert(v.begin(), Value(2));

            Vector a;
            a.assign(l.begin(), l.end());
            expect(a == v);
        }
        {
            // From random access iterators.
            // Other than vector itself, only stands deque.
            std::deque<Value> d;
            d.insert(d.begin(), Value(2));
            d.insert(d.begin(), Value(1));
            d.insert(d.begin(), Value(3));

            // just to compare
            Vector v;
            v.insert(v.begin(), Value(2));
            v.insert(v.begin(), Value(1));
            v.insert(v.begin(), Value(3));

            Vector a;
            a.assign(d.begin(), d.end());
            expect(a == v);
        }
        log("assign by range (1)");
    }
    // by fill (2)
    {
        {
            // assign to empty vector
            Vector a;
            Vector b(10, 42);

            a.assign(10, 42);
            expect(a == b);
        }
        {
            // assign to non-empty vector
            Vector a(42, 21);
            Vector b(10, 42);

            a.assign(10, 42);
            expect(a == b);
        }
        {
            // assign no elements to empty vector
            Vector a;
            Vector b;

            a.assign(0, 42);
            expect(a == b);
        }
        {
            // assign no elements to non-empty vector
            Vector a(10, 42);

            // FAIL (?)
            a.assign(0, 21);

            expect(a.size() == 0);
            expect(a.capacity() == 10);
        }
        log("assign by fill (2)");
    }
}

/// @todo tempate all possible tests with value_type
template <typename T>
void modifiers_tests()
{
    std::cout << "== Modifiers ==" << std::endl;

    typedef typename std::vector<T>::value_type std_value;
    typedef typename  ft::vector<T>::value_type  ft_value;

    clear_test<std::vector<T>>();
    clear_test< ft::vector<T>>();

    erase_test<std::vector<T>>();
    erase_test< ft::vector<T>>();

    insert_test<std::vector<T>,std_value>();
    insert_test< ft::vector<T>, ft_value>();

    push_back_test<std::vector<T>>();
    push_back_test< ft::vector<T>>();

    pop_back_test<std::vector<T>>();
    pop_back_test< ft::vector<T>>();

    resize_test<std::vector<T>>();
    resize_test< ft::vector<T>>();

    swap_test<std::vector<T>>();
    swap_test< ft::vector<T>>();

    assign_test<std::vector<T>,std_value>();
    assign_test< ft::vector<T>, ft_value>();
}

/****** Operators tests *******************************************************/

template <typename Vector>
void equal_test()
{
    // empty vector
    { expect(Vector() == Vector()); }

    // non-empty with default values
    { expect(Vector(10) == Vector(10)); }

    // non-empty with specified values
    { expect(Vector(10, 21) == Vector(10, 21)); }

    log("operator==");
}

template <typename Vector>
void not_equal_test()
{
    expect(Vector() != Vector(10));
    expect(Vector(10) != Vector(10, 21));
    expect(Vector(10, 21) != Vector(10, 42));

    log("operator!=");
}

template <typename Vector>
void vector_assignation_test()
{
    {
        // same size
        Vector a(5, 21);
        Vector b(5, 42);

        expect(a != b);
        a = b;
        expect(a == b);
    }
    {
        // upper size
        Vector a(9, 21);
        Vector b(5, 42);

        expect(a != b);
        a = b;
        expect(a == b);
    }
    {
        // lower size
        Vector a(5, 21);
        Vector b(9, 42);

        expect(a != b);
        a = b;
        expect(a == b);
    }
    {
        // assign from empty
        Vector a(9, 21);
        Vector b;

        expect(a != b);
        a = b;
        expect(a == b);
    }
    {
        // assign to empty
        Vector a;
        Vector b(9, 42);

        expect(a != b);
        a = b;
        expect(a == b);
    }
    log("operator=");
}

template <typename Vector>
void less_than_test()
{
    {
        // with different sizes
        expect(Vector() < Vector(1));
        expect(Vector(0) < Vector(1));
        expect(Vector(1) < Vector(2));

        // with different values
        expect(Vector(1, 21) < Vector(1, 42));
    }
    log("operator<");
}

template <typename Vector>
void greater_than_test()
{
    {
        // with different sizes
        expect(Vector(1) > Vector());
        expect(Vector(1) > Vector(0));
        expect(Vector(2) > Vector(1));

        // with different values
        expect(Vector(1, 42) > Vector(1, 21));
    }
    log("operator>");
}

template <typename Vector>
void less_than_equal_test()
{
    {
        // with different sizes
        expect(Vector() <= Vector());
        expect(Vector() <= Vector(1));
        expect(Vector(0) <= Vector(0));
        expect(Vector(0) <= Vector(1));
        expect(Vector(1) <= Vector(1));
        expect(Vector(1) <= Vector(2));

        // with different values
        expect(Vector(1, 21) <= Vector(1, 21));
        expect(Vector(1, 21) <= Vector(1, 42));
        expect(Vector(1, 21) <= Vector(2, 21));
    }
    log("operator<=");
}

template <typename Vector>
void greater_than_equal_test()
{
    {
        // with different sizes
        expect(Vector() >= Vector());
        expect(Vector(1) >= Vector());
        expect(Vector(0) >= Vector(0));
        expect(Vector(1) >= Vector(0));
        expect(Vector(1) >= Vector(1));
        expect(Vector(2) >= Vector(1));

        // with different values
        expect(Vector(1, 21) >= Vector(1, 21));
        expect(Vector(1, 42) >= Vector(1, 21));
        expect(Vector(2, 21) >= Vector(1, 21));
    }
    log("operator>=");
}

/// @todo tempate all possible tests with value_type
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

template <typename Vector>
void begin_test()
{
    typename Vector::value_type val(21);
    {
        // iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::iterator it = v.begin();
        expect(*it == val);
        it++;
    }
    {
        // const_iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::const_iterator it = v.begin();
        expect(*it == val);
        it++;
    }
    {
        // iterator from const vector -- sould not compile
    //   Vector u; u.insert(u.begin(), val); const Vector v(u);
    //   typename Vector::iterator it = v.begin();
    //   (void)it;
    }
    {
        // const_iterator from const vector
        Vector u; u.insert(u.begin(), val); const Vector v(u);
        typename Vector::const_iterator it = v.begin();
        expect(*it == val);
        it++;
    }
    log("begin()");
}

template <typename Vector>
void end_test()
{
    typename Vector::value_type val(21);
    {
        // iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::iterator it = v.end();
        it--;
        expect(*it == val);
    }
    {
        // const_iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::const_iterator it = v.end();
        it--;
        expect(*it == val);
    }
    {
        // iterator from const vector -- should not compile
    //    Vector u; u.insert(u.begin(), val); const Vector v(u);
    //    typename Vector::iterator it = v.end();
    //    it--;
    //    expect(*it == val);
    }
    {
        // const_iterator from const vector
        Vector u; u.insert(u.begin(), val); const Vector v(u);
        typename Vector::const_iterator it = v.end();
        it--;
        expect(*it == val);
    }
    log("end()");
}

template <typename Vector>
void rbegin_test()
{
    typename Vector::value_type val(21);
    {
        // reverse_iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::reverse_iterator it = v.rbegin();
        expect(it.base() == v.end());
        it++;
        expect(it.base() == v.begin());
    }
    {
        // const_reverse_iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::const_reverse_iterator it = v.rbegin();
        expect(it.base() == v.end());
        it++;
        expect(it.base() == v.begin());
    }
    {
        // reverse_iterator from const vector -- should not compile
    //    Vector u; u.insert(u.begin(), val); const Vector v(u);
    //    typename Vector::reverse_iterator it = v.rbegin();
    //    expect(it.base() == v.end());
    //    it++;
    //    expect(it.base() == v.begin());
    }
    {
        // const_reverse_iterator from const vector
        Vector u; u.insert(u.begin(), val); const Vector v(u);
        typename Vector::const_reverse_iterator it = v.rbegin();
        expect(it.base() == v.end());
        it++;
        expect(it.base() == v.begin());
    }
    log("rbegin()");
}

template <typename Vector>
void rend_test()
{
    typename Vector::value_type val(21);
    {
        // reverse_iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::reverse_iterator it = v.rend();
        expect(it.base() == v.begin());
        it--;
        expect(*it == val);
    }
    {
        // const_reverse_iterator from mutable vector
        Vector v; v.insert(v.begin(), val);
        typename Vector::const_reverse_iterator it = v.rend();
        expect(it.base() == v.begin());
        it--;
        expect(*it == val);
    }
    {
        // reverse_iterator from const vector -- should not compile
    //    Vector u; u.insert(u.begin(), val); const Vector v(u);
    //    typename Vector::reverse_iterator it = v.rend();
    //    expect(it.base() == v.begin());
    //    it--;
    //    expect(*it == val);
    }
    {
        // const_reverse_iterator from const vector
        Vector u; u.insert(u.begin(), val); const Vector v(u);
        typename Vector::const_reverse_iterator it = v.rend();
        expect(it.base() == v.begin());
        it--;
        expect(*it == val);
    }
    log("rend()");
}

template <typename T>
void iterators_tests()
{
    std::cout << "== Iterators ==" << std::endl;

    begin_test<std::vector<T>>();
    begin_test< ft::vector<T>>();

    end_test<std::vector<T>>();
    end_test< ft::vector<T>>();

    rbegin_test<std::vector<T>>();
    rbegin_test< ft::vector<T>>();

    rend_test<std::vector<T>>();
    rend_test< ft::vector<T>>();

    iterator_test<std::vector<T>>();
    iterator_test< ft::vector<T>>();
}

/****** Exceptions tests ******************************************************/

template <typename Vector1D, typename Vector2D>
void exception_constructor_by_fill()
{
    try { Vector2D v(1000000000, Vector1D(1000000000,42)); }
    catch (std::exception & e) { std::cout << e.what() << std::endl; }
}

/// @note mystery: doesn't throw anything (both std and ft)
template <typename Vector1D, typename Vector2D>
void exception_constructor_by_range()
{
    Vector1D a(100000, 42);
    try { Vector2D b(100000, Vector1D(a.begin(), a.end())); }
    catch (std::exception & e) { std::cout << e.what() << std::endl; }
}

template <typename Vector1D, typename Vector2D>
void exception_reserve()
{
    // bad_alloc
    try
    {
        Vector2D v(10);
        for (int i = 0; i < 10; i++)
            v.at(i).reserve(v.at(i).max_size() - 100000);
    }
    catch (std::exception & e) { std::cout << e.what() << std::endl; }

    // lenght_error
    Vector1D v;
    try { v.reserve(v.max_size() + 1); }
    catch (std::length_error & e) { std::cout << e.what() << std::endl; }
}

/// @todo (?)
template <typename T>
void exceptions_tests()
{
    std::cout << "== Exceptions ==" << std::endl;

    exception_constructor_by_fill<std::vector<T>, std::vector<std::vector<T>>>();
    exception_constructor_by_fill< ft::vector<T>,  ft::vector< ft::vector<T>>>();

//    exception_constructor_by_range<std::vector<T>, std::vector<std::vector<T>>>();
//    exception_constructor_by_range< ft::vector<T>,  ft::vector< ft::vector<T>>>();

    exception_reserve<std::vector<T>, std::vector<std::vector<T>>>();
    exception_reserve< ft::vector<T>,  ft::vector< ft::vector<T>>>();

    /// @note at() exception not tested here
}

/****** Vector tests **********************************************************/

template <typename T>
void vector_test()
{
    constructors_tests<T>();
    allocator_tests<T>();
    capacity_tests<T>();
    accessors_tests<T>();
    modifiers_tests<T>();
    operators_tests<T>();
    iterators_tests<T>();
    exceptions_tests<T>();
}

/****** All tests *************************************************************/

int main()
{
    vector_test<A>();
    vector_test<int>();

    /// @todo
    //vector_test<ft::pair<int,int>>();

    /// @note fun fact: this doesn't compile (but not for the same reason...)
    // { std::vector<const int> v; }
    // {  ft::vector<const int> v; }

    return 0;
}