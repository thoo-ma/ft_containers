#ifndef RBTREE_HPP
#define RBTREE_HPP 1

#include <stddef.h> // NULL
#include <memory> // std::allocator
#include <iostream> // std::ostream
#include <fstream> // std::fstream

#include "include/iterators/ft_iterator_base_types.hpp"
#include "include/iterators/ft_reverse_iterator.hpp"

/**
 * @todo benchmark destructors execution time (prefer recursive one if possible)
 * @todo handle allocator failure
 * @todo use comp ??
 */

namespace ft {

template <typename T>
class rbtree
{
    /****** Types *************************************************************/

    private: struct node; // forward declaration

    public:

    typedef T                           key_type;
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

        node (key_type const & key = key_type())
        : key(key), color(Black), left(NULL), right(NULL), parent(NULL) {}

        node (struct node const & n)
        : key(n.key), color(n.color), left(NULL), right(NULL), parent(NULL) { }

        // struct node & operator= (struct node const & rhs) {}
        // bool operator== (struct node const & rhs) {}

       // pointer min ()
       // pointer max ();
       // pointer next ();
       // pointer prev ();

    };

    /****** Iterator **********************************************************/

    private:

    class rbtree_iterator
    : public iterator<bidirectional_iterator_tag, value_type>
    {
        /****** Types *********************************************************/

        public:

        typedef iterator_traits<rbtree_iterator>	traits; // to shorten below
        typedef typename traits::iterator_category  iterator_category;
        typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        typedef typename traits::pointer	        pointer;
        typedef typename traits::reference	        reference;

        /****** Data **********************************************************/

        private:

        pointer _data;

        /****** Public methods ************************************************/

        public:

        /// @note explicit ?
        rbtree_iterator (pointer data = NULL)
        : _data(data) { }

        key_type & operator* () const
        { return _data->key; }

        bool operator== (rbtree_iterator const & it) const
        { return _data == it.data(); }

        bool operator!= (rbtree_iterator const & it) const
        { return _data != it.data(); }

        /// @note prefix
        /// @note BUG
        rbtree_iterator & operator++ ()
        {
            if (_data)
            {
                _data = _data->right;
                while (_data && _data->left) _data = _data->left;
            }
            else
            {
                while (_data->parent) _data = _data->parent;
                while (_data && _data->left) _data = _data->left;
            }
            return *this;
        }

        /// @note prefix
        /// @note BUG
        rbtree_iterator & operator-- ()
        {
            if (_data)
            {
                _data = _data->left;
                while (_data && _data->right) _data = _data->right;
            }
            else
            {

                while (_data->parent) _data = _data->parent;
                while (_data && _data->right) _data = _data->right;
            }
            return *this;
        }

        /// @note postfix
        rbtree_iterator operator++ (int)
        { rbtree_iterator tmp = *this; this->operator++(); return tmp; }

        /// @note postfix
        rbtree_iterator operator-- (int)
        { rbtree_iterator tmp = *this; this->operator--(); return tmp; }

        pointer data() const
        { return _data; }

    };

    public:

    typedef rbtree_iterator iterator;
//    typedef const_iterator;
//    typedef reverse_iterator<iterator> reverse_iterator;
//    typedef reverse_iterator<const_iterator> const_reverse_iterator;

    /****** Data **************************************************************/

    private:

    pointer         _root;
    size_type       _size;
    allocator_type  _alloc;

    /****** Internals *********************************************************/

    //inline bool _is_leaf(pointer x) { return !x->left && !x->right; }

