template <class _Type>
_Type *nox::allocator<_Type>::allocate(std::size_t __element_count)
{
    _Type *ptr = (_Type *)std::malloc(sizeof(_Type) * __element_count);

    if (ptr == nullptr)
        nox::__throw_bad_alloc("nox::allocator<T>::allocate()");
    
    return ptr;
}

template <class _Type>
void nox::allocator<_Type>::deallocate(_Type *__ptr)
{
    if (__ptr != nullptr)
        std::free(__ptr);
    __ptr = nullptr;
    return;
}