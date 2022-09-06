#ifndef FT_MAP_HPP
#define FT_MAP_HPP 1

#include <memory> // std::allocator
#include <functional> // std::less

#include "ft_pair.hpp"
#include "rb_tree.hpp"
#include "ft_type_traits.hpp" // ??

namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<pair<typename ft::add_const<Key>::type, T>>
          //typename Allocator = std::allocator<std::pair<typename ft::add_const<Key>::type, T>>
          //typename Allocator = std::allocator<std::pair<const Key, T>>
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
    typedef pair<Key const, T>	value_type;
    typedef Compare	            key_compare;
    //typedef key_compare  value_compare;
    typedef Allocator           allocator_type;
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;
    typedef value_type &        reference;
    typedef const value_type &  const_reference;
    typedef value_type *        pointer;
    typedef const value_type *  const_pointer;

    /// @note just to shorten typedefs below
    private: typedef rb_tree<value_type> btree_type;

    public:

  //  typename rb_tree<value_type>::iterator iterator;
  //  typename rb_tree<value_type>::const_iterator const_iterator;

    // old
    typedef typename btree_type::iterator	            iterator;
    typedef typename btree_type::const_iterator         const_iterator;
    typedef typename btree_type::reverse_iterator       reverse_iterator;
    typedef typename btree_type::const_reverse_iterator const_reverse_iterator;

    // new (test)
  //  class iterator : public rb_tree<value_type>::iterator
  //  { public: Key const & operator* () { return operator*()->key; } };

  //  class const_iterator : public rb_tree<value_type>::const_iterator
  //  { public: Key const & operator* () { return operator*()->key; } };

  //  typedef ft::reverse_iterator<iterator>          reverse_iterator;
  //  typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

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

    /// @brief empty (1)
    explicit map (const key_compare & comp = key_compare(),
              const allocator_type & alloc = allocator_type())
    : _alloc(alloc), _comp(comp) { }

    /// @brief range (2)
    /// @todo
    //template <class InputIterator>
    //map (InputIterator first, InputIterator last,
//    map (iterator first, iterator last,
//        const key_compare & comp = key_compare(),
//        const allocator_type & alloc = allocator_type())
//    : _alloc(alloc), _comp(comp) { insert(first, last); }

    /// @brief copy (3)
    map (const map & a) : _alloc(a._alloc), _comp(a._comp), _tree(a._tree) { }

    /****** Destructor ********************************************************/

    ~map () { }

    /****** Element access ****************************************************/

///   @todo remove (c++11)
//    mapped_type & at (key_type const & k);
//    mapped_type const & at (key_type const & k) const;

    mapped_type & operator[] (const key_type & key)
    {

    }
    //{ return (*(insert(make_pair(key, mapped_type())).first)).second; }

    /****** Capacity **********************************************************/

    bool empty () const
    { return _tree.empty(); }

    size_type size () const
    { return _tree.size(); }

    /// @todo
    //  size_type max_size () const;

    /****** Modifiers *********************************************************/

    /// @todo remove
  //  void insert (value_type const & val)
  //  { return _tree.insert(_tree.root_node(), val); }

    /// @brief insert single element (1)
    pair<iterator, bool> insert (value_type const & val)
    {
        //return find(val.first) == end()
        //? make_pair(_tree.insert(_tree.root_node(), val), true)
        //: make_pair(end(), false);

        if (find(val.first) == end())
        {
            _tree.insert(_tree.root_node(), val);
            return make_pair(iterator(find(val.first)), true);
        }
        return make_pair(end(), false);
    }

    /// @brief insert with hint (2)
    //iterator insert (iterator position, const value_type & val);

    /// @brief insert range (3)
    //template <class InputIterator>
    //void insert (InputIterator first, InputIterator last);
//    void insert (iterator first, iterator last)
//    { return _tree.insert(first, last); }

    /// @brief erase by iterator position (1)
    void erase (iterator position);

    /// @brief erase by key (2)
    size_type erase (const key_type & key);

    /// @brief erase by iterator range (3)
    void erase (iterator first, iterator last);

    /// @todo
    void swap (map & m);

    /// @todo
   //  void clear ()
   //  { erase(begin(), end()); }

    /****** Observers *********************************************************/

    key_compare key_comp () const
    { return _comp; }

    /// @todo
    //value_compare value_comp () const;

    /****** Iterators *********************************************************/

    iterator begin ()
    { return iterator(_tree.begin()); }

    const_iterator begin () const
    { return const_iterator(_tree.begin()); }

    iterator end ()
    { return iterator(_tree.end()); }

    const_iterator end () const
    { return const_iterator(_tree.end()); }

    reverse_iterator rbegin ()
    { return reverse_iterator(_tree.rbegin()); }

    const_reverse_iterator rbegin () const
    { return const_reverse_iterator(_tree.rbegin()); }

    reverse_iterator rend ()
    { return reverse_iterator(_tree.rend()); }

    const_reverse_iterator rend () const
    { return const_reverse_iterator(_tree.rend()); }

    /****** Operations ********************************************************/

    iterator find (const key_type & key)
    { return iterator(_tree.find(value_type(key, mapped_type()))); }

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

    /// @note since the following operator is defined outside of `map` but still
    /// want to acces its private members, we declare it here as a `friend`.
    template <typename Key_, typename T_, typename Comp_, typename Alloc_>
    friend bool operator== (map<Key_, T_, Comp_, Alloc_> & lhs,
                            map<Key_, T_, Comp_, Alloc_> & rhs);

};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

/// @todo add constness to lhs and rhs (then use const_iterators) -- cf rb_tree
template <typename Key, typename T, typename Comp, typename Alloc>
bool operator== (map<Key, T, Comp, Alloc> & lhs, map<Key, T, Comp, Alloc> & rhs)
{ return lhs._tree == rhs._tree; }

/// @todo add constness to lhs and rhs (then use const_iterators) -- cf rb_tree
template <typename Key, typename T, typename Comp, typename Alloc>
bool operator!= (map<Key, T, Comp, Alloc> & lhs, map<Key, T, Comp, Alloc> & rhs)
{ return !(lhs == rhs); }

} // namespace

#endif /* FT_MAP_HPP */
