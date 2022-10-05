#ifndef OUTPUT_ITERATOR_HPP
#define OUTPUT_ITERATOR_HPP 1

#include <map> // is_map
#include <vector> // is_vector
#include <cassert>
#include <type_traits> // std::is_base_of

#include "ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"
#include "../utils/colors.hpp" // log.hpp
#include "ft_map.hpp" // is_map
#include "ft_vector.hpp" // is_vector

/// @todo Add tests to increment and decrement out of container boundaries.

/****** Value type utilities **************************************************/

template <typename Container>
struct is_vector : std::false_type { };

template <typename T>
struct is_vector<ft::vector<T> > : std::true_type { };

template <typename T>
struct is_vector<std::vector<T> > : std::true_type { };

template <typename Container>
struct is_map : std::false_type { };

template <typename T, typename U>
struct is_map<ft::map<T,U> > : std::true_type { };

template <typename T, typename U>
struct is_map<std::map<T,U> > : std::true_type { };

template <typename Container>
typename std::enable_if<is_vector<Container>::value, typename Container::value_type>::type
value_type (int x) { return typename Container::value_type(x); }

template <typename Container>
typename std::enable_if<is_map<Container>::value, typename Container::value_type>::type
value_type (int x) { return typename Container::value_type(x,x); }

/****** Common iterator test **************************************************/

template <typename Container>
void iterator_constructor_by_default_test()
{
    { typename Container::iterator		          it; (void)it; }
    { typename Container::const_iterator	      it; (void)it; }
    { typename Container::reverse_iterator        it; (void)it; }
    { typename Container::const_reverse_iterator  it; (void)it; }

    log("constructor by default");
}

template <typename Container>
void iterator_constructor_by_copy_test()
{
    // yes, this test is kinda broken since we rely on the default constructor
    // to test the copy constructor. But we should copy from what ???

    typename Container::iterator                a;
    typename Container::const_iterator          b;
    typename Container::reverse_iterator	    c;
    typename Container::const_reverse_iterator  d;

    // it(it)
    typename Container::iterator e(a);

    // it(const_it) --> should not compile !
    // typename Container::iterator x(b); (void)x;

    // const_it(it)
    typename Container::const_iterator f(a);

    // const_it(const_it)
    typename Container::const_iterator g(b);

    // rev_it(it)
    typename Container::reverse_iterator h(a);

    // rev_it(const_it) --> should not compile !
    // typename Container::reverse_iterator y(b); (void)y;

    // rev_it(rev_it)
    typename Container::reverse_iterator i(c);

    // rev_it(const_rev_it) --> should not compile !
    // typename Container::reverse_iterator z(d); (void)z;

    // const_rev_it(it)
    typename Container::const_reverse_iterator j(a);

    // const_rev_it(const_it)
    typename Container::const_reverse_iterator k(b);

    // const_rev_it(rev_it)
    typename Container::const_reverse_iterator l(c);

    // const_rev_it(const_rev_it)
    typename Container::const_reverse_iterator m(d);

    (void)e;
    (void)f;
    (void)g;
    (void)h;
    (void)i;
    (void)j;
    (void)k;
    (void)l;
    (void)m;

    log("constructor by copy");
}

