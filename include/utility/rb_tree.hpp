#ifndef RB_TREE_HPP
#define RB_TREE_HPP 1

#include <stddef.h> // NULL
#include <memory> // std::allocator
#include <iostream> // std::ostream
#include <fstream> // std::fstream
#include <functional> // std::less

#include "ft_iterator_base_types.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_type_traits.hpp"

/// @todo benchmark destructors execution time (keep recursive one if possible)
/// @todo handle allocator failure
/// @todo unsupport duplicate nodes
/// @todo (?) inline function or macro to replace ternaries

namespace ft {

template <typename T, typename Compare = std::less<T>>
class rb_tree
{
    /****** Types *************************************************************/

    private: struct node; // forward declaration

    public:

    typedef T                           key_type;
    typedef Compare                     compare_type;
    typedef size_t                      size_type;
    typedef struct node                 value_type;
    typedef struct node *               pointer;
    typedef enum { Black, Red }         color_type;
    typedef std::allocator<struct node> allocator_type;

    /****** Node **************************************************************/

    private:

    struct node
    {
        key_type key;
        color_type color;
        pointer left;
        pointer right;
        pointer parent;

        /// @brief Constructor by default (1)
        node (key_type const & key = key_type())
        : key(key), color(Black), left(NULL), right(NULL), parent(NULL) {}

        /// @brief Constructor by copy (2)
        node (struct node const & n)
        : key(n.key), color(n.color), left(NULL), right(NULL), parent(NULL) { }

        struct node & operator= (struct node const & rhs)
        {
            this->key = rhs.key;
            this->color = rhs.color;
            return *this;
        }

        /// @todo (?)
    //    bool operator <(struct node const & rhs)
    //    {
    //        std::cout << "comp" << std::endl;
    //        return compare(key, rhs.key);
    //    }

        bool operator== (struct node const & rhs) const
        { return this->key == rhs.key; }

        /// @todo (?)
    //    Compare compare;
    };

    /****** Iterator **********************************************************/

    private:

    /// @todo iterator tag from std
    template <typename U>
    class rb_tree_iterator : public iterator<bidirectional_iterator_tag, U>
    {
        /****** Types *********************************************************/

        public:

        typedef iterator_traits<rb_tree_iterator>	traits; // to shorten below
        typedef typename traits::iterator_category  iterator_category;
        typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        typedef typename traits::pointer	        pointer;
        typedef typename traits::reference	        reference;

        /****** Data **********************************************************/

        private:

        pointer _data;
        pointer _sentinel_ptr;

        /****** Public methods ************************************************/

        public:

        /// @note explicit ?
        rb_tree_iterator (pointer data = NULL, pointer sentinel_ptr = NULL)
        : _data(data), _sentinel_ptr(sentinel_ptr) { }

        rb_tree_iterator (rb_tree_iterator<rb_tree::value_type> const & it)
        : _data(it.data()), _sentinel_ptr(const_cast<pointer>(it.sentinel_ptr()))
        { }

        /// @note yes, those casts are nasty but seems necessary...
        rb_tree_iterator (rb_tree_iterator<rb_tree::value_type const> const & it)
        : _data(const_cast<pointer>(it.data())), _sentinel_ptr(const_cast<pointer>(it.sentinel_ptr()))
        { }

        rb_tree_iterator operator= (rb_tree_iterator const & it)
        { _data = it.data(); _sentinel_ptr = it.sentinel_ptr(); return *this; }

        /// @todo
        key_type const & operator* () const
        { return _data->key; }

        /// @todo
        key_type * operator-> () const
        { return &_data->key; }

    //    value_type & operator* () const
    //    { return *_data; }

    //    pointer operator-> () const
    //    { return _data; }

        bool operator== (rb_tree_iterator<rb_tree::value_type> const & it) const
        {
            return (_data == it.data()
                || (_data == _sentinel_ptr && it.data() == it.sentinel_ptr()));
        }

        bool operator== (rb_tree_iterator<rb_tree::value_type const> const & it) const
        {
            return (_data == it.data()
                || (_data == _sentinel_ptr && it.data() == it.sentinel_ptr()));
        }

        bool operator!= (rb_tree_iterator<rb_tree::value_type> const & it) const
        { return !(*this == it); }

        bool operator!= (rb_tree_iterator<rb_tree::value_type const> const & it) const
        { return !(*this == it); }

