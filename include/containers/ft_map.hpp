#ifndef FT_MAP_HPP
#define FT_MAP_HPP 1

#include <memory> // std::allocator
#include <functional> // std::less

#include "ft_pair.hpp"
#include "rb_tree.hpp"
#include "ft_bidirectional_iterator.hpp"
#include "ft_iterator_base_types.hpp"

// TODO pointer as value_type * instead of T *

namespace ft {

template <typename Key,
          typename T,
          typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>> // ft::pair
          //typename Allocator = std::allocator<ft::pair<const Key, T>>
> class map
{
    /**************************************************************************/
    /*                                                                        */
    /*      Member types                                                      */
    /*                                                                        */
    /**************************************************************************/

    public:

    typedef Key	                key_type;
    typedef T	                mapped_type;
    typedef pair<const Key, T>	value_type;
    typedef Compare	            key_compare;
    //typedef key_compare  value_compare;
    typedef Allocator           allocator_type;
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;
    typedef T &                 reference;
    typedef const T &           const_reference;
    typedef T *                 pointer;
    typedef const T *           const_pointer;

    template <typename U>
    class map_iterator : public iterator<bidirectional_iterator_tag, U>
    {
        typedef iterator_traits<map_iterator>	    traits;
        typedef typename traits::iterator_category  iterator_category;
        typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        typedef typename traits::pointer	        pointer;
        typedef typename traits::reference	        reference;

        private: pointer _data;

        public:

        map_iterator()	                        : _data(NULL)      { }
        map_iterator(pointer data)	            : _data(data)      { }
        map_iterator(const map_iterator & it)	: _data(it._data)  { }

        reference operator=(const map_iterator & it);
        reference operator*() const;
        //reference operator->() const;
        bool operator==(const map_iterator & it) const;
        bool operator!=(const map_iterator & it) const;
        map_iterator & operator++();
        map_iterator operator++(int);
        map_iterator & operator--();
        map_iterator operator--(int);

    };

    typedef map_iterator<value_type>	    iterator;
    typedef map_iterator<const value_type>	const_iterator;
    //typedef reverse_iterator<iterator> reverse_iterator;
    //typedef reverse_iterator<const_iterator> const_reverse_iterator;

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    allocator_type	    _alloc;
    key_compare	        _comp;
    rb_tree<value_type>	_tree;

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Constructors ******************************************************/

    // empty (1)
    explicit map (const key_compare & comp = key_compare(),
              const allocator_type & alloc = allocator_type())
    : _alloc(alloc), _comp(comp) { }

    // range (2)
    //template <class InputIterator>
    //map (InputIterator first, InputIterator last,
    map (iterator first, iterator last,
       const key_compare & comp = key_compare(),
       const allocator_type & alloc = allocator_type());

    // copy (3)
    map (const map & a) : _alloc(a._alloc), _comp(a._comp), _tree(a._tree) { }

    /****** Destructor ********************************************************/

    ~map() { }

    /****** Element access ****************************************************/

  //  mapped_type & operator[] (const key_type & key)
  //  {
  //      value_type * val = _tree.find(_tree.root_node(), key);
  //      return val ? val->second : insert(val)->second;
  //  }

    /****** Capacity **********************************************************/

    bool empty() const { return _tree.root_node() == NULL; }
    size_type size() const { return _tree.size(); }
    size_type max_size() const;

    /****** Modifiers *********************************************************/

    // insert single element (1)
    pair<iterator, bool> insert (const value_type & val)
    {
        return find(val.key) != end()
        ? pair<iterator, bool>(end(), false)
        : pair<iterator, bool>(iterator(), true);
        //: pair<iterator, bool>(iterator(_tree.insert(&_tree._root, val)), true);
    }

    // insert with hint (2)
    iterator insert (iterator position, const value_type & val);

    // insert range (3)
    //template <class InputIterator>
    //void insert (InputIterator first, InputIterator last);
    void insert (iterator first, iterator last);
    // while (first != last) insert((*first)++);

    // erase by iterator position (1)
    void erase (iterator position);

    // erase by key (2)
    size_type erase (const key_type & key);

    // erase by iterator range (3)
    void erase (iterator first, iterator last);

    void swap (map & m);

    //void clear (); { erase(begin(), end()); }

    /****** Observers *********************************************************/

    key_compare key_comp () const { return _comp; }

    //value_compare value_comp () const;

    /****** Iterators *********************************************************/

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    //reverse_iterator rbegin();
    //const_reverse_iterator rbegin() const;
    //reverse_iterator rend();
    //const_reverse_iterator rend() const;

    /****** Operations ********************************************************/

  //  iterator find (const key_type & key) { return iterator(_tree.find(_tree.root(), key)); }
    const_iterator find (const key_type & key) const;

    size_type count (const key_type & key);

    iterator lower_bound (const key_type & key);
    const_iterator lower_bound (const key_type & key) const;

    iterator upper_bound (const key_type & key);
    const_iterator upper_bound (const key_type & key) const;

    pair<iterator, iterator>
    equal_range (const key_type & key);

    pair<const_iterator, const_iterator>
    equal_range (const key_type & key) const;

    /****** Miscellaneous *****************************************************/

    allocator_type get_allocator () const { return _alloc; }

    map & operator= (const map & m);

};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

} // namespace

#endif /* FT_MAP_HPP */