#include <nox/array>
#include <nox/vector>

#include <iostream>

void func(const int* data, std::size_t size)
{
    return;
}

int main(void)
{
    nox::array<int, 5> arr = {0, 1, 2, 3, 4};

    nox::vector<int> vec;
    vec = {0, 1, 2, 3, 4};

    return 0;
}