/// @note vector case
template <typename Container>
typename std::enable_if<is_vector<Container>::value, void>::type
iterator_constructor_by_pointer_test()
{
    typename Container::value_type i = value_type<Container>(21);
    typename Container::pointer     p = &i;

    { typename Container::iterator	        it(p); }
    { typename Container::const_iterator    it(p); }

    /// @note the following should not compile. We get this behavior by adding
    ///       `explicit` qualifier to iterator_base constructor by pointer.

    // { typename Container::reverse_iterator	        it(p); }
    // { typename Container::const_reverse_iterator     it(p); }

    log("constructor by pointer");
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_constructor_by_pointer_test()
{ }

/// @note cf. `is_assignable` vs `is_copy_assignable`.
/// Seems to be a c++11 thing (cf. also the  `= delete` functionnality).
template <typename Container>
void iterator_assignation_test()
{
    Container c;
    typename Container::value_type i = value_type<Container>(42);
    c.insert(c.begin(), i);
    {
        // it = it
        typename Container::iterator    a;
        typename Container::iterator    b = c.begin();

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // const_it = const_it
        typename Container::const_iterator    a;
        typename Container::const_iterator    b = c.begin();

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // const_it = it
        typename Container::const_iterator      a;
        typename Container::iterator            b = c.begin();

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // it = const_it -- should not compile
        // typename Container::iterator	    a;
        // typename Container::const_iterator	b;
        // a = b;
    }
    {
        // rev_it = it -- should not compile
        // typename Container::reverse_iterator	a;
        // typename Container::iterator	        b;
        // a = b;
    }
    {
        // rev_it = const_it -- should not compile
        // typename Container::reverse_iterator	a;
        // typename Container::const_iterator	    b;
        // a = b;
    }
    {
        // rev_it = rev_it
        typename Container::iterator            a = c.begin();
        typename Container::reverse_iterator    b(a);
        typename Container::reverse_iterator    c;

        assert(c != b);
        c = b;
        assert(c == b);
    }
    {
        // rev_it = const_rev_it -- should not compile
        // std::vector<int>::reverse_iterator	    a;
        // std::vector<int>::const_reverse_iterator	b;
        // a = b;
    }
    {
        // const_rev_it = it -- should not compile
        // typename Container::const_reverse_iterator	a;
        // typename Container::iterator	            b;
        // a = b;
    }
    {
        // const_rev_it = const_it -- should not compile
        // typename Container::const_reverse_iterator	a;
        // typename Container::const_iterator	        b;
        // a = b;
    }
    {
        // const_rev_it = rev_it
        typename Container::iterator                a = c.begin();
        typename Container::reverse_iterator        b(a);
        typename Container::const_reverse_iterator  c;

        assert(c != b);
        c = b;
        assert(c == b);
    }
    {
        // const_rev_it = const_rev_it
        typename Container::iterator                a = c.begin();
        typename Container::const_reverse_iterator  b(a);
        typename Container::const_reverse_iterator  c;

        assert(c != b);
        c = b;
        assert(c == b);
    }
    log("assignation");
}

template <typename Container>
void iterator_increment_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // prefix
        {
            // it
            typename Container::iterator it = c.begin();
            assert(*it == a);
            assert(*(++it) == b);
            assert(*it == b);
        }
        {
            // const_it
            typename Container::const_iterator it = c.begin();
            assert(*it == a);
            assert(*(++it) == b);
            assert(*it == b);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rbegin();
            assert(*it == b);
            assert(*(++it) == a);
            assert(*it == a);
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rbegin();
            assert(*it == b);
            assert(*(++it) == a);
            assert(*it == a);
        }
    }
    {
        // postfix
        {
            // it
            typename Container::iterator it = c.begin();
            assert(*it == a);
            assert(*(it++) == a);
            assert(*it == b);
        }
        {
            // const_it
            typename Container::const_iterator it = c.begin();
            assert(*it == a);
            assert(*(it++) == a);
            assert(*it == b);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rbegin();
            assert(*it == b);
            assert(*(it++) == b);
            assert(*it == a);
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rbegin();
            assert(*it == b);
            assert(*(it++) == b);
            assert(*it == a);
        }
    }
    log("increment");
}

template <typename Container>
void reverse_iterator_base_test()
{
    typename Container::value_type i = value_type<Container>(21);
    typename Container::value_type j = value_type<Container>(42);

    Container c;

    c.insert(c.begin(), j);
    c.insert(c.begin(), i);

    assert(c.rbegin().base() == c.end());
    assert(c.rend().base() == c.begin());

    typename Container::iterator it(c.begin());
    typename Container::reverse_iterator rit(it);

    assert(rit.base() == it);
    assert(&*(rit.base() - 1) == &*rit);

    log("base()");
}

/****** Input iterator test ***************************************************/

template <typename Container>
void iterator_equal_test_constructed_by_default()
{
    {
        // it == it
        typename Container::iterator a;
        typename Container::iterator b;
        assert(a == b);
        assert(b == a);
    }
    {
        // it == const_it && const_it == it
        typename Container::iterator	     a;
        typename Container::const_iterator   b;
        assert(a == b);
        assert(b == a);
    }
    {
        // const_it == const_it
        typename Container::const_iterator   a;
        typename Container::const_iterator   b;
        assert(a == b);
        assert(b == a);
    }
    {
        // rev_it = rev_it
        typename Container::reverse_iterator a;
        typename Container::reverse_iterator b;
        assert(a == b);
        assert(b == a);
    }
    {
        // rev_it == const_rev_it && const_rev_it == rev_it
        typename Container::reverse_iterator	     a;
        typename Container::const_reverse_iterator   b;
        assert(a == b);
        assert(b == a);
    }
    {
        // const_rev_it == const_rev_it
        typename Container::const_reverse_iterator   a;
        typename Container::const_reverse_iterator   b;
        assert(a == b);
        assert(b == a);
    }
}

template <typename Container>
void iterator_non_equal_test_constructed_by_default()
{
    {
        // it != it
        typename Container::iterator a;
        typename Container::iterator b;
        assert(!(a != b));
        assert(!(b != a));
    }
    {
        // it != const_it && const_it != it
        typename Container::iterator	     a;
        typename Container::const_iterator   b;
        assert(!(a != b));
        assert(!(b != a));
    }
    {
        // const_it != const_it
        typename Container::const_iterator   a;
        typename Container::const_iterator   b;
        assert(!(a != b));
        assert(!(b != a));
    }
    {
        // rev_it != rev_it
        typename Container::reverse_iterator a;
        typename Container::reverse_iterator b;
        assert(!(a != b));
        assert(!(b != a));
    }
    {
        // rev_it != const_rev_it && const_rev_it != rev_it
        typename Container::reverse_iterator	     a;
        typename Container::const_reverse_iterator   b;
        assert(!(a != b));
        assert(!(b != a));
    }
    {
        // const_rev_it != const_rev_it
        typename Container::const_reverse_iterator   a;
        typename Container::const_reverse_iterator   b;
        assert(!(a != b));
        assert(!(b != a));
    }
}

