#ifndef RB_TREE_HPP
#define RB_TREE_HPP 1

#include <stddef.h> // NULL
#include <memory> // std::allocator
#include <iostream> // std::ostream
#include <fstream> // std::fstream

#include "ft_type_traits.hpp" // ??
#include "ft_reverse_iterator.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_bidirectional_iterator.hpp" // delete

/**
 * @todo use comp
 * @todo inline function or macro to replace ternaries
 * @todo handle allocator failure
 * @todo unsupport duplicate nodes
 */

namespace ft {

template <typename T, typename Compare = std::less<T> >
class rb_tree
{
    /**************************************************************************/
    /*                                                                        */
    /*      Member types                                                      */
    /*                                                                        */
    /**************************************************************************/

    public:

    struct node; // forward declaration

    typedef struct node	                value_type;
    typedef struct node *	            pointer;
    typedef struct node &               reference;
    typedef size_t	                    size_type;
    typedef T	                        key_type;
    typedef Compare	                    compare;
    typedef std::allocator<struct node>	allocator_type;
    typedef enum { Black, Red }	        color_type;

    typedef struct node const &         const_reference;
    typedef struct node const *         const_pointer;

    // private ?
    struct node
    {
        /****** Variables *****************************************************/

        key_type	key;
        color_type	color;
        pointer     left;
        pointer     right;
        pointer     parent;

        /****** Constructors **************************************************/

        /// @brief Constructor by default
        node (key_type const & key = key_type())
        : key(key), color(Red), left(NULL), right(NULL), parent(NULL) { }

        /// @brief Constructor by copy
        node (value_type const & node)
        : key(node.key), color(node.color), left(NULL), right(NULL), parent(NULL) { }

        /// @brief Constructor by color
        node (color_type const & color)
        : key(key_type()), color(color), left(NULL), right(NULL), parent(NULL) { }

        /****** Operators *****************************************************/

        reference operator= (const_reference node)
        {
            this->key = node.key;
            this->color = node.color;
            return *this;
        }

        bool operator== (const_reference node) const
        { return this->key == node.key; }

        /****** Utils *********************************************************/

        /// @brief return the successor of current node according to `compare`
     //   pointer next () const
     //   {
     //       // case 1: current node has a right child
     //       if (this->right)
     //           return min(this->right);
     //       if (this->parent)
     //       {
     //           // case 2: next is parent
     //           if (this == this->parent->left)
     //               return this->parent;
     //           // case 3: next is further parent or is not
     //           pointer next = this->parent;
     //           while (next && next->parent && next == next->parent->right)
     //               next = next->parent;
     //           return next->parent;
     //       }
     //       // case 4: no next node (node is the max/rightmost)
     //       //return const_cast<pointer>(NULL);
     //       return NULL;
     //   }

        /// @todo ??
        pointer next () const
        {
            // case 1: current node has a right child
            if (this->right)
                return min(this->right);

            // case 2: next is parent
            if (this->parent && this == this->parent->left)
                return this->parent;

            // case 3: next is further parent or is not at all
            pointer next = this->parent;
            while (next && next->parent && next == next->parent->right)
                next = next->parent;
            //return next;
            return next == parent ? NULL : next;
        }

        /// @brief return the predecessor of current node according to `compare`
        /// @todo on standby until map is implemented and tested
        /// @todo use compare
        pointer prev () const
        {
            /*
            // case 1:
            if (this->left)
            {
                // return max(this->left);
                pointer prev = this->left;
                while (prev && prev->right)
                    prev = prev->right;
                return prev;
            }

            if (this->parent)
            {
                // case 2: prev is parent
                if (this == this->parent->right)
                    return this->parent;

                // case 3: prev is grand-parent
                if (this->parent == this->parent->parent->right)
                    return this->parent->parent;
            }

            // case 4: no prev node (node is max)
            return const_cast<pointer>(this);
            */

            if (this->parent)
            {
                if (this == this->parent->right)
                {
                    return this->parent->left
                    ? max(this->parent->left)
                    : this->parent;
                }
                else return this->parent->parent->parent;
            }
            else return NULL;
        }

    };

