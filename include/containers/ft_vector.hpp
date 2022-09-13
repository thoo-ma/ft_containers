#ifndef FT_VECTOR_H
#define FT_VECTOR_H 1

#include <iostream> // remove
#include <cstring> // std::memmove (cf. erase)
#include <memory> // std::allocator
#include <stdexcept> // std::out_of_range --> rewrite it for namespace ft ?
#include <algorithm> // std:max

#include "ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_lexicographical_compare.hpp"
#include "ft_reverse_iterator.hpp"
//#include "ft_random_access_iterator.hpp"

///
/// \file ft_vector.hpp
///

/// @todo bien templater les iterateurs en arguments de certaines fonctions
///       (assert, assign, etc.)
/// @todo ne jamais set _capacity ou _size avant d'avoir appele allocate()
/// @todo bien gerer les allocations et les exceptions
/// @todo prendre en compte `size_max`` pour jeter les exceptions appropriees
/// @todo private: _allocate_and_copy() pour eviter les redites
/// @todo (?) add some private functions like STL (like internal primitives for
///       public methods). ex: _reallocate_and_copy(position, n, first, last)
///       def: reallocate n * sizeof(T) at position and copy there values
///            inside [first,last)
/// @todo (?) use `_first` and `_finish` instead of `_size`
/// @todo (?) why can we write `vector` instead of `vector<value_type>`
/// @todo (?) why can we access private variable of vector passed as arguments
/// @todo (?) `val` vs `value`

namespace ft {

///
/// \brief vector class
///

template <class T, class Allocator = std::allocator<T> >
class vector {

    /**************************************************************************/
    /*                                                                        */
    /*      Member types                                                      */
    /*                                                                        */
    /**************************************************************************/

    public:

    /// @note Those types: 'value_type', 'difference_type', 'pointer',
    /// 'reference', could also be defined from `ft_iterator_base_types.hpp` or
    /// from 'std::allocator' (it is defined this way into ISO standard).

    typedef T           value_type;
    typedef Allocator   allocator_type;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef T &         reference;
    typedef const T &   const_reference;
    typedef T *         pointer;
    typedef const T *   const_pointer;

    /**************************************************************************/
    /*                                                                        */
    /*      Vector iterator                                                   */
    /*                                                                        */
    /**************************************************************************/

    /*
    *	TODO
    *
    *	We need 2 more requirments:
    *
    *	1. iterator always pointing to same type than underlying container
    *	    --> NO ft::vector<A>::iterator<B> it;
    *	2. only declare an iterator inside a container namespace
    *	    --> NO ft::vector_iterator<A> it;
    *       --> seems inevitable if iterator class defined outside of container
    *
    *   Solutions
    *
    *   1. do not template `vector_iterator`
    *   2. rename `vector_iterator` into `iterator`
    *
    */

