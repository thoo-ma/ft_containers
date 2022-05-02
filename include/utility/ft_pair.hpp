#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP 1

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

    // constructor by default (1)	
    pair()
    : first(T1()), second(T2()) { }
    
    // constructor copy (2)	
    template<class T1_, class T2_>
    pair(const pair<T1_, T2_> & pair)
    : first(pair.first), second(pair.second) { }
    
    // constructor by initialization (3)	
    pair(const first_type & a, const second_type & b)
    : first(a), second(b) { }

    // assignation operator
    pair &
    operator=(const pair & pair)
    {
        first = pair.first;
        second = pair.second;
        return *this;
    }

};

/****** Non-member functions overload *****************************************/

template <typename T1, typename T2>
bool
operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
{ return lhs.first == rhs.first && lhs.second == rhs.second; }

template <typename T1, typename T2>
bool
operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
{ return !(lhs == rhs); }

template <typename T1, typename T2>
bool
operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
{
    return
    (lhs.first < rhs.first) ||
    (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool
operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
{ return !(rhs < lhs); }

template <typename T1, typename T2>
bool
operator>(const pair<T1,T2>& lhs, const pair<T1,T2> & rhs)
{ return rhs < lhs; }

template <typename T1, typename T2>
bool
operator>=(const pair<T1,T2> & lhs, const pair<T1,T2>& rhs)
{ return !(lhs < rhs); }

/****** make_pair() ***********************************************************/

template <typename T1, typename T2>
pair<T1,T2>
make_pair(T1 a, T2 b)
{ return pair<T1,T2>(a, b); }

#endif /* FT_PAIR_HPP */
