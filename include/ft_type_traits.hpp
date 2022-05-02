#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP 1

namespace ft {

    // arbitrary for now
    typedef long unsigned int	size_t;
    typedef long	            ptrdiff_t;

    /****** enable_if *********************************************************/

    template <bool, class T = void>
    struct enable_if { };

    template <class T>
    struct enable_if<true, T> { typedef T type; };

    /****** remove_const ******************************************************/

    // unused for now

    // default case: less specialized
    template <class T>
    struct remove_const { typedef T type; };

    // const case: more specialized
    template <class T> // class U ?
    struct remove_const <T const> { typedef T type; };

    /****** integral_constant *************************************************/

    template <class T, T v>
    struct integral_constant
    {
       typedef T value_type;
       typedef integral_constant<T,v> type;
       static const T value = v; // const would become constexpr with C++11
       operator T()	{ return v; }
    };

    /****** boolean types *****************************************************/

    struct true_type : public ft::integral_constant<bool, true> {};
    struct false_type : public ft::integral_constant<bool, false> {};

    /****** is_integral *******************************************************/

    // add 'char16_t' 'char32_t' 'wchar_t' ?

    // default case: less specialized
    template <class T> struct is_integral : public false_type {};

    // T const case: remove const qualifier
    template <class T> struct is_integral<T const> : public is_integral<T> {};

    // particular cases
    template <> struct is_integral<bool> : public true_type {};
    template <> struct is_integral<char> : public true_type {};
    template <> struct is_integral<int> : public true_type {};
    template <> struct is_integral<short> : public true_type {};
    template <> struct is_integral<long> : public true_type {};
    template <> struct is_integral<long long> : public true_type {};
    template <> struct is_integral<unsigned char> : public true_type {};
    template <> struct is_integral<unsigned int> : public true_type {};
    template <> struct is_integral<unsigned short> : public true_type {};
    template <> struct is_integral<unsigned long> : public true_type {};
    template <> struct is_integral<unsigned long long> : public true_type {};

    // 'signed char' is a different type than 'char'
    template <> struct is_integral<signed char> : public is_integral<char> {};

} // namespace ft

#endif /* FT_TYPE_TRAITS_HPP */
