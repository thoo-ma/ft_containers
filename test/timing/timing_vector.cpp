#include <vector>
#include <chrono>
#include <cstring> // strcmp
#include <fstream>
#include <iostream>

#include "ft_vector.hpp"

/// @todo absolute path
#include "../utils.hpp"

using namespace std::chrono;

/**
 * @todo add more teste into compute section
 * @todo #define 20.0 limit
 * @todo verify we don't go over max_size !! (could explain very good perfs...)
 * @todo add `timing_log()`
 * @todo template tests upon `vector<T>` instead of `vector<int>`
 * --> gather them in sections (cf. output_vector) instead of alphabetical order
 */

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

void timing_test_vector_at(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_at<ft::vector<int>>();
    double std_chrono = get_timing_vector_at<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,at," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_back(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_back<ft::vector<int>>();
    double std_chrono = get_timing_vector_back<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,back," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** begin() ***************************************************************/

template <typename Vector>
double get_timing_vector_begin()
{
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

void timing_test_vector_begin(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_begin<ft::vector<int>>();
    double std_chrono = get_timing_vector_begin<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,begin," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_capacity(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_capacity<ft::vector<int>>();
    double std_chrono = get_timing_vector_capacity<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,capacity," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_clear(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_clear<ft::vector<int>>();
    double std_chrono = get_timing_vector_clear<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,clear," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_constructor_by_default(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_default<ft::vector<int>>();
    double std_chrono = get_timing_vector_constructor_by_default<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_default," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_constructor_by_copy(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_copy<ft::vector<int>>();
    double std_chrono = get_timing_vector_constructor_by_copy<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_copy," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_constructor_by_fill(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_fill<ft::vector<int>>();
    double std_chrono = get_timing_vector_constructor_by_fill<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_fill," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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
        v[i] = new Vector(v1.begin(), v1.end() - 1);

    // ending point
    time_point<system_clock> end = system_clock::now();

    // delete data
    for (int i = 0; i < 100000; i++)
        delete v[i];

    // get delta
    return duration<double>(end - start).count();
}

void timing_test_vector_constructor_by_range(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_constructor_by_range<ft::vector<int>>();
    double std_chrono = get_timing_vector_constructor_by_range<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,constructor_by_range," << ft_chrono << "," <<
    std_chrono << "," << ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_empty(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_empty<ft::vector<int>>();
    double std_chrono = get_timing_vector_empty<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,empty," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_end(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_end<ft::vector<int>>();
    double std_chrono = get_timing_vector_end<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,end," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_front(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_front<ft::vector<int>>();
    double std_chrono = get_timing_vector_front<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,front," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_get_allocator(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_get_allocator<ft::vector<int>>();
    double std_chrono = get_timing_vector_get_allocator<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,get_allocator," << ft_chrono << "," << std_chrono <<
    "," << ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_max_size(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_max_size<ft::vector<int>>();
    double std_chrono = get_timing_vector_max_size<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,max_size," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_pop_back(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_pop_back<ft::vector<int>>();
    double std_chrono = get_timing_vector_pop_back<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,pop_back," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_push_back(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_push_back<ft::vector<int>>();
    double std_chrono = get_timing_vector_push_back<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,push_back," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** rbegin() **************************************************************/

template <typename Vector>
double get_timing_vector_rbegin()
{
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

void timing_test_vector_rbegin(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_rbegin<ft::vector<int>>();
    double std_chrono = get_timing_vector_rbegin<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,rbegin," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_rend(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_rend<ft::vector<int>>();
    double std_chrono = get_timing_vector_rend<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,rend," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_reserve(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_reserve<ft::vector<int>>();
    double std_chrono = get_timing_vector_reserve<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,reserve," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_resize(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_resize<ft::vector<int>>();
    double std_chrono = get_timing_vector_resize<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,resize," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_size(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_size<ft::vector<int>>();
    double std_chrono = get_timing_vector_size<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,size," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_assign(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_assign<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_assign<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_equal<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_equal<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,==," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_not_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_not_equal<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_not_equal<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,!=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_less_than(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_less_than<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_less_than<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,<," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_greater_than(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_greater_than<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_greater_than<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,>," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_less_than_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_less_than_equal<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_less_than_equal<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,<=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_greater_than_equal(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_greater_than_equal<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_greater_than_equal<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,>=," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_op_bracket(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_op_bracket<ft::vector<int>>();
    double std_chrono = get_timing_vector_op_bracket<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,[]," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_swap(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_swap<ft::vector<int>>();
    double std_chrono = get_timing_vector_swap<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,swap," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
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

void timing_test_vector_erase(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_erase<ft::vector<int>>();
    double std_chrono = get_timing_vector_erase<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,erase," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** insert() **************************************************************/

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

void timing_test_vector_insert(std::ofstream & outfile)
{
    double ft_chrono = get_timing_vector_insert<ft::vector<int>>();
    double std_chrono = get_timing_vector_insert<std::vector<int>>();
    double ratio = ft_chrono / std_chrono;

    outfile << "vector,insert," << ft_chrono << "," << std_chrono << "," <<
    ratio << ",";

    ft_chrono > std_chrono && ratio > 20.0
    ? outfile << RED << "KO" << RESET << std::endl
    : outfile << GREEN << "OK" << RESET << std::endl;
}

/****** main ******************************************************************/

int main()
{
    // open file
    std::ofstream outfile ("timing.csv", std::ofstream::trunc);

    // check for open error
    if (outfile.rdstate())
    {
        std::cout << "Error: can't open timing.csv" << std::endl;
        return 1;
    }

    // append csv header to outfile
    outfile << "container,function,ft,std,ratio,status" << std::endl;

    // tests: each one append a line to outfile

    // allocator
//    timing_test_vector_get_allocator(outfile);

    // constructors
//    timing_test_vector_constructor_by_default(outfile);
//    timing_test_vector_constructor_by_fill(outfile);
//    timing_test_vector_constructor_by_copy(outfile);
//    timing_test_vector_constructor_by_range(outfile);

    // capacity
//    timing_test_vector_empty(outfile);
//    timing_test_vector_size(outfile);
//    timing_test_vector_max_size(outfile);
//    timing_test_vector_capacity(outfile);
//    timing_test_vector_reserve(outfile);

    // iterators
    timing_test_vector_begin(outfile);
    timing_test_vector_end(outfile);
    timing_test_vector_rbegin(outfile);
    timing_test_vector_rend(outfile);

// TODO
//    timing_test_vector_iterator_constructors(outfile);
//    timing_test_vector_iterator_assignation(outfile);
//    timing_test_vector_iterator_dereference(outfile);
//    timing_test_vector_iterator_increment(outfile);
//    timing_test_vector_iterator_decrement(outfile);
//    timing_test_vector_iterator_equal(outfile);
//    timing_test_vector_iterator_not_equal(outfile);
//    timing_test_vector_iterator_addition(outfile);
//    timing_test_vector_iterator_substraction(outfile);
//    timing_test_vector_iterator_less_than(outfile);
//    timing_test_vector_iterator_less_than_equal(outfile);
//    timing_test_vector_iterator_greater_than(outfile);
//    timing_test_vector_iterator_greater_than_equal(outfile);
//    timing_test_vector_iterator_add_then_assign(outfile);
//    timing_test_vector_iterator_sub_then_assign(outfile);

    // accessors
//    timing_test_vector_at(outfile);
//    timing_test_vector_back(outfile);
//    timing_test_vector_front(outfile);
//    timing_test_vector_op_bracket(outfile);

    // modifiers
//    timing_test_vector_clear(outfile); // KO
//    timing_test_vector_erase(outfile);
//    timing_test_vector_insert(outfile); // KO
//    timing_test_vector_push_back(outfile); // KO
//    timing_test_vector_pop_back(outfile);
//    timing_test_vector_resize(outfile); // KO
//    timing_test_vector_swap(outfile);

    // operators
//    timing_test_vector_op_assign(outfile);
//    timing_test_vector_op_equal(outfile);
//    timing_test_vector_op_not_equal(outfile);
//    timing_test_vector_op_less_than(outfile);
//    timing_test_vector_op_less_than_equal(outfile);
//    timing_test_vector_op_greater_than(outfile);
//    timing_test_vector_op_greater_than_equal(outfile);

    // close file
    outfile.close();

    return 0;
}