    template <typename U = T> // delete ?
    class vector_iterator : public iterator<random_access_iterator_tag, U>
    //class vector_iterator : public iterator<random_access_iterator_tag, T>
    {
        /****** Member types **************************************************/

        public:

        typedef iterator_traits<vector_iterator>	    traits;
        typedef typename traits::iterator_category      iterator_category;
        typedef typename traits::value_type             value_type;
        typedef typename traits::difference_type        difference_type;
        typedef typename traits::pointer	            pointer;
        typedef typename traits::reference	            reference;

        /****** Private data **************************************************/

        private: pointer _data;

        /****** Constructors **************************************************/

        public:

        vector_iterator () : _data(NULL) { }

        explicit vector_iterator (pointer data) : _data(data) { }

        vector_iterator (const vector_iterator<T> & it) : _data(&(*it))
        { }

        vector_iterator (const vector_iterator<const T> & it) : _data(&(*it))
        { }

        /****** Operators *****************************************************/

        vector_iterator & operator= (const vector_iterator & it)
        { _data = it._data; return *this; }

        reference operator* () const
        { return *_data; }

        pointer operator-> () const
        { return _data; }

        bool operator== (const vector_iterator<T> & it) const
        {
       //     std::cout << "ici" << std::endl;
            return _data == &(*it);
        }

        bool operator== (const vector_iterator<const T> & it) const
        {
        //    std::cout << "ici" << std::endl;
            return _data == &(*it);
        }

        bool operator!= (const vector_iterator<T> & it) const
        { return _data != &(*it); }

        bool operator!= (const vector_iterator<const T> & it) const
        { return _data != &(*it); }

        /// @note prefix
        vector_iterator & operator++ ()
        { ++_data; return *this; }

        /// @note prefix
        vector_iterator & operator-- ()
        { --_data; return *this; }

        /// @note postfix
        vector_iterator operator++ (int)
        { vector_iterator tmp(*this); operator++(); return tmp; }

        /// @note postfix
        vector_iterator operator-- (int)
        { vector_iterator tmp(*this); operator--(); return tmp; }

        vector_iterator & operator+= (const difference_type n)
        {
            /// @todo Why not delete `const` attribute to `n` ? Hence `m` would
            /// be useless (this also apply upon following operators)
            difference_type m = n;
            if (m >= 0) { while (m--) ++(*this); }
            else        { while (m++) --(*this); }
            return *this;
        }

        vector_iterator & operator-= (const difference_type & n)
        { return operator+=(-n); }

        vector_iterator operator+ (const difference_type & n) const
        { return vector_iterator(this->_data + n); }

        vector_iterator operator- (const difference_type & n) const
        { return operator+(-n); }

        difference_type operator- (const vector_iterator<T> & rhs) const
        { return _data > &(*rhs) ? _data - &(*rhs) : -(&(*rhs) - _data); }
       // { return max(_data, &(*rhs)) - min(_data, &(*rhs)); }

        difference_type operator- (const vector_iterator<const T> & rhs) const
        { return _data > &(*rhs) ? _data - &(*rhs) : -(&(*rhs) - _data); }
       // { return max(_data, &(*rhs)) - min(_data, &(*rhs)); }

        value_type & operator[] (const difference_type n) const
        { return this->_data[n]; }

        bool operator< (const vector_iterator<T> & rhs) const
        { return *this - rhs < 0; }

        bool operator< (const vector_iterator<const T> & rhs) const
        { return *this - rhs < 0; }

        bool operator> (const vector_iterator<T> & rhs) const
        { return rhs < *this; }

        bool operator> (const vector_iterator<const T> & rhs) const
        { return rhs < *this; }

        bool operator<= (const vector_iterator<T> & rhs) const
        { return !(*this > rhs); }

        bool operator<= (const vector_iterator<const T> & rhs) const
        { return !(*this > rhs); }

        bool operator>= (const vector_iterator<T> & rhs) const
        { return !(*this < rhs); }

        bool operator>= (const vector_iterator<const T> & rhs) const
        { return !(*this < rhs); }

    };

    typedef vector_iterator<value_type>	        iterator;
    typedef vector_iterator<value_type const>	const_iterator;

    // namespace below is mandatory since typedef operands share the same name
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    /// @todo rename `T *` into `pointer`
    T *             _data;
    size_type	    _size;
    size_type       _capacity;
    /// @todo Arbitrary initialized at allocator_type.max_size()
    /// cf. https://stackoverflow.com/questions/3813124/c-vector-max-size
    size_type       _max_size;
    allocator_type  _alloc;

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Constructors ******************************************************/

    /// @brief Constructor by default
    /// @todo  add 'explicit' qualifier ?
    vector (const allocator_type & alloc = allocator_type())
    : _data(NULL), _size(0), _capacity(0), _max_size(alloc.max_size()),
        _alloc(alloc) { }

    /// @brief by fill
    /// @todo  add 'explicit' qualifier ?
    vector ( size_type n, const value_type & val = value_type(),
        const allocator_type & alloc = allocator_type()
    ) : _size(n), _capacity(n), _max_size(alloc.max_size()), _alloc(alloc)
    {
        if (n)
        {
            try {
                _data = _alloc.allocate(_size);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(&_data[i], val); // assign
            }
            /// @todo log ?
            catch (std::bad_alloc & ba) { std::cout << ba.what() << std::endl; }
        }
        else { _data = NULL; }
    }

    /// @brief Constructor by iterator range
    // template <class InputIterator>
    // vector (InputIterator first, InputIterator last,
    // const allocator_type & alloc = allocator_type())
    vector ( iterator first, iterator last,
        const allocator_type & alloc = allocator_type()
    ) : _alloc(alloc)//, _max_size(alloc.max_size()) // why? cf. -Wreorder
    {
        _size = last - first;
        _size ? _data = _alloc.allocate(_size) : _data = NULL;
        for (size_type i = 0; i < _size; i++)
            _alloc.construct(&_data[i], *(first++));
        _capacity = _size;
    }

    /// @brief Constructor by copy
    vector (const vector<value_type, allocator_type> & v)
    : _size(0), _capacity(0), _max_size(v.max_size()), _alloc(v._alloc)
    //: _size(v.size()), _capacity(v.capacity()), _max_size(v.max_size()), _alloc(v._alloc)
    { *this = v; }

    /****** Destructor ********************************************************/

