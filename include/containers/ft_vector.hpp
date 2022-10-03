#ifndef FT_VECTOR_H
#define FT_VECTOR_H 1

#include <memory> // std::allocator
#include <stdexcept> // std::out_of_range
#include <cstring> // std::memmove (cf. erase)

#include "ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_lexicographical_compare.hpp"

/// @todo template iterator arguments (assert, assign, etc.)
/// @todo throw appropriate exception (out_of_bound) when `size_max` reached
/// @todo (?) add some private functions like stl: _(re)allocate_and_copy, etc.
/// @todo (?) use `_first` and `_finish` instead of `_size`
/// @todo (?) why can we write `vector` instead of `vector<value_type>`
/// @todo (?) why can we access private variable of vector passed as arguments
/// @todo (?) do not set _capacity nor _size before calling allocate()

namespace ft {

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
    typedef T const &   const_reference;
    typedef T *         pointer;
    typedef T const *   const_pointer;

    /**************************************************************************/
    /*                                                                        */
    /*      Vector iterator                                                   */
    /*                                                                        */
    /**************************************************************************/

    /// @note The following `private` attribute is not well supported by all
    ///       compilers. At 42 Paris, we currently use clang++ 12 that _does_ 
    ///       _support_ private templated nested classes. Further informations
    ///       about this widely spreaded compiler bug at the following this link
    ///       https://stackoverflow.com/questions/3784652

    private:

    /// @todo put std iterator flags into 'ft_iterator_base_types.hpp'
    template <typename U>
    //class vector_iterator : public iterator<random_access_iterator_tag, U>
    class vector_iterator : public iterator<std::random_access_iterator_tag, U>
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

        vector_iterator (vector_iterator<T> const & it) : _data(&(*it))
        { }

        vector_iterator (vector_iterator<T const> const & it) : _data(&(*it))
        { }

        /****** Operators *****************************************************/

        vector_iterator & operator= (vector_iterator const & it)
        { _data = it._data; return *this; }

        reference operator* () const
        { return *_data; }

        pointer operator-> () const
        { return _data; }

        bool operator== (vector_iterator<T> const & it) const
        { return _data == &(*it); }

        bool operator== (vector_iterator<T const> const & it) const
        { return _data == &(*it); }

        bool operator!= (vector_iterator<T> const & it) const
        { return _data != &(*it); }

        bool operator!= (vector_iterator<T const> const & it) const
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

        vector_iterator & operator+= (difference_type const n)
        {
            /// @todo Why not delete `const` attribute to `n` ? Hence `m` would
            /// be useless (this also apply upon following operators)
            difference_type m = n;
            if (m >= 0) { while (m--) ++(*this); }
            else        { while (m++) --(*this); }
            return *this;
        }

        vector_iterator & operator-= (difference_type const & n)
        { return operator+=(-n); }

        vector_iterator operator+ (difference_type const & n) const
        { return vector_iterator(this->_data + n); }

        vector_iterator operator- (difference_type const & n) const
        { return operator+(-n); }

        difference_type operator- (vector_iterator<T> const & rhs) const
        { return _data > &(*rhs) ? _data - &(*rhs) : -(&(*rhs) - _data); }
       // { return max(_data, &(*rhs)) - min(_data, &(*rhs)); }

        difference_type operator- (vector_iterator<T const> const & rhs) const
        { return _data > &(*rhs) ? _data - &(*rhs) : -(&(*rhs) - _data); }
       // { return max(_data, &(*rhs)) - min(_data, &(*rhs)); }

        value_type & operator[] (difference_type const n) const
        { return this->_data[n]; }

        bool operator< (vector_iterator<T> const & rhs) const
        { return *this - rhs < 0; }

        bool operator< (vector_iterator<T const> const & rhs) const
        { return *this - rhs < 0; }

        bool operator> (vector_iterator<T> const & rhs) const
        { return rhs < *this; }

        bool operator> (vector_iterator<T const> const & rhs) const
        { return rhs < *this; }

        bool operator<= (vector_iterator<T> const & rhs) const
        { return !(*this > rhs); }

        bool operator<= (vector_iterator<T const> const & rhs) const
        { return !(*this > rhs); }

        bool operator>= (vector_iterator<T> const & rhs) const
        { return !(*this < rhs); }

