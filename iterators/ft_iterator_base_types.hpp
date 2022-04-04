#ifndef ITERATOR_BASE_TYPES_H
#define ITERATOR_BASE_TYPES_H 1

#include <memory>

namespace ft
{
    /**
     *    @defgroup iterators Iterators
     *    Abstractions for uniform iterating through various underlying types.
    */

    /**
     *    @defgroup iterator_tags Iterator Tags
     *    These are empty types, used to distinguish different iterators. The
     *    distinction is not made by what they contain, but simply by what they
     *    are. Different underlying algorithms can then be used based on the
     *    different operations supported by different iterator types.
    */

    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    /**
     *    @brief    Common iterator class.
     *
     *    This class does nothing but define nested typedefs. Iterator classes
     *    can inherit from this class to save some work. The typedefs are then
     *    used in specializations and overloading.
     *
     *    In particular, there are no default implementations of requirements
     *    such as operator++ and the like. (How could there be?)
    */
    template
    <
        typename Category,
        typename T,
        typename Distance = ptrdiff_t,
        typename Pointer = T *,
        typename Reference = T &
    >
    struct iterator
    {
        typedef Category    iterator_category;  // One of the iterator_tags.
        typedef T	        value_type;         // What iterator points to.
        typedef Distance    difference_type;    // Distance between iterators.
        typedef Pointer     pointer;	        // Pointer-to-value's type.
        typedef Reference   reference;          // Reference-to-value's type.
    };

    /**
     *    @brief    Traits class for iterators.
     *
     *    This class does nothing but define nested typedefs. The general
     *    version simply forwards the nested typedefs from the Iterator
     *    argument. Specialized versions for pointers and pointers-to-const
     *    provide tighter, more correct semantics.
    */
    template<typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

} // namespace ft

#endif /* ITERATOR_BASE_TYPES_H */