/// @note vector case
template <typename Container>
typename std::enable_if<is_vector<Container>::value, void>::type
iterator_equal_test_constructed_by_pointer()
{
    typename Container::value_type i = value_type<Container>(21);
    typename Container::value_type * p = &i;
    {
        // it == it
        typename Container::iterator a(p);
        typename Container::iterator b(p);
        assert(a == b);
        assert(b == a);
    }
    {
        // it == const_it && const_it == it
        typename Container::iterator	    a(p);
        typename Container::const_iterator  b(p);
        assert(a == b);
        assert(b == a);
    }
    {
        // const_it == const_it
        typename Container::const_iterator  a(p);
        typename Container::const_iterator  b(p);
        assert(a == b);
        assert(b == a);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_equal_test_constructed_by_pointer()
{ }

/// @note vector case
template <typename Container>
typename std::enable_if<is_vector<Container>::value, void>::type
iterator_non_equal_test_constructed_by_pointer()
{
    typename Container::value_type i = value_type<Container>(42);
    typename Container::value_type j = value_type<Container>(42);

    typename Container::value_type * p = &i;
    typename Container::value_type * q = &j;
    {
        // it != it
        typename Container::iterator a(p);
        typename Container::iterator b(q);
        assert(a != b);
        assert(b != a);
    }
    {
        // it != const_it
        // const_it != it
        typename Container::iterator	    a(p);
        typename Container::const_iterator  b(q);
        assert(a != b);
        assert(b != a);
    }
    {
        // const_it != const_it
        typename Container::const_iterator	a(p);
        typename Container::const_iterator  b(q);
        assert(a != b);
        assert(b != a);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_non_equal_test_constructed_by_pointer()
{ }

template <typename Container>
void iterator_equal_test_constructed_by_copy()
{
    Container c;

    typename Container::value_type i = value_type<Container>(21);
    typename Container::value_type j = value_type<Container>(42);

    c.insert(c.begin(), j);
    c.insert(c.begin(), i);

    // it
    {
        typename Container::iterator a = c.begin();
        typename Container::iterator b(a);

        assert(a == b);
        assert(b == a);
        assert(a == c.begin());
        assert(b == c.begin());
        assert(c.begin() == c.begin());
        assert(c.end() == c.end());
    }

    // rev_it
    {
        typename Container::reverse_iterator a = c.rend();
        typename Container::reverse_iterator b(a);

        assert(a == b);
        assert(b == a);
        assert(a.base() == c.begin());
        assert(b.base() == c.begin());
        assert(a.base() == a.base());
        assert(b.base() == b.base());
        assert(c.rbegin().base() == c.end());
    }

    (void)i;
    (void)j;
}

template <typename Container>
void iterator_non_equal_test_constructed_by_copy()
{
    Container c1;
    Container c2;

    typename Container::value_type i = value_type<Container>(42);
    typename Container::value_type j = value_type<Container>(42);

    c1.insert(c1.begin(), j);
    c1.insert(c1.begin(), i);

    c2.insert(c2.begin(), j);
    c2.insert(c2.begin(), i);

    // it
    {
        typename Container::iterator a = c1.begin();
        typename Container::iterator b = c2.begin();

        assert(a != b);
        assert(a != c2.begin());
        assert(b != c1.begin());
        assert(c1.begin() != c2.begin());
        assert(c1.end() != c2.end());
    }

    // rev_it
    {
        typename Container::reverse_iterator a = c1.rend();
        typename Container::reverse_iterator b = c2.rend();

        assert(a != b);
        assert(a != c2.rend());
        assert(b != c1.rend());
        assert(c1.rbegin() != c2.rbegin());
        assert(c1.rend() != c2.rend());
        assert(a.base() != b.base());
    }
}

/// @todo clear distinction between:
///       - test constructed by copy
///       - test constructed by container public method
template <typename Container>
void iterator_equal_test()
{
    iterator_equal_test_constructed_by_default<Container>();
    iterator_equal_test_constructed_by_pointer<Container>();
    iterator_equal_test_constructed_by_copy<Container>();

    log("operator==");
}

/// @todo clear distinction between:
///       - test constructed by copy
///       - test constructed by container public method
template <typename Container>
void iterator_not_equal_test()
{
    iterator_non_equal_test_constructed_by_default<Container>();
    iterator_non_equal_test_constructed_by_pointer<Container>();
    iterator_non_equal_test_constructed_by_copy<Container>();

    log("operator!=");
}

template <bool B, typename Container>
typename ft::enable_if<B>::type
input_iterator_test()
{
    iterator_equal_test<Container>();
    iterator_not_equal_test<Container>();
}

template <bool B, typename Container>
typename ft::enable_if<!B>::type
input_iterator_test() { }

/****** Output iterator test **************************************************/

template <typename Container>
void iterator_dereference_test_constructed_by_default()
{
    // segfault
    // typename Container::iterator a;
    // assert(*a);
}

/// @note vector case
template <typename Container>
typename std::enable_if<is_vector<Container>::value, void>::type
iterator_dereference_test_constructed_by_pointer()
{
    typename Container::value_type i = value_type<Container>(42);
    typename Container::value_type * p = &i;
    {
        // it
        typename Container::iterator a(p);
        assert(*a == *p);
        assert(*a ==  i);
    }
    {
        // const_it
        typename Container::const_iterator a(p);
        assert(*a == *p);
        assert(*a ==  i);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_dereference_test_constructed_by_pointer()
{ }

template <typename Container>
void iterator_dereference_test_constructed_by_container()
{
    Container c;

    typename Container::value_type i = value_type<Container>(21);
    typename Container::value_type j = value_type<Container>(42);

    c.insert(c.begin(), j);
    c.insert(c.begin(), i);
    {
        // it
        typename Container::iterator a = c.begin();
        typename Container::iterator b(a);

        assert(*a == *b);
        assert(*a == *(c.begin()));
        assert(*b == *(c.begin()));
        assert(*(c.begin()) == *(c.begin()));
    }
    {
        // const_it
        typename Container::const_iterator a = c.begin();
        typename Container::const_iterator b(a);

        assert(*a == *b);
        assert(*a == *(c.begin()));
        assert(*b == *(c.begin()));
        assert(*(c.begin()) == *(c.begin()));
    }
    {
        // rev_it
        typename Container::iterator a = c.begin();
        typename Container::reverse_iterator b(a);

        assert(*a == *(--b));
        assert(*(++a) == *(--b));
    }
    {
        // const_rev_it
        typename Container::iterator a = c.begin();
        typename Container::const_reverse_iterator b(a);

        assert(*a == *(--b));
        assert(*(++a) == *(--b));
    }
}

template <typename Container>
void iterator_dereference_test()
{
    iterator_dereference_test_constructed_by_default<Container>();
    iterator_dereference_test_constructed_by_pointer<Container>();
    iterator_dereference_test_constructed_by_container<Container>();

    log("operator*");
}

/// @note vector case
template <typename Container>
typename std::enable_if<is_vector<Container>::value, void>::type
iterator_dereference_pointer_test_constructed_by_pointer()
{
    typename Container::value_type i = value_type<Container>(42);
    typename Container::value_type * p = &i;
    {
        // it
        typename Container::iterator a(p);
        assert(a.operator->() == p);
    }
    {
        // const_it
        typename Container::const_iterator a(p);
        assert(a.operator->() == p);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_dereference_pointer_test_constructed_by_pointer()
{ }

template <typename Container>
void iterator_dereference_pointer_test_constructed_by_container()
{
    Container c;

    typename Container::value_type i = value_type<Container>(21);
    typename Container::value_type j = value_type<Container>(42);

    c.insert(c.begin(), j);
    c.insert(c.begin(), i);
    {
        // it
        typename Container::iterator a = c.begin();
        typename Container::iterator b(a);

        assert(a.operator->() == &(*b));
        assert(a.operator->() == &(*(c.begin())));
        assert(b.operator->() == &(*(c.begin())));
        assert(c.begin().operator->() == &(*c.begin()));
    }
    {
        // const_it
        typename Container::const_iterator a = c.begin();
        typename Container::const_iterator b(a);

        assert(a.operator->() == &(*b));
        assert(a.operator->() == &(*(c.begin())));
        assert(b.operator->() == &(*(c.begin())));
        assert(c.begin().operator->() == &(*c.begin()));
    }
    {
        // rev_it
        typename Container::iterator a = c.begin();
        typename Container::reverse_iterator b(a);

        assert(a.operator->() == &(*(--b)));
        assert(a.operator->() == &(*(c.begin())));
        assert(b.operator->() == &(*(c.begin())));
        assert(c.begin().operator->() == &(*c.begin()));
    }
    {
        // const_rev_it
        typename Container::iterator a = c.begin();
        typename Container::const_reverse_iterator b(a);

        assert(a.operator->() == &(*(--b)));
        assert(a.operator->() == &(*(c.begin())));
        assert(b.operator->() == &(*(c.begin())));
        assert(c.begin().operator->() == &(*c.begin()));
    }
}

template <typename Container>
void iterator_dereference_pointer_test()
{
    iterator_dereference_pointer_test_constructed_by_pointer<Container>();
    iterator_dereference_pointer_test_constructed_by_container<Container>();

    log("operator->");
}

template <bool B, typename Container>
typename ft::enable_if<B>::type
output_iterator_test()
{
    iterator_dereference_test<Container>();
    iterator_dereference_pointer_test<Container>();
}

template <bool B, typename Container>
typename ft::enable_if<!B>::type
output_iterator_test() { }

/****** Forward iterator test *************************************************/

template <bool B, typename Container>
typename ft::enable_if<B>::type
forward_iterator_test() { }

template <bool B, typename Container>
typename ft::enable_if<!B>::type
forward_iterator_test() { }

/****** Bidirectional iterator test *******************************************/

/// @note both prefix and postfix
template <typename Container>
void iterator_decrement_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // prefix
        {
            // it
            typename Container::iterator it = c.end();
            --it;
            assert(*it == b);
            assert(*(--it) == a);
            assert(*it == a);
        }
        {
            // const_it
            typename Container::const_iterator it = c.end();
            --it;
            assert(*it == b);
            assert(*(--it) == a);
            assert(*it == a);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rend();
            --it;
            assert(*it == a);
            assert(*(--it) == b);
            assert(*it == b);
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rend();
            --it;
            assert(*it == a);
            assert(*(--it) == b);
            assert(*it == b);
        }
    }
    {
        // postfix
        {
            // it
            typename Container::iterator it = c.end();
            it--;
            assert(*it == b);
            assert(*(it--) == b);
            assert(*it == a);
        }
        {
            // const_it
            typename Container::const_iterator it = c.end();
            it--;
            assert(*it == b);
            assert(*(it--) == b);
            assert(*it == a);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rend();
            it--;
            assert(*it == a);
            assert(*(it--) == a);
            assert(*it == b);
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rend();
            it--;
            assert(*it == a);
            assert(*(it--) == a);
            assert(*it == b);
        }
    }
    log("decrement");
}

template <bool B, typename Container>
typename ft::enable_if<B>::type
bidirectional_iterator_test()
{
    iterator_decrement_test<Container>();
}

template <bool B, typename Container>
typename ft::enable_if<!B>::type
bidirectional_iterator_test() { }

/****** Random access iterator test *******************************************/

template <typename Container>
void iterator_addition_test()
{
    Container ctn;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);
    typename Container::value_type c = value_type<Container>(55);

    ctn.insert(ctn.begin(), c);
    ctn.insert(ctn.begin(), b);
    ctn.insert(ctn.begin(), a);

    {
        // it
        typename Container::iterator it = ctn.begin();

        assert(it + 0 == it);
        assert(it + 1 == ++ctn.begin());
        assert(it + 2 == it + 1 + 1);
        assert(it + 3 == ctn.end());

        assert(*(it + 0) == 21);
        assert(*(it + 1) == 42);
        assert(*(it + 2) == 55);
    }
    {
        // const_it
        typename Container::const_iterator it = ctn.begin();

        assert(it + 0 == it);
        assert(it + 1 == ++ctn.begin());
        assert(it + 2 == it + 1 + 1);
        assert(it + 3 == ctn.end());

        assert(*(it + 0) == 21);
        assert(*(it + 1) == 42);
        assert(*(it + 2) == 55);
    }
    {
        // rev_it
        typename Container::reverse_iterator rit = ctn.rbegin();

        assert(rit + 0 == rit);
        assert(rit + 1 == ++ctn.rbegin());
        assert(rit + 2 == rit + 1 + 1);
        assert(rit + 3 == ctn.rend());

        assert(*(rit + 0) == 55);
        assert(*(rit + 1) == 42);
        assert(*(rit + 2) == 21);
    }
    {
        // const_rev_rit
        typename Container::const_reverse_iterator rit = ctn.rbegin();

        assert(rit + 0 == rit);
        assert(rit + 1 == ++ctn.rbegin());
        assert(rit + 2 == rit + 1 + 1);
        assert(rit + 3 == ctn.rend());

        assert(*(rit + 0) == 55);
        assert(*(rit + 1) == 42);
        assert(*(rit + 2) == 21);
    }
    log("operator+");
}

template <typename Container>
void iterator_substraction_test()
{
    Container ctn;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);
    typename Container::value_type c = value_type<Container>(55);

    ctn.insert(ctn.begin(), c);
    ctn.insert(ctn.begin(), b);
    ctn.insert(ctn.begin(), a);

    {
        // with number
        {
            // it - n
            typename Container::iterator it = ctn.end();

            assert(it - 0 == it);
            assert(it - 1 == --ctn.end());
            assert(it - 2 == it - 1 - 1);
            assert(it - 3 == ctn.begin());

            assert(*(it - 1) == 55);
            assert(*(it - 2) == 42);
            assert(*(it - 3) == 21);
        }
        {
            // const_it - n
            typename Container::const_iterator it = ctn.end();

            assert(it - 0 == it);
            assert(it - 1 == --ctn.end());
            assert(it - 2 == it - 1 - 1);
            assert(it - 3 == ctn.begin());

            assert(*(it - 1) == 55);
            assert(*(it - 2) == 42);
            assert(*(it - 3) == 21);
        }
        {
            // rev_it - n
            typename Container::reverse_iterator it = ctn.rend();

            assert(it - 0 == it);
            assert(it - 1 == --ctn.rend());
            assert(it - 2 == it - 1 - 1);
            assert(it - 3 == ctn.rbegin());

            assert(*(it - 1) == 21);
            assert(*(it - 2) == 42);
            assert(*(it - 3) == 55);
        }
        {
            // const_rev_it - n
            typename Container::const_reverse_iterator it = ctn.rend();

            assert(it - 0 == it);
            assert(it - 1 == --ctn.rend());
            assert(it - 2 == it - 1 - 1);
            assert(it - 3 == ctn.rbegin());

            assert(*(it - 1) == 21);
            assert(*(it - 2) == 42);
            assert(*(it - 3) == 55);
        }
    }
    {
        // with iterator
        {
            // it - it
            typename Container::iterator it = ctn.begin();
            typename Container::iterator ite = ctn.end();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 3);
            assert(ite - it == static_cast<ptrdiff_t>(ctn.size()));
        }
        {
            // it - const_it
            typename Container::iterator it = ctn.begin();
            typename Container::iterator ite = ctn.end();
            typename Container::const_iterator cit = ctn.begin();

            assert(it - cit == 0);
            assert(ite - cit == 3);
            assert(ite - cit == static_cast<ptrdiff_t>(ctn.size())); // TODO
        }
        {
            // const_it - it
            typename Container::iterator it = ctn.begin();
            typename Container::const_iterator cit = ctn.begin();
            typename Container::const_iterator cite = ctn.end();

            assert(cit - it == 0);
            assert(cite - it == 3);
            assert(cite - it == static_cast<ptrdiff_t>(ctn.size())); // TODO
        }
        {
            // const_it - const_it
            typename Container::const_iterator it = ctn.begin();
            typename Container::const_iterator ite = ctn.end();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 3);
            assert(ite - it == static_cast<ptrdiff_t>(ctn.size())); // TOOD
        }
        {
            // rev_it - rev_it
            typename Container::reverse_iterator it = ctn.rbegin();
            typename Container::reverse_iterator ite = ctn.rend();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 3);
            assert(ite - it == static_cast<ptrdiff_t>(ctn.size())); // TODO
        }
        {
            // rev_it - const_rev_it
            typename Container::reverse_iterator rit = ctn.rbegin();
            typename Container::reverse_iterator rite = ctn.rend();
            typename Container::const_reverse_iterator crit = ctn.rbegin();

            assert(rit - crit == 0);
            assert(rite - crit == 3);
            assert(rite - crit == static_cast<ptrdiff_t>(ctn.size())); // TODO
        }
        {
            // const_rev_it - rev_it
            typename Container::reverse_iterator rit = ctn.rbegin();
            typename Container::const_reverse_iterator crit = ctn.rbegin();
            typename Container::const_reverse_iterator crite = ctn.rend();

            assert(crit - rit == 0);
            assert(crite - rit == 3);
            assert(crite - rit == static_cast<ptrdiff_t>(ctn.size())); // TODO
        }
        {
            // const_rev_it - const_rev_it
            typename Container::const_reverse_iterator it = ctn.rbegin();
            typename Container::const_reverse_iterator ite = ctn.rend();

            assert(it - it  == 0);
            assert(ite - ite == 0);
            assert(ite - it == 3);
            assert(ite - it == static_cast<ptrdiff_t>(ctn.size())); // TODO
        }
        /// @note Operations between (const) iterators and (const) reverse
        ///       iterators are forbidden. It means each expression below should
        ///       not compile:
        ///
        ///     . iterator - reverse_iterator
        ///     . iterator - const_reverse_iterator
        ///     . const_iterator - reverse_iterator
        ///     . const_iterator - const_reverse_iterator
        ///     . reverse_iterator - iterator
        ///     . reverse_iterator - const_iterator
        ///     . const_reverse_iterator - iterator
        ///     . const_reverse_iterator - const_iterator
    }
    log("operator-");
}

template <typename Container>
void iterator_less_than_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // it < it
        typename Container::iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // it < const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // const_it < it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // const_it < const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(it < ite);
        assert(it < it + 1);
        assert(it + 1 < it + 2);
    }
    {
        // rev_it < rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        assert(rit < rite);
        assert(rit < rite + 1);
        assert(rit + 1 < rite + 2);
    }
    {
        // rev_it < const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(rit < crite);
        assert(rit < crit + 1);
        assert(rit + 1 < crit + 2);
    }
    {
        // const_rev_it < rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();

        assert(crit < rite);
        assert(crit < rit + 1);
        assert(crit + 1 < rit + 2);
    }
    {
        // const_rev_it < const_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crit < crite);
        assert(crit < crite + 1);
        assert(crit + 1 < crite + 2);
    }
    /// @note Same than operator-. Operations between (const) iterators and
    ///       (const) reverse iterators are forbidden. It means each expression
    //        below should not compile:
    ///
    ///     . iterator < reverse_iterator
    ///     . iterator < const_reverse_iterator
    ///     . const_iterator < reverse_iterator
    ///     . const_iterator < const_reverse_iterator
    ///     . reverse_iterator < iterator
    ///     . reverse_iterator < const_iterator
    ///     . const_reverse_iterator < iterator
    ///     . const_reverse_iterator < const_iterator
    log("operator<");
}

