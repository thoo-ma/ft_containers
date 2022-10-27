#include <map>
#include <list>
#include <deque>
#include <cassert>
#include <memory> // std::allocator
#include <type_traits> // std::is_same (c++11)

#include <limits>

#include "utils.hpp"
#include "ft_map.hpp"
#include "output_iterator.hpp"

/****** Constructors test *****************************************************/

template <typename Map>
void constructor_by_default_test()
{
    {
        // mutable map
        Map a;
        assert(a.empty());
        assert(a.size() == 0);
    }
    {
        // const map
        Map const a;
        assert(a.empty());
        assert(a.size() == 0);
    }
    log("constructor by default");
}

template <typename Map, typename Value>
void constructor_by_copy_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);

    {
        // map(map)
        {
            // from empty
            Map a;
            Map b(a);
            assert(a == b);
        }
        {
            // from non-empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map b(a);
            assert(a == b);
        }
    }
    {
        // map(const map)
        {
            // from empty
            Map const a;
            Map b(a);
            assert(a == b);
        }
        {
            // from non-empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map const b(a);
            assert(a == b);
            Map c(b);
            assert(c == b);
        }
    }
    {
        // const map(map)
        {
            // from empty
            Map a;
            Map const b(a);
            assert(a == b);
        }
        {
            // from non-empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map const b(a);
            assert(a == b);
        }
    }
    {
        // const map(const map)
        {
            // from empty
            Map const a;
            Map const b(a);
            assert(a == b);
        }
        {
            // from non-empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map const b(a);
            assert(a == b);
            Map const c(b);
            assert(c == b);
        }
    }

    log("constructor by copy");
}

template <typename Map, typename Value>
void constructor_by_iterator_range_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);
    {
        // map(map)
        {
            // from empty
            Map a;
            Map b(a.begin(), a.end());
            assert(a == b);
        }
        {
            // from non empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map b(a.begin(), a.end());
            assert(a == b);
        }
    }
    {
        // map(const map)
        {
            // from empty
            Map const a;
            Map b(a.begin(), a.end());
            assert(a == b);
        }
        {
            // from non empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map const m(a);
            Map b(m.begin(), m.end());
            assert(a == b);
        }
    }
    {
        // const map(map)
        {
            // from empty
            Map a;
            Map const b(a.begin(), a.end());
            assert(a == b);
        }
        {
            // from non empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map const b(a.begin(), a.end());
            assert(a == b);
        }
    }
    {
        // const map(const map)
        {
            // from empty
            Map const a;
            Map const b(a.begin(), a.end());
            assert(a == b);
        }
        {
            // from non empty
            Map a;
            a.insert(i);
            a.insert(j);
            a.insert(k);
            Map const m(a);
            Map const b(m.begin(), m.end());
            assert(a == b);
        }
    }
    {
        // From bidirectionnal iterators.
        // Other than (multi)map itself, would also be (multi)set.
        std::list<Value> l;
        l.insert(l.begin(), i);
        l.insert(l.begin(), j);
        l.insert(l.begin(), k);

        Map m;
        m.insert(m.begin(), i);
        m.insert(m.begin(), j);
        m.insert(m.begin(), k);

        assert(Map(l.begin(), l.end()) == m);
    }
    log("constructor by iterator range");
}

template <typename T, typename U>
void constructors_tests()
{
    typedef typename std::map<T,U>::value_type std_value;
    typedef typename  ft::map<T,U>::value_type  ft_value;

    std::cout << "== Constructors ==" << std::endl;

    constructor_by_default_test<std::map<T,U>>();
    constructor_by_default_test< ft::map<T,U>>();

    constructor_by_copy_test<std::map<T,U>,std_value>();
    constructor_by_copy_test< ft::map<T,U>, ft_value>();

    constructor_by_iterator_range_test<std::map<T,U>,std_value>();
    constructor_by_iterator_range_test< ft::map<T,U>, ft_value>();
}

/****** Allocator test ********************************************************/

