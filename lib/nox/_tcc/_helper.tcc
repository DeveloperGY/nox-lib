template <class _Tp>
void nox::_destroy(_Tp *__elem) noexcept
{
    __elem->~_Tp();
    return;
}