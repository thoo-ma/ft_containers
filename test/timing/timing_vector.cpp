#include <vector>
#include <chrono>
#include <cstring> // strcmp
#include <fstream>
#include <iostream>

#include "ft_vector.hpp"
#include "utils.hpp"

using namespace std::chrono;

#define RATIO_LIMIT 20.0

/// @todo operator[] not good (cf. timing_map for a correct one)
/// @todo verify we don't go over max_size !! (could explain very good perfs...)
/// @todo (?) add `timing_log()`
/// @todo (?) test all overloads (insert, erase, etc.)

/****** at() ******************************************************************/

template <typename Vector>
double get_timing_vector_at()
{
    // data we will operate on
    Vector v(10000000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v.at(i);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // return delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_at(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_at<ft::vector<T>>();
    double std_chrono = get_timing_vector_at<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,at," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** back() ****************************************************************/

template <typename Vector>
double get_timing_vector_back()
{
    // data we will operate on
    Vector v(21, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v.back();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_back(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_back<ft::vector<T>>();
    double std_chrono = get_timing_vector_back<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,back," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** begin() ***************************************************************/

template <typename Vector>
double get_timing_vector_begin()
{
    // data we will operate on
    Vector v1;
    Vector v2(10, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++) {
        (void)v1.begin();
        (void)v2.begin();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_begin(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_begin<ft::vector<T>>();
    double std_chrono = get_timing_vector_begin<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,begin," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** capacity() ************************************************************/

template <typename Vector>
double get_timing_vector_capacity()
{
    // data we will operate on
    Vector v(10000000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000000; i++)
        (void)v.capacity();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_capacity(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_capacity<ft::vector<T>>();
    double std_chrono = get_timing_vector_capacity<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,capacity," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** clear() ***************************************************************/

template <typename Vector>
double get_timing_vector_clear()
{
    // data we will operate on
    Vector vec(10000, 42);
    Vector arr[10000];

    // fill before clear
    for (int i = 0; i < 10000; i++)
        arr[i] = vec;

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++)
        arr[i].clear();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_clear(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_clear<ft::vector<T>>();
    double std_chrono = get_timing_vector_clear<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,clear," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by default ************************************************/

template <typename Vector>
double get_timing_vector_constructor_by_default()
{
    // data we will operate on
    Vector * arr[100000];

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++)
        arr[i] = new Vector();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 100000; i++)
        delete arr[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_constructor_by_default(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_default<ft::vector<T>>();
    double std_chrono = get_timing_vector_constructor_by_default<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_default," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by copy ***************************************************/

template <typename Vector>
double get_timing_vector_constructor_by_copy()
{
    // data we will operate on
    Vector * arr1[10000]; Vector v1;
    Vector * arr2[10000]; Vector v2(1000);
    Vector * arr3[10000]; Vector v3(1000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++) {
        arr1[i] = new Vector(v1);
        arr2[i] = new Vector(v2);
        arr3[i] = new Vector(v3);
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete
    for (int i = 0; i < 10000; i++) {
        delete arr1[i];
        delete arr2[i];
        delete arr3[i];
    }

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_constructor_by_copy(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_copy<ft::vector<T>>();
    double std_chrono = get_timing_vector_constructor_by_copy<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_copy," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by fill ***************************************************/

template <typename Vector>
double get_timing_vector_constructor_by_fill()
{
    // data we will operate on
    Vector * v[100000];

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++)
        v[i] = new Vector(100, 42);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 100000; i++)
        delete v[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_constructor_by_fill(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_fill<ft::vector<T>>();
    double std_chrono = get_timing_vector_constructor_by_fill<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_fill," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** constructor by range **************************************************/

template <typename Vector>
double get_timing_vector_constructor_by_range()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector * v[100000];

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++)
        v[i] = new Vector(v1.begin(), v1.end());

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 100000; i++)
        delete v[i];

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_constructor_by_range(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_range<ft::vector<T>>();
    double std_chrono = get_timing_vector_constructor_by_range<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_range," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** empty() ***************************************************************/

template <typename Vector>
double get_timing_vector_empty()
{
    // data we will operate on
    Vector v1(10, 42);
    Vector v2;

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v1.empty();

    for (int i = 0; i < 10000000; i++)
        (void)v2.empty();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

std::pair<int,int> p;

template <typename T>
void timing_test_vector_empty(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_empty<ft::vector<T>>();
    double std_chrono = get_timing_vector_empty<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,empty," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** end() *****************************************************************/

template <typename Vector>
double get_timing_vector_end()
{
    // data we will operate on
    Vector v1;
    Vector v2(10, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++) {
        (void)v1.end();
        (void)v2.end();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_end(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_end<ft::vector<T>>();
    double std_chrono = get_timing_vector_end<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,end," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** front() ***************************************************************/

template <typename Vector>
double get_timing_vector_front()
{
    // data we will operate on
    Vector v(21, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v.front();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_front(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_front<ft::vector<T>>();
    double std_chrono = get_timing_vector_front<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,front," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** get_allocator() *******************************************************/

template <typename Vector>
double get_timing_vector_get_allocator()
{
    // data we will operate on
    Vector v(100, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v.get_allocator();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_get_allocator(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_get_allocator<ft::vector<T>>();
    double std_chrono = get_timing_vector_get_allocator<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,get_allocator," << ft_chrono << "," << std_chrono <<
    "," << ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** max_size() ************************************************************/

template <typename Vector>
double get_timing_vector_max_size()
{
    // data we will operate on
    Vector v1;
    Vector v2(1000);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v1.max_size();

    for (int i = 0; i < 10000000; i++)
        (void)v2.max_size();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_max_size(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_max_size<ft::vector<T>>();
    double std_chrono = get_timing_vector_max_size<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,max_size," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** pop_back() ************************************************************/

template <typename Vector>
double get_timing_vector_pop_back()
{
    // data we will operate on
    Vector v1;
    Vector v2(1000000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++)
        v1.pop_back();

    for (int i = 0; i < 1000000; i++)
        v2.pop_back();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_pop_back(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_pop_back<ft::vector<T>>();
    double std_chrono = get_timing_vector_pop_back<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,pop_back," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** push_back() ***********************************************************/

template <typename Vector>
double get_timing_vector_push_back()
{
    // data we will operate on
    Vector v1;
    Vector v2(100);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++)
        v1.push_back(42);

    for (int i = 0; i < 10000; i++)
        v2.push_back(42);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_push_back(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_push_back<ft::vector<T>>();
    double std_chrono = get_timing_vector_push_back<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,push_back," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** rbegin() **************************************************************/

template <typename Vector>
double get_timing_vector_rbegin()
{
    // data we will operate on
    Vector v1;
    Vector v2(10, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++) {
        (void)v1.rbegin();
        (void)v2.rbegin();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_rbegin(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_rbegin<ft::vector<T>>();
    double std_chrono = get_timing_vector_rbegin<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,rbegin," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** rend() ****************************************************************/

template <typename Vector>
double get_timing_vector_rend()
{
    // data we will operate on
    Vector v1;
    Vector v2(10, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++) {
        (void)v1.rend();
        (void)v2.rend();
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_rend(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_rend<ft::vector<T>>();
    double std_chrono = get_timing_vector_rend<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,rend," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** reserve() *************************************************************/

template <typename Vector>
double get_timing_vector_reserve()
{
    // data we will operate on
    Vector v1;
    Vector v2(100);
    Vector v3(100, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (typename Vector::size_type i = 0; i < 10000; i++)
        v1.reserve(i);

    for (typename Vector::size_type i = 0; i < 10000; i++)
        v2.reserve(i);

    for (typename Vector::size_type i = 0; i < 10000; i++)
        v3.reserve(i);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_reserve(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_reserve<ft::vector<T>>();
    double std_chrono = get_timing_vector_reserve<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,reserve," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** resize() **************************************************************/

template <typename Vector>
double get_timing_vector_resize()
{
    // data we will operate on
    Vector v1;
   // Vector v2(1000);
   // Vector v3(1000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++) {
        v1.resize(i);
       // v2.resize(i);
       // v3.resize(i);
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_resize(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_resize<ft::vector<T>>();
    double std_chrono = get_timing_vector_resize<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,resize," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** size() ****************************************************************/

template <typename Vector>
double get_timing_vector_size()
{
    // data we will operate on
    Vector v1;
    Vector v2(10, 42);
    Vector v3(100000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)v1.size();

    for (int i = 0; i < 10000000; i++)
        (void)v2.size();

    for (int i = 0; i < 10000000; i++)
        (void)v3.size();

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_size(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_size<ft::vector<T>>();
    double std_chrono = get_timing_vector_size<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,size," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator= *************************************************************/

template <typename Vector>
double get_timing_vector_op_assign()
{
    // data we will operate on
    Vector v0(100, 21);
    Vector v1[10000];

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++)
        v1[i] = v0;

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_assign(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_assign<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_assign<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator== ************************************************************/

template <typename Vector>
double get_timing_vector_op_equal()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector v2(100, 21);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)(v1 == v2);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_equal<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_equal<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,==," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator!= ************************************************************/

template <typename Vector>
double get_timing_vector_op_not_equal()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector v2(100, 21);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 10000000; i++)
        (void)(v1 != v2);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_not_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_not_equal<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_not_equal<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,!=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator< *************************************************************/

template <typename Vector>
double get_timing_vector_op_less_than()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector v2(100, 21);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++)
        (void)(v1 < v2);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_less_than(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_less_than<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_less_than<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,<," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator> *************************************************************/

template <typename Vector>
double get_timing_vector_op_greater_than()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector v2(100, 21);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++)
        (void)(v1 > v2);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_greater_than(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_greater_than<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_greater_than<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,>," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator<= ************************************************************/

template <typename Vector>
double get_timing_vector_op_less_than_equal()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector v2(100, 21);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++)
        (void)(v1 <= v2);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_less_than_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_less_than_equal<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_less_than_equal<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,<=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator>= ************************************************************/

template <typename Vector>
double get_timing_vector_op_greater_than_equal()
{
    // data we will operate on
    Vector v1(100, 42);
    Vector v2(100, 21);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++)
        (void)(v1 >= v2);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_greater_than_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_greater_than_equal<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_greater_than_equal<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,>=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** operator[] ************************************************************/

template <typename Vector>
double get_timing_vector_op_bracket()
{
    // data we will operate on
    Vector v[100000];
    Vector tmp;

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 100000; i++)
        tmp = v[i];

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return std::chrono::duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_op_bracket(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_bracket<ft::vector<T>>();
    double std_chrono = get_timing_vector_op_bracket<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,[]," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** swap() ****************************************************************/

template <typename Vector>
double get_timing_vector_swap()
{
    // data we will operate on
    Vector v1(10000, 21);
    Vector v2(10000, 42);

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute
    for (int i = 0; i < 1000000; i++) {
        v1.swap(v2);
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_swap(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_swap<ft::vector<T>>();
    double std_chrono = get_timing_vector_swap<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,swap," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** erase() ***************************************************************/

template <typename Vector>
double get_timing_vector_erase()
{
    // data we will operate on
    Vector arr[1000];
    Vector vec(1000, 42);

    // fill before erase
    for (int i = 0; i < 1000; i++) {
        arr[i] = vec;
    }

    // starting point
    time_point<system_clock> start = system_clock::now();

    // compute (erase by range, not by position)
    for (int i = 0; i < 1000; i++) {
        arr[i].erase(arr[i].begin(), arr[i].end());
    }

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_erase(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_erase<ft::vector<T>>();
    double std_chrono = get_timing_vector_erase<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,erase," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** insert() **************************************************************/

/// @todo insert by fill (3)
template <typename Vector>
double get_timing_vector_insert()
{
    // data we will operate on
    Vector v1, v2, v3;

    // starting point
    time_point<system_clock> start = system_clock::now();

    // insert by position (1)
    for (int i = 0; i < 1000; i++)
        v1.insert(v1.begin(), 42);

    // insert by fill (2)
    for (int i = 0; i < 100; i++)
        v2.insert(v2.begin(), 100, 21);

    // insert by fill (3)
//    for (int i = 0; i < 100; i++)
//        v3.insert(v3.begin(), v1.begin(), v1.begin() + i);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // get delta
    return duration<double>(end - start).count();
}

template <typename T>
void timing_test_vector_insert(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_insert<ft::vector<T>>();
    double std_chrono = get_timing_vector_insert<std::vector<T>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,insert," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > RATIO_LIMIT
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** main ******************************************************************/

template <typename T>
void timing_test_vector(std::ofstream & outfile)
{
    /// @note each function append one line to `outfile`

    // allocator
    timing_test_vector_get_allocator<T>(outfile);

    // constructors
    timing_test_vector_constructor_by_default<T>(outfile);
    timing_test_vector_constructor_by_fill<T>(outfile);
    timing_test_vector_constructor_by_copy<T>(outfile);
    timing_test_vector_constructor_by_range<T>(outfile);

    // capacity
    timing_test_vector_empty<T>(outfile);
    timing_test_vector_size<T>(outfile);
    timing_test_vector_max_size<T>(outfile);
    timing_test_vector_capacity<T>(outfile);
    timing_test_vector_reserve<T>(outfile);

    // iterators
    timing_test_vector_begin<T>(outfile);
    timing_test_vector_end<T>(outfile);
    timing_test_vector_rbegin<T>(outfile);
    timing_test_vector_rend<T>(outfile);

// TODO
//    timing_test_vector_iterator_constructors<T>(outfile);
//    timing_test_vector_iterator_assignation<T>(outfile);
//    timing_test_vector_iterator_dereference<T>(outfile);
//    timing_test_vector_iterator_increment<T>(outfile);
//    timing_test_vector_iterator_decrement<T>(outfile);
//    timing_test_vector_iterator_equal<T>(outfile);
//    timing_test_vector_iterator_not_equal<T>(outfile);
//    timing_test_vector_iterator_addition<T>(outfile);
//    timing_test_vector_iterator_substraction<T>(outfile);
//    timing_test_vector_iterator_less_than<T>(outfile);
//    timing_test_vector_iterator_less_than_equal<T>(outfile);
//    timing_test_vector_iterator_greater_than<T>(outfile);
//    timing_test_vector_iterator_greater_than_equal<T>(outfile);
//    timing_test_vector_iterator_add_then_assign<T>(outfile);
//    timing_test_vector_iterator_sub_then_assign<T>(outfile);

    // accessors
    timing_test_vector_at<T>(outfile);
    timing_test_vector_back<T>(outfile);
    timing_test_vector_front<T>(outfile);
    timing_test_vector_op_bracket<T>(outfile);

    // modifiers
    timing_test_vector_clear<T>(outfile); // KO
    timing_test_vector_erase<T>(outfile);
    timing_test_vector_insert<T>(outfile); // KO
    timing_test_vector_push_back<T>(outfile); // KO
    timing_test_vector_pop_back<T>(outfile);
    timing_test_vector_resize<T>(outfile); // KO
    timing_test_vector_swap<T>(outfile);

    // operators
    timing_test_vector_op_assign<T>(outfile);
    timing_test_vector_op_equal<T>(outfile);
    timing_test_vector_op_not_equal<T>(outfile);
    timing_test_vector_op_less_than<T>(outfile);
    timing_test_vector_op_less_than_equal<T>(outfile);
    timing_test_vector_op_greater_than<T>(outfile);
    timing_test_vector_op_greater_than_equal<T>(outfile);
}

int main()
{
    // open file
    std::ofstream outfile ("timing_vector.csv", std::ofstream::trunc);

    // check for open error
    if (outfile.rdstate())
    {
        std::cout << "Error: can't open timing_vector.csv" << std::endl;
        return 1;
    }

    // append csv header to outfile
    outfile << "container,function,ft,std,ratio,status" << std::endl;

    // change the templated type as you want but call this function once
    timing_test_vector<int>(outfile);

    // close file
    outfile.close();

    return 0;
}