/// @todo
/// @note this allocator is not used at all in my map implementation
template <typename Map>
void get_allocator_test()
{
    /// @todo
    /// result may change whether we use:
    /// - ft::pair or std::pair
    /// - ft::add_const or std::add_const
    ///
    /// see. https://mapoverflow.com/a/40598287 about use of double brackets

    typedef typename Map::key_type      key_type;
    typedef typename Map::mapped_type   mapped_type;

    assert((Map().get_allocator() == std::allocator<std::pair<key_type,mapped_type>>()));

  //  assert((std::is_same<
  //              typename Map::allocator_type::value_type,
  //              typename std::allocator<std::pair<typename std::add_const<key_type>::type,mapped_type>>::value_type
  //          >::value));

    log("get_allocator()");
}

template <typename T, typename U>
void allocator_tests()
{
    get_allocator_test<std::map<T,U>>();
    get_allocator_test< ft::map<T,U>>();
}

/****** Capacity test *********************************************************/

template <typename Map>
void empty_test()
{
    Map m;
    {
        // by default
        assert(m.empty());
    }
    {
        // by copy
        assert(Map(m).empty());
    }
    {
        // by iterator range
        assert(Map(m.begin(), m.end()).empty());
    }
    log("empty()");
}

template <typename Map>
void size_test()
{
    Map m;

    // constructed by default
    assert(m.size() == 0);

    m.insert(typename Map::value_type());
    assert(m.size() == 1);

    // constructed by iterator copy
    assert(Map(m).size() == m.size());

    // constructed by iterator range
    assert(Map(m.begin(), m.end()).size() == m.size());

    log("size()");
}

/// @todo this test kinda broken
template <typename Map>
void max_size_test()
{
    log("max_size()");
}

template <typename T, typename U>
void capacity_tests()
{
    std::cout << "== Capacity ==" << std::endl;

    empty_test<std::map<T,U>>();
    empty_test< ft::map<T,U>>();

    size_test<std::map<T,U>>();
    size_test< ft::map<T,U>>();

//    max_size_test<std::map<T,U>>();
//    max_size_test< ft::map<T,U>>();
}

/****** Accessors test ********************************************************/

template <typename Map>
void operator_bracket_test()
{
    typedef typename Map::value_type    value;
    typedef typename Map::key_type      key;
    typedef typename Map::mapped_type   mapped;

    {
        // undefined behavior when map is empty (doesn't thow anything)
        Map()[0];
        Map()[9];
    }
    {
        Map m;
        m.insert(value(key(65), mapped(65)));
        m.insert(value(key(79), mapped(79)));
        m.insert(value(key(21), mapped(21)));
        m.insert(value(key(88), mapped(88)));

        assert(m[65] == 65);
        assert(m[79] == 79);
        assert(m[21] == 21);
        assert(m[88] == 88);

        m.insert(value(key(33), mapped(33)));
        m.insert(value(key(99), mapped(99)));
        m.insert(value(key(16), mapped(16)));

        assert(m[33] == 33);
        assert(m[99] == 99);
        assert(m[16] == 16);
    }
    log("operator[]");
}

template <typename T, typename U>
void accessors_tests()
{
    std::cout << "== Accessors ==" << std::endl;

    operator_bracket_test<std::map<T,U>>();
    operator_bracket_test< ft::map<T,U>>();
}

/****** Modifiers tests *******************************************************/

/// @todo add more tests. especially on return values and insert by range
/// @todo test duplicate nodes
template <typename Map>
void insert_test()
{
    // insert by value (1)
    {
        Map a, b;

        assert(a == b);

        /// @note not the same result if interverting two `==` operands as below
        //  assert(a.begin() == a.insert(typename Map::value_type()).first);
        //  assert(a.insert(typename Map::value_type()).first == a.begin());

        assert(a.insert(typename Map::value_type()).second == true);
        assert(a != b);

        assert(b.insert(typename Map::value_type()).second == true);
        assert(a == b);

        assert(a.insert(typename Map::value_type()).second == false);
        assert(b.insert(typename Map::value_type()).second == false);

        assert(a.insert(typename Map::value_type()).first == a.begin());
        assert(b.insert(typename Map::value_type()).first == b.begin());

        log("insert by value");
    }
    // insert by hint (2)
    {
        Map a, b;

        assert(a == b);

        /// @note may fail depending on compiler when interverting `==` operands
    //    assert(a.insert(a.begin(), typename Map::value_type()) == a.begin());
    //    assert(a != b);

        /// @note may fail depending on compiler when interverting `==` operands
    //    assert(b.insert(b.begin(), typename Map::value_type()) == b.begin());
    //    assert(a == b);

        /// @note doesn't fail depending on compiler since insert fails anyway
    //    assert(a.insert(a.begin(), typename Map::value_type()) == a.begin());
    //    assert(b.insert(b.begin(), typename Map::value_type()) == b.begin());

        log("insert by hint");
    }
    // insert by range (3)
    {
        Map a, b;
        assert(a == b);

        a.insert(a.begin(), a.end());
        assert(a == b);

        a.insert(typename Map::value_type());
        assert(a != b);

        b.insert(a.begin(), a.end());
        assert(a == b);

        log("insert by range");
    }
}

