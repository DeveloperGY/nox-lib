#include <nox/tui>
#include <nox/io>

#include <iostream>

int main(void)
{
    nox::tui<40, 24> tui;

    nox::getch(0);

    tui.display();
    return 0;
}