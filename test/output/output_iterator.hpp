#ifndef OUTPUT_ITERATOR_HPP
#define OUTPUT_ITERATOR_HPP 1

#include <map>
#include <vector>
#include <type_traits> // std::is_base_of

#include "ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"

#include "ft_map.hpp"
#include "rb_tree.hpp"
#include "ft_vector.hpp"
#include "utils.hpp"

/// @todo Add tests to increment and decrement out of container boundaries.

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

/// @note rbtree case
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, void>::type
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

        expect(a != b);
        a = b;
        expect(a == b);
    }

    {
        // const_it = const_it
        typename Container::const_iterator    a;
        typename Container::const_iterator    b = c.begin();

        expect(a != b);
        a = b;
        expect(a == b);
    }
    {
        // const_it = it
        typename Container::const_iterator      a;
        typename Container::iterator            b = c.begin();

        expect(a != b);
        a = b;
        expect(a == b);
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

        expect(c != b);
        c = b;
        expect(c == b);
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

        expect(c != b);
        c = b;
        expect(c == b);
    }
    {
        // const_rev_it = const_rev_it
        typename Container::iterator                a = c.begin();
        typename Container::const_reverse_iterator  b(a);
        typename Container::const_reverse_iterator  c;

        expect(c != b);
        c = b;
        expect(c == b);
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
            expect(*it == a);
            expect(*(++it) == b);
            expect(*it == b);
        }
        {
            // const_it
            typename Container::const_iterator it = c.begin();
            expect(*it == a);
            expect(*(++it) == b);
            expect(*it == b);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rbegin();
            expect(it.base() == c.end());
            ++it;
            expect(it.base() == --c.end());
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rbegin();
            expect(it.base() == c.end());
            ++it;
            expect(it.base() == --c.end());
        }
    }
    {
        // postfix
        {
            // it
            typename Container::iterator it = c.begin();
            expect(*it == a);
            expect(*(it++) == a);
            expect(*it == b);
        }
        {
            // const_it
            typename Container::const_iterator it = c.begin();
            expect(*it == a);
            expect(*(it++) == a);
            expect(*it == b);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rbegin();
            expect(it.base() == c.end());
            ++it;
            expect(it.base() == --c.end());
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rbegin();
            expect(it.base() == c.end());
            ++it;
            expect(it.base() == --c.end());
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

    expect(c.rbegin().base() == c.end());
    expect(c.rend().base() == c.begin());

    typename Container::iterator it(c.begin());
    typename Container::reverse_iterator rit(it);

    expect(rit.base() == it);
    expect(&*(--(typename Container::iterator(rit.base()))) == &*rit);

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
        expect(a == b);
        expect(b == a);
    }
    {
        // it == const_it && const_it == it
        typename Container::iterator	     a;
        typename Container::const_iterator   b;
        expect(a == b);
        expect(b == a);
    }
    {
        // const_it == const_it
        typename Container::const_iterator   a;
        typename Container::const_iterator   b;
        expect(a == b);
        expect(b == a);
    }
    {
        // rev_it = rev_it
        typename Container::reverse_iterator a;
        typename Container::reverse_iterator b;
        expect(a == b);
        expect(b == a);
    }
    {
        // rev_it == const_rev_it && const_rev_it == rev_it
        typename Container::reverse_iterator	     a;
        typename Container::const_reverse_iterator   b;
        expect(a == b);
        expect(b == a);
    }
    {
        // const_rev_it == const_rev_it
        typename Container::const_reverse_iterator   a;
        typename Container::const_reverse_iterator   b;
        expect(a == b);
        expect(b == a);
    }
}

