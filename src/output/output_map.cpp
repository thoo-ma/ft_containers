#include <map>
#include <memory> // std::allocator
#include <cassert>
#include <utility> // std::pair
#include <iostream> // put into log
#include <type_traits> // std::is_same std::is_const (c++11)

#include "ft_map.hpp"
//#include "output_iterator.hpp"
#include "../utils/colors.hpp" // put into log

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

// remove
inline void log(std::string s)
{
    std::cout << s << GREEN << " OK" << RESET << std::endl;
}

/****** Constructors test *****************************************************/

template <typename Map>
void constructor_by_default_test()
{
    Map a;

    assert(a.empty());
    assert(a.size() == 0);
    //assert(a.mzx_size() == 0); // TODO

    log("constructor by default");
}

/// @todo
template <typename Map>
void constructor_by_copy_test()
{
    {
        // from empty
        Map a;
        Map b(a);

        assert(a == b);
    }
    {
        // from non-empty
        Map a; a.insert(typename Map::value_type(21, 42));
        Map b(a);

        assert(a == b);
    }
    log("constructor by copy");
}

/// @todo
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
    //    Map a(10, typename Map::value_type());
    //    Map b(a.begin(), a.end());

    //    assert(a == b);
    }
    log("constructor by iterator range");
}

/// @todo
template <typename T, typename U>
void constructors_tests()
{
    constructor_by_default_test<std::map<T,U>>();
    constructor_by_default_test< ft::map<T,U>>();

    constructor_by_copy_test<std::map<T,U>>();
    constructor_by_copy_test< ft::map<T,U>>();

//    constructor_by_iterator_range_test<std::map<T,U>>();
//    constructor_by_iterator_range_test< ft::map<T,U>>();
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

/// @todo add iterator range test
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
//        assert(Map(m.begin(), m.end()).empty());
    }
    log("empty()");
}

/// @todo add iterator range test
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
//    assert(Map(m.begin(), m.end()).size() == m.size());

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

// TODO
template <typename Map>
void insert_test()
{
    // insert by value (1)
    {
//        Map a, b;
//
//        assert(a == b);

//        /// @note not the same result if interverting two `==` operands as below
//        //  assert(a.begin() == a.insert(typename Map::value_type()).first);
//        //  assert(a.insert(typename Map::value_type()).first == a.begin());
//
//        assert(a.insert(typename Map::value_type()).second == true);
//        assert(a != b);
//
//        assert(b.insert(typename Map::value_type()).second == true);
//        assert(a == b);
//
//        assert(a.insert(typename Map::value_type()).first == a.begin());
//        assert(b.insert(typename Map::value_type()).first == b.begin());
//
//        assert(a.insert(typename Map::value_type()).second == false);
//        assert(b.insert(typename Map::value_type()).second == false);

//        log("insert by value");
    }
    // insert by hint (2)
    {
        //log("insert by hint");
    }
    // insert by range (3)
    {
        //log("insert by range");
    }
}

// TODO
template <typename Map>
void erase_test()
{
    log("erase()");
}

// TODO
template <typename Map>
void swap_test()
{
    log("swap()");
}

// TODO
template <typename Map>
void clear_test()
{
    log("clear()");
}

// TODO
template <typename T, typename U>
void modifiers_tests()
{
    std::cout << "== Modifiers ==" << std::endl;

    insert_test<std::map<T,U>>();
    insert_test< ft::map<T,U>>();

 //   erase_test<std::map<T,U>>();
 //   erase_test< ft::map<T,U>>();

 //   swap_test<std::map<T,U>>();
 //   swap_test< ft::map<T,U>>();

 //   clear_test<std::map<T,U>>();
 //   clear_test< ft::map<T,U>>();
}

/****** Observers tests *******************************************************/

// TODO
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

// TODO
template <typename Map>
void value_comp_test()
{
    log("value_comp()");
}

// TODO
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

// TODO
template <typename Map>
void find_test()
{
    log("find()");
}

// TODO
template <typename Map>
void count_test()
{
    log("count()");
}

// TODO
template <typename Map>
void lower_bound_test()
{
    log("lower_bound()");
}

// TODO
template <typename Map>
void upper_bound_test()
{
    log("upper_bound()");
}

