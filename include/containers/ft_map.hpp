#ifndef FT_MAP_HPP
#define FT_MAP_HPP 1

#include <memory> // std::allocator
#include <functional> // std::less (delete since into rb_tree.hpp)

#include "ft_pair.hpp"
#include "rb_tree.hpp"
#include "ft_type_traits.hpp"

/// @todo std::add_const    --> ft::add_const
/// @todo std::remove_const --> ft::remove_const

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

    class value_compare; // forward declaration

    typedef Key	                key_type;
    typedef T	                mapped_type;
    typedef pair<Key const, T>	value_type;
    typedef Compare	            key_compare;
    typedef value_compare       value_compare;
    typedef Allocator           allocator_type; // not used
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;
    typedef value_type &        reference;
    typedef value_type const &  const_reference;
    typedef value_type *        pointer;
    typedef value_type const *  const_pointer;

    private:

    /// @note just some convenient typedefs
    typedef rb_tree<value_type, value_compare> btree_type;
    typedef typename btree_type::value_type     node_type;
    typedef typename btree_type::value_type &   node_reference;
    typedef typename btree_type::value_type *   node_pointer;


    template <typename U = T>
    class map_iterator : public iterator<bidirectional_iterator_tag, U>
    {
        public:

        typedef iterator_traits<map_iterator>       traits; // to shorten below
        typedef typename traits::iterator_category  iterator_category;
        typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        typedef typename traits::pointer	        pointer;
        typedef typename traits::reference	        reference;

        private:

        node_pointer _current;
        node_pointer _sentinel;

        public:

        /// @brief Constructor by default
        map_iterator (node_pointer current = NULL, node_pointer sentinel = NULL)
        :_current(current), _sentinel(sentinel)
        { }

        /// @brief Constructor by copy from mutable iterator
        map_iterator (map_iterator<typename std::remove_const<value_type>::type> const & it)
        : _current(it.current_node()),
         _sentinel(const_cast<node_pointer>(it.sentinel_node()))
        { }

        /// @brief Constructor by copy from const iterator
        map_iterator (map_iterator<typename std::add_const<value_type>::type> const & it)
        : _current(const_cast<node_pointer>(it.current_node())),
         _sentinel(const_cast<node_pointer>(it.sentinel_node()))
        { }

        map_iterator operator= (map_iterator const & it)
        {
            _current = it.current_node();
            _sentinel = it.sentinel_node();
            return *this;
        }

        reference operator* () const
        { return _current->key; }

        pointer operator-> () const
        { return &_current->key; }

        bool operator== (map_iterator const & it) const
        { return _current == it.current_node(); }

    //    bool operator== (map_iterator<value_type> const & it) const
    //    { return _current == it.current_node(); }

    //    bool operator== (map_iterator<value_type const> const & it) const
    //    { return _current == it.current_node(); }

        bool operator!= (map_iterator const & it) const
        { return !(*this == it); }

       // bool operator!= (map_iterator<value_type> const & it) const
       // { return !(*this == it); }

       // bool operator!= (map_iterator<value_type const> const & it) const
       // { return !(*this == it); }

        /// @brief prefix incerement
        map_iterator & operator++ ()
        {
            // case 1: next node is min(_current->right)
            if (_current->right != _sentinel)
            {
                _current = _current->right;
                while (_current != _sentinel && _current->left != _sentinel)
                    _current = _current->left;
                return *this;
            }

            // case 2: next node is parent
            if (_current->parent != _sentinel && _current == _current->parent->left)
            {
                _current = _current->parent;
                return *this;
            }

            // case 3: next node is further parent or not at all
            _current = _current->parent;
            while (_current != _sentinel
                && _current->parent != _sentinel
                && _current == _current->parent->left)
                _current = _current->parent;

            if (_current->parent == _sentinel)
                _current = _sentinel;

            return *this;
        }

        /// @brief prefix decerement
        map_iterator & operator-- ()
        {
            // case 0: previous node is max(root)
            if (_current == _sentinel)
            {
                _current = _current->right;
                while (_current != _sentinel && _current->right != _sentinel)
                    _current = _current->right;
                return *this;
            }

            // case 1: previous node is max(_current->left)
            if (_current->left != _sentinel)
            {
                _current = _current->left;
                while (_current != _sentinel && _current->right != _sentinel)
                    _current = _current->right;
                return *this;
            }

            // case 2: previous node is parent
            if (_current->parent != _sentinel && _current == _current->parent->right)
            {
                _current = _current->parent;
                return *this;
            }

            // case 3: previous node is further parent or not at all
            _current = _current->parent;
            while (_current != _sentinel
                && _current->parent != _sentinel
                && _current == _current->parent->right)
                _current = _current->parent;

            if (_current->parent == _sentinel)
                _current = _sentinel;

            return *this;
        }

        /// @brief postfix incerement
        map_iterator operator++ (int)
        { map_iterator tmp = *this; this->operator++(); return tmp; }

        /// @brief postfix decerement
        map_iterator operator-- (int)
        { map_iterator tmp = *this; this->operator--(); return tmp; }

        node_pointer current_node () const
        { return _current; }

        node_pointer sentinel_node () const
        { return _sentinel; }
    };

    public:

    typedef map_iterator<value_type>                iterator;
    typedef map_iterator<value_type const>          const_iterator;

    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    class value_compare
    {
        /// @note why friend ?
        friend class map;

        /// @note why protected ?
        protected:

        Compare comp;
        value_compare (Compare c) : comp(c) { }

        public:

        /// @note we shoudn't have this
        value_compare () { }

        typedef bool        result_type;
        typedef value_type  first_argument_type;
        typedef value_type  second_argument_type;

        bool operator () (value_type const & a, value_type const & b) const
        { return comp(a.first, b.first); }

    };

    /**************************************************************************/
    /*                                                                        */
    /*      Internal data                                                     */
    /*                                                                        */
    /**************************************************************************/

    private:

    typename btree_type::allocator_type	    _alloc; // (?) remove
    key_compare	            _key_comp;
    value_compare	        _value_comp;
    btree_type              _tree;
    //allocator_type	    _alloc; // this is not used

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Constructors ******************************************************/

    /// @brief Constructor by default (1)
    explicit map (key_compare const & comp = key_compare(),
                allocator_type const & alloc = allocator_type())
    : _alloc(alloc), _key_comp(comp), _value_comp(comp) { }

    /// @brief Constructor by range (2)
    template <class InputIterator>
    map (InputIterator first, InputIterator last,
        key_compare const & comp = key_compare(),
        allocator_type const & alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
    : _alloc(alloc), _key_comp(comp), _value_comp(comp) { insert(first, last); }

    /// @brief Constructor by copy (3)
    map (map const & a)
    : _alloc(a._alloc), _key_comp(a._key_comp), _value_comp(a._key_comp),
      _tree(a._tree) { }

    /****** Destructor ********************************************************/

    ~map () { }

    /****** Element access ****************************************************/

///   @todo remove (c++11)
//    mapped_type & at (key_type const & k);
//    mapped_type const & at (key_type const & k) const;

    mapped_type & operator[] (key_type const & key)
    { return (insert(make_pair(key, mapped_type())).first)->second; }

    /****** Capacity **********************************************************/

    bool empty () const
    { return _tree.empty(); }

    size_type size () const
    { return _tree.size(); }

    /// @todo
    size_type max_size () const
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
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
    { for (; first != last; first++) insert(*first); }

    /// @brief erase by iterator position (1)
    void erase (iterator position)
    { return _tree.erase(*position); }
    //{ return _tree.erase(position); }

    /// @brief erase by key (2)
    /// @note always return 1 since our map doesn't support duplicated keys
    size_type erase (key_type const & key)
    { _tree.erase(value_type(key, mapped_type())); return 1; }

    /// @brief erase by iterator range (3)
    void erase (iterator first, iterator last)
    {
        iterator node;
        while (first != last)
        {
            node = first;
            ++first;
            erase(node);
        }
    }
    //{ for (; first != last; first++) { _tree.erase(*first); } }

    void swap (map & m)
    { map tmp(m); m = *this; *this = tmp; }

    void clear ()
    { erase(begin(), end()); }

    /****** Observers *********************************************************/

    key_compare key_comp () const
    { return _key_comp; }

    value_compare value_comp () const
    { return _value_comp; }

    /****** Iterators *********************************************************/

    iterator begin ()
    { return iterator(_tree.min(_tree.root()), _tree.sentinel()); }

    const_iterator begin () const
    { return const_iterator(_tree.min(_tree.root()), _tree.sentinel()); }

    iterator end ()
    { return iterator(_tree.sentinel(), _tree.sentinel()); }

    const_iterator end () const
    { return const_iterator(_tree.sentinel(), _tree.sentinel()); }

    reverse_iterator rbegin ()
    { return reverse_iterator(end()); }

    const_reverse_iterator rbegin () const
    { return const_reverse_iterator(end()); }

    reverse_iterator rend ()
    { return reverse_iterator(begin()); }

    const_reverse_iterator rend () const
    { return const_reverse_iterator(begin()); }

    /****** Operations ********************************************************/

    iterator find (key_type const & key)
    {
        node_pointer p = _tree.find(value_type(key, mapped_type()));
        return p ? iterator(p, _tree.sentinel()) : end();
    }

    const_iterator find (key_type const & key) const
    {
        node_pointer p = _tree.find(value_type(key, mapped_type()));
        return p ? const_iterator(p, _tree.sentinel()) : end();
    }

    size_type count (key_type const & key)
    { return find(key) == end() ? 0 : 1; }

    /// @todo
    iterator lower_bound (key_type const & key)
    {
    //    std::cout << "lower mutable" << std::endl;

        iterator it = begin();
        iterator ite = end();

        //while (it != ite && _key_comp(it->first, key)) it++;
        while (it != ite && _key_comp((*it).first, key)) it++;
        return it;
    }

    /// @todo
    const_iterator lower_bound (key_type const & key) const
    {
    //    std::cout << "lower const" << std::endl;

        const_iterator it = begin();
        const_iterator ite = end();

        //while (it != ite && _key_comp(it->first, key)) it++;
        while (it != ite && _key_comp((*it).first, key)) it++;
        return it;
    }

    /// @todo
    iterator upper_bound (key_type const & key)
    {
    //    std::cout << "upper mutable" << std::endl;

        iterator it = begin();
        iterator ite = end();

        //while (it != ite && !_key_comp(key, it->first)) it++;
        while (it != ite && !_key_comp(key, (*it).first)) it++;
        return it;
    }

    /// @todo
    const_iterator upper_bound (key_type const & key) const
    {
    //    std::cout << "upper const" << std::endl;

        const_iterator it = begin();
        const_iterator ite = end();

        //while (it != ite && !_key_comp(key, it->first)) it++;
        while (it != ite && !_key_comp(key, (*it).first)) it++;
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
    { return _tree.get_allocator(); }

    map & operator= (map const & m)
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