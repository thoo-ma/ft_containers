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

#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring> // strcmp

#define xstr(s) str(s)
#define str(s) #s

using namespace std::chrono;

int main()
{
    // open file
    std::ofstream outfile ("timing.csv", std::ofstream::app);

    // check for open error
    if (outfile.rdstate())
    {
        std::cout << "Error: can't open timing.csv" << std::endl;
        return 1;
    }

    // append to file
    strcmp(xstr(NAMESPACE), "ft") == 0
    ? outfile << "vector,clear,"
    : outfile << ",";

    // useful stuff
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;

    NAMESPACE::vector<int> vec(10000, 42);
    NAMESPACE::vector<int> arr[10000];

    for (int i = 0; i < 10000; i++)
        arr[i] = vec;

    // starting point
    start = std::chrono::system_clock::now();

    // compute
    for (int i = 0; i < 10000; i++)
        arr[i].clear();

    // ending point
    end = std::chrono::system_clock::now();

    // get delta
    std::chrono::duration<double> delta = end - start;

    // append delta
    outfile << delta.count();

    // close file
    outfile.close();

    return 0;
}
