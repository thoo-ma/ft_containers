#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP 1

#include "ft_iterator_base_types.hpp"

namespace ft
{

template <typename Iterator>
class reverse_iterator {

    /****** Member types **************************************************/

    public:

    typedef Iterator	                                iterator_type;
    typedef typename iterator_type::iterator_category	iterator_category;
    typedef typename iterator_type::value_type          value_type;
    typedef typename iterator_type::difference_type     difference_type;
    typedef typename iterator_type::pointer	            pointer;
    typedef typename iterator_type::reference	        reference;

    /****** Private data **************************************************/

    private: iterator_type _base;

    /****** Constructors **************************************************/

    public:

    reverse_iterator() { }

    reverse_iterator(const iterator_type & it) : _base(it) { }

    template <typename Iter>
    reverse_iterator(const reverse_iterator<Iter> & rit) : _base(rit.base()) { }

    /****** Member functions **********************************************/

    /// @todo why cannot return a reference ?
    iterator_type base() const { return _base; }

    /****** Operators *****************************************************/

    reverse_iterator & operator=(const reverse_iterator & it)
    { _base = it.base(); return *this; }

    reference operator*() const
    { return _base.operator*(); }

    pointer operator->() const
    { return _base.operator->(); }

    template <typename Iter>
    bool operator==(const reverse_iterator<Iter> & it) const
    { return _base == it.base(); }

    template <typename Iter>
    bool operator!=(const reverse_iterator<Iter> & it) const
    { return _base != it.base(); }

    /// @note prefix
    reverse_iterator & operator++()
    { _base.operator--(); return *this; }

    /// @note prefix
    reverse_iterator & operator--()
    { _base.operator++(); return *this; }

    /// @note postfix
    reverse_iterator operator++(int)
    { reverse_iterator tmp(*this); operator++(); return tmp; }

    /// @note postfix
    reverse_iterator operator--(int)
    { reverse_iterator tmp(*this); operator--(); return tmp; }

    /// @note why `n` is not a reference here ?
    reverse_iterator & operator+=(const difference_type n)
    { _base -= n; return *this; }

    reverse_iterator & operator-=(const difference_type & n)
    { _base += n; return *this; }

    reverse_iterator operator+(const difference_type & n) const
    { return reverse_iterator(_base - n); }

    reverse_iterator operator-(const difference_type & n) const
    { return operator+(-n); }

    template <typename Iter>
    difference_type operator-(const reverse_iterator<Iter> & rhs) const
    { return rhs.base() - _base; }

    value_type & operator[](const difference_type n) const
    { return _base[-n]; }

    template <typename Iter>
    bool operator<(const reverse_iterator<Iter> & rhs) const
    { return _base > rhs.base(); }

    template <typename Iter>
    bool operator>(const reverse_iterator<Iter> & rhs) const
    { return _base < rhs.base(); }

    template <typename Iter>
    bool operator<=(const reverse_iterator<Iter> & rhs) const
    { return !(*this > rhs); }

    template <typename Iter>
    bool operator>=(const reverse_iterator<Iter> & rhs) const
    { return !(*this < rhs); }

};

} // namespace

#endif /* REVERSE_ITERATOR_HPP */
