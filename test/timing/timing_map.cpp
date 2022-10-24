#include <map>
#include <chrono>
#include <cstring> // strcmp
#include <fstream>
#include <iostream>
#include <cstdlib> // rand()

#include "ft_map.hpp"
#include "utils.hpp"

/// @todo test all overloads (insert, erase, etc.)
/// @todo clear test leak sometimes

using namespace std::chrono;

#define RATIO_LIMIT 20.0

/****** utility ***************************************************************/

template <typename Map>
void random_map (Map & m, int const & size)
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    std::srand(std::time(0));

    // assume `key_type` and `mapped_type` are constructible from `int`
    for (int i = 0; i < size; i++)
    {
        int j = std::rand();
        try { m.insert(Value(Key(j), Mapped(j))); }
        catch (std::exception & e)
        {
            std::cout << e.what() << std::endl;
            m.clear();
            return;
        }
    }
}

/****** begin() ***************************************************************/

template <typename Map>
double get_timing_map_begin()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++) {
        (void)m1.begin();
        (void)m2.begin();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_begin(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_begin<ft::map<T,U>>();
    double std_chrono = get_timing_map_begin<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,begin," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** clear() ***************************************************************/

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

template <typename T, typename U>
void timing_test_map_clear(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_clear<ft::map<T,U>>();
    double std_chrono = get_timing_map_clear<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,clear," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by default ************************************************/

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

template <typename T, typename U>
void timing_test_map_constructor_by_default(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_constructor_by_default<ft::map<T,U>>();
    double std_chrono = get_timing_map_constructor_by_default<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,constructor_by_default," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by copy ***************************************************/

template <typename Map>
double get_timing_map_constructor_by_copy()
{
    // data we will operate on
    Map * arr1[10000]; Map m1; random_map<Map>(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++)
        arr1[i] = new Map(m1);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete
    for (int i = 0; i < 10000; i++)
        delete arr1[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_constructor_by_copy(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_constructor_by_copy<ft::map<T,U>>();
    double std_chrono = get_timing_map_constructor_by_copy<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,constructor_by_copy," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by range **************************************************/

template <typename Map>
double get_timing_map_constructor_by_range()
{
    // data we will operate on
    Map * m[10000]; Map m1; random_map<Map>(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++)
        m[i] = new Map(m1.begin(), m1.end());

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 10000; i++)
        delete m[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_constructor_by_range(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_constructor_by_range<ft::map<T,U>>();
    double std_chrono = get_timing_map_constructor_by_range<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,constructor_by_range," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** empty() ***************************************************************/

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

template <typename T, typename U>
void timing_test_map_empty(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_empty<ft::map<T,U>>();
    double std_chrono = get_timing_map_empty<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,empty," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** end() *****************************************************************/

template <typename Map>
double get_timing_map_end()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100; i++) {
        (void)m1.end();
        (void)m2.end();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_end(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_end<ft::map<T,U>>();
    double std_chrono = get_timing_map_end<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,end," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** find() ****************************************************************/

template <typename Map>
double get_timing_map_find()
{
    // some convenient typedefs
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    // data we will operate on
    Map m; Value v[100];
    for (int i = 0; i < 100; i++)
    {
        int j = rand();
        v[i] = Value(Key(j), Mapped(j));
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

template <typename T, typename U>
void timing_test_map_find(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_find<ft::map<T,U>>();
    double std_chrono = get_timing_map_find<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,find," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** get_allocator() *******************************************************/

template <typename Map>
double get_timing_map_get_allocator()
{
    // data we will operate on
    Map m; random_map(m, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++)
        (void)m.get_allocator();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_get_allocator(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_get_allocator<ft::map<T,U>>();
    double std_chrono = get_timing_map_get_allocator<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,get_allocator," << ft_chrono << "," << std_chrono <<
    "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** key_comp() ************************************************************/

template <typename Map>
double get_timing_map_key_comp()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++) {
        (void)m1.key_comp();
        (void)m2.key_comp();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_key_comp(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_key_comp<ft::map<T,U>>();
    double std_chrono = get_timing_map_key_comp<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,key_comp," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** max_size() ************************************************************/

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
void timing_test_map_max_size(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_max_size<ft::map<T,U>>();
    double std_chrono = get_timing_map_max_size<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,max_size," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** rbegin() **************************************************************/

template <typename Map>
double get_timing_map_rbegin()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++) {
        (void)m1.rbegin();
        (void)m2.rbegin();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_rbegin(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_rbegin<ft::map<T,U>>();
    double std_chrono = get_timing_map_rbegin<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,rbegin," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** rend() ****************************************************************/

template <typename Map>
double get_timing_map_rend()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++) {
        (void)m1.rend();
        (void)m2.rend();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_rend(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_rend<ft::map<T,U>>();
    double std_chrono = get_timing_map_rend<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,rend," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** size() ****************************************************************/

template <typename Map>
double get_timing_map_size()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++) {
        (void)m1.size();
        (void)m2.size();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_size(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_size<ft::map<T,U>>();
    double std_chrono = get_timing_map_size<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,size," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** value_comp() **********************************************************/

template <typename Map>
double get_timing_map_value_comp()
{
    // data we will operate on
    Map m1, m2; random_map(m1, 100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++) {
        (void)m1.value_comp();
        (void)m2.value_comp();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T, typename U>
void timing_test_map_value_comp(std::ofstream & outfile)
{
    double ft_chrono = get_timing_map_value_comp<ft::map<T,U>>();
    double std_chrono = get_timing_map_value_comp<std::map<T,U>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "map,value_comp," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** main ******************************************************************/

template <typename T, typename U>
void timing_test_map(std::ofstream & outfile)
{
    /// @note each function append one line to `outfile`

    // allocator
//    timing_test_map_get_allocator<T,U>(outfile);

    // constructors
//    timing_test_map_constructor_by_default<T,U>(outfile);
//    timing_test_map_constructor_by_range<T,U>(outfile);
//    timing_test_map_constructor_by_copy<T,U>(outfile);

    // capacity
//    timing_test_map_empty<T,U>(outfile);
//    timing_test_map_size<T,U>(outfile);
//    timing_test_map_max_size<T,U>(outfile);

    // iterators
//    timing_test_map_begin<T,U>(outfile);
//    timing_test_map_end<T,U>(outfile);
//    timing_test_map_rbegin<T,U>(outfile);
//    timing_test_map_rend<T,U>(outfile);

// TODO
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

    // observers
//    timing_test_map_key_comp<T,U>(outfile);
//    timing_test_map_value_comp<T,U>(outfile);

    // operations
    timing_test_map_find<T,U>(outfile);
//    timing_test_map_count<T,U>(outfile); // TODO
//    timing_test_map_lower_bound<T,U>(outfile); // TODO
//    timing_test_map_upper_bound<T,U>(outfile); // TODO
//    timing_test_map_equal_range<T,U>(outfile); // TODO

    // modifiers
//    timing_test_map_clear<T,U>(outfile);
//    timing_test_map_erase<T,U>(outfile); // TODO
//    timing_test_map_insert<T,U>(outfile); // TODO
//    timing_test_map_swap<T,U>(outfile); // TODO

    // operators
//    timing_test_map_op_brackets<T,U>(outfile); // TODO
//    timing_test_map_op_assign<T,U>(outfile); // TODO
//    timing_test_map_op_equal<T,U>(outfile); // TODO
//    timing_test_map_op_not_equal<T,U>(outfile); // TODO
//    timing_test_map_op_less_than<T,U>(outfile); // TODO
//    timing_test_map_op_less_than_equal<T,U>(outfile); // TODO
//    timing_test_map_op_greater_than<T,U>(outfile); // TODO
//    timing_test_map_op_greater_than_equal<T,U>(outfile); // TODO
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