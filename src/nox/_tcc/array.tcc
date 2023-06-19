// Element access

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::at(std::size_t __index)
{
    if (__index >= _ElementCount)
        nox::__throw_out_of_range("nox::array::at()");

    return this->m_elems[__index];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::at(std::size_t __index) const
{
    if (__index >= _ElementCount)
        nox::__throw_out_of_range("nox::array::at()");

    return this->m_elems[__index];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::operator[](std::size_t __index) noexcept
{
    return this->m_elems[__index];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::operator[](std::size_t __index) const noexcept
{
    return this->m_elems[__index];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::front() noexcept
{
    return this->m_elems[0];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::front() const noexcept
{
    return this->m_elems[0];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::back() noexcept
{
    return this->m_elems[_ElementCount];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type &nox::array<_Type, _ElementCount>::back() const noexcept
{
    return this->m_elems[_ElementCount ? _ElementCount-1 : 0];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type *nox::array<_Type, _ElementCount>::data() noexcept
{
    return this->m_elems;
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type *nox::array<_Type, _ElementCount>::data() const noexcept
{
    return this->m_elems;
}

// Iterators

template <class _Type, std::size_t _ElementCount>
constexpr _Type *nox::array<_Type, _ElementCount>::begin() noexcept
{
    return &this->m_elems[0];
}

template <class _Type, std::size_t _ElementCount>
constexpr const _Type *nox::array<_Type, _ElementCount>::begin() const noexcept
{
    return &this->m_elems[0];
}

template <class _Type, std::size_t _ElementCount>
constexpr _Type *nox::array<_Type, _ElementCount>::end() noexcept
{
    return &this->m_elems[_ElementCount];
}

template <class _Type, std::size_t _ElementCount>
constexpr const _Type *nox::array<_Type, _ElementCount>::end() const noexcept
{
    return &this->m_elems[_ElementCount];
}

// Capacity

template <class _Type, std::size_t _ElementCount>
constexpr bool nox::array<_Type, _ElementCount>::empty() const noexcept
{
    return this->begin() == this->end();
}

template <class _Type, std::size_t _ElementCount>
constexpr std::size_t nox::array<_Type, _ElementCount>::size() const noexcept
{
    return _ElementCount;
}

// Modifiers

template <class _Type, std::size_t _ElementCount>
constexpr void nox::array<_Type, _ElementCount>::fill(const _Type & __element) noexcept
{
    for (_Type &element: *this)
    {
        element = __element;
    }

    return;
}

template <class _Type, std::size_t _ElementCount>
constexpr void nox::array<_Type, _ElementCount>::swap(nox::array<_Type, _ElementCount> &__array) noexcept
{
    _Type *temp = this->m_elems;
    this->m_elems = __array.m_elems;
    __array.m_elems = temp;

    return;
}

template <class _Type, std::size_t _ElementCount>
constexpr nox::vector<_Type> nox::array<_Type, _ElementCount>::filter(bool (*__predicate)(const _Type &)) const
{
    nox::vector<_Type> vec;

    for (const _Type &element: *this)
    {
        if (__pred(element))
            vec.push_back(element);
    }

    return vec;
}