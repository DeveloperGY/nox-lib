template <class _Tp>
_Tp *nox::allocator<_Tp>::allocate(std::size_t __n)
{
    _Tp *ptr = (_Tp *)std::malloc(sizeof(_Tp) * __n);

    if (ptr == nullptr)
        nox::__throw_bad_alloc("nox::allocator<T>::allocate()");
    
    return ptr;
}

template <class _Tp>
void nox::allocator<_Tp>::deallocate(_Tp *__ptr)
{
    if (__ptr != nullptr)
        std::free(__ptr);
    __ptr = nullptr;
    return;
}