    ~vector ()
    {
        for (size_type i = 0; i < _size; i++) { _alloc.destroy(&_data[i]); }
        if (_capacity) _alloc.deallocate(_data, _capacity);
    }

    /****** Element access ****************************************************/

    reference at (size_type n)
    { if (n < _size) return _data[n]; else throw std::out_of_range(""); }
    //{ return n < _size ? _data[n] : throw std::out_of_range(""); }

    const_reference at (size_type n) const
    { if (n < _size) return _data[n]; else throw std::out_of_range(""); }

    /// @note defined behavior if vector is empty
    reference front ()
    { return _data[0]; }

    /// @note defined behavior if vector is empty
    const_reference front () const
    { return _data[0]; }

    /// @note defined behavior if vector is empty
    reference back ()
    { return _data[_size - 1]; }

    /// @note defined behavior if vector is empty
    const_reference back () const
    { return _data[_size - 1]; }

    /// @todo add ? (c++11)
    // pointer data () { return _data; }

    /****** Capacity **********************************************************/

    bool        empty ()     const    { return _size ? false : true;  }
    size_type   size ()      const    { return _size;                 }
    size_type   max_size ()  const    { return _max_size;             }
    size_type   capacity ()  const    { return _capacity;             }


    /// @note stl version
    // void reserve (size_type n)
    // {
    //     if (n > this->max_size())
    //         __throw_length_error(__N("vector::reserve"));
    //     if (this->capacity() < n)
    //     {
    //         const size_type old_size = size();
    //   	    pointer tmp = _M_allocate_and_copy(n,this->_M_impl._M_start,
    //                                             this->_M_impl._M_finish);
    //   	    std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
    //           		    _M_get_Tp_allocator());
   	//         _M_deallocate(this->_M_impl._M_start,this->_M_impl._M_end_of_storage
   	// 	                - this->_M_impl._M_start);
   	//         this->_M_impl._M_start = tmp;
   	//         this->_M_impl._M_finish = tmp + old_size;
   	//         this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
   	//     }
    // }

    void reserve (size_type n)
    {
        if (n > _max_size) throw std::length_error("vector::reserve");
        if (_capacity < n)
        {
            // reallocate
            pointer tmp = _alloc.allocate(n);
            // copy
            for (size_type i = 0; i < size(); i++)
                _alloc.construct(&tmp[i], at(i));
            // save size
            size_type size = _size;
            // destroy (reset size at 0 !)
            if (_size) clear();
            // update size
            _size = size;
            // deallocate
            // (`if` needed : otherwise double free can happen)
            if (_capacity) _alloc.deallocate(_data, _capacity);
            // update capacity
            _capacity = n;
            // update pointer to internal array
            _data = tmp;
        }
    }

    /****** Modifiers *********************************************************/

    void clear ()
    { erase(begin(), end()); } // x2000
    //{ for (size_type i = 0; i < _size; i++) { _alloc.destroy(_data + i); } _size = 0; } // x2000

    /// @brief Insert by single element (1)
    iterator insert (iterator position, const value_type & val)
    {
        size_type offset = position - begin();
        insert(position, 1, val);
        return begin() + offset;
    }

    /// @brief Insert by fill (2)
    void insert (iterator position, size_type n, const value_type & val)
    {
        // reallocate
        if (_size + n > _capacity)
        {
            // because of reallocation, position need to be reset
            size_type offset = position - begin();
            reserve((_size + n) * 2); // remove *2 and we have terrible perfs
            position = begin() + offset;
        }
        // insert
        for (size_type i = 0; i < n; i++)
        {
            _alloc.construct(&_data[_size++], _data[position - begin() + i]);
            _data[position - begin() + i] = val;
        }
    }