/// @todo add more tests. especially on return values and insert by range
template <typename Map>
void erase_test()
{
    {
        // by iterator position
        Map a, b;
        assert(a == b);
        a.insert(typename Map::value_type());
        assert(a != b);
        a.erase(a.begin());
        assert(a == b);
    }
    {
        // by key
        Map a, b;
        assert(a == b);
        a.insert(typename Map::value_type());
        assert(a != b);
        a.erase(typename Map::key_type());
        assert(a == b);
    }
    {
        // by iterator range
        Map a, b;
        assert(a == b);
        a.insert(typename Map::value_type());
        assert(a != b);
        a.erase(a.begin(), a.begin());
        assert(a != b);
        a.erase(a.begin(), a.end());
        assert(a == b);
    }
    log("erase()");
}

template <typename Map, typename Value>
void swap_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);
    Value l(4,4);

    {
        // test equality
        Map a, b;

        a.insert(i);
        a.insert(j);

        b.insert(j);
        b.insert(k);

        assert(a.size() == 2);
        assert(b.size() == 2);

        Map c(a);
        Map d(b);

        assert(c == a);
        assert(d == b);

        c.swap(d);

        assert(c == b);
        assert(d == a);
    }
    {
        // test iterators
        Map a, b;

        a.insert(i);
        b.insert(j);

        assert(*a.begin() == i);
        assert(*b.begin() == j);

        a.swap(b);

        assert(*a.begin() == j);
        assert(*b.begin() == i);

        a.insert(k);
        b.insert(l);

        a.swap(b);

        assert(*a.begin() == i);
        assert(*b.begin() == j);

        assert(*(++(a.begin())) == l);
        assert(*(++(b.begin())) == k);
    }
    log("swap()");
}

template <typename Map, typename Value>
void clear_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);
    Value l(4,4);

    {
        // empty map
        Map m;
        assert(m.size() == 0);
        m.clear();
        assert(m.size() == 0);
    }
    {
        // non-empty map
        Map m;

        m.insert(i);
        m.insert(j);
        m.insert(k);
        m.insert(l);

        assert(m.size() == 4);
        m.clear();
        assert(m.size() == 0);
    }
    log("clear()");
}

template <typename T, typename U>
void modifiers_tests()
{
    typedef typename std::map<T,U>::value_type std_value;
    typedef typename  ft::map<T,U>::value_type  ft_value;

    std::cout << "== Modifiers ==" << std::endl;

    insert_test<std::map<T,U>>();
    insert_test< ft::map<T,U>>();

    erase_test<std::map<T,U>>();
    erase_test< ft::map<T,U>>();

    swap_test<std::map<T,U>,std_value>();
    swap_test< ft::map<T,U>, ft_value>();

    clear_test<std::map<T,U>,std_value>();
    clear_test< ft::map<T,U>, ft_value>();
}

/****** Observers tests *******************************************************/

template <typename Map>
void key_comp_test()
{
    typedef typename Map::key_type key_type;
    typedef typename Map::key_compare key_compare;

    /// @todo (?) move to type tests
    assert((std::is_same<key_compare, std::less<key_type>>::value));

    key_type i(21);
    key_type j(42);

    assert(std::less<int>()(i,j));
    assert(Map().key_comp()(i,j));
    assert(key_compare()(i,j));

    log("key_comp()");
}

template <typename Map>
void value_comp_test()
{
    typedef typename Map::value_type value_type;
    typedef typename Map::value_compare::first_argument_type first;
    typedef typename Map::value_compare::second_argument_type second;
    typedef typename Map::value_compare::result_type result;

    /// @todo (?) move to type tests
    assert((std::is_same<result, bool>::value));
    assert((std::is_same<first,  value_type>::value));
    assert((std::is_same<second, value_type>::value));

    /// @note should not compile
    // typename Map::value_compare x;
    // typename Map().value_compare x;

    value_type i(21, 21);
    value_type j(21, 42);
    value_type k(42, 21);

    // same key
    assert(!Map().value_comp()(i,j));

    // different key
    assert(Map().value_comp()(i,k));

    log("value_comp()");
}