    /**************************************************************************/
    /*                                                                        */
    /*      Private variables                                                 */
    /*                                                                        */
    /**************************************************************************/

    private:

    pointer         _root;
    size_type	    _size;
    compare	        _comp; // TODO
    allocator_type	_alloc;

    /**************************************************************************/
    /*                                                                        */
    /*      Tree iterator                                                     */
    /*                                                                        */
    /**************************************************************************/

    public:

    // private ?
    template <typename U> // remove
    class rb_tree_iterator : public iterator<bidirectional_iterator_tag, U>
    {
        /****** Member types **************************************************/

        public:

        typedef iterator_traits<rb_tree_iterator>	traits;
        typedef typename traits::iterator_category  iterator_category;
        typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        typedef typename traits::pointer	        pointer;
        typedef typename traits::reference	        reference;

        /****** Private data **************************************************/

        private:

        pointer _data;
        pointer * _root_pointer;

        /****** Constructors **************************************************/

        public:

        /// @brief Constructor by default and by pointer
        explicit rb_tree_iterator (pointer data = NULL, pointer * root_pointer = NULL)
        : _data(data), _root_pointer(root_pointer)
        { }

        rb_tree_iterator (rb_tree_iterator<rb_tree::value_type> const & it)
        : _data(it.data()), _root_pointer(const_cast<pointer*>(it.root_pointer()))
        { }

        rb_tree_iterator (rb_tree_iterator<rb_tree::value_type const> const & it)
        : _data(it.data()), _root_pointer(const_cast<pointer*>(it.root_pointer()))
        { }

        /****** Operators *****************************************************/

        rb_tree_iterator & operator= (rb_tree_iterator const & it)
        { _data = it._data; return *this; }

        /// @note A more natural semantic for this operator would be to return
        /// a node. However, to match the `map` iterator behavior (witch is no
        /// more than a typedef from the current one) we choose to return the
        /// node key instead. In the context of `map`, the node key is a pair.
        key_type & operator* () const
        { return _data->key; }

        /// @note cf. operator*
        key_type * operator-> () const
        { return &_data->key; }

        //template <typename V = U>
        //bool operator== (rb_tree_iterator<U> const & it) const
        //{ return _data == it._data; }
        bool operator== (rb_tree_iterator<rb_tree::value_type> const & it) const
        { return _data == it.data(); }

        //template <typename V = U>
        //bool operator== (rb_tree_iterator<U const> const & it) const
        //{ return _data == it._data; }
        bool operator== (rb_tree_iterator<rb_tree::value_type const> const & it) const
        { return _data == it.data(); }

        //template <typename V = U>
        //bool operator!= (rb_tree_iterator<V> & it) const
        //{ return !(_data == it._data); }
        bool operator!= (rb_tree_iterator<rb_tree::value_type> const & it) const
        { return !(*this == it); }

        //template <typename V = U>
        //bool operator!= (rb_tree_iterator<V const> & it) const
        //{ return !(_data == it._data); }
        bool operator!= (rb_tree_iterator<rb_tree::value_type const> const & it) const
        { return !(*this == it); }

        /// @note prefix
        rb_tree_iterator & operator++ ()
        {
            _data ? _data = _data->next() : _data = min(*_root_pointer);
            return *this;
        }

        /// @note prefix
        rb_tree_iterator & operator-- ()
        {
            _data ? _data = _data->prev() : _data = max(*_root_pointer);
            return *this;
        }

        /// @note postfix
        rb_tree_iterator operator++ (int)
        { rb_tree_iterator tmp = *this; this->operator++(); return tmp; }

        /// @note postfix
        rb_tree_iterator operator-- (int)
        { rb_tree_iterator tmp = *this; this->operator--(); return tmp; }

