#include <nox/tui>

#include <iostream>

int main(void)
{
    nox::tui<640, 480> display;

    std::cout << " \x1b[48;2;255;255;000mtest\x1b[m\n";

    return 0;
}