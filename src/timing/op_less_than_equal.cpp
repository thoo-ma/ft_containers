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

int main()
{
    NAMESPACE::vector<int> v1(100, 42);
    NAMESPACE::vector<int> v2(100, 21);

    for (int i = 0; i < 10000000; i++)
        (void)(v1 <= v2);

    return 0;
}