        /// @note prefix
        /// @note might improve case 3
        /// @pre  _sentinel.right == _root
        rb_tree_iterator & operator++ ()
        {
            // case 1: next node is min(_data->right)
            if (_data->right != _sentinel_ptr)
            {
                _data = _data->right;
                while (_data != _sentinel_ptr && _data->left != _sentinel_ptr)
                    _data = _data->left;
                return *this;
            }

            // case 2: next node is parent
            if (_data->parent != _sentinel_ptr && _data == _data->parent->left)
            {
                _data = _data->parent;
                return *this;
            }

            // case 3: next node is further parent or not at all
            _data = _data->parent;
            while (_data != _sentinel_ptr
                && _data->parent != _sentinel_ptr
                && _data == _data->parent->left)
                _data = _data->parent;

            if (_data->parent == _sentinel_ptr)
                _data = _sentinel_ptr;

            return *this;
        }

        /// @note prefix
        /// @note might improve case 3
        /// @pre  _sentinel.right == _root
        rb_tree_iterator & operator-- ()
        {
            // case 0: previous node is max(root)
            if (_data == _sentinel_ptr)
            {
                _data = _data->right;
                while (_data != _sentinel_ptr && _data->right != _sentinel_ptr)
                    _data = _data->right;
                return *this;
            }

            // case 1: previous node is max(_data->left)
            if (_data->left != _sentinel_ptr)
            {
                _data = _data->left;
                while (_data != _sentinel_ptr && _data->right != _sentinel_ptr)
                    _data = _data->right;
                return *this;
            }

            // case 2: previous node is parent
            if (_data->parent != _sentinel_ptr && _data == _data->parent->right)
            {
                _data = _data->parent;
                return *this;
            }

            // case 3: previous node is further parent or not at all
            _data = _data->parent;
            while (_data != _sentinel_ptr
                && _data->parent != _sentinel_ptr
                && _data == _data->parent->right)
                _data = _data->parent;

            if (_data->parent == _sentinel_ptr)
                _data = _sentinel_ptr;

            return *this;
        }

        /// @note postfix
        rb_tree_iterator operator++ (int)
        { rb_tree_iterator tmp = *this; this->operator++(); return tmp; }

        /// @note postfix
        rb_tree_iterator operator-- (int)
        { rb_tree_iterator tmp = *this; this->operator--(); return tmp; }

        pointer data() const
        { return _data; }

        pointer sentinel_ptr() const
        { return _sentinel_ptr; }

    };

    public:

    typedef rb_tree_iterator<value_type>             iterator;
    typedef rb_tree_iterator<value_type const>       const_iterator;

    // namespace below is mandatory since typedef operands share the same name
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    /****** Data **************************************************************/

    private:

    pointer         _root;
    size_type       _size;
    //size_type       _max_size; // just to be inherited by map
    value_type      _sentinel;
    allocator_type  _alloc;
    compare_type    _comp;

    /****** Internals *********************************************************/

