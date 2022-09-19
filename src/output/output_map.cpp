#include <map>
#include <memory> // std::allocator
#include <cassert>
#include <utility> // std::pair
#include <iostream> // put into log
#include <type_traits> // std::is_same std::is_const (c++11)

#include "ft_map.hpp"
#include "output_iterator.hpp"
#include "../utils/colors.hpp" // put into log

/// @todo for all tests, find a way to work with different instanciations of
///       value_types. useful for insert, erase, and some others. (knowing that
///       this is a templated type...)

/// @todo delete
template <typename T1, typename T2>
void compare_maps(const ft::map<T1,T2> & a, const std::map<T1,T2> & b)
{
    assert(a.empty() == b.empty());
    assert(a.size() == b.size());
    //assert(a.max_size() == b.max_size());
   // assert(typeid(a.key_comp()).name() == typeid(b.key_comp()).name());
   // assert(typeid(a.value_comp()).name() == typeid(b.value_comp()).name());


    /****** Compare ***********************************************************/

    // verify default type of key_compare with std::map
    assert((std::is_same<std::less<int>, std::map<int,char>::key_compare>::value));
    assert((std::is_same<std::less<char>,std::map<char,int>::key_compare>::value));

    // compare default type of key_compare
    assert((std::is_same<std::less<int>, ft::map<int,char>::key_compare>::value));
    assert((std::is_same<std::less<char>,ft::map<char,int>::key_compare>::value));

    // default Compare type
    assert((typeid(std::map<int,int>().key_comp()).name() == typeid(ft::map<int,int>().key_comp()).name()));
    assert((typeid(std::map<char,int>().key_comp()).name() == typeid(ft::map<char,int>().key_comp()).name()));
    assert((typeid(std::map<const char,int>().key_comp()).name() == typeid(ft::map<const char,int>().key_comp()).name()));

    // custom Compare type
    assert((typeid(ft::map<int,int,std::less<char>>().key_comp()).name() == typeid(std::less<char>).name()));
    assert((typeid(ft::map<int,int,std::less<char>>().key_comp()).name() == typeid(std::map<char,int>().key_comp()).name()));
}

/****** Log *******************************************************************/

/// @todo remove
inline void log(std::string s)
{
    std::cout << s << GREEN << " OK" << RESET << std::endl;
}

/****** Constructors test *****************************************************/

