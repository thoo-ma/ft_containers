#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP 1

#include <iostream> // ???

namespace ft {

template <typename T1, typename T2>
struct pair
{
    /****** Member types ******************************************************/

    typedef T1 first_type;
    typedef T2 second_type;

    /****** Member variables **************************************************/

    T1 first;
    T2 second;

    /****** Member functions **************************************************/

    /// @brief Constructor by default (1)
    pair() : first(T1()), second(T2()) { }

    /// @brief Constructor by copy (2) with different types
    template <typename U1, typename U2>
    pair(pair<U1,U2> const & pair) : first(pair.first), second(pair.second) { }

    /// @brief constructor by copy (2) with same type
    ///
    /// This is needed for the following case:
    /// - we construct a pair from another with the same type
    /// - constructed pair has at least one const member type
    ///
    /// In such a case, since the compiler assume (U1 != T1 || U2 != T2),
    /// the constructor above will not be called.
    ///
    /// Then, it will be `operator=` that will be called for such construct.
    /// But if we construct a pair with const values (as we must have for map),
    /// then we cannot assign, we must list-initialize: this is what will be done here.
    pair(pair<T1,T2> const & pair) : first(pair.first), second(pair.second) { }

    /// @brief Constructor by initialization (3)
    pair(first_type const & a, second_type const & b) : first(a), second(b) { }

    pair & operator=(pair const & pair)
    {
        first = pair.first;
        second = pair.second;
        return *this;
    }

};

/****** Non-member functions overload *****************************************/

template <typename T1, typename T2>
bool operator==(pair<T1,T2> const & lhs, pair<T1,T2> const & rhs)
{ return lhs.first == rhs.first && lhs.second == rhs.second; }

template <typename T1, typename T2>
bool operator!=(pair<T1,T2> const & lhs, pair<T1,T2> const & rhs)
{ return !(lhs == rhs); }

template <typename T1, typename T2>
bool operator<(pair<T1,T2> const & lhs, pair<T1,T2> const & rhs)
{
    return
    (lhs.first < rhs.first) ||
    (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool operator<=(pair<T1,T2> const & lhs, pair<T1,T2> const & rhs)
{ return !(rhs < lhs); }

template <typename T1, typename T2>
bool operator>(pair<T1,T2> const & lhs, pair<T1,T2> const & rhs)
{ return rhs < lhs; }

template <typename T1, typename T2>
bool operator>=(pair<T1,T2> const & lhs, pair<T1,T2> const & rhs)
{ return !(lhs < rhs); }

/****** make_pair() ***********************************************************/

template <typename T1, typename T2>
pair<T1,T2> make_pair(T1 a, T2 b)
{ return pair<T1,T2>(a, b); }

} //namespace

#endif /* FT_PAIR_HPP */
