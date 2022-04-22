#ifndef FT_STACK_HPP
#define FT_STACK_HPP 1

#include "ft_vector.hpp"

namespace ft {

template <class T, class Container = vector<T>>
class stack {

    /**************************************************************************/
    /*                                                                        */
    /*      Member types                                                      */
    /*                                                                        */
    /**************************************************************************/

    public:

    typedef T	        value_type;
    typedef Container	container_type;
    typedef size_t	    size_type;

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    container_type _c;

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    stack(const container_type & container = container_type())
    : _c(container) { }

    bool
    empty() const
    { return _c.empty(); }

    bool
    size() const
    { return _c.size(); }

    value_type &
    top()
    { return _c.back(); }

    const value_type &
    top() const
    { return _c.back(); } ;

    void
    push(const value_type & val)
    { return _c.push.back(val); }

    void
    pop()
    { return _c.pop.back(); }

};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

template <class T, class Container>
bool
operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{ return (lhs._c == rhs._c); }

template <class T, class Container>
bool
operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{ return (lhs._c != rhs._c); }

template <class T, class Container>
bool
operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{ return (lhs._c < rhs._c); }

template <class T, class Container>
bool
operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{ return (lhs._c > rhs._c); }

template <class T, class Container>
bool
operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{ return (lhs._c <= rhs._c); }

template <class T, class Container>
bool
operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{ return (lhs._c >= rhs._c); }

} // namespace

#endif /* FT_STACK_HPP */