        /****** Utils (MUST delete later) *************************************/

        pointer data () const
        { return _data;}

        pointer * root_pointer () const
        { return _root_pointer; }

    };

    typedef rb_tree_iterator<value_type>            iterator;
    typedef rb_tree_iterator<value_type const>      const_iterator;

    /// @note 'ft::' mandatory since typedef operands share the same name
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    // what is private inside iterator class should now be protected
    // class rb_tree_const_iterator : public rb_tree_iterator<value_type const> {};
    // typedef rb_tree_const_iterator test;

    /**************************************************************************/
    /*                                                                        */
    /*      Private functions                                                 */
    /*                                                                        */
    /**************************************************************************/

    /// @brief utility for recursive fashion destructor
    void _destroy (pointer const node)
    {
        if (node == NULL)
            return;
        _destroy(node->left);
        _destroy(node->right);
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
    }

    /// @todo ??
    pointer _get_brother (pointer const node)
    {
        return node == node->parent->left
        ? node->parent->right
        : node->parent->left;
    }

    /// @brief recursive fashion
    /// @todo  give std/ft ratio
    pointer _copy (pointer src, pointer parent)
    {
        pointer dst;

        if (src == NULL)
            return NULL;

        dst = _alloc.allocate(1);
        _alloc.construct(dst, *src);

        if (parent)
            dst->parent = parent;

        dst->left = _copy(src->left, dst);
        dst->right = _copy(src->right, dst);

        return dst;
    }

    /// @brief iterative fashion
    /// @todo  give std/ft ratio
    pointer _copy (pointer src)
    {
        pointer dst;
        pointer dst_root;

        if (src == NULL)
            return NULL;
//        _allocate_and_copy(dst, src);
        dst_root = _alloc.allocate(1);
        _alloc.construct(dst_root, *src);
        dst = dst_root;
        while (1)
        {
            while (src->left)
            {
                dst->left = _alloc.allocate(1);
                _alloc.construct(dst->left, *src);
                dst->left->parent = dst;
                src = src->left;
                dst = dst->left;
            }
            dst->left = NULL;
            while (1)
            {
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
                    dst->right = NULL;
                while (1)
                {
                    pointer tmp = src;

                    src = src->parent;
                    if (src == NULL)
                        return dst_root;
                    dst = dst->parent;
                    if (tmp == src->left)
                        break;
                }
            }
        }
    }

    void _left_rotate ();
    void _right_rotate ();

    /// @brief the number of black nodes from `node` (not included) to leafs
    size_type black_height(pointer node);

    /// @brief replace subtree rooted at `a` with subtree rooted at `b`
    void _transplant (pointer a, pointer b)
    {
        if (a->parent == NULL)
            _root = b;
        else if (a == a->parent->left)
            a->parent->left = b;
        else
            a->parent->right = b;
        if (b)
            b->parent = a->parent;
    }

    /**************************************************************************/
    /*                                                                        */
    /*      Member functions                                                  */
    /*                                                                        */
    /**************************************************************************/

    public:

    /****** Utility (might delete later) **************************************/

    pointer * root_ptr ()
    { return &_root; }

    pointer & root_ref ()
    { return  _root; } // !const bc used into map[]

    pointer  root () const
    { return _root; }

    void print (const pointer node)
    {
        if (node == NULL)
            return;

        node->color == Red
        ? std::cout << "\33[31m" << node->key << "\33[0m"
        : std::cout << "\33[37m" << node->key << "\33[0m";

        if (node->left || node->right)
        {
            std::cout << '(';
            print(node->left);
            if (node->right)
            {
                std::cout << ',';
                print(node->right);
            }
            std::cout << ')';
        }
    }

    rb_tree & operator= (const rb_tree & tree)
    {
        _root = _copy(tree._root, NULL);
        //_root = _copy(tree._root);
        return *this;
    }

    /// @todo private + rename to leftmost
    static pointer min (pointer node)
    {
        for (; node && node->left; node = node->left);
        return node;
    }

