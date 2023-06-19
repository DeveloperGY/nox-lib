#include <nox/tui>

#include <iostream>

int main(void)
{
    nox::tui<20, 10> tui;
    tui.draw_character({1,1}, 'C', {255, 0, 255}, {0, 255, 0});
    tui.draw_pixel({2, 2}, {89, 73, 158});
    tui.draw_rect({3, 3}, {6, 4}, {255, 100, 255}, {255, 100, 255});
    tui.draw_fill_rect({4, 4}, {4, 2}, {255, 255, 255});
    tui.display();
    return 0;
}