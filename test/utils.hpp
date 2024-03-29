#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP 1

#include <map>
#include <vector>
#include <iostream>
#include <cstdlib> // rand()
#include <ctime> // time()

#include "ft_map.hpp"
#include "rb_tree.hpp"
#include "ft_pair.hpp"
#include "ft_vector.hpp"

#define RATIO_LIMIT 20.0

/****** Colors ****************************************************************/

#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

/****** Log *******************************************************************/

int test_status = 0;

#define expect(expr)                                                           \
if (!(expr)) {                                                                 \
    std::cout <<                                                               \
    static_cast<std::string>(__FILE__) + ":" + std::to_string(__LINE__) + ":" +\
    static_cast<std::string>(__PRETTY_FUNCTION__) + " Assertion `" + #expr +   \
    "` failed." << std::endl; test_status = 1;                                 \
}

inline void success(std::string const s)
{ std::cout << s << GREEN << " OK" << RESET << std::endl; }

inline void failure(std::string const s)
{ std::cout << s << RED << " KO" << RESET << std::endl; test_status = 0; }

inline void log(std::string const s)
{ test_status ? failure(s) : success(s); }

/****** Timing log ************************************************************/

void timing_log(std::ofstream & o, double ft, double std, std::string const & s)
{
    double ratio = ft / std;

    o << s << "," << ft << "," << std << "," << ratio << ",";

    ft > std && ratio > RATIO_LIMIT
    ? o <<   RED << "KO" << RESET << std::endl
    : o << GREEN << "OK" << RESET << std::endl;
}

/****** Custom datatype *******************************************************/

/// @note depending on how your containers are implemented, this class might
///       require specific operators and methods in order to perform all tests.
class A
{
    public:
    int data;
    A () : data(int()) { }
    A (int const & i) : data(i) { }
    A (A const & a) : data(a.data) { }
    A & operator =(A const & a) { data = a.data; return *this; }
};

bool operator==(A const & lhs, A const & rhs)
{ return lhs.data == rhs.data; }

bool operator!=(A const & lhs, A const & rhs)
{ return lhs.data != rhs.data; }

bool operator< (A const & lhs, A const & rhs)
{ return lhs.data < rhs.data; }

bool operator> (A const & lhs, A const & rhs)
{ return lhs.data > rhs.data; }

bool operator<= (A const & lhs, A const & rhs)
{ return !(lhs > rhs); }

bool operator>= (A const & lhs, A const & rhs)
{ return !(lhs < rhs); }

/****** is_rbtree *************************************************************/

template <typename Container>
struct is_rbtree : std::false_type { };

template <typename T>
struct is_rbtree<ft::rb_tree<T> > : std::true_type { };

/****** is_pair ***************************************************************/

template <typename T>
struct is_pair : public std::false_type { };

template <typename T, typename U>
struct is_pair<ft::pair<T, U> > : public std::true_type { };

template <typename T, typename U>
struct is_pair<std::pair<T, U> > : public std::true_type { };

/****** is_vector *************************************************************/

template <typename Container>
struct is_vector : std::false_type { };

template <typename T>
struct is_vector<ft::vector<T> > : std::true_type { };

template <typename T>
struct is_vector<std::vector<T> > : std::true_type { };

/****** is_map ****************************************************************/

template <typename Container>
struct is_map : std::false_type { };

template <typename T, typename U>
struct is_map<ft::map<T,U> > : std::true_type { };

template <typename T, typename U>
struct is_map<std::map<T,U> > : std::true_type { };

/****** Key type utilities ****************************************************/

template <typename Tree>
typename std::enable_if<is_pair<typename Tree::key_type>::value, typename Tree::key_type>::type
key_type (int x) { return typename Tree::key_type(x,x); }

template <typename Tree>
typename std::enable_if<std::is_same<typename Tree::key_type, int>::value, typename Tree::key_type>::type
key_type (int x) { return typename Tree::key_type(x); }

template <typename Tree>
typename std::enable_if<std::is_same<typename Tree::key_type, A>::value, typename Tree::key_type>::type
key_type (int x) { return typename Tree::key_type(x); }

/****** Value type utilities **************************************************/

/// @brief Construct a vector `value_type` object from `int`
template <typename Container>
typename std::enable_if<is_vector<Container>::value, typename Container::value_type>::type
value_type (int x) { return typename Container::value_type(x); }

/// @brief Construct a map `value_type` object from `int`
template <typename Container>
typename std::enable_if<is_map<Container>::value, typename Container::value_type>::type
value_type (int x)
{
    return typename Container::value_type(
        typename Container::key_type(x),
        typename Container::mapped_type(x));
}

/// @brief Construct a rbtree `value_type` object from `int`
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, typename Container::value_type>::type
value_type (int x) { return typename Container::value_type(key_type<Container>(x)); }

/****** Fill a map with random values *****************************************/

template <typename Map>
void random_map (Map & m, int const & size)
{
    typedef typename Map::value_type    Value;
    typedef typename Map::key_type      Key;
    typedef typename Map::mapped_type   Mapped;

    std::srand(static_cast<unsigned int>(std::time(0)));

    // assume `key_type` and `mapped_type` are constructible from `int`
    for (int i = 0; i < size; i++)
    {
        int j = std::rand();
        try { m.insert(Value(Key(j), Mapped(j))); }
        catch (std::exception & e)
        { std::cout << e.what() << std::endl; m.clear(); return; }
    }
}

/******************************************************************************/

#endif /* TEST_UTILS_HPP */