    /// @todo private + rename to leftmost
    static const_pointer min (const_pointer node)
    {
        for (; node && node->left; node = node->left);
        return node;
    }

    /// @todo private + rename to rightmost
    static pointer max (pointer node)
    {
        for (; node && node->right; node = node->right);
        return node;
    }

    /// @todo private + rename to rightmost
    static const_pointer max (const_pointer node)
    {
        for (; node && node->right; node = node->right);
        return node;
    }

/*
    /// @todo delete: moved into node class
    pointer next(pointer & node)
    {
        // case 1: no next node (empty tree)
        if (node == NULL)
            return node;

        // case 2:
        if (node->right)
        {
            pointer next = node->right;
            while (next && next->left)
                next = next->left;
            return next;
            // return min(node->right);
        }

        if (node->parent)
        {
            // case 3: next is parent
            if (node == node->parent->left)
                return node->parent;

            // case 4: next is grand-parent
            if (node->parent == node->parent->parent->left)
                return node->parent->parent;

            // case 4: next is grand-parent
//            pointer next = node->parent;
//            while (next && next->parent && next == next->parent->right)
//                next = next->parent;
//            if (next->parent)
//                return next->parent;
        }

        // case 5: no next node (node is max)
        return node;
    }

    /// @todo delete: moved into node class
    pointer prev(pointer const & node)
    {
        // case 0: prev node is max
        if (node )
            return (max());

        // case 1: no prev node (empty tree)
        if (node == NULL)
            return node;

        // case 2:
        if (node->left)
        {
            pointer prev = node->left;
            while (prev && prev->right)
                prev = prev->right;
            return prev;
            // return max(node->left);
        }

        if (node->parent)
        {
            // case 3: prev is parent
            if (node == node->parent->right)
                return node->parent;

            // case 4: prev is grand-parent
            if (node->parent == node->parent->parent->right)
                return node->parent->parent;
        }

        // case 5: no prev node (node is max)
        return node;
    }
*/

    /****** Constructors ******************************************************/

    /// @brief Constructor by default
    rb_tree ()
    : _root(NULL), _size(0), _comp(compare()), _alloc(allocator_type()) { }

    /// @brief Constructor by copy
    rb_tree (const rb_tree & tree)
    : _root(NULL), _size(tree._size), _comp(tree._comp), _alloc(tree._alloc)
    { *this = tree; }
    //{ _root = _copy(tree._root, NULL); }

    /// @brief Constructor by iterator range
    rb_tree (iterator first, iterator last, compare comp = compare())
    : _root(NULL), _size(0), _comp(comp), _alloc(allocator_type())
    { insert(first, last); }

    /****** Destructor ********************************************************/

    /// @brief Iterative fashion destructor
    ~rb_tree ()
    {
        pointer	    node;
        pointer     parent;

        node = _root;
        while (node)
        {
            parent = node->parent;
            while (node && node->left)
            {
                parent = node;
                node = node->left;
            }
            if (node && node->right)
            {
                parent = node;
                node = node->right;
            }
            if (node && node->left == NULL && node->right == NULL)
            {
                _alloc.destroy(node);
                _alloc.deallocate(node, 1);
                if (parent && node == parent->left) parent->left = NULL;
                if (parent && node == parent->right) parent->right = NULL;
                node = parent;
            }
        }
    }

    /// @brief Recursive fashion destructor
    //~rb_tree ()
    //{ _destroy(_root); }

    /****** Capacity **********************************************************/

    /// @todo ??
    //size_type height () const { return _height; }

    size_type size () const
    { return _size; }

    bool empty() const
    { return _size == 0; }

    /****** Element access ****************************************************/

    pointer find (key_type const & key)// const
    { return find(_root, key); }

