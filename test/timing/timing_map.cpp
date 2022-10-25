#include <map>
#include <chrono>
#include <fstream>

#include "ft_map.hpp"
#include "utils.hpp"

/// @todo `clear()` test leak sometimes
/// @todo (?) test all overloads (insert, erase, etc.)

using namespace std::chrono;

/****** Allocator *************************************************************/

template <typename Map>
double get_timing_map_get_allocator()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000; i++)
        (void)m.get_allocator();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_allocator(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    ft_chrono  = get_timing_map_get_allocator< ft::map<T,U>>();
    std_chrono = get_timing_map_get_allocator<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,get_allocator");
}

/****** Constructors **********************************************************/

template <typename Map>
double get_timing_map_constructor_by_default()
{
    // data we will operate on
    Map * arr[100000];

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++)
        arr[i] = new Map();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 100000; i++)
        delete arr[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_constructor_by_copy()
{
    // data we will operate on
    Map * arr1[1000]; Map m1; random_map<Map>(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000; i++)
        arr1[i] = new Map(m1);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete
    for (int i = 0; i < 1000; i++)
        delete arr1[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_constructor_by_range()
{
    // data we will operate on
    Map * m[1000]; Map m1; random_map<Map>(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000; i++)
        m[i] = new Map(m1.begin(), m1.end());

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 1000; i++)
        delete m[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_constructors(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** by default ********************************************************/

    ft_chrono  = get_timing_map_constructor_by_default< ft::map<T,U>>();
    std_chrono = get_timing_map_constructor_by_default<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,constructor_by_default");

    /****** by copy ***********************************************************/

    ft_chrono  = get_timing_map_constructor_by_copy< ft::map<T,U>>();
    std_chrono = get_timing_map_constructor_by_copy<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,constructor_by_copy");

    /****** by range **********************************************************/

    ft_chrono  = get_timing_map_constructor_by_range< ft::map<T,U>>();
    std_chrono = get_timing_map_constructor_by_range<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,constructor_by_range");
}

/****** Capacity **************************************************************/

template <typename Map>
double get_timing_map_empty()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m1.empty();

    for (int i = 0; i < 100; i++)
        (void)m2.empty();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_size()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000; i++)
        (void)m.size();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_max_size()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++) {
        (void)m1.max_size();
        (void)m2.max_size();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_capacity(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** empty *************************************************************/

    ft_chrono  = get_timing_map_empty< ft::map<T,U>>();
    std_chrono = get_timing_map_empty<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,empty");

    /****** size **************************************************************/

    ft_chrono  = get_timing_map_size< ft::map<T,U>>();
    std_chrono = get_timing_map_size<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,size");

    /****** max_size **********************************************************/

    ft_chrono  = get_timing_map_max_size< ft::map<T,U>>();
    std_chrono = get_timing_map_max_size<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,max_size");
}

/****** Observers *************************************************************/

template <typename Map>
double get_timing_map_key_comp()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.key_comp();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_value_comp()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.value_comp();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_observers(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** key_comp **********************************************************/

    ft_chrono  = get_timing_map_key_comp< ft::map<T,U>>();
    std_chrono = get_timing_map_key_comp<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,key_comp");

    /****** value_comp ********************************************************/

    ft_chrono  = get_timing_map_value_comp< ft::map<T,U>>();
    std_chrono = get_timing_map_value_comp<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,value_comp");
}

/****** Operations ************************************************************/

template <typename Map>
double get_timing_map_find()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    // we use a vecor instead of an array to not construct `Value` by default
    Map m; std::vector<Value> v;
    for (int i = 0; i < 100; i++)
    {
        int j = rand();
        v.push_back(Value(Key(j), Mapped(j)));
        m.insert(v[i]);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.find(v[i].first);

    // finding point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_count()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    // we use a vecor instead of an array to not construct `Value` by default
    Map m; std::vector<Value> v;
    for (int i = 0; i < 100; i++)
    {
        int j = rand();
        v.push_back(Value(Key(j), Mapped(j)));
        m.insert(v[i]);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.count(v[i].first);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_lower_bound()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    // we use a vecor instead of an array to not construct `Value` by default
    Map m; std::vector<Value> v;
    for (int i = 0; i < 100; i++)
    {
        int j = rand();
        v.push_back(Value(Key(j), Mapped(j)));
        m.insert(v[i]);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.lower_bound(v[i].first);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_upper_bound()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    // we use a vecor instead of an array to not construct `Value` by default
    Map m; std::vector<Value> v;
    for (int i = 0; i < 100; i++)
    {
        int j = rand();
        v.push_back(Value(Key(j), Mapped(j)));
        m.insert(v[i]);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.upper_bound(v[i].first);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_equal_range()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    // we use a vecor instead of an array to not construct `Value` by default
    Map m; std::vector<Value> v;
    for (int i = 0; i < 100; i++)
    {
        int j = rand();
        v.push_back(Value(Key(j), Mapped(j)));
        m.insert(v[i]);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.equal_range(v[i].first);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_operations(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** find **************************************************************/

    ft_chrono  = get_timing_map_find< ft::map<T,U>>();
    std_chrono = get_timing_map_find<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,find");

    /****** count *************************************************************/

    ft_chrono  = get_timing_map_count< ft::map<T,U>>();
    std_chrono = get_timing_map_count<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,count");

    /****** lower_bound *******************************************************/

    ft_chrono  = get_timing_map_lower_bound< ft::map<T,U>>();
    std_chrono = get_timing_map_lower_bound<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,lower_bound");

    /****** upper_bound *******************************************************/

    ft_chrono  = get_timing_map_upper_bound< ft::map<T,U>>();
    std_chrono = get_timing_map_upper_bound<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,upper_bound");

    /****** equal_range *******************************************************/

    ft_chrono  = get_timing_map_equal_range< ft::map<T,U>>();
    std_chrono = get_timing_map_equal_range<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,equal_range");
}

/****** Modifiers *************************************************************/

template <typename Map>
double get_timing_map_clear()
{
    // data we will operate on
    Map arr[10];

    // fill before clear
    for (int i = 0; i < 10; i++)
        random_map(arr[i], 10);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10; i++)
        arr[i].clear();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_erase()
{
    // data we will operate on
    Map m1; random_map(m1, 1000); typename Map::iterator its1[1000];
    Map m2; random_map(m2, 1000); typename Map::iterator its2[1000];

    typename Map::iterator it1 = m1.begin();
    typename Map::iterator it2 = m2.begin();

    for (int i = 0; i < 1000; i++, it1++, it2++) {
        its1[i] = it1;
        its2[i] = it2;
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000; i++) {
        (void)m1.erase(its1[i]); // erase by iterator position (1)
        (void)m2.erase((*its2[i]).first); // erase by key (2)
    }

    // eraseing point
    time_point<system_clock> erase = system_clock::now();

    // get delta
    return duration<double>(erase - start).count();
}

template <typename Map>
double get_timing_map_insert()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    // we use a vecor instead of an array to not construct `Value` by default
    Map m1; std::vector<Value> v;
    for (int i = 0; i < 10000; i++)
    {
        int j = rand();
        v.push_back(Value(Key(j), Mapped(j)));
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++) {
        m1.insert(v[i]); // insert single element (1)
        // insert with hint (2)
        // insert by iterator range (3)
    }

    // inserting point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_swap()
{
    // data we will operate on
    Map m1[1000], m2[1000];

    for (int i = 0; i < 1000; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000; i++)
        (void)m1[i].swap(m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_modifiers(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** clear *************************************************************/

    ft_chrono  = get_timing_map_clear< ft::map<T,U>>();
    std_chrono = get_timing_map_clear<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,clear");

    /****** erase *************************************************************/

    ft_chrono  = get_timing_map_erase< ft::map<T,U>>();
    std_chrono = get_timing_map_erase<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,erase");

    /****** insert ************************************************************/

    ft_chrono  = get_timing_map_insert< ft::map<T,U>>();
    std_chrono = get_timing_map_insert<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,insert");

    /****** swap **************************************************************/

    ft_chrono  = get_timing_map_swap< ft::map<T,U>>();
    std_chrono = get_timing_map_swap<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,swap");
}

/****** Operators *************************************************************/

template <typename Map>
double get_timing_map_op_brackets()
{
    // some convenient typedefs
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    Map m; Mapped tmp1, tmp2; Key key[100];

    for (int i = 0; i < 100; i++)
        key[i] = static_cast<Key>(rand());

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++) {
        tmp1 = m[key[i]];
        tmp2 = m[key[i]];
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    (void)tmp1;
    (void)tmp2;

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_assign()
{
    // data we will operate on
    Map m1, m2[100]; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        m2[i] = m1;

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_equal()
{
    // data we will operate on
    Map m1[100], m2[100];

    for (int i = 0; i < 100; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)(m1[i] == m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_not_equal()
{
    // data we will operate on
    Map m1[100], m2[100];

    for (int i = 0; i < 100; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)(m1[i] != m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_less_than()
{
    // data we will operate on
    Map m1[100], m2[100];

    for (int i = 0; i < 100; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)(m1[i] < m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_less_than_equal()
{
    // data we will operate on
    Map m1[100], m2[100];

    for (int i = 0; i < 100; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)(m1[i] <= m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_greater_than()
{
    // data we will operate on
    Map m1[100], m2[100];

    for (int i = 0; i < 100; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)(m1[i] > m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_op_greater_than_equal()
{
    // data we will operate on
    Map m1[100], m2[100];

    for (int i = 0; i < 100; i++) {
        random_map(m1[i], 100);
        random_map(m2[i], 100);
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)(m1[i] >= m2[i]);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_operators(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** operator[] ********************************************************/

    ft_chrono  = get_timing_map_op_brackets< ft::map<T,U>>();
    std_chrono = get_timing_map_op_brackets<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_brackets");

    /****** operator= *********************************************************/

    ft_chrono  = get_timing_map_op_assign< ft::map<T,U>>();
    std_chrono = get_timing_map_op_assign<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_assign");

    /****** operator== ********************************************************/

    ft_chrono  = get_timing_map_op_equal< ft::map<T,U>>();
    std_chrono = get_timing_map_op_equal<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_equal");

    /****** operator!= ********************************************************/

    ft_chrono  = get_timing_map_op_not_equal< ft::map<T,U>>();
    std_chrono = get_timing_map_op_not_equal<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_not_equal");

    /****** operator< *********************************************************/

    ft_chrono  = get_timing_map_op_less_than< ft::map<T,U>>();
    std_chrono = get_timing_map_op_less_than<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_less_than");

    /****** operator<= ********************************************************/

    ft_chrono  = get_timing_map_op_less_than_equal< ft::map<T,U>>();
    std_chrono = get_timing_map_op_less_than_equal<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_less_than_equal");

    /****** operator> *********************************************************/

    ft_chrono  = get_timing_map_op_greater_than< ft::map<T,U>>();
    std_chrono = get_timing_map_op_greater_than<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_greater_than");

    /****** operator>= ********************************************************/

    ft_chrono  = get_timing_map_op_greater_than_equal< ft::map<T,U>>();
    std_chrono = get_timing_map_op_greater_than_equal<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,op_greater_than_equal");
}

/****** Iterators *************************************************************/

template <typename Map>
double get_timing_map_begin()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.begin();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_end()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.end();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_rbegin()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.rbegin();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename Map>
double get_timing_map_rend()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++)
        (void)m.rend();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

/// @todo use `timing_iterator.cpp`
template <typename T, typename U>
void timing_test_map_iterators(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** begin *************************************************************/

    ft_chrono  = get_timing_map_begin< ft::map<T,U>>();
    std_chrono = get_timing_map_begin<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,begin");

    /****** end ***************************************************************/

    ft_chrono  = get_timing_map_end< ft::map<T,U>>();
    std_chrono = get_timing_map_end<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,end");

    /****** rbegin ************************************************************/

    ft_chrono  = get_timing_map_rbegin< ft::map<T,U>>();
    std_chrono = get_timing_map_rbegin<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,rbegin");

    /****** rend **************************************************************/

    ft_chrono  = get_timing_map_rend< ft::map<T,U>>();
    std_chrono = get_timing_map_rend<std::map<T,U>>();

    timing_log(outfile, ft_chrono, std_chrono, "map,rend");

//    timing_test_map_iterator_constructors<T,U>(outfile);
//    timing_test_map_iterator_assignation<T,U>(outfile);
//    timing_test_map_iterator_dereference<T,U>(outfile);
//    timing_test_map_iterator_increment<T,U>(outfile);
//    timing_test_map_iterator_decrement<T,U>(outfile);
//    timing_test_map_iterator_equal<T,U>(outfile);
//    timing_test_map_iterator_not_equal<T,U>(outfile);
//    timing_test_map_iterator_addition<T,U>(outfile);
//    timing_test_map_iterator_substraction<T,U>(outfile);
//    timing_test_map_iterator_less_than<T,U>(outfile);
//    timing_test_map_iterator_less_than_equal<T,U>(outfile);
//    timing_test_map_iterator_greater_than<T,U>(outfile);
//    timing_test_map_iterator_greater_than_equal<T,U>(outfile);
//    timing_test_map_iterator_add_then_assign<T,U>(outfile);
//    timing_test_map_iterator_sub_then_assign<T,U>(outfile);
}

/****** All tests *************************************************************/

template <typename T, typename U>
void timing_test_map(std::ofstream & outfile)
{
    timing_test_map_allocator<T,U>(outfile);
//    timing_test_map_constructors<T,U>(outfile);
//    timing_test_map_capacity<T,U>(outfile);
//    timing_test_map_observers<T,U>(outfile);
//    timing_test_map_operations<T,U>(outfile);
//    timing_test_map_modifiers<T,U>(outfile);
//    timing_test_map_operators<T,U>(outfile);
//    timing_test_map_iterators<T,U>(outfile);
}

int main()
{
    // open file
    std::ofstream outfile ("timing_map.csv", std::ofstream::trunc);

    // check for open error
    if (outfile.rdstate())
    {
        std::cout << "Error: can't open timing_map.csv" << std::endl;
        return 1;
    }

    // append csv header to outfile
    outfile << "container,function,ft,std,ratio,status" << std::endl;

    // change the templated type as you want but call this function once
    timing_test_map<int,int>(outfile);

    // close file
    outfile.close();

    return 0;
}