        bool operator>= (vector_iterator<T const> const & rhs) const
        { return !(*this < rhs); }

    };

    public:

    typedef vector_iterator<value_type>	        iterator;
    typedef vector_iterator<value_type const>	const_iterator;

    /// @note namespace mandatory since typedef operands share the same name
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    pointer         _data;
    size_type	    _size;
    size_type       _capacity;
    size_type       _max_size;// cf. https://stackoverflow.com/questions/3813124
    allocator_type  _alloc;

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Constructors ******************************************************/

    /// @brief Constructor by default (1)
    /// @todo  add 'explicit' qualifier ?
    vector (allocator_type const & alloc = allocator_type())
    : _data(NULL), _size(0), _capacity(0), _max_size(alloc.max_size()),
        _alloc(alloc) { }

    /// @brief Constructor by fill (2)
    /// @todo  add 'explicit' qualifier ?
    vector (size_type n, value_type const & val = value_type(),
        allocator_type const & alloc = allocator_type()
    ) : _size(n), _capacity(n), _max_size(alloc.max_size()), _alloc(alloc)
    {
        if (n)
        {
            _data = _alloc.allocate(_size);
            for (size_type i = 0; i < _size; i++)
                _alloc.construct(&_data[i], val);
        }
        else { _data = NULL; }
    }

    /// @brief Constructor by iterator range (3)
    /// @todo bad_alloc not well thrown and catched (same for std)
    template <class InputIterator>
    vector (InputIterator first, InputIterator last,
    allocator_type const & alloc = allocator_type(),
    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0
    ) : _alloc(alloc)
    {
        _size = 0;
        for (InputIterator it = first; it != last; it++)
            _size++;
        _size ? _data = _alloc.allocate(_size) : _data = NULL;
        for (size_type i = 0; i < _size; i++)
            _alloc.construct(&_data[i], *(first++));
        _capacity = _size;
    }

    /// @brief Constructor by copy (4)
    vector (vector<value_type, allocator_type> const & v)
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

    const_reference at (size_type n) const
    { if (n < _size) return _data[n]; else throw std::out_of_range(""); }

    /// @note undefined behavior if vector is empty
    reference front ()
    { return _data[0]; }

    /// @note undefined behavior if vector is empty
    const_reference front () const
    { return _data[0]; }

    /// @note undefined behavior if vector is empty
    reference back ()
    { return _data[_size - 1]; }

    /// @note undefined behavior if vector is empty
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
    iterator insert (iterator position, value_type const & val)
    {
        size_type offset = position - begin();
        insert(position, 1, val);
        return begin() + offset;
    }

    /// @brief Insert by fill (2)
    void insert (iterator position, size_type n, value_type const & val)
    {
        // reallocate
        if (_size + n > _capacity)
        {
            // because of reallocation, position need to be reset
            size_type offset = position - begin();
            reserve((_size + n) * 2); // remove *2 and we have terrible perfs
            position = begin() + offset;
        }

        // move what is after inserted range at the end
        for (size_type i = end() - position, j = n; i > 0; i--, j--)
            _data[_size - 1 + j] = _data[_size - 1 + j - n];

        // insert
        for (size_type i = 0; i < n; i++, position++, _size++)
            _data[position - begin()] = val;
    }

    /// @brief Insert by range (3)
   // void insert (iterator position, iterator first, iterator last)
   // {
   //     // reallocate
   //     if (_capacity - _size < static_cast<size_type>(last - first))
   //     {
   //         // because of reallocation, position need to be reset
   //         size_type pos = position - begin();
   //         reserve(_size + (last - first));
   //         position = begin() + pos;
   //     }
   //     // insert
   //     while (first != last)
   //     {
   //         _data[_size] = *position;
   //         _data[position - begin()] = *first;
   //         first++;
   //         position++;
   //         _size++;
   //     }
   // }

    /// @todo why `type*` instead of `type` for enable_if unless constructor (3)
    /// @brief Insert by range (3)
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
    {
        // get range distance
        size_type n = 0;
        InputIterator it = first;
        while (it++ != last) n++;

        // reallocate if needed
        if (n > _capacity - _size)
        {
            // because of reallocation, position need to be reset
            size_type pos = position - begin();
            reserve(_size + n);
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

    void push_back (value_type const & value)
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

    /// @todo why `type*` instead of `type`
    /// @brief Assign by range (1)
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
    {
        erase(begin(), end());
        insert(begin(), first, last);
    }

    /// @brief Assign by fill (2)
    void assign (size_type n, value_type const & value)
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
    operator= (vector<value_type, allocator_type> const & v)
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

/// @todo
template <class T, class Alloc>
bool operator== (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
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

template <class T, class Alloc>
bool operator!= (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return !(lhs == rhs); }

template <class T, class Alloc>
bool operator< (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{
    return
    lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator> (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return rhs < lhs; }

template <class T, class Alloc>
bool operator<= (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return !(lhs > rhs); }

template <class T, class Alloc>
bool operator>= (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return !(lhs < rhs); }

} // namespace ft

#endif /* FT_VECTOR_H */