    /// @brief Recursive fashion find
    /// @note  This Red Black Tree support duplicate keys.
    ///        This function return the first equivalent key when there are.
    /// @todo  private ?
    pointer find (const pointer node, const key_type & key) const
    {
        if (node == NULL || node->key == key)
            return node;
        return key < node->key
        ? find(node->left, key)
        : find(node->right, key);
    }

    /****** Modifiers *********************************************************/

    /// @brief insert by `key_type`
    void insert(key_type const & key)
    { return insert(_root, key); }

    /// @brief insert by `value_type`
    void insert (value_type const & val)
    { return insert(_root, val.key); }

    /// @brief To be compliant with tests.
    /// @todo delete this since insert by key will be replaced with insert by value_type
    void insert (iterator position, value_type const val)
    { return insert(&(*position), val.key); }

    void insert (iterator position, key_type key)
    { return insert(position.data(), key); }

    /// @brief Recursive insert
    /// @todo  replace key by node
    /// @note  this is buggy, got to fix it
    void insert (pointer * const node, pointer * const parent, key_type & key)
    {
        // insert at leaf -- or root
        if (*node == NULL)
        {
            // allocate & construct `node` from `key`
            *node = _alloc.allocate(1);
            _alloc.construct(*node, value_type(key));
            _size++;
            // insert `node` below `parent`
            if (parent == NULL)
            {
                (*node)->parent = NULL;
                return;
            }
            (*node)->parent = *parent;
            if (*parent)
            {
                key < (*parent)->key
                ? (*parent)->left = *node
                : (*parent)->right = *node;
            }
            else return;
            // rebalance
            while (*parent && (*parent)->parent && (*parent)->color == Red)
            {
                *node == (*parent)->left
                ?  _left_balance(node, parent, _get_brother(*parent))
                : _right_balance(node, parent, _get_brother(*parent));
            }
            _root->color = Black;
            return;
        }
        // recursive until leaf
        return key < (*node)->key
        ? insert(&(*node)->left, node, key)
        : insert(&(*node)->right, node, key);
    }

    /// @brief Iterative insert
    /// @todo  replace key by node ?
    /// @todo  return pair<iterator,bool> like map insert
    void insert (pointer node, key_type key)
    {
        // parent of the new node
        pointer parent = NULL;

        // find leaf where to insert new node
        while (1) // while (node)
        {
            if (node == NULL) // remove
                break;
            if (key == node->key)
                return;
            while (node && key < node->key)
            {
                parent = node;
                node = node->left;
            }
            while (node && key > node->key)
            {
                parent = node;
                node = node->right;
            }
        }

        // alloc and construct new node
        pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, value_type(key));

        // update size
        _size++;

        // insert parent above new node
        new_node->parent = parent;

        // new node is root: insertion complete
        if (parent == NULL)
        {
            _root = new_node;
            return;
        }

        // insert new node below its parent
        new_node->key < parent->key
        ? parent->left = new_node
        : parent->right = new_node;

