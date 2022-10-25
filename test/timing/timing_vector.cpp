#include <vector>
#include <chrono>
#include <fstream>

#include "ft_vector.hpp"
#include "utils.hpp"

using namespace std::chrono;

/// @todo operator[] not good (cf. timing_map for a correct one)
/// @todo verify we don't go over max_size !! (could explain very good perfs...)
/// @todo (?) test all overloads (insert, erase, etc.)

/****** Allocator *************************************************************/

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
void timing_test_vector_allocator(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    ft_chrono  = get_timing_vector_get_allocator< ft::vector<T>>();
    std_chrono = get_timing_vector_get_allocator<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,get_allocator");
}

/****** Constructors **********************************************************/

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
void timing_test_vector_constructors(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** by default ********************************************************/

    ft_chrono  = get_timing_vector_constructor_by_default< ft::vector<T>>();
    std_chrono = get_timing_vector_constructor_by_default<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,constructor_by_default");

    /****** by fill ***********************************************************/

    ft_chrono  = get_timing_vector_constructor_by_fill< ft::vector<T>>();
    std_chrono = get_timing_vector_constructor_by_fill<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,constructor_by_fill");

    /****** by copy ***********************************************************/

    ft_chrono  = get_timing_vector_constructor_by_copy< ft::vector<T>>();
    std_chrono = get_timing_vector_constructor_by_copy<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,constructor_by_copy");

    /****** by range **********************************************************/

    ft_chrono  = get_timing_vector_constructor_by_range< ft::vector<T>>();
    std_chrono = get_timing_vector_constructor_by_range<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,constructor_by_range");
}

/****** Capacity **************************************************************/

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
void timing_test_vector_capacity(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** empty *************************************************************/

    ft_chrono  = get_timing_vector_empty< ft::vector<T>>();
    std_chrono = get_timing_vector_empty<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,empty");

    /****** size **************************************************************/

    ft_chrono  = get_timing_vector_size< ft::vector<T>>();
    std_chrono = get_timing_vector_size<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,size");

    /****** max_size **********************************************************/

    ft_chrono  = get_timing_vector_max_size< ft::vector<T>>();
    std_chrono = get_timing_vector_max_size<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,max_size");

    /****** capacity **********************************************************/

    ft_chrono  = get_timing_vector_capacity< ft::vector<T>>();
    std_chrono = get_timing_vector_capacity<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,capacity");

    /****** reserve ***********************************************************/

    ft_chrono  = get_timing_vector_reserve< ft::vector<T>>();
    std_chrono = get_timing_vector_reserve<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,reserve");
}

/****** Accessors *************************************************************/

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
void timing_test_vector_accessors(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** at ****************************************************************/

    ft_chrono  = get_timing_vector_at< ft::vector<T>>();
    std_chrono = get_timing_vector_at<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,at");

    /****** back **************************************************************/

    ft_chrono  = get_timing_vector_back< ft::vector<T>>();
    std_chrono = get_timing_vector_back<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,back");

    /****** front *************************************************************/

    ft_chrono  = get_timing_vector_front< ft::vector<T>>();
    std_chrono = get_timing_vector_front<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,front");

    /****** operator[] ********************************************************/

    ft_chrono  = get_timing_vector_op_bracket< ft::vector<T>>();
    std_chrono = get_timing_vector_op_bracket<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_bracket");
}

/****** Modifiers *************************************************************/

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
void timing_test_vector_modifiers(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** clear *************************************************************/

    ft_chrono  = get_timing_vector_clear< ft::vector<T>>();
    std_chrono = get_timing_vector_clear<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,clear");

    /****** erase *************************************************************/

    ft_chrono  = get_timing_vector_erase< ft::vector<T>>();
    std_chrono = get_timing_vector_erase<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,erase");

    /****** insert ************************************************************/

    ft_chrono  = get_timing_vector_insert< ft::vector<T>>();
    std_chrono = get_timing_vector_insert<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,insert");

    /****** push_back *********************************************************/

    ft_chrono  = get_timing_vector_push_back< ft::vector<T>>();
    std_chrono = get_timing_vector_push_back<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,push_back");

    /****** pop_back **********************************************************/

    ft_chrono  = get_timing_vector_pop_back< ft::vector<T>>();
    std_chrono = get_timing_vector_pop_back<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,pop_back");

    /****** resize ************************************************************/

    ft_chrono  = get_timing_vector_resize< ft::vector<T>>();
    std_chrono = get_timing_vector_resize<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,resize");

    /****** swap **************************************************************/

    ft_chrono  = get_timing_vector_swap< ft::vector<T>>();
    std_chrono = get_timing_vector_swap<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,swap");
}

/****** Operators *************************************************************/

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
void timing_test_vector_operators(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** operator= *********************************************************/

    ft_chrono  = get_timing_vector_op_assign< ft::vector<T>>();
    std_chrono = get_timing_vector_op_assign<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_assign");

    /****** operator== *********************************************************/

    ft_chrono  = get_timing_vector_op_equal< ft::vector<T>>();
    std_chrono = get_timing_vector_op_equal<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_equal");

    /****** operator!= ********************************************************/

    ft_chrono  = get_timing_vector_op_not_equal< ft::vector<T>>();
    std_chrono = get_timing_vector_op_not_equal<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_not_equal");

    /****** operator< *********************************************************/

    ft_chrono  = get_timing_vector_op_less_than< ft::vector<T>>();
    std_chrono = get_timing_vector_op_less_than<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_less_than");

    /****** operator<= ********************************************************/

    ft_chrono  = get_timing_vector_op_less_than_equal< ft::vector<T>>();
    std_chrono = get_timing_vector_op_less_than_equal<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_less_than_equal");

    /****** operator> *********************************************************/

    ft_chrono  = get_timing_vector_op_greater_than< ft::vector<T>>();
    std_chrono = get_timing_vector_op_greater_than<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_greater_than");

    /****** operator>= ********************************************************/

    ft_chrono  = get_timing_vector_op_greater_than_equal< ft::vector<T>>();
    std_chrono = get_timing_vector_op_greater_than_equal<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,op_greater_than_equal");
}

/****** Iterators *************************************************************/

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

/// @todo use `timing_iterator.cpp`
template <typename T>
void timing_test_vector_iterators(std::ofstream & outfile)
{
    double ft_chrono, std_chrono;

    /****** begin *************************************************************/

    ft_chrono  = get_timing_vector_begin< ft::vector<T>>();
    std_chrono = get_timing_vector_begin<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,begin");

    /****** end ***************************************************************/

    ft_chrono  = get_timing_vector_end< ft::vector<T>>();
    std_chrono = get_timing_vector_end<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,end");

    /****** rbegin ************************************************************/

    ft_chrono  = get_timing_vector_rbegin< ft::vector<T>>();
    std_chrono = get_timing_vector_rbegin<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,rbegin");

    /****** rend **************************************************************/

    ft_chrono  = get_timing_vector_rend< ft::vector<T>>();
    std_chrono = get_timing_vector_rend<std::vector<T>>();

    timing_log(outfile, ft_chrono, std_chrono, "vector,rend");

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
}

/****** All tests *************************************************************/

template <typename T>
void timing_test_vector(std::ofstream & outfile)
{
    timing_test_vector_allocator<T>(outfile);
//    timing_test_vector_constructors<T>(outfile);
//    timing_test_vector_capacity<T>(outfile);
//    timing_test_vector_accessors<T>(outfile);
//    timing_test_vector_modifiers<T>(outfile);
//    timing_test_vector_operators<T>(outfile);
//    timing_test_vector_iterators<T>(outfile);
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