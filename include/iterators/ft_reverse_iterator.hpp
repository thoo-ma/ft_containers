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

    reverse_iterator() : _base() { }

    reverse_iterator(iterator_type const & it) : _base(it) { }

    template <typename Iter>
    reverse_iterator(reverse_iterator<Iter> const & rit) : _base(rit.base()) { }

    /****** Destructor ****************************************************/

    virtual ~reverse_iterator() { }

    /****** Member functions **********************************************/

    iterator_type base() const
    { iterator_type tmp = _base; return ++tmp; }

    /****** Operators *****************************************************/

    reverse_iterator & operator=(reverse_iterator const & it)
    { _base = it.base(); return *this; }

    reference operator*() const
    { iterator_type tmp = _base; return (--tmp).operator*(); }

    pointer operator->() const
    { iterator_type tmp = _base; return (--tmp).operator->(); }

    template <typename Iter>
    bool operator==(reverse_iterator<Iter> const & it) const
    { return _base == it.base(); }

    template <typename Iter>
    bool operator!=(reverse_iterator<Iter> const & it) const
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
    reverse_iterator & operator+=(difference_type const n)
    { _base -= n; return *this; }

    reverse_iterator & operator-=(difference_type const & n)
    { _base += n; return *this; }

    reverse_iterator operator+(difference_type const & n) const
    { return reverse_iterator(_base - n); }

    reverse_iterator operator-(difference_type const & n) const
    { return operator+(-n); }

    template <typename Iter>
    difference_type operator-(reverse_iterator<Iter> const & rhs) const
    { return rhs.base() - _base; }

    value_type & operator[](difference_type const n) const
    { return _base[-n]; }

    template <typename Iter>
    bool operator<(reverse_iterator<Iter> const & rhs) const
    { return _base > rhs.base(); }

    template <typename Iter>
    bool operator>(reverse_iterator<Iter> const & rhs) const
    { return _base < rhs.base(); }

    template <typename Iter>
    bool operator<=(reverse_iterator<Iter> const & rhs) const
    { return !(*this > rhs); }

    template <typename Iter>
    bool operator>=(reverse_iterator<Iter> const & rhs) const
    { return !(*this < rhs); }

};

} // namespace

#endif /* REVERSE_ITERATOR_HPP */