template <typename Container>
void iterator_non_equal_test_constructed_by_default()
{
    {
        // it != it
        typename Container::iterator a;
        typename Container::iterator b;
        expect(!(a != b));
        expect(!(b != a));
    }
    {
        // it != const_it && const_it != it
        typename Container::iterator	     a;
        typename Container::const_iterator   b;
        expect(!(a != b));
        expect(!(b != a));
    }
    {
        // const_it != const_it
        typename Container::const_iterator   a;
        typename Container::const_iterator   b;
        expect(!(a != b));
        expect(!(b != a));
    }
    {
        // rev_it != rev_it
        typename Container::reverse_iterator a;
        typename Container::reverse_iterator b;
        expect(!(a != b));
        expect(!(b != a));
    }
    {
        // rev_it != const_rev_it && const_rev_it != rev_it
        typename Container::reverse_iterator	     a;
        typename Container::const_reverse_iterator   b;
        expect(!(a != b));
        expect(!(b != a));
    }
    {
        // const_rev_it != const_rev_it
        typename Container::const_reverse_iterator   a;
        typename Container::const_reverse_iterator   b;
        expect(!(a != b));
        expect(!(b != a));
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
        expect(a == b);
        expect(b == a);
    }
    {
        // it == const_it && const_it == it
        typename Container::iterator	    a(p);
        typename Container::const_iterator  b(p);
        expect(a == b);
        expect(b == a);
    }
    {
        // const_it == const_it
        typename Container::const_iterator  a(p);
        typename Container::const_iterator  b(p);
        expect(a == b);
        expect(b == a);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_equal_test_constructed_by_pointer()
{ }

/// @note rbtree case
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, void>::type
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
        expect(a != b);
        expect(b != a);
    }
    {
        // it != const_it
        // const_it != it
        typename Container::iterator	    a(p);
        typename Container::const_iterator  b(q);
        expect(a != b);
        expect(b != a);
    }
    {
        // const_it != const_it
        typename Container::const_iterator	a(p);
        typename Container::const_iterator  b(q);
        expect(a != b);
        expect(b != a);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_non_equal_test_constructed_by_pointer()
{ }

/// @note rbtree case
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, void>::type
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

        expect(a == b);
        expect(b == a);
        expect(a == c.begin());
        expect(b == c.begin());
        expect(c.begin() == c.begin());
        expect(c.end() == c.end());
    }

    // rev_it
    {
        typename Container::reverse_iterator a = c.rend();
        typename Container::reverse_iterator b(a);

        expect(a == b);
        expect(b == a);
        expect(a.base() == c.begin());
        expect(b.base() == c.begin());
        expect(a.base() == a.base());
        expect(b.base() == b.base());
        expect(c.rbegin().base() == c.end());
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

        expect(a != b);
        expect(a != c2.begin());
        expect(b != c1.begin());
        expect(c1.begin() != c2.begin());
        expect(c1.end() != c2.end());
    }

    // rev_it
    {
        typename Container::reverse_iterator a = c1.rend();
        typename Container::reverse_iterator b = c2.rend();

        expect(a != b);
        expect(a != c2.rend());
        expect(b != c1.rend());
        expect(c1.rbegin() != c2.rbegin());
        expect(c1.rend() != c2.rend());
        expect(a.base() != b.base());
    }
}

template <typename Container>
void iterator_equal_test()
{
    iterator_equal_test_constructed_by_default<Container>();
    iterator_equal_test_constructed_by_pointer<Container>();
    iterator_equal_test_constructed_by_copy<Container>();

    log("operator==");
}

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
    // expect(*a);
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
        expect(*a == *p);
        expect(*a ==  i);
    }
    {
        // const_it
        typename Container::const_iterator a(p);
        expect(*a == *p);
        expect(*a ==  i);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_dereference_test_constructed_by_pointer()
{ }

/// @note rbtree case
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, void>::type
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

        expect(*a == *b);
        expect(*a == *(c.begin()));
        expect(*b == *(c.begin()));
        expect(*(c.begin()) == *(c.begin()));
    }
    {
        // const_it
        typename Container::const_iterator a = c.begin();
        typename Container::const_iterator b(a);

        expect(*a == *b);
        expect(*a == *(c.begin()));
        expect(*b == *(c.begin()));
        expect(*(c.begin()) == *(c.begin()));
    }
    {
        // rev_it
        typename Container::iterator a = c.begin();
        typename Container::reverse_iterator b(a);

        expect(*a == *(--b));
        expect(*(++a) == *(--b));
    }
    {
        // const_rev_it
        typename Container::iterator a = c.begin();
        typename Container::const_reverse_iterator b(a);

        expect(*a == *(--b));
        expect(*(++a) == *(--b));
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
        expect(a.operator->() == p);
    }
    {
        // const_it
        typename Container::const_iterator a(p);
        expect(a.operator->() == p);
    }
}