template <typename Container>
void iterator_greather_than_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // it > it
        typename Container::iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // it > const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // const_it > it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // const_it > const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(ite > it);
        assert(it + 1 > it);
        assert(it + 2 > it + 1);
    }
    {
        // rev_it > rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        assert(rite > rit);
        assert(rit + 1 > rit);
        assert(rit + 2 > rit + 1);
    }
    {
        // rev_it > const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();

        assert(rite > crit);
        assert(rit + 1 > crit);
        assert(rit + 2 > crit + 1);
    }
    {
        // const_rev_it > rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crite > rit);
        assert(crit + 1 > rit);
        assert(crit + 2 > rit + 1);
    }
    {
        // const_rev_it > const_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crite > crit);
        assert(crit + 1 > crit);
        assert(crit + 2 > crit + 1);
    }

    log("operator>");
}

template <typename Container>
void iterator_less_than_or_equal_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // it <= it
        typename Container::iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // it <= const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // const_it <= it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // const_it <= const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(it <= it);
        assert(ite <= ite);
        assert(it <= it + 1);
        assert(it + 1 <= it + 2);
        assert(it <= ite);
    }
    {
        // rev_it <= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        assert(rit <= rit);
        assert(rite <= rite);
        assert(rit <= rit + 1);
        assert(rit + 1 <= rit + 2);
        assert(rit <= rite);
    }
    {
        // rev_it <= const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(rit <= crit);
        assert(rite <= crite);
        assert(rit <= crit + 1);
        assert(rit + 1 <= crit + 2);
        assert(rit <= crite);
    }
    {
        // const_rev_it <= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crit <= rit);
        assert(crite <= rite);
        assert(crit <= rit + 1);
        assert(crit + 1 <= rit + 2);
        assert(crit <= rite);
    }
    {
        // const_rev_it <= cnost_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crit <= crit);
        assert(crite <= crite);
        assert(crit <= crit + 1);
        assert(crit + 1 <= crit + 2);
        assert(crit <= crite);
    }
    log("operator<=");
}