template <typename T, typename U>
void observers_tests()
{
    std::cout << "== Observers ==" << std::endl;

    key_comp_test<std::map<T,U>>();
    key_comp_test< ft::map<T,U>>();

    value_comp_test<std::map<T,U>>();
    value_comp_test< ft::map<T,U>>();
}

/****** Operations tests ******************************************************/

template <typename Map>
void find_test()
{
    typename Map::value_type k(42, 42);
    typename Map::value_type l(21, 21);

    // mutable
    {
        Map m;

        assert(m.find(k.first) == m.end());
        m.insert(k);
        assert(m.find(k.first) != m.end());

        assert(m.find(l.first) == m.end());
        m.insert(l);
        assert(m.find(l.first) != m.end());
    }

    // const
    {
        const Map m;

        assert(m.find(k.first) == m.end());
        assert(m.find(l.first) == m.end());
    }

    log("find()");
}

template <typename Map>
void count_test()
{
    Map m;

    typename Map::value_type k(42, 42);
    typename Map::value_type l(21, 21);

    assert(m.count(0)  == 0);
    assert(m.count(21) == 0);
    assert(m.count(42) == 0);

    m.insert(l);

    assert(m.count(0)  == 0);
    assert(m.count(21) == 1);
    assert(m.count(42) == 0);

    m.insert(k);

    assert(m.count(0)  == 0);
    assert(m.count(21) == 1);
    assert(m.count(42) == 1);

    m.insert(l);
    m.insert(l);
    m.insert(k);
    m.insert(k);

    assert(m.count(0)  == 0);
    assert(m.count(21) == 1);
    assert(m.count(42) == 1);

    log("count()");
}

template <typename Map>
void lower_bound_test()
{
    typename Map::value_type k(42, 42);
    typename Map::value_type l(21, 21);

    // mutable
    {
        Map m;

        assert(m.lower_bound(0)  == m.end());
        assert(m.lower_bound(21) == m.end());
        assert(m.lower_bound(42) == m.end());
        assert(m.lower_bound(55) == m.end());

        m.insert(l);

        assert(m.lower_bound(0)  == m.begin());
        assert(m.lower_bound(21) == m.begin());
        assert(m.lower_bound(42) == m.end());
        assert(m.lower_bound(55) == m.end());

        m.insert(k);

        assert(m.lower_bound(0)  == m.begin());
        assert(m.lower_bound(21) == m.begin());
        assert(m.lower_bound(42) == ++m.begin());
        assert(m.lower_bound(55) == m.end());
    }

    // mutable
    {
        Map m;

        Map const a(m);
        assert(a.lower_bound(0)  == a.end());
        assert(a.lower_bound(21) == a.end());
        assert(a.lower_bound(42) == a.end());
        assert(a.lower_bound(55) == a.end());

        m.insert(l);

        Map const b(m);
        assert(b.lower_bound(0)  == b.begin());
        assert(b.lower_bound(21) == b.begin());
        assert(b.lower_bound(42) == b.end());
        assert(b.lower_bound(55) == b.end());

        m.insert(k);

        Map const c(m);
        assert(c.lower_bound(0)  == c.begin());
        assert(c.lower_bound(21) == c.begin());
        assert(c.lower_bound(42) == ++c.begin());
        assert(c.lower_bound(55) == c.end());
    }

    log("lower_bound()");
}

