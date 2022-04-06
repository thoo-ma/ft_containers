#ifndef FT_VECTOR_H
#define FT_VECTOR_H 1

#include <iostream>

//#include "ft_type_traits.hpp"
#include "ft_random_access_iterator.hpp"
#include "ft_iterator_base_types.hpp"

#include <memory> // std::allocator
#include <stdexcept> // std::out_of_range --> rewrite it for namespace ft ?

namespace ft {L

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

    /*
     * STL
     * reserve(size_type n)
     * {
     *     if (n > this->max_size())
     *         __throw_length_error(__N("vector::reserve"));
     *     if (this->capacity() < n)
	 *     {
	 *         const size_type old_size = size();

     * 	    pointer tmp = _M_allocate_and_copy(n,
     *                         this->_M_impl._M_start,
     *                         this->_M_impl._M_finish);

     * 	    std::_Destroy(this->_M_impl._M_start,
     *             this->_M_impl._M_finish,
     * 		    _M_get_Tp_allocator());

     * 	    _M_deallocate(this->_M_impl._M_start,
     * 		    this->_M_impl._M_end_of_storage
     * 		    - this->_M_impl._M_start);

     * 	    this->_M_impl._M_start = tmp;
     * 	    this->_M_impl._M_finish = tmp + old_size;
     * 	    this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
     * 	}
     * }
     */

    void
    reserve(size_type n)
    {
        if (_capacity < n)
        {
            vector<value_type> tmp(n);
            tmp.assign(begin(), end());
            *this = tmp;
        }
    }
    //{ if (_capacity < n) { &_data[_size] = _alloc.allocate(n - _capacity); } } // bug
    //{ if (_capacity < n) { back() = _alloc.allocate(n - _capacity); } } // fix ?

    /****** Modifiers *********************************************************/

    void
    clear()
    { erase(begin(), end()); }

    /****** insert ******/

    // single element (1)
   // iterator
   // insert (iterator position, const value_type & val)
   // { return (insert(position, 1, val)); }

    // fill (2)
    void
    insert (iterator position, size_type n, const value_type & val)
    {
        if (_size + n > _capacity)
        {
            // 1
            vector<value_type> tmp;

            tmp.reserve(_size + n);

            tmp.insert(tmp.begin(), begin(), end());

            tmp.insert(tmp.begin() + (position - begin()), n, val);

            *this = tmp;

            return;

            // 2
            
            // reallocation (might fail. if so, do we exit current function here ?)
//            value_type * tmp = NULL;
//            try { tmp = _alloc.allocate(_size + n); }
//            catch (std::bad_alloc & ba) { std::cout << ba.what() << std::endl; } // log ?
//
//            // copy before position
//            for (size_type i = 0; i < position - begin(); i++)
//            {
//                tmp[i] = _data[i];
//                _alloc.destroy(&_data[i]);
//            }

            // update capacity
     //       if (_capacity)
     //           _alloc.deallocate(_data, _capacity);
     //       _capacity = _size + n;

//            _data = tmp;
        }
//        size_type lo = position - begin();
//        size_type hi = lo + n;
//        while (lo < hi)
//        {
//            _data[_size] = _data[lo];
//            _data[lo] = val;
//            _size++;
//            lo++;
//        }
        for (size_type i = position - begin(); i < position - begin() + n; i++)
        {
            _data[_size] = _data[i];
            _data[i] = val;
            _size++;
        }
    }

    // range (3)
    template <class InputIterator>
    void
    insert (iterator position, InputIterator first, InputIterator last)
    {
        std::cout << "hi" << std::endl;
        if (_capacity - _size < last - first)
        {
            vector<value_type, allocator_type> tmp(_size + (last - first)); // reserve ? construct by copy ?
            
            return tmp.insert(tmp.begin(), begin(), end());

        }
        while (first != last)
        {
            _data[position - begin()] = *first;
            first++;
        }
        std::cout << "bye" << std::endl;
    }

    /****** erase ******/

    // erase by position
    iterator
    erase(iterator position)
    { return (erase(position, position + 1)); }

    // erase by range
    iterator
    erase(iterator first, iterator last)
    {
        // 1. Get return value
        iterator ret = first == last ? last : first;

        // 2. Detroy elements in range [first, last)
        iterator it = first;
        while (it != last)
        {
            _alloc.destroy(&_data[it - begin()]);
            it++;
        }

        // 3. Move elements from [last, enf) to [first, ...)
        while (it != end())
        {
            _data[first - begin()] = _data[it - begin()];
            _alloc.destroy(&_data[it - begin()]);
            it++;
            first++;
        }

        // 4. Update size
        if (it != first)
            _size = first - begin();

        return ret;
    }

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
    vector<value_type, allocator_type> &
    operator=(const vector<value_type, allocator_type> & v)
    {
        if (*this != v)
        {
            if (_capacity < v.size())
            {
                std::cout << "here" << std::endl;
                vector<value_type, allocator_type> tmp(v.size()); // reserve ?
                tmp.insert(tmp.begin(), begin(), end()); // here
                *this = tmp; // recursive call
                return *this;
            }
            std::cout << "ici" << std::endl;
            for (size_type i = 0; i < v.size(); i++)
            {
                _alloc.destroy(&_data[i]);
                _data[i] = v.at(i);
            }
            _size = v.size();
            std::cout << "la" << std::endl;
        }
        return *this;
    }

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