// TODO
template <typename Map>
void equal_range_test()
{
    log("equal_range()");
}

// TODO
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

    equal_range_test<std::map<T,U>>();
    equal_range_test< ft::map<T,U>>();
}

/****** Operators tests *******************************************************/

/// @todo
template <typename Map>
void equal_test()
{
    // empty map
    { assert(Map() == Map()); }

    // non-empty with default values
//    { assert(Map(10) == Map(10)); }

    // non-empty with specified values
//    { assert(Map(10, 21) == Map(10, 21)); }

    std::cout << "operator== " << GREEN << "OK" << RESET << std::endl;
}

template <typename T, typename U>
void operators_tests()
{
    std::cout << "== Operators ==" << std::endl;

//    equal_test<std::map<T,U>>();
//    equal_test< ft::map<T,U>>();

//    not_equal_test<std::map<T,U>>();
//    not_equal_test< ft::map<T,U>>();

//    assignation_test<std::map<T,U>>();
//    assignation_test< ft::map<T,U>>();

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

template <typename Map>
void iterator_assignation_test()
{
    //typedef typename Map::value_type    Pair;
    {
        // it = it
        typename Map::value_type pair(10,42);
        typename Map::value_type * p = &pair;

       // Pair pair(10,42);
       // Pair * ptr = &pair;

        typename Map::iterator       a;
        typename Map::const_iterator b(p);

    //    assert(a != b);
    //    a = b;
    //    assert(a == b);

    //    int i = 42;
    //    int * p = &i;
    //    ft::vector<int>::iterator a;
    //    ft::vector<int>::iterator b(p);
    //    assert(a != b);
    //    a = b;
    //    assert(a == b);
    }
    {
        // const_it = const_it
    }
    {
        // const_it = it
    }
    {
        // it = const_it -- should not compile
    }
    {
        // rev_it = it -- should not compile
    }
    {
        // rev_it = const_it -- should not compile
    }
    {
        // rev_it = rev_it
    }
    {
        // rev_it = const_rev_it -- should not compile
    }
    {
        // const_rev_it = it -- should not compile
    }
    {
        // const_rev_it = const_it -- should not compile
    }
    {
        // const_rev_it = rev_it
    }
    {
        // const_rev_it = const_rev_it
    }
    log("assignation");
}

template <typename Map>
void begin_test()
{
    typedef typename Map::value_type    Pair;

    if (!std::is_const<Map>::value)
    {
        {
            // iterator from mutable map
            Map m;
            Pair p(10,21);

            m.insert(p);

            typename Map::iterator it1 = m.begin();
            assert(*it1 == p);

       //     m.insert(5);

       //     typename Map::iterator it2 = m.begin();
       //     assert(*it2 == 21);

            //it++;
        }
        {
            // const_iterator from mutable map
            Map m;
            Pair p(10,21);

            m.insert(p);

            //typename Map::const_iterator it1;
          //  typename Map::const_iterator it1 = m.begin();
          //  assert(*it1 == p);
            //it++;
        }
    }
    else
    {
        // iterator from const map -- sould not compile
        // const_iterator from const map
    }

    /*
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
    */
    log("begin()");
}

template <typename Map>
void end_test()
{
    log("end()");
}

template <typename T, typename U>
void iterator_tests()
{
    std::cout << "== Iterators ==" << std::endl;

    iterator_assignation_test<std::map<T,U>>();
    //iterator_assignation_test< ft::map<T,U>>();

    //begin_test<std::map<T,U>>();
    //begin_test< ft::map<T,U>>();

 //   begin_test<const std::map<T,U>>();
 //   begin_test<const  ft::map<T,U>>();

//    end_test<std::map<T,U>>();
//    end_test< ft::map<T,U>>();
}

/****** Map tests *************************************************************/

template <typename T, typename U>
void map_test()
{
   // constructors_tests<T,U>();
   // allocator_tests<T,U>();
   // observers_tests<T,U>();
   // capacity_tests<T,U>();
    accessors_tests<T,U>();
   // modifiers_tests<T,U>();
   // operations_tests<T,U>(); // TODO

//    iterator_test<std::map<T,U>>();
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