template <typename Map>
void upper_bound_test()
{
    typename Map::value_type k(42, 42);
    typename Map::value_type l(21, 21);

    // mutable
    {
        Map m;

        assert(m.upper_bound(0)  == m.begin());
        assert(m.upper_bound(21) == m.begin());
        assert(m.upper_bound(42) == m.begin());
        assert(m.upper_bound(55) == m.begin());

        m.insert(l);

        assert(m.upper_bound(0)  == m.begin());
        assert(m.upper_bound(21) == m.end());
        assert(m.upper_bound(42) == m.end());
        assert(m.upper_bound(55) == m.end());

        m.insert(k);

        assert(m.upper_bound(0)  == m.begin());
        assert(m.upper_bound(21) == ++m.begin());
        assert(m.upper_bound(42) == m.end());
        assert(m.upper_bound(55) == m.end());
    }

    // const
    {
        Map m;

        Map const a(m);
        assert(a.upper_bound(0)  == a.begin());
        assert(a.upper_bound(21) == a.begin());
        assert(a.upper_bound(42) == a.begin());
        assert(a.upper_bound(55) == a.begin());

        m.insert(l);

        Map const b(m);
        assert(b.upper_bound(0)  == b.begin());
        assert(b.upper_bound(21) == b.end());
        assert(b.upper_bound(42) == b.end());
        assert(b.upper_bound(55) == b.end());

        m.insert(k);

        Map const c(m);
        assert(c.upper_bound(0)  == c.begin());
        assert(c.upper_bound(21) == ++c.begin());
        assert(c.upper_bound(42) == c.end());
        assert(c.upper_bound(55) == c.end());
    }

    log("upper_bound()");
}

/// @todo last `assert` fails for `ft` but not for `std`
template <typename Map, typename IteratorPair, typename ConstIteratorPair>
void equal_range_test()
{
    typename Map::value_type i(21, 21);
    typename Map::value_type j(42, 42);
    typename Map::value_type k(55, 55);

    // mutable
    {
        Map m;

        assert((m.equal_range(0) == IteratorPair(m.begin(),m.begin())));
        assert((m.equal_range(5) == IteratorPair(m.begin(),m.begin())));

        m.insert(i);

        assert((m.equal_range(0) == IteratorPair(m.begin(),m.begin())));
        assert((m.equal_range(5) == IteratorPair(m.begin(),m.begin())));
        assert((m.equal_range(21) == IteratorPair(m.begin(),m.end())));
        assert((m.equal_range(22) == IteratorPair(m.end(),m.end())));

        m.insert(j);
        m.insert(k);

        assert((m.equal_range(0) == IteratorPair(m.begin(),m.begin())));
        assert((m.equal_range(5) == IteratorPair(m.begin(),m.begin())));
        assert((m.equal_range(21) == IteratorPair(m.begin(),++m.begin())));
        assert((m.equal_range(22) == IteratorPair(++m.begin(),++m.begin())));
        assert((m.equal_range(42) == IteratorPair(++m.begin(),++(++m.begin()))));
        assert((m.equal_range(45) == IteratorPair(++(++m.begin()),++(++m.begin()))));
        assert((m.equal_range(55) == IteratorPair(++(++m.begin()),m.end())));
        //assert((m.equal_range(55) == IteratorPair(--m.end(),m.end())));
    }

    // const
    {
        Map m;

        Map const a(m);
        assert((a.equal_range(0) == ConstIteratorPair(a.begin(),a.begin())));
        assert((a.equal_range(5) == ConstIteratorPair(a.begin(),a.begin())));

        m.insert(i);

        Map const b(m);
        assert((b.equal_range(0) == ConstIteratorPair(b.begin(),b.begin())));
        assert((b.equal_range(5) == ConstIteratorPair(b.begin(),b.begin())));
        assert((b.equal_range(21) == ConstIteratorPair(b.begin(),b.end())));
        assert((b.equal_range(22) == ConstIteratorPair(b.end(),b.end())));

        m.insert(j);
        m.insert(k);

        Map const c(m);
        assert((c.equal_range(0) == ConstIteratorPair(c.begin(),c.begin())));
        assert((c.equal_range(5) == ConstIteratorPair(c.begin(),c.begin())));
        assert((c.equal_range(21) == ConstIteratorPair(c.begin(),++c.begin())));
        assert((c.equal_range(22) == ConstIteratorPair(++c.begin(),++c.begin())));
        assert((c.equal_range(42) == ConstIteratorPair(++c.begin(),++(++c.begin()))));
        assert((c.equal_range(45) == ConstIteratorPair(++(++c.begin()),++(++c.begin()))));
        assert((c.equal_range(55) == ConstIteratorPair(++(++c.begin()),c.end())));
        //assert((c.equal_range(55) == ConstIteratorPair(--c.end(),c.end())));
    }

    log("equal_range()");
}

