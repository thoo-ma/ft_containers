#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP 1

#include <map>
#include <vector>
#include <iostream>

#include "ft_map.hpp"
#include "rb_tree.hpp"
#include "ft_pair.hpp"
#include "ft_vector.hpp"

/****** Colors ****************************************************************/

#define RESET       "\033[0m"
#define BLACK       "\033[30m"          /* Black */
#define RED         "\033[31m"          /* Red */
#define GREEN       "\033[32m"          /* Green */
#define YELLOW      "\033[33m"          /* Yellow */
#define BLUE        "\033[34m"          /* Blue */
#define MAGENTA     "\033[35m"          /* Magenta */
#define CYAN        "\033[36m"          /* Cyan */
#define WHITE       "\033[37m"          /* White */
#define BOLDBLACK   "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"   /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"   /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"   /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"   /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"   /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"   /* Bold White */

/****** Log *******************************************************************/

inline void log(std::string const s)
{
    std::cout << s << GREEN << " OK" << RESET << std::endl;
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
value_type (int x) { return typename Container::value_type(x,x); }

/// @brief Construct a rbtree `value_type` object from `int`
template <typename Container>
typename std::enable_if<is_rbtree<Container>::value, typename Container::value_type>::type
value_type (int x) { return typename Container::value_type(key_type<Container>(x)); }

/******************************************************************************/

#endif /* TEST_UTILS_HPP */