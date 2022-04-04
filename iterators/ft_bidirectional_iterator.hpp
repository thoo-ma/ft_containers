#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H 1

#include "ft_iterator_base_types.hpp"

namespace ft {

template <typename T>
class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T>
{
    public:

    typedef iterator<bidirectional_iterator_tag, T> base_iterator;

    // these types need to be redefined.
    // cf. https://stackoverflow.com/questions/32270597/inheriting-typedefs

    typedef typename base_iterator::iterator_category iterator_category;
    typedef typename base_iterator::value_type        value_type;
    typedef typename base_iterator::difference_type   difference_type;
    typedef typename base_iterator::pointer           pointer;
    typedef typename base_iterator::reference         reference;

    protected: T * _data;
};

} // namespace ft

#endif /* BIDIRECTIONAL_ITERATOR_H */