template <typename T, typename U>
void operations_tests()
{
    std::cout << "== Operations ==" << std::endl;

    find_test<std::map<T,U>>();
    find_test< ft::map<T,U>>();

    count_test<std::map<T,U>>();
    count_test< ft::map<T,U>>();

    lower_bound_test<std::map<T,U>>();
    lower_bound_test< ft::map<T,U>>();

    upper_bound_test<std::map<T,U>>();
    upper_bound_test< ft::map<T,U>>();

    typedef typename std::map<T,U>::iterator std_iterator;
    typedef typename  ft::map<T,U>::iterator  ft_iterator;
    typedef typename std::map<T,U>::const_iterator std_const_iterator;
    typedef typename  ft::map<T,U>::const_iterator  ft_const_iterator;

    equal_range_test<std::map<T,U>, std::pair<std_iterator,std_iterator>,
                     std::pair<std_const_iterator,std_const_iterator>>();

    equal_range_test<ft::map<T,U>, ft::pair<ft_iterator,ft_iterator>,
                     ft::pair<ft_const_iterator,ft_const_iterator>>();
}

/****** Operators tests *******************************************************/

template <typename Map, typename Value>
void assignation_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);

    {
        // same size
        Map a, b;

        a.insert(i);
        b.insert(j);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // upper size
        Map a, b;

        b.insert(i);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // lower size
        Map a, b;

        a.insert(i);
        a.insert(j);
        b.insert(k);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // assign from empty
        Map a, b;

        a.insert(i);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    {
        // assign to empty
        Map a, b;

        b.insert(i);

        assert(a != b);
        a = b;
        assert(a == b);
    }
    log("operator=");
}

template <typename Map, typename Value>
void equal_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);

    Map a, b;
    assert(a == b);

    a.insert(i);
    assert(!(a == b));

    b.insert(i);
    assert(a == b);

    a.insert(k);
    assert(!(a == b));

    b.insert(k);
    assert(a == b);

    a.insert(j);
    assert(!(a == b));

    b.insert(j);
    assert(a == b);

    // insert duplicate pair (don't insert)
    b.insert(i);
    assert(a == b);

    // insert duplicate pair (don't insert)
    a.insert(k);
    assert(a == b);

    // insert duplicate key (don't insert)
    a.insert(Value(1,42));
    assert(a == b);

    // insert duplicate mapped (do insert)
    a.insert(Value(9,2));
    assert(!(a == b));

    log("operator==");
}

template <typename Map, typename Value>
void not_equal_test()
{
    Value i(1,1);
    Value j(2,2);
    Value k(3,3);

    Map a, b;
    assert(!(a != b));

    a.insert(i);
    assert(a != b);

    b.insert(i);
    assert(!(a != b));

    a.insert(k);
    assert(a != b);

    b.insert(k);
    assert(!(a != b));

    a.insert(j);
    assert(a != b);

    b.insert(j);
    assert(!(a != b));

    // insert duplicate pair (don't insert)
    b.insert(i);
    assert(!(a != b));

    // insert duplicate pair (don't insert)
    a.insert(k);
    assert(!(a != b));

    // insert duplicate key (don't insert)
    a.insert(Value(1,42));
    assert(!(a != b));

    // insert duplicate mapped (do insert)
    a.insert(Value(42,1));
    assert(a != b);

    log("operator!=");
}

template <typename Map, typename Value>
void less_than_test()
{
    Map a, b;

    // empty maps
    assert(!(a < b));
    assert(!(b < a));

    // different size
    a.insert(Value(1, 1));
    assert(b < a);
    assert(!(a < b));

    // same size, same values
    b.insert(Value(1, 1));
    assert(!(b < a));
    assert(!(a < b));

    // same size, different key values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(2, 42));
        d.insert(Value(3, 42));
        assert(c < d);
        assert(!(d < c));
    }

    // same size, different mapped values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(4, 21));
        d.insert(Value(4, 42));
        assert(c < d);
        assert(!(d < c));
    }

    log("operator<");
}

template <typename Map, typename Value>
void greater_than_test()
{
    Map a, b;

    // empty maps
    assert(!(a > b));
    assert(!(b > a));

    // different size
    a.insert(Value(1, 1));
    assert(a > b);
    assert(!(b > a));

    // same size, same values
    b.insert(Value(1, 1));
    assert(!(a > b));
    assert(!(b > a));

    // same size, different key values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(2, 42));
        d.insert(Value(3, 42));
        assert(d > c);
        assert(!(c > d));
    }

    // same size, different mapped values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(4, 21));
        d.insert(Value(4, 42));
        assert(d > c);
        assert(!(c > d));
    }

    log("operator>");
}