template <typename Container>
void iterator_greather_than_or_equal_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // it >= it
        typename Container::iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // it >= const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // const_it >= it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // const_it >= const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        assert(it >= it);
        assert(ite >= ite);
        assert(it + 1 >= it);
        assert(it + 2 >= it + 1);
        assert(ite >= it);
    }
    {
        // rev_it >= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        assert(rit >= rit);
        assert(rite >= rite);
        assert(rit + 1 >= rit);
        assert(rit + 2 >= rit + 1);
        assert(rite >= rit);
    }
    {
        // rev_it >= const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(rit >= crit);
        assert(rite >= crite);
        assert(rit + 1 >= crit);
        assert(rit + 2 >= crit + 1);
        assert(rite >= crit);
    }
    {
        // const_rev_it >= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crit >= rit);
        assert(crite >= rite);
        assert(crit + 1 >= rit);
        assert(crit + 2 >= rit + 1);
        assert(crite >= rit);
    }
    {
        // const_rev_it >= const_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        assert(crit >= crit);
        assert(crite >= crite);
        assert(crit + 1 >= crit);
        assert(crit + 2 >= crit + 1);
        assert(crite >= crit);
    }
    log("operator>=");
}

template <typename Container>
void iterator_add_then_assign_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // it += n
        typename Container::iterator it = c.begin();

        assert((it += 1) == c.begin() + 1);
        assert((it += 1) == c.begin() + 2);
        assert((it += 2) == c.begin() + 4);
    }
    {
        // const_it += n
        typename Container::const_iterator it = c.begin();

        assert((it += 1) == c.begin() + 1);
        assert((it += 1) == c.begin() + 2);
        assert((it += 2) == c.begin() + 4);
    }
    {
        // rev_it += n
        typename Container::reverse_iterator it = c.rbegin();

        assert((it += 1) == c.rbegin() + 1);
        assert((it += 1) == c.rbegin() + 2);
        assert((it += 2) == c.rbegin() + 4);
    }
    {
        // const_rev_it += n
        typename Container::const_reverse_iterator it = c.rbegin();

        assert((it += 1) == c.rbegin() + 1);
        assert((it += 1) == c.rbegin() + 2);
        assert((it += 2) == c.rbegin() + 4);
    }

    log("operator+=");
}

