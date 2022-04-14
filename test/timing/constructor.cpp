#if defined(STD) == 0 && defined(FT) == 0
#error Error: need to #define `STD` or `FT`
#endif

#ifdef FT
#include "ft_vector.hpp"
#define NAMESPACE ft
#endif

#ifdef STD
#include <vector>
#define NAMESPACE std
#endif

// cf. https://stackoverflow.com/a/10791845
// cf. https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define XSTR(x) STR(x)
#define STR(x) #x

int main()
{
   // replace `static_assert` to enable compilation with c++98
   static_assert(XSTR(NAMESPACE) == "std" || XSTR(NAMESPACE) == "ft");

    for (int i = 0; i < 100000; i++)
        NAMESPACE::vector<int> v(1000);

    return 0;
}
