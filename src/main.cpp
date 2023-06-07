#include <nox/vector>

#include <iostream>

int main(void)
{
    nox::vector<int> vec;
    for (int i=0; i<20; i++)
    {
        vec.push_back(i);
    }

    for(int &e: vec)
    {
        std::cout << e << "\n";
    }

    auto vec1 = vec.filter([](int &e) -> bool
    {
        return (e % 4) == 0;
    });

    for(int &e: vec1)
    {
        std::cout << e << "\n";
    }

    return 0;
}