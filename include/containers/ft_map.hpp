#ifndef FT_MAP_HPP
#define FT_MAP_HPP 1

#include <memory> // std::allocator
#include <functional> // std::less (delete since into rb_tree.hpp)

#include "ft_pair.hpp"
#include "rb_tree.hpp"
#include "ft_type_traits.hpp" // ??

namespace ft {

/// @note Allocator won't be used. This map uses rb_tree allocator.
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
    typedef Allocator           allocator_type; // not used
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;
    typedef value_type &        reference;
    typedef const value_type &  const_reference;
    typedef value_type *        pointer;
    typedef const value_type *  const_pointer;

    /// @note just to shorten typedefs below
    private: typedef rb_tree<value_type> btree_type;

    public:

    /// @note same semantic than tree for `operator *`
    typedef typename btree_type::iterator	            iterator;
    typedef typename btree_type::const_iterator         const_iterator;
    typedef typename btree_type::reverse_iterator       reverse_iterator;
    typedef typename btree_type::const_reverse_iterator const_reverse_iterator;

    /// @note different semantic than tree for `operator *`
//    class iterator : public rb_tree<value_type>::iterator
//    { public: Key const & operator* () { return operator*()->key; } };
//
//    class const_iterator : public rb_tree<value_type>::const_iterator
//    { public: Key const & operator* () { return operator*()->key; } };
//
//    typedef ft::reverse_iterator<iterator>          reverse_iterator;
//    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    //allocator_type	    _alloc; // this is not used
    typename btree_type::allocator_type	    _alloc;
    key_compare	        _comp;
    rb_tree<value_type>	_tree;
    //size_type           _max_size; // remove

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Constructors ******************************************************/

    /// @brief Constructor by default (1)
    explicit map (const key_compare & comp = key_compare(),
              const allocator_type & alloc = allocator_type())
    : _alloc(alloc), _comp(comp) { }

    /// @brief Constructor by range (2)
    /// @todo
    //template <class InputIterator>
    //map (InputIterator first, InputIterator last,
    map (iterator first, iterator last,
        const key_compare & comp = key_compare(),
        const allocator_type & alloc = allocator_type())
    : _alloc(alloc), _comp(comp) { insert(first, last); }

    /// @brief Constructor by copy (3)
    map (map const & a) : _alloc(a._alloc), _comp(a._comp), _tree(a._tree) { }

    /****** Destructor ********************************************************/

    ~map () { }

    /****** Element access ****************************************************/

///   @todo remove (c++11)
//    mapped_type & at (key_type const & k);
//    mapped_type const & at (key_type const & k) const;

    /// @todo
    //mapped_type & operator[] (const key_type & key)
    //{

    //}
    //{ return (*(insert(make_pair(key, mapped_type())).first)).second; }

    /****** Capacity **********************************************************/

    bool empty () const
    { return _tree.empty(); }

    size_type size () const
    { return _tree.size(); }

    /// @todo
    size_type max_size () const
    //{ return _max_size; }
    { return _tree.get_allocator().max_size(); }

    /****** Modifiers *********************************************************/

    /// @todo ??
  //  void insert (value_type const & val)
  //  { return _tree.insert(_tree.root(), val); }

    /// @brief Insert single element (1)
    /// @todo modify _tree.insert() return value to allow ternary below
    pair<iterator, bool> insert (value_type const & val)
    {
        //iterator it = find(val.first);
        //return it == end()
        //? make_pair(_tree.insert(val), true)
        //: make_pair(it, false);

        if (find(val.first) == end())
        {
            _tree.insert(val);
            return make_pair(iterator(find(val.first)), true);
            //return make_pair(find(val.first), true);
        }
        return make_pair(find(val.first), false);
    }

    /// @brief Insert with hint (2)
    iterator insert (iterator position, value_type const & val)
    { (void)position; insert(val); return find(val.first); }

    /// @brief Insert by iterator range (3)
    //template <class InputIterator>
    //void insert (InputIterator first, InputIterator last);
    void insert (iterator first, iterator last)
    { return _tree.insert(first, last); }

    /// @brief erase by iterator position (1)
    void erase (iterator position)
    { return _tree.erase(position); }

    /// @brief erase by key (2)
    /// @note always return 1 since our map doesn't support duplicated keys
    size_type erase (key_type const & key)
    { _tree.erase(value_type(key, mapped_type())); return 1; }

    /// @brief erase by iterator range (3)
    void erase (iterator first, iterator last)
    { return _tree.erase(first, last); }