template <typename Container>
void iterator_sub_then_assign_test()
{
    Container c;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);

    c.insert(c.begin(), b);
    c.insert(c.begin(), a);

    {
        // it += n
        typename Container::iterator ite = c.end();

        assert((ite -= 1) == c.end() - 1);
        assert((ite -= 1) == c.end() - 2);
        assert((ite -= 2) == c.end() - 4);
    }
    {
        // const_it -= n
        typename Container::const_iterator ite = c.end();

        assert((ite -= 1) == c.end() - 1);
        assert((ite -= 1) == c.end() - 2);
        assert((ite -= 2) == c.end() - 4);
    }
    {
        // rev_it -= n
        typename Container::reverse_iterator ite = c.rend();

        assert((ite -= 1) == c.rend() - 1);
        assert((ite -= 1) == c.rend() - 2);
        assert((ite -= 2) == c.rend() - 4);
    }
    {
        // const_rev_it -= n
        typename Container::const_reverse_iterator ite = c.rend();

        assert((ite -= 1) == c.rend() - 1);
        assert((ite -= 1) == c.rend() - 2);
        assert((ite -= 2) == c.rend() - 4);
    }

    log("operator-=");
}

template <typename Container>
void iterator_brackets_operator_test()
{
    Container ctn;

    typename Container::value_type a = value_type<Container>(21);
    typename Container::value_type b = value_type<Container>(42);
    typename Container::value_type c = value_type<Container>(55);

    ctn.insert(ctn.begin(), c);
    ctn.insert(ctn.begin(), b);
    ctn.insert(ctn.begin(), a);

    {
        // it
        typename Container::iterator it = ctn.begin();

        assert(it[0] == 21);
        assert(it[1] == 42);
        assert(it[2] == 55);
    }
    {
        // const_it
        typename Container::const_iterator it = ctn.begin();

        assert(it[0] == 21);
        assert(it[1] == 42);
        assert(it[2] == 55);
    }
    {
        // rev_it
        typename Container::reverse_iterator it = ctn.rbegin();

        assert(it[0] == 55);
        assert(it[1] == 42);
        assert(it[2] == 21);
    }
    {
        // const_rev_it
        typename Container::const_reverse_iterator it = ctn.rbegin();

        assert(it[0] == 55);
        assert(it[1] == 42);
        assert(it[2] == 21);
    }

    typename Container::iterator it = ctn.begin();
    typename Container::value_type x = it[42]; // doesn't throw anything
    typename Container::value_type y = it[-4]; // doesn't throw anything
    (void)x;
    (void)y;

    log("operator[]");
}