/// @todo test max_size()
template <typename Map>
void constructor_by_default_test()
{
    {
        // mutable map
        Map a;
        assert(a.empty());
        assert(a.size() == 0);
        //assert(a.max_size() == 0);
    }
    {
        // const map
        Map const a;
        assert(a.empty());
        assert(a.size() == 0);
        //assert(a.max_size() == 0);
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

/// @todo add test cases for const iterators and const maps
template <typename Map>
void constructor_by_iterator_range_test()
{
    {
        // empty range
        Map a;
        Map b(a.begin(), a.end());

        assert(a == b);
    }
    {
        // non-empty range
        Map a;
        a.insert(typename Map::value_type());
        Map b(a.begin(), a.end());

        assert(a == b);
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

    constructor_by_iterator_range_test<std::map<T,U>>();
    constructor_by_iterator_range_test< ft::map<T,U>>();
}

/****** Allocator test ********************************************************/

/// @todo
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

/// @todo
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

/// @todo
template <typename Map>
void operator_bracket_test()
{
    typedef typename Map::value_type    value;
    typedef typename Map::key_type      key;
    typedef typename Map::mapped_type   mapped;

    {
        // undefined behavior when map is empty
        // assert(Map().back() == 0);
    }
    {
        Map m;
        m.insert(value(key(65), mapped(65)));
    //    m.insert(value(key(79), mapped(79)));
    //    m.insert(value(key(21), mapped(21)));
    //    m.insert(value(key(88), mapped(88)));
    //    m.insert(value(key(16), mapped(16)));

        //assert(m[65] == 65);
        std::cout << m[65] << std::endl;
    }
//    {
//        Map v(10, 42);
//        for (typename Map::size_type i = 0; i < 10; i++)
//            assert(m[i] == 42);
//    }
//    {
//        // doesn't thow anything
//        Map(10)[10];
//    }
//    {
//        const Map m(10);
//        typename Map::value_type i = typename Map::value_type();
//        for (typename Map::size_type j = 0; j < 10; j++)
//            assert(m[j] == i);
//    }
//    {
//        const Map m(10, 42);
//        for (typename Map::size_type i = 0; i < 10; i++)
//            assert(m[i] == 42);
//    }
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
    //typedef typename Map::value_type value_type;
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

        /// @note not the same result when interverting the two `==` operands
        assert(a.begin() == a.insert(a.begin(), typename Map::value_type()));
        assert(a != b);

        assert(b.begin() == b.insert(b.begin(), typename Map::value_type()));
        assert(a == b);

        assert(a.insert(a.begin(), typename Map::value_type()) == a.begin());
        assert(b.insert(b.begin(), typename Map::value_type()) == b.begin());

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

/// @todo
template <typename Map>
void key_comp_test()
{
//    // move to type tests
//    assert((std::is_same<
//        typename Map::key_compare,
//        std::less<typename Map::key_type>
//    >::value));

//    assert((Map().key_comp() == std::less<typename Map::key_type>));

    log("key_comp()");
}

/// @todo
template <typename Map>
void value_comp_test()
{
    log("value_comp()");
}

/// @todo
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

    Map m;

    assert(m.find(k.first) == m.end());
    m.insert(k);
    assert(m.find(k.first) != m.end());

    assert(m.find(l.first) == m.end());
    m.insert(l);
    assert(m.find(l.first) != m.end());

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
    Map m;

    typename Map::value_type k(42, 42);
    typename Map::value_type l(21, 21);

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

    log("lower_bound()");
}

template <typename Map>
void upper_bound_test()
{
    Map m;

    typename Map::value_type k(42, 42);
    typename Map::value_type l(21, 21);

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

    log("upper_bound()");
}

/// @todo
template <typename Map, typename IteratorPair>
void equal_range_test()
{
    Map m;

    typename Map::value_type i(21, 21);
    typename Map::value_type j(42, 42);
    typename Map::value_type k(55, 55);
    typename Map::value_type l(88, 88); // delete ?

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

    log("equal_range()");
}

/// @todo test const version of each method (but how...)
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

    equal_range_test<std::map<T,U>,std::pair<std_iterator,std_iterator>>();
    equal_range_test< ft::map<T,U>, ft::pair< ft_iterator, ft_iterator>>();
}

/****** Operators tests *******************************************************/

/// @todo move those typedefs and types instanciations outide to be available by
///       any test function
/// @pre map `key_type` and `mapped_type` are constructible by integers
template <typename Map>
void assignation_test()
{
    typedef typename Map::key_type      key;
    typedef typename Map::mapped_type   mapped;
    typedef typename Map::value_type    value;

    value i(key(1), mapped(1));
    value j(key(2), mapped(2));
    value k(key(3), mapped(3));

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
    std::cout << "operator= " << GREEN << "OK" << RESET << std::endl;
}

/// @todo
template <typename Map>
void equal_test()
{
    // empty map
    //{ assert(Map() == Map()); }

    {
        // non-empty with default values
        Map a, b;

        a.insert(typename Map::value_type());
        b.insert(typename Map::value_type());

//        assert(a == b);
    }

    // non-empty with specified values
//    { assert(Map(10, 21) == Map(10, 21)); }

    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

/// @todo
template <typename T, typename U>
void operators_tests()
{
    std::cout << "== Operators ==" << std::endl;

//    assignation_test<std::map<T,U>>();
//    assignation_test< ft::map<T,U>>();

    equal_test<std::map<T,U>>();
    equal_test< ft::map<T,U>>();

//    not_equal_test<std::map<T,U>>();
//    not_equal_test< ft::map<T,U>>();

//    less_than_test<std::map<T,U>>();
//    less_than_test< ft::map<T,U>>();

//    greater_than_test<std::map<T,U>>();
//    greater_than_test< ft::map<T,U>>();

//    less_than_equal_test<std::map<T,U>>();
//    less_than_equal_test< ft::map<T,U>>();

//    greater_than_equal_test<std::map<T,U>>();
//    greater_than_equal_test< ft::map<T,U>>();
}

/****** Iterators tests *******************************************************/

void begin_test()
{
    /// @note we use pair of `int` but it has no importance
    ft::pair<const int,int> p(21,42);

    {
        // iterator from mutable map
        ft::map<int,int> m;
        m.insert(p);
        ft::map<int,int>::iterator it = m.begin();
        assert(*it == p);
        it++;
    }
    {
        // const_iterator from mutable map
        ft::map<int,int> m;
        m.insert(p);
        ft::map<int,int>::const_iterator it = m.begin();
        assert(*it == p);
        it++;
    }
    {
        // iterator from const map -- sould not compile
    //    ft::map<int,int> m;
    //    m.insert(p);
    //    const ft::map<int,int> n(m);
    //    ft::map<int,int>::iterator it = n.begin();
    //    assert(*it == p);
    //    (void)it;
    }
    {
        // const_iterator from const map
        ft::map<int,int> m;
        m.insert(p);
        const ft::map<int,int> n(m);
        ft::map<int,int>::const_iterator it = n.begin();
        assert(*it == p);
        it++;
    }
    log("begin");
}

void end_test()
{
    /// @note we use pair of `int` but it has no importance
    ft::pair<const int,int> p(21,42);

    {
        // iterator from mutable map
        ft::map<int,int> m;
        m.insert(p);
        ft::map<int,int>::iterator it = m.end();
        it--;
        assert(*it == p);
    }
    {
        // const_iterator from mutable map
        ft::map<int,int> m;
        m.insert(p);
        ft::map<int,int>::const_iterator it = m.end();
        it--;
        assert(*it == p);
    }
    {
        // iterator from const map -- should not compile
    //    ft::map<int,int> m;
    //    m.insert(p);
    //    const ft::map<int,int> n(m);
    //    ft::map<int,int>::iterator it = n.end();
    //    assert(*it == p);
    //    (void)it;
    }
    {
        // const_iterator from const map
        ft::map<int,int> m;
        m.insert(p);
        const ft::map<int,int> n(m);
        ft::map<int,int>::const_iterator it = n.end();
        it--;
        assert(*it == p);
    }
    log("end");
}

/*
void rbegin_test()
{
    /// @note we use pair of `int` but it has no importance
    ft::pair<const int,int> p(21,42);

    {
        // reverse_iterator from mutable map
        ft::map<int,int> m;
        m.insert(p);
        ft::map<int,int>::reverse_iterator it = m.rbegin();
        assert(it.base() == m.end());
        //it++;
        assert(*it == p);
    }
//    {
//        // const_reverse_iterator from mutable map
//        ft::vector<int> v(10, 21);
//        ft::vector<int>::const_reverse_iterator it = v.rbegin();
//        assert(it.base() == v.end());
//        it++;
//        assert(*it == 21);
//    }
//    {
//        // reverse_iterator from const map -- should not compile
//     //   const ft::vector<int> v(10, 21);
//     //   ft::vector<int>::reverse_iterator it = v.rbegin();
//     //   assert(it.base() == v.end());
//     //   it++;
//     //   assert(*it == 21);
//    }
//    {
//        // const_reverse_iterator from const map
//        const ft::vector<int> v(10, 21);
//        ft::vector<int>::const_reverse_iterator it = v.rbegin();
//        assert(it.base() == v.end());
//        it++;
//        assert(*it == 21);
//    }
    log("rbegin");
}
*/

void rend_test()
{
    log("rend");
}

/// @todo (?) move to iterator test suite
void iterators_tests()
{
    std::cout << "== Iterators ==" << std::endl;

//    begin_test();
//    end_test();

//    rbegin_test();
//    rend_test();
}

/****** Map tests *************************************************************/

template <typename T, typename U>
void map_test()
{
   // constructors_tests<T,U>();
   // allocator_tests<T,U>();
   // observers_tests<T,U>();
   // capacity_tests<T,U>();
   // accessors_tests<T,U>();
   // modifiers_tests<T,U>();
   // operations_tests<T,U>();
//   iterators_tests();

    iterator_test<std::map<T,U>>();
//    iterator_test< ft::map<T,U>>();

//    operators_tests<T,U>();
}

/****** All tests *************************************************************/

int main()
{
    map_test<int, char>();
//  map_test<double, char>();
//  map_test<A, B>();

    {
    //    ft::map<int,int>::iterator a;
    //    ft::map<int,int>::iterator b;
    //    ft::map<int,int>::const_iterator c;
    //    assert(a == b);
    //    assert(a == c);
    //    assert(c == a);
    //
    //    ft::map<int,int> m;
    //    ft::pair<const int,int> p(4,2);
    //    m.insert(p);
    }

/*
    {
        std::cout << typeid(ft::map<int,int>::pointer).name() << std::endl;
        std::cout << typeid(ft::map<int,int>::iterator::pointer).name() << std::endl;
        std::cout << typeid(ft::map<int,int>::const_iterator::pointer).name() << std::endl;
    }
    {
        ft::map<int,int> m;
        ft::map<int,int>::const_iterator it = m.begin();
        ft::map<int,int>::const_iterator it(m.begin());
    }
    {
        ft::map<int,int>::iterator a;
        ft::map<int,int>::const_iterator b;
        ft::map<int,int>::iterator c;
        ft::map<int,int>::const_iterator d;

        c = a;
        b = d;
        //a = b; // should not compile
        b = a;
    }
    {
        ft::pair<int,int> a;
        ft::pair<int,int> * p = &a;
        const ft::pair<int,int> b;
        p = &b;
    }
    {
        std::pair<int,int> a;
        std::pair<int,int> * p = &a;
        const std::pair<int,int> b;
        p = &b;
    }
*/

    return 0;
}