    void swap (map & m)
    {
        map tmp(m);
        m = *this;
        *this = tmp;
    }

    void clear ()
    { erase(begin(), end()); }

    /****** Observers *********************************************************/

    /// @todo
    key_compare key_comp () const
    { return _comp; }
    //{ return _comp(); }

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

    /// @todo update following `operator*` and `operator->` iterator semantic
    iterator find (key_type const & key)
    {
        iterator it = begin();
        iterator ite = end();

        while (it != ite && it->first != key) it++;
        //while (it != ite && it->key.first != key) it++;
        return it;
    }

    /// @todo update following `operator*` and `operator->` iterator semantic
    const_iterator find (key_type const & key) const
    {
        const_iterator it = begin();
        const_iterator ite = end();

        while (it != ite && it->first != key) it++;
        //while (it != ite && it->key.first != key) it++;
        return it;
    }

    size_type count (key_type const & key)
    { return find(key) == end() ? 0 : 1; }

    /// @todo update following `operator*` and `operator->` iterator semantic
    iterator lower_bound (key_type const & key)
    {
        iterator it = begin();
        iterator ite = end();

        while (it != ite && _comp(it->key.first, key)) it++;
        return it;
    }

    /// @todo update following `operator*` and `operator->` iterator semantic
    const_iterator lower_bound (key_type const & key) const
    {
        const_iterator it = begin();
        const_iterator ite = end();

        while (it != ite && _comp(it->key.first, key)) it++;
        return it;
    }

    /// @todo update following `operator*` and `operator->` iterator semantic
    iterator upper_bound (key_type const & key)
    {
        iterator it = begin();
        iterator ite = end();

        while (it != ite && !_comp(key, it->key.first)) it++;
        return it;
    }

    /// @todo update following `operator*` and `operator->` iterator semantic
    const_iterator upper_bound (key_type const & key) const
    {
        const_iterator it = begin();
        const_iterator ite = end();

        while (it != ite && !_comp(key, it->key.first)) it++;
        return it;
    }

    pair<iterator, iterator>
    equal_range (key_type const & key)
    { return pair<iterator, iterator>(lower_bound(key), upper_bound(key)); }

    pair<const_iterator, const_iterator>
    equal_range (key_type const & key) const
    { return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)); }

    /****** Miscellaneous *****************************************************/

    allocator_type get_allocator () const
    //{ return _alloc; }
    { return _tree.get_allocator(); }

    map & operator= (const map & m)
    { _tree = m._tree; return *this; }

    /// @note since the following operator is defined outside of `map` but still
    /// want to acces its private members, we declare it here as a `friend`.
    template <typename Key_, typename T_, typename Comp_, typename Alloc_>
    friend bool operator== (map<Key_, T_, Comp_, Alloc_> const & lhs,
                            map<Key_, T_, Comp_, Alloc_> const & rhs);

};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

/// @note not possible to compare underlying tree since they are private and we
///       not allowed to add public methods from stl spec.
template <typename Key, typename T, typename Comp, typename Alloc>
bool operator== (map<Key, T, Comp, Alloc> const & lhs,
                 map<Key, T, Comp, Alloc> const & rhs)
{
    typename map<Key, T, Comp, Alloc>::const_iterator lit = lhs.begin();
    typename map<Key, T, Comp, Alloc>::const_iterator rit = rhs.begin();
    typename map<Key, T, Comp, Alloc>::const_iterator lite = lhs.end();
    typename map<Key, T, Comp, Alloc>::const_iterator rite = rhs.end();

    for (; lit != lite && rit != rite && *lit == *rit; lit++, rit++);
    return (lit == lite && rit == rite);
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator!= (map<Key, T, Comp, Alloc> const & lhs,
                 map<Key, T, Comp, Alloc> const & rhs)
{ return !(lhs == rhs); }

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator< (map<Key, T, Comp, Alloc> const & lhs,
                map<Key, T, Comp, Alloc> const & rhs)
{
    return
    lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator> (map<Key, T, Comp, Alloc> const & lhs,
                map<Key, T, Comp, Alloc> const & rhs)
{ return rhs < lhs; }

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator<= (map<Key, T, Comp, Alloc> const & lhs,
                 map<Key, T, Comp, Alloc> const & rhs)
{ return !(rhs < lhs); }

template <typename Key, typename T, typename Comp, typename Alloc>
bool operator>= (map<Key, T, Comp, Alloc> const & lhs,
                 map<Key, T, Comp, Alloc> const & rhs)
{ return !(lhs < rhs); }

} // namespace

#endif /* FT_MAP_HPP */
