// Element access

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::at(std::size_t __n)
{
    if (__n >= _Nm)
        nox::__throw_out_of_range("nox::array::at()");

    return this->_M_elems[__n];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::at(std::size_t __n) const
{
    if (__n >= _Nm)
        nox::__throw_out_of_range("nox::array::at()");

    return this->_M_elems[__n];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::operator[](std::size_t __n) noexcept
{
    return this->_M_elems[__n];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::operator[](std::size_t __n) const noexcept
{
    return this->_M_elems[__n];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::front() noexcept
{
    return this->_M_elems[0];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::front() const noexcept
{
    return this->_M_elems[0];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::back() noexcept
{
    return this->_M_elems[_Nm];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp &nox::array<_Tp, _Nm>::back() const noexcept
{
    return this->_M_elems[_Nm ? _Nm-1 : 0];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp *nox::array<_Tp, _Nm>::data() noexcept
{
    return this->_M_elems;
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp *nox::array<_Tp, _Nm>::data() const noexcept
{
    return this->_M_elems;
}

// Iterators

template <class _Tp, std::size_t _Nm>
constexpr _Tp *nox::array<_Tp, _Nm>::begin() noexcept
{
    return &this->_M_elems[0];
}

template <class _Tp, std::size_t _Nm>
constexpr const _Tp *nox::array<_Tp, _Nm>::begin() const noexcept
{
    return &this->_M_elems[0];
}

template <class _Tp, std::size_t _Nm>
constexpr _Tp *nox::array<_Tp, _Nm>::end() noexcept
{
    return &this->_M_elems[_Nm];
}

template <class _Tp, std::size_t _Nm>
constexpr const _Tp *nox::array<_Tp, _Nm>::end() const noexcept
{
    return &this->_M_elems[_Nm];
}

// Capacity

template <class _Tp, std::size_t _Nm>
constexpr bool nox::array<_Tp, _Nm>::empty() const noexcept
{
    return this->begin() == this->end();
}

template <class _Tp, std::size_t _Nm>
constexpr std::size_t nox::array<_Tp, _Nm>::size() const noexcept
{
    return _Nm;
}

// Modifiers

template <class _Tp, std::size_t _Nm>
constexpr void nox::array<_Tp, _Nm>::fill(const _Tp & __e) noexcept
{
    for (_Tp &e: *this)
    {
        e = __e;
    }

    return;
}

template <class _Tp, std::size_t _Nm>
constexpr void nox::array<_Tp, _Nm>::swap(nox::array<_Tp, _Nm> &__a) noexcept
{
    _Tp *__temp = this->_M_elems;
    this->_M_elems = __a._M_elems;
    __a._M_elems = __temp;

    return;
}

template <class _Tp, std::size_t _Nm>
constexpr nox::vector<_Tp> nox::array<_Tp, _Nm>::filter(bool (*__pred)(const _Tp &)) const
{
    nox::vector<_Tp> __v;

    for (const _Tp &__e: *this)
    {
        if (__pred(__e))
            __v.push_back(__e);
    }

    return __v;
}