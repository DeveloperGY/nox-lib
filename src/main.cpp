#include <nox/tui>

#include <iostream>

int main(void)
{
    nox::tui<10, 10> tui;
    tui.draw_character({1,1}, 'C', {255, 0, 255}, {0, 255, 0});
    tui.draw_pixel({2, 2}, {89, 73, 158});
    tui.display();
    return 0;
}