template <typename Map, typename Value>
void less_than_equal_test()
{
    Map a, b;

    // empty maps
    assert(a <= b);
    assert(b <= a);

    // different size
    a.insert(Value(1, 1));
    assert(b <= a);
    assert(!(a <= b));

    // same size, same values
    b.insert(Value(1, 1));
    assert(b <= a);
    assert(a <= b);

    // same size, different key values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(2, 42));
        d.insert(Value(3, 42));
        assert(c <= d);
        assert(!(d <= c));
    }

    // same size, different mapped values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(4, 21));
        d.insert(Value(4, 42));
        assert(c <= d);
        assert(!(d <= c));
    }

    log("operator<=");
}

template <typename Map, typename Value>
void greater_than_equal_test()
{
    Map a, b;

    // empty maps
    assert(a >= b);
    assert(b >= a);

    // different size
    a.insert(Value(1, 1));
    assert(a >= b);
    assert(!(b >= a));

    // same size, same values
    b.insert(Value(1, 1));
    assert(a >= b);
    assert(b >= a);

    // same size, different key values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(2, 42));
        d.insert(Value(3, 42));
        assert(d >= c);
        assert(!(c >= d));
    }

    // same size, different mapped values
    {
        Map c(a);
        Map d(a);
        c.insert(Value(4, 21));
        d.insert(Value(4, 42));
        assert(d >= c);
        assert(!(c >= d));
    }

    log("operator>=");
}

template <typename T, typename U>
void operators_tests()
{
    typedef typename std::map<T,U>::value_type std_value;
    typedef typename  ft::map<T,U>::value_type  ft_value;

    std::cout << "== Operators ==" << std::endl;

    assignation_test<std::map<T,U>,std_value>();
    assignation_test< ft::map<T,U>, ft_value>();

    equal_test<std::map<T,U>,std_value>();
    equal_test< ft::map<T,U>, ft_value>();

    not_equal_test<std::map<T,U>,std_value>();
    not_equal_test< ft::map<T,U>, ft_value>();

    less_than_test<std::map<T,U>,std_value>();
    less_than_test< ft::map<T,U>, ft_value>();

    greater_than_test<std::map<T,U>,std_value>();
    greater_than_test< ft::map<T,U>, ft_value>();

    less_than_equal_test<std::map<T,U>,std_value>();
    less_than_equal_test< ft::map<T,U>, ft_value>();

    greater_than_equal_test<std::map<T,U>,std_value>();
    greater_than_equal_test< ft::map<T,U>, ft_value>();
}

/****** Iterators tests *******************************************************/

template <typename Map>
void begin_test()
{
    typedef typename Map::iterator          iterator;
    typedef typename Map::const_iterator    const_iterator;

    typename Map::value_type p(21,42);
    {
        // iterator from mutable map
        Map m; m.insert(p);
        iterator it = m.begin();
        assert(*it == p);
        it++;
    }
    {
        // const_iterator from mutable map
        Map m; m.insert(p);
        const_iterator it = m.begin();
        assert(*it == p);
        it++;
    }
    {
        // iterator from const map -- sould not compile
        // Map m; m.insert(p); const Map n(m);
        // iterator it = n.begin();
        // assert(*it == p);
        // (void)it;
    }
    {
        // const_iterator from const map
        Map m; m.insert(p); const Map n(m);
        const_iterator it = n.begin();
        assert(*it == p);
        it++;
    }
    log("begin");
}

template <typename Map>
void end_test()
{
    typedef typename Map::iterator          iterator;
    typedef typename Map::const_iterator    const_iterator;

    typename Map::value_type p(21,42);
    {
        // iterator from mutable map
        Map m; m.insert(p);
        iterator it = m.end();
        it--;
        assert(*it == p);
    }
    {
        // const_iterator from mutable map
        Map m; m.insert(p);
        const_iterator it = m.end();
        it--;
        assert(*it == p);
    }
    {
        // iterator from const map -- should not compile
        // Map m; m.insert(p); Map n(m);
        // iterator it = n.end();
        // assert(*it == p);
        // (void)it;
    }
    {
        // const_iterator from const map
        Map m; m.insert(p); const Map n(m);
        const_iterator it = n.end();
        it--;
        assert(*it == p);
    }
    log("end");
}

