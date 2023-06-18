template <std::size_t _Wd, std::size_t _Ht>
nox::tui<_Wd, _Ht>::tui()
{
    this->_M_character_buffer.reserve(_Wd * _Ht);
    this->_M_foreground_color_buffer.reserve(_Wd * _Ht);
    this->_M_background_color_buffer.reserve(_Wd * _Ht);
    this->_M_print_buffer.reserve(_Ht * (_Wd * 42 + 1));

    for (std::size_t i=0; i<_Wd*_Ht; i++)
    {
        this->_M_character_buffer.push_back(' ');
        this->_M_foreground_color_buffer.push_back({0, 0, 0});
        this->_M_background_color_buffer.push_back({0, 0, 0});
    }

    for (std::size_t i=0; i<_Ht * (_Wd * 42 + 1); i++)
    {
        this->_M_print_buffer.push_back(' ');
    }

    return;
}

template <std::size_t _Wd, std::size_t _Ht>
constexpr void nox::tui<_Wd, _Ht>::display() noexcept
{
    std::size_t index = 0;

    char __fg_red[4];
    char __fg_green[4];
    char __fg_blue[4];

    char __bg_red[4];
    char __bg_green[4];
    char __bg_blue[4];

    for (std::size_t __row=0; __row<_Ht; __row++)
    {
        for (std::size_t __col=0; __col<_Wd; __col++)
        {
            std::size_t __current_pixel = __row * _Wd + __col;

            std::snprintf(__fg_red, 4, "%03d", this->_M_foreground_color_buffer[__current_pixel].x);
            std::snprintf(__fg_green, 4, "%03d", this->_M_foreground_color_buffer[__current_pixel].y);
            std::snprintf(__fg_blue, 4, "%03d", this->_M_foreground_color_buffer[__current_pixel].z);

            std::snprintf(__bg_red, 4, "%03d", this->_M_background_color_buffer[__current_pixel].x);
            std::snprintf(__bg_green, 4, "%03d", this->_M_background_color_buffer[__current_pixel].y);
            std::snprintf(__bg_blue, 4, "%03d", this->_M_background_color_buffer[__current_pixel].z);

            this->_M_print_buffer[index++] = '\x1b';
            this->_M_print_buffer[index++] = '[';
            this->_M_print_buffer[index++] = '3';
            this->_M_print_buffer[index++] = '8';
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = '2';
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = __fg_red[0];
            this->_M_print_buffer[index++] = __fg_red[1];
            this->_M_print_buffer[index++] = __fg_red[2];
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = __fg_green[0];
            this->_M_print_buffer[index++] = __fg_green[1];
            this->_M_print_buffer[index++] = __fg_green[2];
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = __fg_blue[0];
            this->_M_print_buffer[index++] = __fg_blue[1];
            this->_M_print_buffer[index++] = __fg_blue[2];
            this->_M_print_buffer[index++] = 'm';
            this->_M_print_buffer[index++] = '\x1b';
            this->_M_print_buffer[index++] = '[';
            this->_M_print_buffer[index++] = '4';
            this->_M_print_buffer[index++] = '8';
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = '2';
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = __bg_red[0];
            this->_M_print_buffer[index++] = __bg_red[1];
            this->_M_print_buffer[index++] = __bg_red[2];
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = __bg_green[0];
            this->_M_print_buffer[index++] = __bg_green[1];
            this->_M_print_buffer[index++] = __bg_green[2];
            this->_M_print_buffer[index++] = ';';
            this->_M_print_buffer[index++] = __bg_blue[0];
            this->_M_print_buffer[index++] = __bg_blue[1];
            this->_M_print_buffer[index++] = __bg_blue[2];
            this->_M_print_buffer[index++] = 'm';
            this->_M_print_buffer[index++] = this->_M_character_buffer[__current_pixel];
            this->_M_print_buffer[index++] = '\x1b';
            this->_M_print_buffer[index++] = '[';
            this->_M_print_buffer[index++] = 'm';

            this->_M_character_buffer[__current_pixel] = ' ';
            this->_M_foreground_color_buffer[__current_pixel] = {0, 0, 0};
            this->_M_background_color_buffer[__current_pixel] = {0, 0, 0};
        }
        this->_M_print_buffer[index++] = '\n';
    }

    this->_M_print_buffer[index-1] = '\0';

    std::printf("\x1b[2J\x1b[H%s", this->_M_print_buffer.data());

    return;
}

template <std::size_t _Wd, std::size_t _Ht>
constexpr void nox::tui<_Wd, _Ht>::draw_character(nox::vec2<std::size_t> __pos, const char &__c, const nox::color &__fg, const nox::color &__bg) noexcept
{
    if (__pos.x < _Wd && __pos.y < _Ht)
    {
        std::size_t __index = __pos.y * _Wd + __pos.x;
        this->_M_character_buffer[__index] = __c;
        this->_M_foreground_color_buffer[__index] = __fg;
        this->_M_background_color_buffer[__index] = __bg;
    }
    
    return;
}

template <std::size_t _Wd, std::size_t _Ht>
constexpr void nox::tui<_Wd, _Ht>::draw_pixel(nox::vec2<std::size_t> __pos, const nox::color &__color) noexcept
{
    if (__pos.x < _Wd && __pos.y < _Ht)
    {
        std::size_t __index = __pos.y * _Wd + __pos.x;
        this->_M_character_buffer[__index] = ' ';
        this->_M_foreground_color_buffer[__index] = __color;
        this->_M_background_color_buffer[__index] = __color;
    }
    return;
}