        // rebalance
        while (parent && parent->parent && parent->color == Red)
        {
            // left-balance
            if (parent == parent->parent->left)
            {
                /*
                 * case 1: uncle is Red
                 *
                 *        B               R
                 *       / \             / \
                 *      R   R    ==>    B   B
                 *     / \             / \
                 *   (R   R)         (R   R)
                 *
                 */
                if (parent->parent->right && parent->parent->right->color == Red)
                {
                    parent->parent->left->color = Black;
                    parent->parent->right->color = Black;
                    parent->parent->color = Red;
                    new_node = parent->parent;
                    parent = new_node->parent;
                }
                else
                {
                    /*
                     * case 3: node direction != parent direction
                     *
                     *       A                A
                     *      /                /
                     *     B       ==>      C
                     *    / \              / \
                     *   x   C            B   z
                     *      / \          / \
                     *     y   z        x   y
                     *
                     */
                    if (new_node == parent->right)
                    {
                        parent->parent->left = new_node;
                        new_node->parent = parent->parent;

                        parent->right = new_node->left;
                        if (parent->right)
                            parent->right->parent = parent;

                        new_node->left = parent;
                        parent->parent = new_node;

                        parent = new_node;
                        new_node = parent->left;
                    }
                    /*
                     *  case 2: now node direction == parent direction
                     *
                     *         A              C
                     *        /              / \
                     *       C      ==>     /   \
                     *      / \            B     A
                     *     B   z          / \   /
                     *    / \            x   y z
                     *   x   y
                     *
                     */
                    parent->parent->left = parent->right;
                    if (parent->right)
                        parent->right->parent = parent->parent;
                    parent->right = parent->parent;
                    if (parent->parent->parent)
                    {
                        parent->parent == parent->parent->parent->left
                        ? parent->parent->parent->left = parent
                        : parent->parent->parent->right = parent;
                    }
                    else
                        _root = parent;
                    parent->parent = parent->parent->parent;
                    parent->right->parent = parent;

                    parent->color = Black;
                    parent->right->color = Red;
                    break;
                }
            }
            // right-balance
            else
            {
                /*
                 * case 1: uncle is Red
                 *
                 *      B                R
                 *     / \              / \
                 *    R   R     ==>    B   B
                 *       / \              / \
                 *     (R   R)          (R   R)
                 *
                 */
                if (parent->parent->left && parent->parent->left->color == Red)
                {
                    parent->parent->left->color = Black;
                    parent->parent->right->color = Black;
                    parent->parent->color = Red;
                    new_node = parent->parent;
                    parent = new_node->parent;
                }
                else
                {
                    /*
                     * case 3: node direction != parent direction
                     *
                     *    A              A
                     *     \              \
                     *      B     ==>      C
                     *     / \            / \
                     *    C   x          y   B
                     *   / \                / \
                     *  y   z              z   x
                     *
                     */
                    if (new_node == parent->left)
                    {
                        parent->parent->right = new_node;
                        new_node->parent = parent->parent;

                        parent->left = new_node->right;
                        if (parent->left)
                            parent->left->parent = parent;

                        new_node->right = parent;
                        parent->parent = new_node;

                        parent = new_node;
                        new_node = parent->right;
                    }
                    /*
                     *  case 2: now node direction == parent direction
                     *
                     *    A                   C
                     *     \                 / \
                     *      C      ==>      /   \
                     *     / \             A     B
                     *    y   B             \   / \
                     *       / \             y z   x
                     *      z   x
                     *
                     */
                    parent->parent->right = parent->left;
                    if (parent->left)
                        parent->left->parent = parent->parent;
                    parent->left = parent->parent;
                    if (parent->parent->parent)
                    {
                        parent->parent == parent->parent->parent->left
                        ? parent->parent->parent->left = parent
                        : parent->parent->parent->right = parent;
                    }
                    else
                        _root = parent;
                    parent->parent = parent->parent->parent;
                    parent->left->parent = parent;

                    parent->color = Black;
                    parent->left->color = Red;
                    break;
                }
            }
        }

        // TODO
        _root->color = Black;
    }