    /**
     *  @pre 'x' right child is not the sentinel node
     *  @pre 'x' right child is not NULL
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
        //if (x->parent == &_sentinel)
        if (x->parent == NULL)
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
     *  @pre `y` left child is not NULL
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
        //if (y->parent == &_sentinel)
        if (y->parent == NULL)
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
    /// @todo Protect against null-dereferencing
    void _insert_fixup (pointer z)
    {
        pointer y; // 'z' uncle
        while (z != _root && z->parent->color == Red)
        {
            // left-balance
            if (z->parent == z->parent->parent->left)
            {
                y = z->parent->parent->right;
                // case 1
                if (y && y->color == Red)
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
                if (y && y->color == Red)
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
        if (x)
        {
            std::cout << "erase_fixup(" << x->key << ")" << std::endl;
            x->color == Red
            ? std::cout << "color: Red" << std::endl
            : std::cout << "color: Black" << std::endl;
        }
        else
            std::cout << "erase_fixup _nil_" << std::endl;

        pointer w; // `x` sibling
        while (x && x != _root && x->color == Black)
        {
            // left-balance
            if (x == x->parent->left)
            {
                std::cout << "erase_fixup left" << std::endl;
                w = x->parent->right;
                // case 1
                if (w->color == Red)
                {
                    std::cout << "erase_fixup case 1" << std::endl;
                    w->color = Black;
                    x->parent->color = Red;
                    _left_rotate(x->parent);
                    w = x->parent->right;
                }
                // case 2
                if (w->left->color == Black && w->right->color == Black)
                {
                    std::cout << "erase_fixup case 2" << std::endl;
                    w->color = Red;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (w->right->color == Black)
                    {
                        std::cout << "erase_fixup case 3" << std::endl;
                        w->left->color = Black;
                        w->color = Red;
                        _right_rotate(w);
                        w = x->parent->right;
                    }
                    // case 4
                    std::cout << "erase_fixup case 4" << std::endl;
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
                std::cout << "erase_fixup right" << std::endl;
                w = x->parent->left;
                // case 1
                if (w->color == Red)
                {
                    std::cout << "erase_fixup case 1" << std::endl;
                    w->color = Black;
                    x->parent->color = Red;
                    _right_rotate(x->parent);
                    w = x->parent->left;
                }
                // case 2
                if (w->left->color == Black && w->right->color == Black)
                {
                    std::cout << "erase_fixup case 2" << std::endl;
                    w->color = Red;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (w->left->color == Black)
                    {
                    std::cout << "erase_fixup case 3" << std::endl;
                        w->right->color = Black;
                        w->color = Red;
                        _left_rotate(w);
                        w = x->parent->left;
                    }
                    // case 4
                    std::cout << "erase_fixup case 4" << std::endl;
                    w->color = x->parent->color;
                    x->parent->color = Black;
                    w->left->color = Black;
                    _right_rotate(x->parent);
                    x = _root; // break
                }
            }
        }
        if (x)
            x->color = Black;
    }

    /// @brief Replace subtree `u` by subtree `v`
    void _transplant (pointer u, pointer v)
    {
        if (u->parent == NULL)
            _root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v)
            v->parent = u->parent;
    }

    /// @brief Destroy and deallocate subtree `x`
    void _destroy (pointer x)
    {
        if (x == NULL)
            return;
        _destroy(x->left);
        _destroy(x->right);
        _alloc.destroy(x);
        _alloc.deallocate(x, 1);
    }

    /// @return a deep copy of subtree `src`
    /// @param src root of subtree to be copied
    /// @param sentinel sentinel node of subtree `src`
    pointer _copy (pointer src/*, pointer sentinel*/)
    {
        pointer tmp;
        pointer dst;
        pointer dst_root;

        if (src == NULL)
            //return &_sentinel;
            return NULL;

        dst_root = _alloc.allocate(1);
        _alloc.construct(dst_root, *src);
        //dst_root->parent = &_sentinel;
        dst_root->parent = NULL;
        dst = dst_root;

        while (1)
        {
            //while (src->left != sentinel)
            while (src->left)
            {
                dst->left = _alloc.allocate(1);
                _alloc.construct(dst->left, *(src->left));
                dst->left->parent = dst;
                src = src->left;
                dst = dst->left;
            }
            //dst->left = &_sentinel;
            dst->left = NULL;
            while (1)
            {
                //if (src->right != sentinel)
                if (src->right)
                {
                    dst->right = _alloc.allocate(1);
                    _alloc.construct(dst->right, *src);
                    dst->right->parent = dst;
                    src = src->right;
                    dst = dst->right;
                    break;
                }
                else
                    //dst->right = &_sentinel;
                    dst->right = NULL;
                while (1)
                {
                    tmp = src;
                    src = src->parent;
                    //if (src == sentinel)
                    if (src == NULL)
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

    rbtree ()
    : _root(NULL), _size(0) {}

    /// @brief Constructor by copy (2)
    rbtree (const rbtree & tree)
    : _root(NULL), _size(tree._size), _alloc(tree._alloc)
    { *this = tree; }
    //{ _root = _copy(tree._root, NULL); }

    /// @brief Constructor by iterator range (3)

    /// @brief Recursive destructor
//    ~rbtree ()
//    { _destroy(_root); }

    /// @brief Iterative destructor
    ~rbtree ()
    {
        pointer x = _root;
        pointer p;
        while (x)
        {
            p = x->parent;
            while (x && x->left)
            {
                p = x;
                x = x->left;
            }
            if (x && x->right)
            {
                p = x;
                x = x->right;
            }
            if (x && x->left == NULL && x->right == NULL)
            {
                _alloc.destroy(x);
                _alloc.deallocate(x, 1);
                if (p)
                    x == p->left ? p->left = NULL : p->right = NULL;
                x = p;
            }
        }
    }

    void insert (pointer z)
    {
        //pointer y = &_sentinel;
        pointer y = NULL;
        pointer x = _root;

        //while (x != &_sentinel)
        while (x)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        //if (y == &_sentinel) // ?? _sentinel->parent == &_sentinel ?
        if (y == NULL)
            _root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
       // z->left = &_sentinel;
       // z->right = &_sentinel;
        z->left = NULL;
        z->right = NULL;
        z->color = Red;
        _insert_fixup(z);
    }

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

    void insert (value_type const & val)
    { return insert(val.key); }

    void erase (pointer z)
    {
        //std::cout << "erase " << z->key << std::endl;

        pointer x;
        pointer y = z;
        color_type c = y->color;

        if (z->left == NULL)
        {
            x = z->right;
            _transplant(z, z->right);
        }
        else if (z->right == NULL)
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
            {
                if (x)
                    x->parent = y;
            }
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

    void erase (key_type const & key)
    {
        pointer x = find(_root, key);
        if (x) erase(x);
    }

    // erase by position (1)
    void erase (iterator position)
    { return erase(position.data()); }

    pointer find (pointer x, key_type const & key) const
    {
        // while (x != &_sentinel && x->key != key)
        //     key < x->key ? x = x->left : x = x->right;
        // return x != &_sentinel ? x : NULL;

        while (x && x->key != key)
            key < x->key ? x = x->left : x = x->right;
        return x;
    }

    pointer find (key_type const & key) const
    { return find(_root, key); }

    pointer min (pointer x) const
    {
        while (x && x->left) x = x->left;
        return x;
    }

    pointer max (pointer x) const
    {
        while (x && x->right) x = x->right;
        return x;
    }

    /// @todo
    pointer pred (pointer x)
    { return x ? min(x->right) : min(_root); }

    /// @todo
    pointer next (pointer x)
    { return x ? min(x->right) : min(_root); }

//    size_type black_height (pointer x) const;

    rbtree & operator= (rbtree & rhs)
    {
        _destroy(_root);
        if (rhs.empty())
        {
            _root = NULL;
            _size = 0;
        }
        else
        {
            //_root = _copy(rhs.root(), rhs.sentinel());
            _root = _copy(rhs.root());
            _size = rhs.size();
        }
        return *this;
    }

    size_type size () const
    { return _size; }

    bool empty () const
    { return _size == 0; }

    pointer root () const
    { return _root; }

    /****** Iterator **********************************************************/

    iterator begin ()
    { return iterator(min(_root)); }

    iterator end()
    { return iterator(max(_root)); }

    /****** Debug *************************************************************/

    void make_graph () const
    {
		std::ofstream file ("graph.md");
        file << "```mermaid" << std::endl;
        file << "graph TD;" << std::endl;
        //file << "style sentinel fill:black" << std::endl;
        if (_size)
            _draw_graph(file, _root);
        file << "```" << std::endl;
        file.close();
    }

    private:
    void _draw_graph (std::ofstream & file, pointer node) const
    {
        file << node->key << "; style " << node->key << " fill:";
        node->color == Red ? file << "red" : file << "black";
        file << std::endl;

        //if (node->left != &_sentinel)
        if (node->left)
        {
            file << node->key << " --- " << node->left->key << std::endl;
            _draw_graph(file, node->left);
        //} else file << node->key << " --- sentinel" << std::endl;
        } else file << node->key << " --- nil" << std::endl;

        //if (node->right != &_sentinel)
        if (node->right)
        {
            file << node->key << " --- " << node->right->key << std::endl;
            _draw_graph(file, node->right);
        // } else file << node->key << " --- sentinel" << std::endl;
        } else file << node->key << " --- nil" << std::endl;
    }

};

/// @todo add constness to lhs and rhs
template <typename T>
bool operator== (rbtree<T> & lhs, rbtree<T> & rhs)
{
    typename rbtree<T>::iterator lit = lhs.begin();
    typename rbtree<T>::iterator rit = rhs.begin();
    typename rbtree<T>::iterator lite = lhs.end();
    typename rbtree<T>::iterator rite = rhs.end();

    for (; lit != lite && rit != rite && *lit == *rit; lit++, rit++);
    return (lit == lite && rit == rite);
}

/// @todo add constness to lhs and rhs
template <typename T>
bool operator!= (rbtree<T> & lhs, rbtree<T> & rhs)
{ return !(lhs == rhs); }

} // namespace

#endif /* RBTREE_HPP */