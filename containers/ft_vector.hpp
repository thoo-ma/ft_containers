#ifndef FT_VECTOR_H
#define FT_VECTOR_H 1

#include <iostream>

//#include "ft_type_traits.hpp"
#include "ft_random_access_iterator.hpp"
#include "ft_iterator_base_types.hpp"

#include <memory> // std::allocator
#include <stdexcept> // std::out_of_range --> rewrite it for namespace ft ?

/*
 * TODO
 *
 * - bien templater les iterateurs en arguments de certaines fonctions
 * - ne jamais set _capacity ou _size avant d'avoir appele allocate()
 * - bien gerer les allocations et les exceptions
 * - bien prendre en compte size_max pour jeter les exceptions appropriees
 *
 * MAYBE
 *
 * - add some private functions like STL (like internal primitives for public methods)
 *   --> _reallocate_and_copy(position, n, first, last)
 *  @def: reallocate n * sizeof(T) at position and copy there values inside [first,last)
 *
 * - use `_first` and `_finish` instead of `_size`
 */

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
    // _data = NULL

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
   // vector (InputIterator first, InputIterator last,
   // const allocator_type & alloc = allocator_type())
    vector (
        iterator first,
        iterator last,
        const allocator_type & alloc = allocator_type()
    ) : _alloc(alloc)
    {
        size_type len = last - first;
        // allocate...
        _data = _alloc.allocate(len);
        // then assign capacity
        _capacity = len;
        // fill...
        for (size_type i = 0; i < len; i++)
            _data[i] = *(first++);
        // then assign size
        _size = len;
    }

    // by copy
    vector (const vector<value_type, allocator_type> & v)
    : _size(0), _capacity(0), _max_size(v.max_size()), _alloc(v._alloc)
    { *this = v; }

    /****** Destructor ********************************************************/

    ~vector()
    {
        for (size_type i = 0; i < _size; i++) { _alloc.destroy(&_data[i]); }
        if (_capacity) _alloc.deallocate(_data, _capacity);
    }

    /****** Element access ****************************************************/

    // TODO
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
   //         // reallocate
   //         pointer tmp = _alloc.allocate(n);
   //         // recopy
   //         for (size_type i = 0; i < size(); i++)
   //             tmp[i] = at(i);
   //         clear();
            vector<value_type> tmp(*this);
            clear();
            _data = _alloc.allocate(n);
            _capacity = n;
            *this = tmp;
        }
    }

    /****** Modifiers *********************************************************/

    // TODO
    void
    clear()
    { erase(begin(), end()); }

    // single element (1)
    iterator
    insert (iterator position, const value_type & val)
    {
        size_type offset = position - begin();
        insert(position, 1, val);
        return begin() + offset;
    }

    // fill (2)
    void
    insert (iterator position, size_type n, const value_type & val)
    {
        // reallocate
        if (_size + n > _capacity)
        {
            // because of reallocation, position need to be reset
            size_type offset = position - begin();
            reserve(_size + n);
            position = begin() + offset;
        }
        // insert
        for (size_type i = 0; i < n; i++)
        {
            _data[_size] = *position;
            _data[position - begin()] = val;
            _size++;
            position++;
        }
    }

    // range (3)
    //template <class InputIterator>
    void
    insert (iterator position, iterator first, iterator last)
    //insert (iterator position, InputIterator first, InputIterator last)
    {
        // reallocate
        if (_capacity - _size < last - first)
        {
            // because of reallocation, position need to be reset
            size_type pos = position - begin();
            reserve(_size + (last - first));
            position = begin() + pos;
        }
        // insert
        while (first != last)
        {
            _data[_size] = *position;
            _data[position - begin()] = *first;
            first++;
            position++;
            _size++;
        }
    }

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

    // TODO
    // add 'const_reference' return type overload for each function below

	iterator begin() { return iterator(&_data[0]); }
	//iterator begin() { return iterator(_data); }

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
            // reallocate
            if (_capacity < v.size())
                reserve(v.size());
            // copy values
            for (size_type i = 0; i < v.size(); i++)
                _data[i] = v.at(i);
            // destroy unused left values
            for (size_type i = v.size(); i < _size; i++)
                _alloc.destroy(&_data[i]);
            // update size
            _size = v.size();
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

    // TODO
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

#endif /* FT_VECTOR_H */
