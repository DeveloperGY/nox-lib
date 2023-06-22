#include <nox/tui>

#include <iostream>

int main(void)
{
    nox::tui<10, 10> tui;
    tui.draw_fill_rect({0, 0}, {10, 10}, {255, 255, 255});
    tui.draw_line_c({0, 0}, {4, 4}, ' ', {0, 0, 0}, {0, 0, 0});
    tui.draw_line_c({0, 0}, {6, 3}, 'c', {0, 0, 255}, {0, 0, 255});
    tui.draw_line_c({0, 3}, {6, 0}, 'x', {255, 0, 255}, {255, 100, 255});
    tui.display();
    return 0;
}