    /// @brief Insert by range (3)
    //template <class InputIterator>
    //insert (iterator position, InputIterator first, InputIterator last)
    void insert (iterator position, iterator first, iterator last)
    {
        // reallocate
        if (_capacity - _size < static_cast<size_type>(last - first))
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

    /// @brief Erase by position
    iterator erase (iterator position)
    { return (erase(position, position + 1)); }

    /// @brief Erase by range (x24)
//    iterator
//    erase (iterator first, iterator last)
//    {
//        // 1. Utils variables (avoid futur computation)
//        difference_type start = first - begin();
//        difference_type finish = last - begin();
//
//        // 2. Detroy elements in range [first, last)
//        for (difference_type i = start; i < finish; i++)
//            _alloc.destroy(&_data[i]);
//
//        // 3. Move elements from [last, enf) to [first, ...)
//        for (difference_type i = finish; i < static_cast<difference_type>(_size); i++)
//        {
//            if (start >= finish)
//                 _data[start++] = _data[i];
//            else
//            {
//                _alloc.construct(&_data[start++], _data[i]);
//                _alloc.destroy(&_data[i]);
//            }
//        }
//
//        // 4. Update size
//        _size = start;
//
//        // 5. return
//        return first;
//    }

    /// @brief Erase by range (x27)
    iterator erase (iterator first, iterator last)
    {
       // 1. Utils variables (avoid futur computation)
       difference_type start = first - begin();
       difference_type finish = last - begin();

       // 2. Copy elements than can be copied
       difference_type i = finish;
       while (i < static_cast<difference_type>(_size) && start < finish)
           _data[start++] = _data[i++];

       // 3. Destroy elements not copied to [first, last) until end
       while (start < static_cast<difference_type>(_size))
           _alloc.destroy(&_data[start++]);

       // 4. update size
       _size = (first - begin()) + (end() - last);

       // 5. return
       return first;
    }

    /// @brief Erase by range (incredible performances !!)
    /// @note  cf. https://github.com/ojoubout/ft_containers/blob/main/Vector/Vector.hpp
    /// @note  can raise -Wclass-memaccess warning at compile time
   // iterator
   // erase (iterator first, iterator last)
   // {
   //     size_type pos = first - begin();
   //     size_type len = last - first;
   //     std::memmove(_data + pos, _data + pos + len, (_size - pos - len) * sizeof(value_type));
   //     _size -= len;
   //     return first;
   // }

    void push_back (const value_type & value)
    { insert(end(), value); }

    void pop_back ()
    { if (_size) _alloc.destroy(&_data[_size--]); }

    void resize (size_type n, value_type value = value_type())
    {
        if (n < _size) return (void)(erase(iterator(&_data[n]), end()));
        if (n > _size) return insert(iterator(&_data[_size]), n, value);
    }

    void swap (vector & v)
    {
        // `this` to tmp
        pointer data = _data;
        size_type size = _size;
        size_type capacity = _capacity;

        // `v` to `this`
        _data = v._data;
        _size = v.size();
        _capacity = v.capacity();

        // tmp to `v`
        v._data = data;
        v._size = size;
        v._capacity = capacity;
    }

    /// @brief Assign by range
//    template <typename InputIterator>
//    void assign(InputIterator first, InputIterator last)
    void assign (iterator first, iterator last)
    {
        erase(begin(), end());
        insert(begin(), first, last);
    }

    /// @brief Assign by fill
    void assign (size_type n, const value_type & value)
    {
        erase(begin(), end());
        insert(begin(), n, value);
    }

    /****** Iterators *********************************************************/

	iterator begin ()
    { return iterator(_data); }

	const_iterator begin () const
    { return const_iterator(_data); }

	iterator end ()
    { return iterator(&_data[_size]); }

	const_iterator end () const
    { return const_iterator(&_data[_size]); }

	reverse_iterator rbegin ()
    { return reverse_iterator(--end()); }

	const_reverse_iterator rbegin () const
    { return const_reverse_iterator(--end()); }

	reverse_iterator rend ()
    { return reverse_iterator(--begin()); }

	const_reverse_iterator rend () const
    { return const_reverse_iterator(--begin()); }

    /****** Operators *********************************************************/

    vector<value_type, allocator_type> &
    operator= (const vector<value_type, allocator_type> & v)
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

    /// @note doesn't check boundaries
    reference operator[] (size_type n)
    { return _data[n]; }

    /// @note doesn't check boundaries
    const_reference operator[] (size_type n) const
    { return _data[n]; }

    /****** Miscellaneous *****************************************************/

    allocator_type get_allocator() const { return _alloc; }

};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

/// @todo add constness to lhs and rhs
template <class T, class Alloc>
bool operator== (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++) {
        if (lhs.at(i) != rhs.at(i))
            return false;
    }
    return true;
//    return
//    lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/// @todo add constness to lhs and rhs
template <class T, class Alloc>
bool operator!= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{ return !(lhs == rhs); }

/// @todo add constness to lhs and rhs
template <class T, class Alloc>
bool operator< (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
    return
    lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// @todo add constness to lhs and rhs
template <class T, class Alloc>
bool operator> (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{ return rhs < lhs; }

/// @todo add constness to lhs and rhs
template <class T, class Alloc>
bool operator<= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{ return !(lhs > rhs); }

/// @todo add constness to lhs and rhs
template <class T, class Alloc>
bool operator>= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{ return !(lhs < rhs); }

} // namespace ft

#endif /* FT_VECTOR_H */