/// @note map case
template <typename Container>
typename std::enable_if<is_map<Container>::value, void>::type
iterator_dereference_pointer_test_constructed_by_pointer()
{ }

/// @note rbtree case
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, void>::type
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

        expect(a.operator->() == &(*b));
        expect(a.operator->() == &(*(c.begin())));
        expect(b.operator->() == &(*(c.begin())));
        expect(c.begin().operator->() == &(*c.begin()));
    }
    {
        // const_it
        typename Container::const_iterator a = c.begin();
        typename Container::const_iterator b(a);

        expect(a.operator->() == &(*b));
        expect(a.operator->() == &(*(c.begin())));
        expect(b.operator->() == &(*(c.begin())));
        expect(c.begin().operator->() == &(*c.begin()));
    }
    {
        // rev_it
        typename Container::iterator a = c.begin();
        typename Container::reverse_iterator b(a);

        expect(a.operator->() == &(*(--b)));
        expect(a.operator->() == &(*(c.begin())));
        expect(b.operator->() == &(*(c.begin())));
        expect(c.begin().operator->() == &(*c.begin()));
    }
    {
        // const_rev_it
        typename Container::iterator a = c.begin();
        typename Container::const_reverse_iterator b(a);

        expect(a.operator->() == &(*(--b)));
        expect(a.operator->() == &(*(c.begin())));
        expect(b.operator->() == &(*(c.begin())));
        expect(c.begin().operator->() == &(*c.begin()));
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
            expect(*it == b);
            expect(*(--it) == a);
            expect(*it == a);
        }
        {
            // const_it
            typename Container::const_iterator it = c.end();
            --it;
            expect(*it == b);
            expect(*(--it) == a);
            expect(*it == a);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rend();
            --it;
            expect(*it == a);
            expect(*(--it) == b);
            expect(*it == b);
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rend();
            --it;
            expect(*it == a);
            expect(*(--it) == b);
            expect(*it == b);
        }
    }
    {
        // postfix
        {
            // it
            typename Container::iterator it = c.end();
            it--;
            expect(*it == b);
            expect(*(it--) == b);
            expect(*it == a);
        }
        {
            // const_it
            typename Container::const_iterator it = c.end();
            it--;
            expect(*it == b);
            expect(*(it--) == b);
            expect(*it == a);
        }
        {
            // rev_it
            typename Container::reverse_iterator it = c.rend();
            it--;
            expect(*it == a);
            expect(*(it--) == a);
            expect(*it == b);
        }
        {
            // const_rev_it
            typename Container::const_reverse_iterator it = c.rend();
            it--;
            expect(*it == a);
            expect(*(it--) == a);
            expect(*it == b);
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

        expect(it + 0 == it);
        expect(it + 1 == ++ctn.begin());
        expect(it + 2 == it + 1 + 1);
        expect(it + 3 == ctn.end());

        expect(*(it + 0) == 21);
        expect(*(it + 1) == 42);
        expect(*(it + 2) == 55);
    }
    {
        // const_it
        typename Container::const_iterator it = ctn.begin();

        expect(it + 0 == it);
        expect(it + 1 == ++ctn.begin());
        expect(it + 2 == it + 1 + 1);
        expect(it + 3 == ctn.end());

        expect(*(it + 0) == 21);
        expect(*(it + 1) == 42);
        expect(*(it + 2) == 55);
    }
    {
        // rev_it
        typename Container::reverse_iterator rit = ctn.rbegin();

        expect(rit + 0 == rit);
        expect(rit + 1 == ++ctn.rbegin());
        expect(rit + 2 == rit + 1 + 1);
        expect(rit + 3 == ctn.rend());

        expect(*(rit + 0) == 55);
        expect(*(rit + 1) == 42);
        expect(*(rit + 2) == 21);
    }
    {
        // const_rev_rit
        typename Container::const_reverse_iterator rit = ctn.rbegin();

        expect(rit + 0 == rit);
        expect(rit + 1 == ++ctn.rbegin());
        expect(rit + 2 == rit + 1 + 1);
        expect(rit + 3 == ctn.rend());

        expect(*(rit + 0) == 55);
        expect(*(rit + 1) == 42);
        expect(*(rit + 2) == 21);
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

            expect(it - 0 == it);
            expect(it - 1 == --ctn.end());
            expect(it - 2 == it - 1 - 1);
            expect(it - 3 == ctn.begin());

            expect(*(it - 1) == 55);
            expect(*(it - 2) == 42);
            expect(*(it - 3) == 21);
        }
        {
            // const_it - n
            typename Container::const_iterator it = ctn.end();

            expect(it - 0 == it);
            expect(it - 1 == --ctn.end());
            expect(it - 2 == it - 1 - 1);
            expect(it - 3 == ctn.begin());

            expect(*(it - 1) == 55);
            expect(*(it - 2) == 42);
            expect(*(it - 3) == 21);
        }
        {
            // rev_it - n
            typename Container::reverse_iterator it = ctn.rend();

            expect(it - 0 == it);
            expect(it - 1 == --ctn.rend());
            expect(it - 2 == it - 1 - 1);
            expect(it - 3 == ctn.rbegin());

            expect(*(it - 1) == 21);
            expect(*(it - 2) == 42);
            expect(*(it - 3) == 55);
        }
        {
            // const_rev_it - n
            typename Container::const_reverse_iterator it = ctn.rend();

            expect(it - 0 == it);
            expect(it - 1 == --ctn.rend());
            expect(it - 2 == it - 1 - 1);
            expect(it - 3 == ctn.rbegin());

            expect(*(it - 1) == 21);
            expect(*(it - 2) == 42);
            expect(*(it - 3) == 55);
        }
    }
    {
        // with iterator
        {
            // it - it
            typename Container::iterator it = ctn.begin();
            typename Container::iterator ite = ctn.end();

            expect(it - it  == 0);
            expect(ite - ite == 0);
            expect(ite - it == 3);
            expect(ite - it == static_cast<ptrdiff_t>(ctn.size()));
        }
        {
            // it - const_it
            typename Container::iterator it = ctn.begin();
            typename Container::iterator ite = ctn.end();
            typename Container::const_iterator cit = ctn.begin();

            expect(it - cit == 0);
            expect(ite - cit == 3);
        }
        {
            // const_it - it
            typename Container::iterator it = ctn.begin();
            typename Container::const_iterator cit = ctn.begin();
            typename Container::const_iterator cite = ctn.end();

            expect(cit - it == 0);
            expect(cite - it == 3);
        }
        {
            // const_it - const_it
            typename Container::const_iterator it = ctn.begin();
            typename Container::const_iterator ite = ctn.end();

            expect(it - it  == 0);
            expect(ite - ite == 0);
            expect(ite - it == 3);
        }
        {
            // rev_it - rev_it
            typename Container::reverse_iterator it = ctn.rbegin();
            typename Container::reverse_iterator ite = ctn.rend();

            expect(it - it  == 0);
            expect(ite - ite == 0);
            expect(ite - it == 3);
        }
        {
            // rev_it - const_rev_it
            typename Container::reverse_iterator rit = ctn.rbegin();
            typename Container::reverse_iterator rite = ctn.rend();
            typename Container::const_reverse_iterator crit = ctn.rbegin();

            expect(rit - crit == 0);
            expect(rite - crit == 3);
        }
        {
            // const_rev_it - rev_it
            typename Container::reverse_iterator rit = ctn.rbegin();
            typename Container::const_reverse_iterator crit = ctn.rbegin();
            typename Container::const_reverse_iterator crite = ctn.rend();

            expect(crit - rit == 0);
            expect(crite - rit == 3);
        }
        {
            // const_rev_it - const_rev_it
            typename Container::const_reverse_iterator it = ctn.rbegin();
            typename Container::const_reverse_iterator ite = ctn.rend();

            expect(it - it  == 0);
            expect(ite - ite == 0);
            expect(ite - it == 3);
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

        expect(it < ite);
        expect(it < it + 1);
        expect(it + 1 < it + 2);
    }
    {
        // it < const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(it < ite);
        expect(it < it + 1);
        expect(it + 1 < it + 2);
    }
    {
        // const_it < it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        expect(it < ite);
        expect(it < it + 1);
        expect(it + 1 < it + 2);
    }
    {
        // const_it < const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(it < ite);
        expect(it < it + 1);
        expect(it + 1 < it + 2);
    }
    {
        // rev_it < rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        expect(rit < rite);
        expect(rit < rite + 1);
        expect(rit + 1 < rite + 2);
    }
    {
        // rev_it < const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(rit < crite);
        expect(rit < crit + 1);
        expect(rit + 1 < crit + 2);
    }
    {
        // const_rev_it < rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();

        expect(crit < rite);
        expect(crit < rit + 1);
        expect(crit + 1 < rit + 2);
    }
    {
        // const_rev_it < const_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crit < crite);
        expect(crit < crite + 1);
        expect(crit + 1 < crite + 2);
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

        expect(ite > it);
        expect(it + 1 > it);
        expect(it + 2 > it + 1);
    }
    {
        // it > const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(ite > it);
        expect(it + 1 > it);
        expect(it + 2 > it + 1);
    }
    {
        // const_it > it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        expect(ite > it);
        expect(it + 1 > it);
        expect(it + 2 > it + 1);
    }
    {
        // const_it > const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(ite > it);
        expect(it + 1 > it);
        expect(it + 2 > it + 1);
    }
    {
        // rev_it > rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        expect(rite > rit);
        expect(rit + 1 > rit);
        expect(rit + 2 > rit + 1);
    }
    {
        // rev_it > const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();

        expect(rite > crit);
        expect(rit + 1 > crit);
        expect(rit + 2 > crit + 1);
    }
    {
        // const_rev_it > rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crite > rit);
        expect(crit + 1 > rit);
        expect(crit + 2 > rit + 1);
    }
    {
        // const_rev_it > const_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crite > crit);
        expect(crit + 1 > crit);
        expect(crit + 2 > crit + 1);
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

        expect(it <= it);
        expect(ite <= ite);
        expect(it <= it + 1);
        expect(it + 1 <= it + 2);
        expect(it <= ite);
    }
    {
        // it <= const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(it <= it);
        expect(ite <= ite);
        expect(it <= it + 1);
        expect(it + 1 <= it + 2);
        expect(it <= ite);
    }
    {
        // const_it <= it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        expect(it <= it);
        expect(ite <= ite);
        expect(it <= it + 1);
        expect(it + 1 <= it + 2);
        expect(it <= ite);
    }
    {
        // const_it <= const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(it <= it);
        expect(ite <= ite);
        expect(it <= it + 1);
        expect(it + 1 <= it + 2);
        expect(it <= ite);
    }
    {
        // rev_it <= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        expect(rit <= rit);
        expect(rite <= rite);
        expect(rit <= rit + 1);
        expect(rit + 1 <= rit + 2);
        expect(rit <= rite);
    }
    {
        // rev_it <= const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(rit <= crit);
        expect(rite <= crite);
        expect(rit <= crit + 1);
        expect(rit + 1 <= crit + 2);
        expect(rit <= crite);
    }
    {
        // const_rev_it <= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crit <= rit);
        expect(crite <= rite);
        expect(crit <= rit + 1);
        expect(crit + 1 <= rit + 2);
        expect(crit <= rite);
    }
    {
        // const_rev_it <= cnost_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crit <= crit);
        expect(crite <= crite);
        expect(crit <= crit + 1);
        expect(crit + 1 <= crit + 2);
        expect(crit <= crite);
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

        expect(it >= it);
        expect(ite >= ite);
        expect(it + 1 >= it);
        expect(it + 2 >= it + 1);
        expect(ite >= it);
    }
    {
        // it >= const_it
        typename Container::iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(it >= it);
        expect(ite >= ite);
        expect(it + 1 >= it);
        expect(it + 2 >= it + 1);
        expect(ite >= it);
    }
    {
        // const_it >= it
        typename Container::const_iterator it = c.begin();
        typename Container::iterator ite = c.end();

        expect(it >= it);
        expect(ite >= ite);
        expect(it + 1 >= it);
        expect(it + 2 >= it + 1);
        expect(ite >= it);
    }
    {
        // const_it >= const_it
        typename Container::const_iterator it = c.begin();
        typename Container::const_iterator ite = c.end();

        expect(it >= it);
        expect(ite >= ite);
        expect(it + 1 >= it);
        expect(it + 2 >= it + 1);
        expect(ite >= it);
    }
    {
        // rev_it >= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();

        expect(rit >= rit);
        expect(rite >= rite);
        expect(rit + 1 >= rit);
        expect(rit + 2 >= rit + 1);
        expect(rite >= rit);
    }
    {
        // rev_it >= const_rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(rit >= crit);
        expect(rite >= crite);
        expect(rit + 1 >= crit);
        expect(rit + 2 >= crit + 1);
        expect(rite >= crit);
    }
    {
        // const_rev_it >= rev_it
        typename Container::reverse_iterator rit = c.rbegin();
        typename Container::reverse_iterator rite = c.rend();
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crit >= rit);
        expect(crite >= rite);
        expect(crit + 1 >= rit);
        expect(crit + 2 >= rit + 1);
        expect(crite >= rit);
    }
    {
        // const_rev_it >= const_rev_it
        typename Container::const_reverse_iterator crit = c.rbegin();
        typename Container::const_reverse_iterator crite = c.rend();

        expect(crit >= crit);
        expect(crite >= crite);
        expect(crit + 1 >= crit);
        expect(crit + 2 >= crit + 1);
        expect(crite >= crit);
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

        expect((it += 1) == c.begin() + 1);
        expect((it += 1) == c.begin() + 2);
        expect((it += 2) == c.begin() + 4);
    }
    {
        // const_it += n
        typename Container::const_iterator it = c.begin();

        expect((it += 1) == c.begin() + 1);
        expect((it += 1) == c.begin() + 2);
        expect((it += 2) == c.begin() + 4);
    }
    {
        // rev_it += n
        typename Container::reverse_iterator it = c.rbegin();

        expect((it += 1) == c.rbegin() + 1);
        expect((it += 1) == c.rbegin() + 2);
        expect((it += 2) == c.rbegin() + 4);
    }
    {
        // const_rev_it += n
        typename Container::const_reverse_iterator it = c.rbegin();

        expect((it += 1) == c.rbegin() + 1);
        expect((it += 1) == c.rbegin() + 2);
        expect((it += 2) == c.rbegin() + 4);
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

        expect((ite -= 1) == c.end() - 1);
        expect((ite -= 1) == c.end() - 2);
        expect((ite -= 2) == c.end() - 4);
    }
    {
        // const_it -= n
        typename Container::const_iterator ite = c.end();

        expect((ite -= 1) == c.end() - 1);
        expect((ite -= 1) == c.end() - 2);
        expect((ite -= 2) == c.end() - 4);
    }
    {
        // rev_it -= n
        typename Container::reverse_iterator ite = c.rend();

        expect((ite -= 1) == c.rend() - 1);
        expect((ite -= 1) == c.rend() - 2);
        expect((ite -= 2) == c.rend() - 4);
    }
    {
        // const_rev_it -= n
        typename Container::const_reverse_iterator ite = c.rend();

        expect((ite -= 1) == c.rend() - 1);
        expect((ite -= 1) == c.rend() - 2);
        expect((ite -= 2) == c.rend() - 4);
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

        expect(it[0] == 21);
        expect(it[1] == 42);
        expect(it[2] == 55);
    }
    {
        // const_it
        typename Container::const_iterator it = ctn.begin();

        expect(it[0] == 21);
        expect(it[1] == 42);
        expect(it[2] == 55);
    }
    {
        // rev_it
        typename Container::reverse_iterator it = ctn.rbegin();

        expect(it[0] == 55);
        expect(it[1] == 42);
        expect(it[2] == 21);
    }
    {
        // const_rev_it
        typename Container::const_reverse_iterator it = ctn.rbegin();

        expect(it[0] == 55);
        expect(it[1] == 42);
        expect(it[2] == 21);
    }

    /// @note doesn't throw anything but valgrind warns about invalid read
//    typename Container::iterator it = ctn.begin();
//    typename Container::value_type x = it[42];
//    typename Container::value_type y = it[-4];
//    (void)x;
//    (void)y;

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

    reverse_iterator_base_test<Container>();

    /// @note both prefix and postfix
    iterator_increment_test<Container>();

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