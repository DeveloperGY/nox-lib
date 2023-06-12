template <class _Tp, class _Al>
constexpr nox::vector<_Tp, _Al>::vector()
{
    _Al al;

    this->_M_elems = al.allocate(1);
    this->_M_capacity = 1;
    this->_M_size = 0;
}

template <class _Tp, class _Al>
nox::vector<_Tp, _Al>::~vector() noexcept
{
    _Al al;
    al.deallocate(this->_M_elems);
    this->_M_capacity = 0;
    this->_M_size = 0;
}

template <class _Tp, class _Al>
constexpr nox::vector<_Tp, _Al> &nox::vector<_Tp, _Al>::operator=(nox::vector<_Tp, _Al> &__v)
{
    _Al al;
    _Tp *arr = al.allocate(__v._M_capacity);
    al.deallocate(this->_M_elems);
    this->_M_size = 0;
    this->_M_capacity = __v._M_capacity;

    for (_Tp &e: __v)
    {
        this->push_back(e);
    }

    return *this;
}

// Element access

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::operator[](std::size_t __n) noexcept
{
    return this->_M_elems[__n];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::operator[](std::size_t __n) const noexcept
{
    return this->_M_elems[__n];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::at(std::size_t __n)
{
    if (__n >= this->_M_size)
        nox::__throw_out_of_range("nox::vector::at()");
    
    return this->_M_elems[__n];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::at(std::size_t __n) const
{
    if (__n >= this->_M_size)
        nox::__throw_out_of_range("nox::vector::at()");
    
    return this->_M_elems[__n];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::front() noexcept
{
    return this->_elems[0];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::front() const noexcept
{
    return this->_elems[0];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::back() noexcept
{
    return this->_M_elems[this->_M_size-1];
}

template <class _Tp, class _Al>
constexpr _Tp &nox::vector<_Tp, _Al>::back() const noexcept
{
    return this->_M_elems[this->_M_size-1];
}

template <class _Tp, class _Al>
constexpr _Tp *nox::vector<_Tp, _Al>::data() noexcept
{
    return this->_M_elems;
}

template <class _Tp, class _Al>
constexpr _Tp *nox::vector<_Tp, _Al>::data() const noexcept
{
    return this->_M_elems;
}

// Iterators

template <class _Tp, class _Al>
constexpr _Tp *nox::vector<_Tp, _Al>::begin() noexcept
{
    return &this->_M_elems[0];
}

template <class _Tp, class _Al>
constexpr _Tp *nox::vector<_Tp, _Al>::begin() const noexcept
{
    return &this->_M_elems[0];
}

template <class _Tp, class _Al>
constexpr _Tp *nox::vector<_Tp, _Al>::end() noexcept
{
    return &this->_M_elems[this->_M_size];
}

template <class _Tp, class _Al>
constexpr _Tp *nox::vector<_Tp, _Al>::end() const noexcept
{
    return &this->_M_elems[this->_M_size];
}

// Capacity

template <class _Tp, class _Al>
constexpr bool nox::vector<_Tp, _Al>::empty() noexcept
{
    return this->_M_size == 0;
}

template <class _Tp, class _Al>
constexpr bool nox::vector<_Tp, _Al>::empty() const noexcept
{
    return this->_M_size == 0;
}