template <bool B, typename Container>
typename ft::enable_if<B>::type
random_access_iterator_test()
{
    iterator_addition_test<Container>();
    iterator_substraction_test<Container>();

    iterator_less_than_test<Container>();
    iterator_greather_than_test<Container>();

    iterator_less_than_or_equal_test<Container>();
    iterator_greather_than_or_equal_test<Container>();

    iterator_add_then_assign_test<Container>();
    iterator_sub_then_assign_test<Container>();

    iterator_brackets_operator_test<Container>();
}

template <bool B, typename Container>
typename ft::enable_if<!B>::type
random_access_iterator_test() { }

/****** All iterator tests ****************************************************/

template <typename Container>
void iterator_test()
{
    /// @note Since we can't template a namespace, we will use the `||` operator
    /// to match iterator tag for both `std` and `ft` based containers. There
    /// might be better approach.

    /****** Common iterator test **********************************************/

    iterator_constructor_by_default_test<Container>();

    iterator_constructor_by_pointer_test<Container>();

    iterator_constructor_by_copy_test<Container>();

    iterator_assignation_test<Container>();

    /// @note both prefix and postfix
    iterator_increment_test<Container>();

    reverse_iterator_base_test<Container>();

    typedef typename Container::iterator::iterator_category iterator_category;

    /****** Input iterator test ***********************************************/

    typedef typename  ft::input_iterator_tag     ft_input_tag;
    typedef typename std::input_iterator_tag    std_input_tag;

    input_iterator_test<
    std::is_base_of< ft_input_tag, iterator_category>::value ||
    std::is_base_of<std_input_tag, iterator_category>::value, Container
    >();

    /****** Output iterator test **********************************************/

    typedef typename  ft::output_iterator_tag    ft_output_tag;
    typedef typename std::output_iterator_tag   std_output_tag;

    output_iterator_test<
    std::is_base_of< ft_output_tag, iterator_category>::value ||
    std::is_base_of<std_output_tag, iterator_category>::value, Container
    >();

    /// @note Yes this is shit. Hopefully temporary.
    output_iterator_test<true, Container>();

    /****** Forward iterator test *********************************************/

    typedef typename  ft::forward_iterator_tag   ft_forward_tag;
    typedef typename std::forward_iterator_tag  std_forward_tag;

    forward_iterator_test<
    std::is_base_of< ft_forward_tag, iterator_category>::value ||
    std::is_base_of<std_forward_tag, iterator_category>::value, Container
    >();

    /****** Bidirectional iterator test ***************************************/

    typedef typename  ft::bidirectional_iterator_tag     ft_bidirectional_tag;
    typedef typename std::bidirectional_iterator_tag    std_bidirectional_tag;

    bidirectional_iterator_test<
    std::is_base_of< ft_bidirectional_tag, iterator_category>::value ||
    std::is_base_of<std_bidirectional_tag, iterator_category>::value, Container
    >();

    /****** Random access iterator test ***************************************/

    typedef typename  ft::random_access_iterator_tag     ft_random_access_tag;
    typedef typename std::random_access_iterator_tag    std_random_access_tag;

    random_access_iterator_test<
    std::is_base_of< ft_random_access_tag, iterator_category>::value ||
    std::is_base_of<std_random_access_tag, iterator_category>::value, Container
    >();
}

#endif /* OUTPUT_ITERATOR_HPP */