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