    /// @brief Insert by iterator range
    void insert (iterator first, iterator last)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    /// @brief the 'erase' used by all other 'erase'
    /// @todo work on colors
    /// @todo private ?
    void erase (pointer node)
    {
        if (node == NULL) return;

        // case 0: node is root
        if (!node->parent)
        {
        //    node->parent = node;
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
            _size--;
            _root = NULL;
            return;
        }

        pointer f; // balance_root
        pointer x;

        // case 1: node has no right child
        if (node->right == NULL)
        {
            f = node->parent;
            x = _get_brother(node);

            /// @note `node->parent` is not null (cf. case 0)
            node->parent->left == node
            ? node->parent->left = node->left
            : node->parent->right = node->left;
            if (node->left)
                node->left->parent = node->parent;

            //_root = NULL; // add
        }

        // case 2: node's right child has no left child
        else if (node->right->left == NULL)
        {
            f = node->right; // f = r
            x = node->right->left;
            //x = node->right->right;
            // dir = 0

            /// @note `node->parent` is not null (cf. case 0)
            node->parent->left == node
            ? node->parent->left = node->right
            : node->parent->right = node->right;
            node->right->parent = node->parent;
            node->right->left = node->left;
            if (node->left)
                node->left->parent = node->right;

            // swap `node->color` and `node->right->color`
            // why keep track of `node->color` ?
            color_type temp = node->color;
            node->color = node->right->color;
            node->right->color = temp;

            if (node->key == 2)
            {
                std::cout << "case 2" << std::endl;
            //    node->color == Red
            //    ? std::cout << "node->color: Red" << std::endl
            //    : std::cout << "node->color: Black" << std::endl;
            }
        }

        // case 3: node's right child has a left child
        else
        {
            // find inorder successor (could also be predecessor)
            pointer succ = node->right->left;
            while (succ->left) { succ = succ->left; }

            f = succ->parent;
            x = succ->parent->right;
            // dir = 1

            // link `succ->parent` to `succ->right`
            succ->parent->left = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;

            // link `succ` to `node` parent
            succ->parent = node->parent;
            /// @note `node->parent` is not null (cf. case 0)
            node == node->parent->left
            ? node->parent->left = succ
            : node->parent->right = succ;

            // link `succ` to `node` left subtree
            succ->left = node->left;
            if (succ->left)
                succ->left->parent = succ;

            // link `succ` to `node` right subtree
            succ->right = node->right;
            if (succ->right)
                succ->right->parent = succ;

            // swap `node->color` and `succ->color`
            // why keep track of `node->color` ?
            color_type temp = node->color;
            node->color = succ->color;
            succ->color = temp;
        }

        // debug
        //return ;

        // rebalance
        if (node->color == Black)
        {
            while (1)
            {
                if (x && x->color == Red)
                {
                    x->color = Black;
                    break;
                }

                if (f == _root)
                    break;

                pointer g = f->parent;
                if (g == NULL)
                    g = _root;

                // left-balance
                if (f == f->parent->left) // null protection ??
                {
                    std::cout << "left-balance" << std::endl;
                    pointer w = f->right;
                    // case reduction
                    if (w->color == Red)
                    {
                        w->color = Black;
                        f->color = Red;

                        f->right = w->left;
                        w->left = f;
                        g->left == f ? g->left = w : g->right = w;

                        w->parent = f->parent;
                        f->parent = w;

                        g = w;
                        w = f->right;

                        w->parent = f;
                    }
                    // case 1
                    if ((w->right == NULL || w->left->color == Black)
                        && (w->right == NULL || w->right->color == Black))
                        w->color = Red;
                    else
                    {
                        // case 3 (transforming into case 2)
                        if (w->right == NULL || w->right->color == Black)
                        {
                            pointer y = w->left;
                            y->color = Black;
                            w->color = Red;
                            w->left = y->right;
                            y->right = w;
                            if (w->left != NULL)
                                w->left->parent = w;
                            w = f->right = y;
                            w->right->parent = w;
                        }
                        // case 2
                        w->color = f->color;
                        f->color = Black;
                        w->right->color = Black;

                        f->right = w->left;
                        w->left = f;
                        g->left == f ? g->left = w : g->right = w;

                        w->parent = f->parent;
                        f->parent = w;
                        if (f->right != NULL)
                            f->right->parent = f;
                        break;
                    }
                }
                // right-balance
                else
                {
                    std::cout << "right-balance" << std::endl;
                    pointer w = f->left;
                    // case reduction
                    if (w->color == Red)
                    {
                        w->color = Black;
                        f->color = Red;

                        f->left = w->right;
                        w->right = f;
                        g->left == f ? g->left = w : g->right = w;

                        w->parent = f->parent;
                        f->parent = w;

                        g = w;
                        w = f->left;

                        w->parent = f;
                    }
                    // case 1
                    if ((w->left == NULL || w->left->color == Black)
                        && (w->right == NULL || w->right->color == Black))
                    {
                        w->color = Red;
                    }
                    else
                    {
                        // case 3 (transforming into case 2)
                        if (w->left == NULL || w->left->color == Black)
                        {
                            pointer y = w->right;
                            y->color = Black;
                            w->color = Red;
                            w->right = y->left;
                            y->left = w;
                            if (w->right != NULL)
                                w->right->parent = w;
                            w = f->left = y;
                            w->left->parent = w;
                        }
                        // case 2
                        w->color = f->color;
                        f->color = Black;
                        w->left->color = Black;

                        f->left = w->right;
                        w->right = f;
                        g->left == f ? g->left = w : g->right = w;

                        w->parent = f->parent;
                        f->parent = w;
                        if (f->left != NULL)
                            f->left->parent = f;
                        break;
                    }
                }
                std::cout << "balance done" << std::endl;
                f = f->parent;
                if (f == NULL)
                    f = _root;
            }
        }

        // destroy and deallocate
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);

