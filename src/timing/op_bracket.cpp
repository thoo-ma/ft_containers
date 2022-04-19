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
    NAMESPACE::vector<int> v(1000000, 42);
    int j;

    for (int i = 0; i < 1000000; i++)
        j = v[i];

    (void)j;

    return 0;
}
