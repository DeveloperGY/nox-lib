template <std::size_t _Wd, std::size_t _Ht>
nox::tui<_Wd, _Ht>::tui():
    _M_character_buffer(nox::array<char, _Wd*_Ht>()),
    _M_foreground_color_buffer(nox::array<nox::color, _Wd*_Ht>()),
    _M_background_color_buffer(nox::array<nox::color, _Wd*_Ht>())
    // _M_print_buffer(nox::array<char, _Ht * _Wd * 45 + _Ht>())
{
    for (char &__e: this->_M_character_buffer)
    {
        __e = ' ';
    }

    return;
}