        // update size
        _size--;
    }

    // erase by position (1)
    void erase(iterator position)
    { return erase(position.data()); }

    // erase by key (2)
    void erase(key_type const & key)
    { return erase(find(key)); }

    // erase by range (3)
    //void erase(iterator first, iterator last)
    //{ for(; first != last; erase(first), first++); }

    /****** Iterators *********************************************************/

	iterator begin ()
    { return iterator(min(_root), &_root); }

	const_iterator begin () const
    { return const_iterator(min(_root), &_root); }

	iterator end ()
    { return iterator(NULL, &_root); }

	const_iterator end () const
    { return const_iterator(NULL, &_root); }

	reverse_iterator rbegin ()
    { return reverse_iterator(--end()); }

	const_reverse_iterator rbegin () const
    { return const_reverse_iterator(--end()); }

	reverse_iterator rend ()
    { return reverse_iterator(--begin()); }

	const_reverse_iterator rend () const
    { return const_reverse_iterator(--begin()); }

    /****** print *************************************************************/

    public:
    void make_graph ()
    {
		std::ofstream file ("graph.md");
        file << "```mermaid" << std::endl << "graph TD;" << std::endl;
        _draw_graph(file, _root);
        file << "```" << std::endl;
        file.close();
    }

    private:
    void _draw_graph (std::ofstream & file, pointer node)
    {
        file << node->key << "; style " << node->key << " fill:";
        node->color == Red ? file << "red" : file << "black";
        file << std::endl;

        if (node->left)
        {
            file << node->key << " --- " << node->left->key << std::endl;
            _draw_graph(file, node->left);
        } else file << node->key << " --- null" << std::endl;

        if (node->right)
        {
            file << node->key << " --- " << node->right->key << std::endl;
            _draw_graph(file, node->right);
        } else file << node->key << " --- null" << std::endl;
    }
};

/******************************************************************************/
/*                                                                            */
/*      Non member functions                                                  */
/*                                                                            */
/******************************************************************************/

/// @todo add constness to lhs and rhs (then use const_iterators)
template <typename T, typename Comp>
bool operator== (rb_tree<T, Comp> & lhs, rb_tree<T, Comp> & rhs)
{
    typename rb_tree<T, Comp>::iterator lit = lhs.begin();
    typename rb_tree<T, Comp>::iterator rit = rhs.begin();
    typename rb_tree<T, Comp>::iterator lite = lhs.end();
    typename rb_tree<T, Comp>::iterator rite = rhs.end();

    for (; lit != lite && rit != rite && *lit == *rit; lit++, rit++);
    return (lit == lite && rit == rite);
}

/// @todo add constness to lhs and rhs
template <typename T, typename Comp>
bool operator!= (rb_tree<T, Comp> & lhs, rb_tree<T, Comp> & rhs)
{ return !(lhs == rhs); }

} // namespace

#endif /* RB_TREE_HPP */