    /**
     *  @pre 'x' right child is not the sentinel node
     *
     *       y                           x
     *      / \                         / \
     *     x   c     left-rotate(x)    a   y
     *    / \        <------------        / \
     *   a   b                           b   c
     *
     */
    void _left_rotate (pointer x)
    {
        pointer y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == &_sentinel)
            _root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    /**
     *  @pre `y` left child is not the sentinel node
     *
     *       y                           x
     *      / \                         / \
     *     x   c    right-rotate(y)    a   y
     *    / \       -------------->       / \
     *   a   b                           b   c
     *
     */
    void _right_rotate (pointer y)
    {
        pointer x = y->left;
        y->left = x->right;
        if (x->right)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == &_sentinel)
            _root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    /// @param z A newly inserted red node
    /// @note If 'z' is root its parent node (sentinel) is black
    void _insert_fixup (pointer z)
    {
        pointer y; // 'z' uncle
        while (z->parent->color == Red)
        {
            // left-balance
            if (z->parent == z->parent->parent->left)
            {
                y = z->parent->parent->right;
                // case 1
                if (y->color == Red)
                {
                    z->parent->color = Black;
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                }
                else
                {
                    // case 2
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        _left_rotate(z);
                    }
                    // case 3
                    z->parent->color = Black;
                    z->parent->parent->color = Red;
                    _right_rotate(z->parent->parent);
                }
            }
            // right-balance
            else
            {
                y = z->parent->parent->left;
                // case 1
                if (y->color == Red)
                {
                    z->parent->color = Black;
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                }
                else
                {
                    // case 2
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        _right_rotate(z);
                    }
                    // case 3
                    z->parent->color = Black;
                    z->parent->parent->color = Red;
                    _left_rotate(z->parent->parent);
                }
            }
        }
        _root->color = Black;
    }

    void _erase_fixup (pointer x)
    {
       // if (x)
       // {
       //     std::cout << "erase_fixup(" << x->key << ")" << std::endl;
       //     x->color == Red
       //     ? std::cout << "color: Red" << std::endl
       //     : std::cout << "color: Black" << std::endl;
       // }

        pointer w; // `x` sibling
        while (x != _root && x->color == Black)
        {
            // left-balance
            if (x == x->parent->left)
            {
                w = x->parent->right;
                // case 1
                if (w->color == Red)
                {
                    w->color = Black;
                    x->parent->color = Red;
                    _left_rotate(x->parent);
                    w = x->parent->right;
                }
                // case 2
                if (w->left->color == Black && w->right->color == Black)
                {
                    w->color = Red;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (w->right->color == Black)
                    {
                        w->left->color = Black;
                        w->color = Red;
                        _right_rotate(w);
                        w = x->parent->right;
                    }
                    // case 4
                    w->color = x->parent->color;
                    x->parent->color = Black;
                    w->right->color = Black;
                    _left_rotate(x->parent);
                    x = _root; // break
                }
            }
            // right-balance
            else
            {
                w = x->parent->left;
                // case 1
                if (w->color == Red)
                {
                    w->color = Black;
                    x->parent->color = Red;
                    _right_rotate(x->parent);
                    w = x->parent->left;
                }
                // case 2
                if (w->left->color == Black && w->right->color == Black)
                {
                    w->color = Red;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (w->left->color == Black)
                    {
                        w->right->color = Black;
                        w->color = Red;
                        _left_rotate(w);
                        w = x->parent->left;
                    }
                    // case 4
                    w->color = x->parent->color;
                    x->parent->color = Black;
                    w->left->color = Black;
                    _right_rotate(x->parent);
                    x = _root; // break
                }
            }
        }
        x->color = Black;
    }

    /// @brief Replace subtree `u` by subtree `v`
    void _transplant (pointer u, pointer v)
    {
        if (u->parent == &_sentinel)
            _root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    /// @brief Destroy and deallocate subtree `x`
    void _destroy (pointer x)
    {
        if (x == &_sentinel)
            return;
        _destroy(x->left);
        _destroy(x->right);
        _alloc.destroy(x);
        _alloc.deallocate(x, 1);
    }

    /// @return a deep copy of subtree `src`
    /// @param src root of subtree to be copied
    /// @param sentinel sentinel node of subtree `src`
    pointer _copy (pointer src, pointer sentinel)
    {
        pointer tmp;
        pointer dst;
        pointer dst_root;

        if (src == NULL)
            return &_sentinel;

        dst_root = _alloc.allocate(1);
        _alloc.construct(dst_root, *src);
        dst_root->parent = &_sentinel;
        dst = dst_root;

        while (1)
        {
            while (src->left != sentinel)
            {
                dst->left = _alloc.allocate(1);
                _alloc.construct(dst->left, *(src->left));
                dst->left->parent = dst;
                src = src->left;
                dst = dst->left;
            }
            dst->left = &_sentinel;
            while (1)
            {
                if (src->right != sentinel)
                {
                    dst->right = _alloc.allocate(1);
                    _alloc.construct(dst->right, *src->right);
                    dst->right->parent = dst;
                    src = src->right;
                    dst = dst->right;
                    break;
                }
                else
                    dst->right = &_sentinel;
                while (1)
                {
                    tmp = src;
                    src = src->parent;
                    if (src == sentinel)
                        return dst_root;
                    dst = dst->parent;
                    if (tmp == src->left)
                        break;
                }
            }
        }
    }

    /****** Public methods ****************************************************/

    public:

    /// @brief Constructor by default (1)
    explicit rb_tree ()
    : _root(&_sentinel), _size(0)//, _max_size(_alloc.max_size())
    {
        _sentinel.left = _root;
        _sentinel.right = _root;
        _sentinel.parent = _root;
    } //{ _root = _copy(tree._root, NULL); }

    /// @brief Constructor by copy (2)
    /// @todo those three assignations not needed if constructor by default is
    ///       called before function execution. need to check this. (delete ?)
    rb_tree (rb_tree const & tree)
    : _root(&_sentinel)//, _max_size(tree.max_size())
    {
        *this = tree;
    //    _sentinel.left = _root;
    //    _sentinel.right = _root;
    //    _sentinel.parent = _root;
    } //{ _root = _copy(tree._root, NULL); }

    /// @brief Constructor by iterator range (3)
    rb_tree (iterator first, iterator last)
    : _root(&_sentinel), _size(0)//, _max_size(_alloc.max_size())
    {
        _sentinel.left = _root;
        _sentinel.right = _root;
        _sentinel.parent = _root;
        insert(first, last);
    }

    /// @brief Recursive destructor
//    ~rb_tree ()
//    { _destroy(_root); }

    /// @brief Iterative destructor
    ~rb_tree ()
    {
        pointer x = _root;
        pointer p = x->parent;
        while (x != &_sentinel)
        {
            p = x->parent;
            while (x != &_sentinel && x->left != &_sentinel)
            {
                p = x;
                x = x->left;
            }
            if (x != &_sentinel && x->right != &_sentinel)
            {
                p = x;
                x = x->right;
            }
            if (x != &_sentinel && x->left == &_sentinel && x->right == &_sentinel)
            {
                _alloc.destroy(x);
                _alloc.deallocate(x, 1);
                if (p != &_sentinel)
                    x == p->left ? p->left = &_sentinel : p->right = &_sentinel;
                x = p;
            }
        }
    }

    /// @brief Base routine to insert a node
    /// @param z New node to be inserted in the tree
    void insert (pointer z)
    {
        pointer y = &_sentinel;
        pointer x = _root;

        while (x != &_sentinel)
        {
            y = x;
            //if (z->key < x->key)
            if (_comp(z->key, x->key))
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == &_sentinel) // ?? _sentinel->parent == &_sentinel ?
        {
            _root = z;
            _sentinel.left = _root;
            _sentinel.right = _root;

        }
        //else if (z->key < y->key)
        else if (_comp(z->key, y->key))
            y->left = z;
        else
            y->right = z;
        z->left = &_sentinel;
        z->right = &_sentinel;
        z->color = Red;
        _insert_fixup(z);
    }

    /// @brief Insert by key
    /// @param key Key of the new node inserted
    /// @note Is it necessary ?...
    void insert (key_type const & key)
    {
        // do not insert duplicated key
        if (find(_root, key))
            return;

        // alloc and construct
        pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, value_type(key));

        // insert
        insert(new_node);

        // update size
        _size++;
    }

    /// @brief Insert by value (1)
    void insert (value_type const & val)
    { return insert(val.key); }

    /// @brief Insert with hint (2)
    /// @todo Use position to improve speed
    void insert (iterator position, value_type const & val)
    { (void)position; return insert(val); }

    /// @brief Insert by iterator range (3)
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    /// @brief Erase base routine
    /// @todo private/protected ?
    void erase (pointer z)
    {
        pointer x;
        pointer y = z;
        color_type c = y->color;

        if (z->left == &_sentinel)
        {
            x = z->right;
            _transplant(z, z->right);
        }
        else if (z->right == &_sentinel)
        {
            x = z->left;
            _transplant(z, z->left);
        }
        else
        {
            y = min(z->right);
            c = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                _transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            _transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (c == Black)
            _erase_fixup(x);
        _alloc.destroy(z);
        _alloc.deallocate(z, 1);
        _size--;
    }

    /// @brief Erase by position (1)
    void erase (iterator position)
    { return erase(position.data()); }

    /// @brief Erase by key (2)
    void erase (key_type const & key)
    {
        pointer x = find(_root, key);
        if (x) erase(x);
    }

    /// @brief Erase by iterator range (3)
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

    pointer find (pointer x, key_type const & key) const
    {
        while (x != &_sentinel && x->key != key)
            //key < x->key ? x = x->left : x = x->right;
            _comp(key, x->key) ? x = x->left : x = x->right;
        return x != &_sentinel ? x : NULL;
    }

    pointer find (key_type const & key) const
    { return find(_root, key); }

    /// @note is it very useful ?...
    pointer min (pointer x) const
    {
        while (x != &_sentinel && x->left != &_sentinel) x = x->left;
        return x;
    }

    /// @note is it very useful ?...
    pointer max (pointer x) const
    {
        while (x != &_sentinel && x->right != &_sentinel) x = x->right;
        return x;
    }

    rb_tree & operator= (rb_tree const & rhs)
    {
        _destroy(_root);
        if (rhs.empty())
        {
            _root = &_sentinel;
            _size = 0;
        }
        else
        {
            _root = _copy(rhs.root(), rhs.sentinel());
            _size = rhs.size();
        }
        _sentinel.left = _root;
        _sentinel.right = _root;
        _sentinel.parent = _root;
        return *this;
    }

    size_type size () const
    { return _size; }

    /// @todo
    size_type max_size () const
    //{ return _max_size; }
    { return _alloc.max_size(); }

    bool empty () const
    { return _size == 0; }

    allocator_type get_allocator () const
    { return _alloc; }

    pointer root () const
    { return _root; }

    pointer sentinel () const
    { return const_cast<pointer>(&_sentinel); }

    /****** Iterator **********************************************************/

    iterator begin ()
    { return iterator(min(_root), &_sentinel); }

    const_iterator begin () const
    { return const_iterator(min(_root), &_sentinel); }

    iterator end()
    { return iterator(&_sentinel, &_sentinel); }

    const_iterator end() const
    { return const_iterator(&_sentinel, &_sentinel); }

    reverse_iterator rbegin()
    { return reverse_iterator(--end()); }
    //{ return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(--end()); }
    //{ return const_reverse_iterator(end()); }

    reverse_iterator rend()
    { return reverse_iterator(end()); }

    const_reverse_iterator rend() const
    { return const_reverse_iterator(end()); }

    /****** Debug *************************************************************/

    void make_graph () const
    {
		std::ofstream file ("graph.md");
        file << "```mermaid" << std::endl;
        file << "graph TD;" << std::endl;
        file << "style sentinel fill:black" << std::endl;
        if (_size)
            //_draw_graph(file, _root);
            _draw_graph_pair(file, _root);
        file << "```" << std::endl;
        file.close();
    }

//    private: void _draw_graph (std::ofstream & file, pointer node) const
//    {
//        file << node->key << "; style " << node->key << " fill:";
//        node->color == Red ? file << "red" : file << "black";
//        file << std::endl;
//
//        if (node->left != &_sentinel)
//        {
//            file << node->key << " --- " << node->left->key << std::endl;
//            _draw_graph(file, node->left);
//        } else file << node->key << " --- sentinel" << std::endl;
//
//        if (node->right != &_sentinel)
//        {
//            file << node->key << " --- " << node->right->key << std::endl;
//            _draw_graph(file, node->right);
//        } else file << node->key << " --- sentinel" << std::endl;
//    }

    private: void _draw_graph_pair (std::ofstream & file, pointer node) const
    {
        file << node->key.first << "; style " << node->key.first << " fill:";
        node->color == Red ? file << "red" : file << "black";
        file << std::endl;

        if (node->left != &_sentinel)
        {
            file << (node->key).first << " --- " << node->left->key.first << std::endl;
            _draw_graph_pair(file, node->left);
        } else file << (node->key).first << " --- sentinel" << std::endl;

        if (node->right != &_sentinel)
        {
            file << (node->key).first << " --- " << node->right->key.first << std::endl;
            _draw_graph_pair(file, node->right);
        } else file << (node->key).first << " --- sentinel" << std::endl;
    }

};

/// @note not used by map
template <typename T>
bool operator== (rb_tree<T> const & lhs, rb_tree<T> const & rhs)
{
    typename rb_tree<T>::const_iterator lit = lhs.begin();
    typename rb_tree<T>::const_iterator rit = rhs.begin();
    typename rb_tree<T>::const_iterator lite = lhs.end();
    typename rb_tree<T>::const_iterator rite = rhs.end();

    for (; lit != lite && rit != rite && *lit == *rit; lit++, rit++);
    return (lit == lite && rit == rite);
}

/// @note not used by map
template <typename T>
bool operator!= (rb_tree<T> const & lhs, rb_tree<T> const & rhs)
{ return !(lhs == rhs); }

} // namespace

#endif /* RB_TREE_HPP */