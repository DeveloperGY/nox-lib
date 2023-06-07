#include <nox/array>
#include <nox/vector>

#include <iostream>

int main(void)
{
    nox::array<int, 5> arr = {0, 1, 2, 3, 4};
    nox::vector<int> vec;
    for (int i=0; i<20; i++)
    {
        vec.push_back(i);
    }

    for (int &e: arr)
    {
        std::cout << e << "\n";
    }

    for(int &e: vec)
    {
        std::cout << e << "\n";
    }

    return 0;
}