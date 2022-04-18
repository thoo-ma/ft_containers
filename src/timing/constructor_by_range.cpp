#if defined(STD) == 0 && defined(FT) == 0
#error need to #define `STD` or `FT`
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
    NAMESPACE::vector<int> v1(100, 42);

    for (int i = 0; i < 100000; i++)
        NAMESPACE::vector<int> v2(v1.begin(), v1.begin() + 42);

    return 0;
}