template <typename Map>
void rbegin_test()
{
    typedef typename Map::reverse_iterator          reverse_iterator;
    typedef typename Map::const_reverse_iterator    const_reverse_iterator;

    typename Map::value_type p(21,42);
    {
        // reverse_iterator from mutable map
        Map m; m.insert(p);
        reverse_iterator it = m.rbegin();
        assert(it.base() == m.end());
        it++;
        assert(it.base() == m.begin());
    }
    {
        // const_reverse_iterator from mutable map
        Map m; m.insert(p);
        const_reverse_iterator it = m.rbegin();
        assert(it.base() == m.end());
        it++;
        assert(it.base() == m.begin());
    }
    {
        // reverse_iterator from const map -- should not compile
    //    Map m; m.insert(p); const Map n(m);
    //    reverse_iterator it = n.rbegin();
    //    assert(it.base() == n.end());
    //    it++;
    //    assert(it.base() == m.begin());
    }
    {
        // const_reverse_iterator from const map
        Map m; m.insert(p); const Map n(m);
        const_reverse_iterator it = n.rbegin();
        assert(it.base() == n.end());
        it++;
        assert(it.base() == n.begin());
    }
    log("rbegin");
}

template <typename Map>
void rend_test()
{
    typedef typename Map::reverse_iterator          reverse_iterator;
    typedef typename Map::const_reverse_iterator    const_reverse_iterator;

    typename Map::value_type p(21,42);
    {
        // reverse_iterator from mutable map
        Map m; m.insert(p);
        reverse_iterator it = m.rend();
        assert(it.base() == m.begin());
        it++;
        assert(*it == p);
    }
    {
        // const_reverse_iterator from mutable map
        Map m; m.insert(p);
        const_reverse_iterator it = m.rend();
        assert(it.base() == m.begin());
        it++;
        assert(*it == p);
    }
    {
        // reverse_iterator from const map -- should not compile
    //    Map m; m.insert(p); const Map n(m);
    //    reverse_iterator it = n.rend();
    //    assert(it.base() == n.begin());
    //    it++;
    //    assert(*it == p);
    }
    {
        // const_reverse_iterator from const map
        Map m; m.insert(p); const Map n(m);
        const_reverse_iterator it = n.rend();
        assert(it.base() == n.begin());
        it++;
        assert(*it == p);
    }
    log("rend");
}

template <typename T, typename U>
void iterators_tests()
{
    std::cout << "== Iterators ==" << std::endl;

    begin_test<std::map<T,U>>();
    begin_test< ft::map<T,U>>();

    end_test<std::map<T,U>>();
    end_test< ft::map<T,U>>();

    rbegin_test<std::map<T,U>>();
    rbegin_test< ft::map<T,U>>();

    rend_test<std::map<T,U>>();
    rend_test< ft::map<T,U>>();

    iterator_test<std::map<T,U>>();
    iterator_test< ft::map<T,U>>();
}

/****** Map tests *************************************************************/

/// @note test exceptions like we did for vector
template <typename T, typename U>
void map_test()
{
    constructors_tests<T,U>();
    allocator_tests<T,U>();
    observers_tests<T,U>();
    capacity_tests<T,U>();
    accessors_tests<T,U>();
    modifiers_tests<T,U>();
    operations_tests<T,U>();
    operators_tests<T,U>();
    iterators_tests<T,U>();
}

/****** All tests *************************************************************/

int main()
{
    /// @note some tests about max_size. this is a shitty place.
    /*
    {
        std::cout << sizeof(std::pair<int,char>) << std::endl;
        std::cout << sizeof(typename std::map<int,char>::value_type) << std::endl;

        std::map<int,char> m;
        std::cout << m.max_size() << std::endl;
        std::cout << m.get_allocator().max_size() << std::endl;
        std::cout << std::numeric_limits<typename std::map<int,char>::difference_type>::max() << std::endl;
    }
    {
        std::cout << sizeof(ft::pair<int,char>) << std::endl;
        std::cout << sizeof(typename ft::map<int,char>::value_type) << std::endl;

        ft::map<int,char> m;
        std::cout << m.max_size() << std::endl;
        std::cout << m.get_allocator().max_size() << std::endl;
        std::cout << std::numeric_limits<typename ft::map<int,char>::difference_type>::max() << std::endl;
    }
    */

    map_test<int, char>();
//  map_test<double, char>();
//  map_test<A, B>();

    return 0;
}