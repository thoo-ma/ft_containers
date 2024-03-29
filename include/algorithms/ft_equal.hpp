#ifndef FT_EQUAL_HPP
#define FT_EQUAL_HPP 1

namespace ft {

template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    while (first1 != last1)
    {
        if (!(*first1 == *first2))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

} // namespace

#endif /* FT_EQUAL_HPP */