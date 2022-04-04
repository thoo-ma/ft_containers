#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H 1

#include "ft_iterator_base_types.hpp"

namespace ft {

/*
 * This iterator class meets all `random_access_iterator` requirements, i.e:
 *
 * (table 72 at https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf)
 *
 * | EXPRESSION | RETURN TYPE |   SEMANTIC   |   NOTES && POST/PRE-CONDITIONS  |
 * | -----------|-------------|--------------|---------------------------------|
 * | X u        |             |              | notes:                          |
 * |            |             |              | . u might have a singular value |
 * |            |             |              | . a destructor is assumed       |
 * | -----------|-------------|--------------|---------------------------------|
 * | X()        |             |              | note: X() might be singular     |
 * | -----------|-------------|--------------|---------------------------------|
 * | X(a)       |             |              | a == X(a)                       |
 * | -----------|-------------|--------------|---------------------------------|
 * | X u(a);    |             | X u; u = a;  | post: u == a                    |
 * | X u = a;   |             |              |                                 |
 * | -----------|-------------|--------------|---------------------------------|
 * | a == b     | bool        |              | == is an equivalence relation   |
 * | -----------|-------------|--------------|---------------------------------|
 * | a != b     | bool        | !(a == b)    |                                 |
 * | -----------|-------------|--------------|---------------------------------|
 * | r = a      | X &         |              | post: r == a                    |
 * | -----------|-------------|--------------|---------------------------------|
 * | *a         | T &         |              | pre:                            |
 * |            |             |              | . a is dereferenceable          |
 * |            |             |              | . a == b implies *a == *b       |
 * |            |             |              | . if X is mutable,              |
 * |            |             |              |   then *a = t is valid          |
 * | -----------|-------------|--------------|---------------------------------|
 * | a->m       | U &         | (*a).m       | pre: (*a).m is well-defined.    |
 * | -----------|-------------|--------------|---------------------------------|
 * | ++r        | X &         |              | pre:                            |
 * |            |             |              | . r is dereferenceable          |
 * |            |             |              | post:                           |
 * |            |             |              | . r is dereferenceable or r is  |
 * |            |             |              |   past-the-end                  |
 * |            |             |              | . r == s and r is dereference-  |
 * |            |             |              |   able implies ++r == ++s       |
 * |            |             |              | . &r == &++r                    |
 * | -----------|-------------|--------------|---------------------------------|
 * | r++        | convertible | X tmp = r;   |                                 |
 * |            | to const X& | ++r;         |                                 |
 * |            |             | return tmp;  |                                 |
 * | -----------|-------------|--------------|---------------------------------|
 * | *r++       | T &         |              |                                 |
 * | -----------|--------------------------------------------------------------|
 * | BIDIRECTIONAL_ITERATOR                                                    |
 * | -----------|--------------------------------------------------------------|
 * | --r        | X &         |              | pre:                            |
 * |            |             |              | . there exists s such that      |
 * |            |             |              |   r == ++s                      |
 * |            |             |              | post:                           |
 * |            |             |              | . s is dereferenceable          |
 * |            |             |              | . --(++r) == r                  |
 * |            |             |              | . --r == --s implies r == s     |
 * |            |             |              | . &r == &--r                    |
 * | -----------|-------------|--------------|---------------------------------|
 * | r--        | convertible | X tmp = r;   |                                 |
 * |            | to const X& | --r;         |                                 |
 * |            |             | return tmp;  |                                 |
 * | -----------|-------------|--------------|---------------------------------|
 * | *r--       | convertible |              |                                 |
 * |            | to T        |              |                                 |
 * | --------------------------------------------------------------------------|
 * | RANDOM_ACCESS_ITERATOR                                                    |
 * | --------------------------------------------------------------------------|
 * | r += n     | X &         | Distance     |                                 |
 * |            |             | m = n;       |                                 |
 * |            |             | if (m >= 0)  |                                 |
 * |            |             | while (m--)  |                                 |
 * |            |             | ++r;         |                                 |
 * |            |             | else         |                                 |
 * |            |             | while (m++)  |                                 |
 * |            |             | --r;         |                                 |
 * |            |             | return r;    |                                 |
 * | --------------------------------------------------------------------------|
 * | a + n      | X           | X b = a;     | a + n == n + a                  |
 * |            |             | return b+=n; |                                 |
 * | --------------------------------------------------------------------------|
 * | r -= n     | X &         | return       |                                 |
 * |            |             | r += -n;     |                                 |
 * | --------------------------------------------------------------------------|
 * | a - n      | X           | X b = a;     |                                 |
 * |            |             | return b-=n; |                                 |
 * | --------------------------------------------------------------------------|
 * | b - a      | Distance    | if (a<b)     | pre: there exists a value n     |
 * |            |             | distance(a,b)| of Distance such that           |
 * |            |             | else         | . a + n == b                    |
 * |            |             | distance(b,a)| . b == a + (b - a)              |
 * |            |             | * (-1)       |                                 |
 * | --------------------------------------------------------------------------|
 * | a[n]       | T           | *(a + n)     |                                 |
 * | --------------------------------------------------------------------------|
 * | a < b      | bool        | b - a > 0    | < is a total ordering relation  |
 * | --------------------------------------------------------------------------|
 * | a > b      | bool        | b < a        | > is opposite to <              |
 * | --------------------------------------------------------------------------|
 * | a >= b     | bool        | !(a < b)     |                                 |
 * | --------------------------------------------------------------------------|
 * | a <= b     | bool        | !(a > b)     |                                 |
 * | --------------------------------------------------------------------------|
 *
 *  Constructor by pointer is the only member function not required implemented.
 *
 */

template <typename T>
class random_access_iterator : public iterator<std::random_access_iterator_tag, T>
//class vector_iterator : public iterator<std::random_access_iterator_tag, T>
{
    public: void debug() { std::cout << _data << std::endl; }

    public:

    typedef iterator<std::random_access_iterator_tag, T> base_iterator;

    // these types need to be redefined.
    // cf. https://stackoverflow.com/questions/32270597/inheriting-typedefs

    typedef typename base_iterator::iterator_category iterator_category;
    typedef typename base_iterator::value_type        value_type;
    typedef typename base_iterator::difference_type   difference_type;
    typedef typename base_iterator::pointer           pointer;
    typedef typename base_iterator::reference         reference;

//    typedef typename iterator_traits<std::random_access_iterator>::value_type value_type;

    protected: T * _data; // private

    public:

    // constructor by default
    random_access_iterator()
    : _data(NULL)
    {
    //    std::cout << "default iterator constructor" << std::endl;
    }

    // constructor by pointer
    random_access_iterator(T * data)
    : _data(data)
    {
    //    std::cout << "pointer iterator constructor" << std::endl;
    }

    // constructor by copy
    random_access_iterator(const random_access_iterator & it)
    : _data(it._data)
    {
    //    std::cout << "copy iterator constructor" << std::endl;
    }

    // assignation
    random_access_iterator & operator=(const random_access_iterator & rhs)
    {
        //std::cout << "assignation operator called" << std::endl;
        _data = rhs._data;
        return *this;
    };

    // dereference
    reference
    operator*() const
    { return *_data; }

    // equal
    bool
    operator==(const random_access_iterator<T> & rhs) const
    {
        //std::cout << "iterator member function '=='" << std::endl;
        return _data == rhs._data;
    }

    // not equal
    bool
    operator!=(const random_access_iterator<T> & rhs) const
    {
        //std::cout << "iterator member function '!='" << std::endl;
        return !(*this == rhs);
    }

    // prefix incrementation
    random_access_iterator &
    operator++()
    { ++_data; return *this; }

    // postfix incrementation
    // How this `int` arg helps the compiler to distinguish this function from the one above ?
    random_access_iterator
    operator++(int)
    { random_access_iterator tmp(*this); operator++(); return tmp; }

    // prefix decrementation
    random_access_iterator &
    operator--()
    { --_data; return *this; }

   // postfix decrementation
   // How this `int` arg helps the compiler to distinguish this function from the one above ?
    random_access_iterator
    operator--(int)
    { random_access_iterator tmp(*this); operator--(); return tmp; }

    // multiple increment
    random_access_iterator &
    operator+=(const difference_type n)
    {
    // why not delete `const` attribute to `n` ?
    // Hence `m` would be useless.
    // (this also apply upon following operators)
        difference_type m = n;
        if (m >= 0) { while (m--) ++(*this); }
        else        { while (m++) --(*this); }
        return *this;
    }

    // multiple decrement
    random_access_iterator &
    operator-=(const difference_type & n)
    {
        //return *this += -n;
        return operator+=(-n);
    }

    // addition
    random_access_iterator
    operator+(const difference_type & n) const
    {
       // std::cout << "iterator member function '+'" << std::endl;
        return random_access_iterator<T>(this->_data + n);
    }

    // substraction
    random_access_iterator
    operator-(const difference_type & n) const
    {
        //std::cout << "iterator member function '-'" << std::endl;
        return random_access_iterator<T>(this->_data - n);
        //return operator+(-n); // WHY THIS DOESN'T WORK ??
    }

    // substraction between iterators
    difference_type
    operator-(const random_access_iterator<T> & rhs) const
    {
        return *this > rhs
        ? this->_data - rhs._data
        : -(rhs._data - this->_data);
    }

    // brackets operator
    value_type &
    operator[](const difference_type n) const
    { return *this + n; }

    // Less than
    bool
    operator<(const random_access_iterator<T> & rhs) const
    //{ return *this - rhs > 0; }
    { return this->_data > rhs._data; }

   // // Greather than
    bool
    operator>(const random_access_iterator<T> & rhs) const
    { return rhs < *this; }

   // // Less or equal than
   // bool
   // operator<=(const random_access_iterator<T> & rhs) const
   // { return !(*this > rhs); }

   // // Greather or equal than
   // bool
   // operator>=(const random_access_iterator<T> & rhs) const
   // { return !(*this < rhs); }

};

} // namespace ft

#endif /* RANDOM_ACCESS_ITERATOR_H */
