template <std::size_t _Width, std::size_t _Height>
nox::tui<_Width, _Height>::tui()
{
    // Number of characters required to represent one character in the tui,
    // including the character to be printed, represented in number of characters
    const std::size_t ANSI_ESCAPE_CODE_LENGTH = 42;

    // Length of one line in the print buffer, represented in number of characters
    // The + 1 represents a newline or null terminator character
    const std::size_t PRINT_LINE_LENGTH = _Width * ANSI_ESCAPE_CODE_LENGTH + 1;

    this->m_character_buffer.reserve(_Width * _Height);
    this->m_foreground_color_buffer.reserve(_Width * _Height);
    this->m_background_color_buffer.reserve(_Width * _Height);
    
    this->m_print_buffer.reserve(_Height * PRINT_LINE_LENGTH); 

    for (std::size_t index=0; index<_Width*_Height; index++)
    {
        this->m_character_buffer.push_back(' ');
        this->m_foreground_color_buffer.push_back({0, 0, 0});
        this->m_background_color_buffer.push_back({0, 0, 0});
    }

    for (std::size_t index=0; index<_Height * PRINT_LINE_LENGTH; index++)
    {
        this->m_print_buffer.push_back(' ');
    }

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::display() noexcept
{
    // The index in the print buffer
    std::size_t index = 0;

    // string representations of the color values
    char foreground_red[4];
    char foreground_green[4];
    char foreground_blue[4];

    char background_red[4];
    char background_green[4];
    char background_blue[4];

    for (std::size_t row=0; row<_Height; row++)
    {
        for (std::size_t col=0; col<_Width; col++)
        {
            // A conversion from 2d array index form to 1d array index form
            std::size_t current_pixel = row * _Width + col;

            std::snprintf(foreground_red, 4, "%03d", this->m_foreground_color_buffer[current_pixel].r);
            std::snprintf(foreground_green, 4, "%03d", this->m_foreground_color_buffer[current_pixel].g);
            std::snprintf(foreground_blue, 4, "%03d", this->m_foreground_color_buffer[current_pixel].b);

            std::snprintf(background_red, 4, "%03d", this->m_background_color_buffer[current_pixel].r);
            std::snprintf(background_green, 4, "%03d", this->m_background_color_buffer[current_pixel].g);
            std::snprintf(background_blue, 4, "%03d", this->m_background_color_buffer[current_pixel].b);

            this->m_print_buffer[index++] = '\x1b';
            this->m_print_buffer[index++] = '[';
            this->m_print_buffer[index++] = '3';
            this->m_print_buffer[index++] = '8';
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = '2';
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = foreground_red[0];
            this->m_print_buffer[index++] = foreground_red[1];
            this->m_print_buffer[index++] = foreground_red[2];
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = foreground_green[0];
            this->m_print_buffer[index++] = foreground_green[1];
            this->m_print_buffer[index++] = foreground_green[2];
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = foreground_blue[0];
            this->m_print_buffer[index++] = foreground_blue[1];
            this->m_print_buffer[index++] = foreground_blue[2];
            this->m_print_buffer[index++] = 'm';
            this->m_print_buffer[index++] = '\x1b';
            this->m_print_buffer[index++] = '[';
            this->m_print_buffer[index++] = '4';
            this->m_print_buffer[index++] = '8';
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = '2';
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = background_red[0];
            this->m_print_buffer[index++] = background_red[1];
            this->m_print_buffer[index++] = background_red[2];
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = background_green[0];
            this->m_print_buffer[index++] = background_green[1];
            this->m_print_buffer[index++] = background_green[2];
            this->m_print_buffer[index++] = ';';
            this->m_print_buffer[index++] = background_blue[0];
            this->m_print_buffer[index++] = background_blue[1];
            this->m_print_buffer[index++] = background_blue[2];
            this->m_print_buffer[index++] = 'm';
            this->m_print_buffer[index++] = this->m_character_buffer[current_pixel];
            this->m_print_buffer[index++] = '\x1b';
            this->m_print_buffer[index++] = '[';
            this->m_print_buffer[index++] = 'm';

            this->m_character_buffer[current_pixel] = ' ';
            this->m_foreground_color_buffer[current_pixel] = {0, 0, 0};
            this->m_background_color_buffer[current_pixel] = {0, 0, 0};
        }
        this->m_print_buffer[index++] = '\n';
    }

    this->m_print_buffer[index-1] = '\0';

    std::printf("\x1b[2J\x1b[H%s", this->m_print_buffer.data());

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_character(nox::vec2<std::size_t> __position, const char &__character, const nox::color &__foreground_color, const nox::color &__background_color) noexcept
{
    if (__position.x < _Width && __position.y < _Height)
    {
        std::size_t index = __position.y * _Width + __position.x;
        this->m_character_buffer[index] = __character;
        this->m_foreground_color_buffer[index] = __foreground_color;
        this->m_background_color_buffer[index] = __background_color;
    }
    
    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_pixel(nox::vec2<std::size_t> __position, const nox::color &__color) noexcept
{
    this->draw_character(__position, ' ', __color, __color);
    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_rect_c(nox::vec2<std::size_t> __position, nox::vec2<std::size_t> __dimensions, const char &__fill_character, const char &__border_character, const nox::color &__fill_foreground_color, const nox::color &__fill_background_color, const nox::color &__border_foreground_color, const nox::color &__border_background_color)
{
    for (std::size_t row=0; row<__dimensions.y; row++)
    {
        for (std::size_t col=0; col<__dimensions.x; col++)
        {
            if (row == 0 || col == 0 || row == __dimensions.y-1 || col == __dimensions.x-1)
                this->draw_character({__position.x + col, __position.y + row}, __border_character, __border_foreground_color, __border_background_color);
            else
                this->draw_character({__position.x + col, __position.y + row}, __fill_character, __fill_foreground_color, __fill_background_color);
        }
    }

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_rect(nox::vec2<std::size_t> __position, nox::vec2<std::size_t> __dimensions, const nox::color &__fill_color, const nox::color &__border_color)
{
    this->draw_rect_c(__position, __dimensions, ' ', ' ', __fill_color, __fill_color, __border_color, __border_color);
    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_fill_rect_c(nox::vec2<std::size_t> __position, nox::vec2<std::size_t> __dimensions, const char &__character, const nox::color &__foreground_color, const nox::color &__background_color)
{
    this->draw_rect_c(__position, __dimensions, __character, __character, __foreground_color, __background_color, __foreground_color, __background_color);
    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_fill_rect(nox::vec2<std::size_t> __position, nox::vec2<std::size_t> __dimensions, const nox::color &__color)
{
    this->draw_fill_rect_c(__position, __dimensions, ' ', __color, __color);
    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_stroke_rect_c(nox::vec2<std::size_t> __position, nox::vec2<std::size_t> __dimensions, const char &__character, const nox::color &__foreground_color, const nox::color &__background_color)
{
    for (std::size_t row=0; row<__dimensions.y; row++)
    {
        for (std::size_t col=0; col<__dimensions.x; col++)
        {
            if (row == 0 || col == 0 || row == __dimensions.y-1 || col == __dimensions.x-1)
                this->draw_character({__position.x + col, __position.y + row}, __character, __foreground_color, __background_color);
        }
    }

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_stroke_rect(nox::vec2<std::size_t> __position, nox::vec2<std::size_t> __dimensions, const nox::color &__color)
{
    this->draw_stroke_rect_c(__position, __dimensions, ' ', __color, __color);

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_text_horizontal(nox::vec2<std::size_t> __position, const char *__text, const nox::color &__foreground_color, const nox::color &__background_color)
{
    for (std::size_t index=0; __text[index]!='\0'; index++)
    {
        this->draw_character({__position.x + index, __position.y}, __text[index], __foreground_color, __background_color);
    }

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_text_vertical(nox::vec2<std::size_t> __position, const char *__text, const nox::color &__foreground_color, const nox::color &__background_color)
{
    for (std::size_t index=0; __text[index]!='\0'; index++)
    {
        this->draw_character({__position.x, __position.y + index}, __text[index], __foreground_color, __background_color);
    }

    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_line_c(nox::vec2<std::size_t> __start_position, nox::vec2<std::size_t> __end_position, const char &__character, const nox::color __foreground_color, const nox::color &__background_color)
{
    int dx = (int)__end_position.x - (int)__start_position.x;
    int dy = (int)__end_position.y - (int)__start_position.y;

    if (dy == 0)
    {
        for (std::size_t x_value=__start_position.x; x_value<=__end_position.x; x_value++)
        {
            this->draw_character({x_value, __start_position.y}, __character, __foreground_color, __background_color);
        }

        return;
    }
    else if (dx == 0)
    {
        for (std::size_t y_value=__start_position.y; y_value<=__end_position.y; y_value++)
        {
            this->draw_character({__start_position.x, y_value}, __character, __foreground_color, __background_color);
        }

        return;
    }

    float slope = (float)dy/(float)dx;
    bool loop_y = slope > 1.0f || slope < -1.0f;

    slope = (loop_y) ? -1 / slope : slope;

    std::size_t independent_start = (loop_y) ? ((__start_position.y > __end_position.y) ? __end_position.y : __start_position.y) : ((__start_position.x > __end_position.x) ? __end_position.x : __start_position.x);
    std::size_t independent_end = (loop_y) ? ((__start_position.y > __end_position.y) ? __start_position.y : __end_position.y) : ((__start_position.x > __end_position.x) ? __start_position.x : __end_position.x);
    std::size_t dependent_start = (loop_y) ? ((__start_position.y > __end_position.y) ? __end_position.x : __start_position.x) : ((__start_position.x > __end_position.x) ? __end_position.y : __start_position.y);
    std::size_t dependent_end = (loop_y) ? ((__start_position.y > __end_position.y) ? __start_position.x : __end_position.x) : ((__start_position.x > __end_position.x) ? __start_position.y : __end_position.y);

    float error = 0.0f;
    std::size_t independent = independent_start;
    std::size_t dependent = dependent_start;
    
    std::size_t *x_coord = (loop_y) ? &dependent : &independent;
    std::size_t *y_coord = (loop_y) ? &independent : &dependent;
    
    float error_modifier = (slope >= 0) ? slope : -1 * slope;
    std::size_t dependent_modifier = (slope >= 0) ? ((loop_y) ? -1 : 1) : ((loop_y) ? 1 : -1);

    for (;independent<independent_end; independent++)
    {
        this->draw_character({*x_coord, *y_coord}, __character, __foreground_color, __background_color);

        error += error_modifier;
        if (error > 0.5f)
        {
            dependent += dependent_modifier;
            error -= 1.0f;
        }
    }
    
    return;
}

template <std::size_t _Width, std::size_t _Height>
constexpr void nox::tui<_Width, _Height>::draw_line(nox::vec2<std::size_t> __start_position, nox::vec2<size_t> __end_position, const nox::color *__color)
{
    this->draw_line_c(__start_position, __end_position, ' ', __color, __color);
    return;
}