#ifndef FT_VECTOR_H
#define FT_VECTOR_H 1

//#include <iostream>

//#include "ft_type_traits.hpp"
#include "ft_random_access_iterator.hpp"
#include "ft_iterator_base_types.hpp"

#include <memory> // std::allocator
#include <stdexcept> // std::out_of_range --> rewrite it for namespace ft ?

namespace ft {

template <class T, class Allocator = std::allocator<T>>
class vector {

    /**************************************************************************/
    /*                                                                        */
    /*      Member types                                                      */
    /*                                                                        */
    /**************************************************************************/

    public:

    // those types: 'value_type', 'difference_type', 'pointer', 'reference'
    // could also be defined from iterator (cf. ft_iterator_base_types.hpp)
    // or from allocator (it is defined this way into ISO standard)

    typedef T           value_type;
    typedef Allocator   allocator_type;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef T &         reference;
    typedef const T &   const_reference;
    typedef T *         pointer;
    typedef const T *   const_pointer;

    // random_access_iterator --> random_access_iterator

    typedef random_access_iterator<T> iterator;
//    typedef const random_access_iterator<T> const_iterator;
    //typedef reverse_iterator;
    //typedef const_reverse_iterator;

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    T *             _data;
    size_type	    _size;
    size_type       _capacity;
    size_type       _max_size;  // arbitrary initialized at allocator_type.max_size()
                                // cf. https://stackoverflow.com/questions/3813124/c-vector-max-size
    allocator_type  _alloc;

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Constructors ******************************************************/

    // by default - add 'explicit' qualifier ?
    vector (const allocator_type & alloc = allocator_type())
    : _size(0), _capacity(0), _max_size(alloc.max_size()), _alloc(alloc) { }

    // by fill - add 'explicit' qualifier ?
    vector (
        size_type n,
        const value_type & val = value_type(),
        const allocator_type & alloc = allocator_type()
    ) : _size(n), _capacity(n), _max_size(alloc.max_size()), _alloc(alloc)
    {
        try { _data = _alloc.allocate(_size); }
        catch (std::bad_alloc & ba) { std::cout << ba.what() << std::endl; } // log ?
        for (size_type i = 0; i < _size; i++) { _alloc.construct(&_data[i], val); } // assign
    }

    // by iterator range
    // template <class InputIterator>
    //         vector (InputIterator first, InputIterator last,
    //                 const allocator_type& alloc = allocator_type());

    // by copy
 //   vector (const vector<value_type, allocator_type> & v)
 //   : _size(v._size), _capacity(v._capacity), _max_size(v.max_size()),
 //       _alloc(v._alloc)
 //   { *this = v; }


    /****** Destructor ********************************************************/

    ~vector()
    {
        for (size_type i = 0; i < _size; i++) { _alloc.destroy(&_data[i]); }
        if (_capacity) _alloc.deallocate(_data, _capacity);
    }

    /****** Element access ****************************************************/

    // add 'const_reference' return type overload for each function below

    reference at(size_type n)
    { if (n < _size) return _data[n]; else throw std::out_of_range(""); }
    //{ return n < _size ? _data[n] : throw std::out_of_range(""); }

    const_reference at(size_type n) const
    { if (n < _size) return _data[n]; else throw std::out_of_range(""); }

    // undefined behavior if vector is empty
    reference front() { return _data[0]; }

    // undefined behavior if vector is empty
    reference back() { return _data[_size - 1]; }

    // C++11
    // pointer data() { return _data; }

    /****** Capacity **********************************************************/

    bool        empty()     const    { return _size ? false : true;  }
    size_type   size()      const    { return _size;                 }
    size_type   max_size()  const    { return _max_size;             }
    size_type   capacity()  const    { return _capacity;             }

    void
    reserve(size_type n)
    {
    //    if (_capacity < n)
    //    {
    //        vecto<value_type> tmp(n);
    //        tmp.assign(begin(), end());
    //        ~
    //    }

    }
    //{ if (_capacity < n) { &_data[_size] = _alloc.allocate(n - _capacity); } } // bug
    //{ if (_capacity < n) { back() = _alloc.allocate(n - _capacity); } } // fix ?

    /****** Modifiers *********************************************************/

    void
    clear()
    {
        // erase(begin(), end());
        // _size = 0;
        for (size_type i = 0; i < _size; i++) {
           _alloc.destroy(&_data[i]);
        }
        _size = 0;
    }

    // insert()

    /****** erase ******/

    // erase by iterator position
    iterator erase(iterator position)
    {
       // if (position != end())
       // {
       //     _alloc.destroy(position);
       //     iterator tmp = position;
       //     for (; ++tmp != end();)
       //         ;
       //        // tmp - 1 = value_type(*tmp);
       //     tmp = NULL;

       //     _size--;
       // }
        return position;
    }

    // erase by iterator range
   // iterator erase(iterator first, iterator last)
   // {
    //_size -= end() - position;
   // }

    // push_back()
    // pop_back()
    // resize()
    // swap()

    // assign by iterator range
   // template <typename InputIterator>
   // void assign(InputIterator first, InputIterator last)
   // {
   //     erase(begin(), end());
   //     insert(begin(), first, last);
   // }

    // assign by size and value
   // void assign(size_type n, const T& t);
   // {
   //     erase(begin(), end());
   //     insert(begin(), n, t);
   // }

    /****** Iterators *********************************************************/

    // add 'const_reference' return type overload for each function below

	iterator begin() { return iterator(&_data[0]); }

	iterator end() { return iterator(&_data[_size]); }

	// reverse_iterator rbegin() { };
	// reverse_iterator rend() { };

    /****** Operators *********************************************************/

    // operator=
  //  vector<value_type, allocator_type> &
  //  operator=(const vector<value_type, allocator_type> & v)
  //  {
  //      if (*this != v)
  //      {
  //          if (this->_capacity < v._size())

  //          else

  //      }
  //  }

    // doesn't check boundaries
    reference
    operator[](size_type n) { return _data[n]; }

    // doesn't check boundaries
    const reference
    operator[](size_type n) const { return _data[n]; }

    /****** Miscellaneous *****************************************************/

    // get_allocator()
};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++) {
        if (lhs.at(i) != rhs.at(i))
            return false;
    }
    return true;
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    { return !(lhs == rhs); }

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
    //return
    //ft::lexicographical_compare<typename lhs::iterator, typename rhs::iterator>
    //(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    return false;
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    { return rhs < lhs; }

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    { return !(rhs > lhs); }

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    { return !(lhs > rhs); }

} // namespace ft

#endif  /* FT_VECTOR_H */
