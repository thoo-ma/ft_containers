#ifndef FT_LEXICOGRAPHICAL_COMPARE_HPP
#define FT_LEXICOGRAPHICAL_COMPARE_HPP 1

namespace ft {

/// @brief Default compare operator (==)
template <typename InputIterator1, typename InputIterator2>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2)
{
    while (first1 != last1)
    {
        if (first2 == last2)
            return false;
        else if (*first2 < *first1)
            return false;
        else if (*first1 < *first2)
            return true;
        ++first1;
        ++first2;
    }
    return (first2 != last2);
}

/// @brief Custom compare function (comp)
template <class InputIterator1, class InputIterator2, class Compare>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        Compare comp)
{
    while (!comp(first1,last1))
    {
        if (comp(first2, last2))
            return false;
        else if (*first2 < *first1)
            return false;
        else if (*first1 < *first2)
            return true;
        ++first1;
        ++first2;
    }
    return (!comp(first2, last2));
}

} // namespace ft

#endif /* FT_LEXICOGRAPHICAL_COMPARE_HPP */
