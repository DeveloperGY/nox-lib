template <class _Type, class _Allocator>
constexpr nox::vector<_Type, _Allocator>::vector()
{
    _Allocator al;

    this->m_elems = al.allocate(1);
    this->m_capacity = 1;
    this->m_size = 0;
}

template <class _Type, class _Allocator>
nox::vector<_Type, _Allocator>::~vector() noexcept
{
    _Allocator al;
    al.deallocate(this->m_elems);
    this->m_capacity = 0;
    this->m_size = 0;
}

template <class _Type, class _Allocator>
constexpr nox::vector<_Type, _Allocator> &nox::vector<_Type, _Allocator>::operator=(const nox::vector<_Type, _Allocator> &__vector)
{
    _Allocator al;
    _Type *ptr = al.allocate(__vector.m_capacity);
    al.deallocate(this->m_elems);
    this->m_elems = ptr;
    this->m_size = 0;
    this->m_capacity = __vector.m_capacity;

    for (_Type &element: __vector)
    {
        this->push_back(element);
    }

    return *this;
}

// Element access

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::operator[](std::size_t __index) noexcept
{
    return this->m_elems[__index];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::operator[](std::size_t __index) const noexcept
{
    return this->m_elems[__index];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::at(std::size_t __index)
{
    if (__index >= this->m_size)
        nox::__throw_out_of_range("nox::vector::at()");
    
    return this->m_elems[__index];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::at(std::size_t __index) const
{
    if (__index >= this->m_size)
        nox::__throw_out_of_range("nox::vector::at()");
    
    return this->m_elems[__index];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::front() noexcept
{
    return this->_elems[0];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::front() const noexcept
{
    return this->_elems[0];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::back() noexcept
{
    return this->m_elems[this->m_size-1];
}

template <class _Type, class _Allocator>
constexpr _Type &nox::vector<_Type, _Allocator>::back() const noexcept
{
    return this->m_elems[this->m_size-1];
}

template <class _Type, class _Allocator>
constexpr _Type *nox::vector<_Type, _Allocator>::data() noexcept
{
    return this->m_elems;
}

template <class _Type, class _Allocator>
constexpr _Type *nox::vector<_Type, _Allocator>::data() const noexcept
{
    return this->m_elems;
}

// Iterators

template <class _Type, class _Allocator>
constexpr _Type *nox::vector<_Type, _Allocator>::begin() noexcept
{
    return &this->m_elems[0];
}

template <class _Type, class _Allocator>
constexpr _Type *nox::vector<_Type, _Allocator>::begin() const noexcept
{
    return &this->m_elems[0];
}

template <class _Type, class _Allocator>
constexpr _Type *nox::vector<_Type, _Allocator>::end() noexcept
{
    return &this->m_elems[this->m_size];
}

template <class _Type, class _Allocator>
constexpr _Type *nox::vector<_Type, _Allocator>::end() const noexcept
{
    return &this->m_elems[this->m_size];
}

// Capacity

template <class _Type, class _Allocator>
constexpr bool nox::vector<_Type, _Allocator>::empty() noexcept
{
    return this->m_size == 0;
}

template <class _Type, class _Allocator>
constexpr bool nox::vector<_Type, _Allocator>::empty() const noexcept
{
    return this->m_size == 0;
}

template <class _Type, class _Allocator>
constexpr std::size_t nox::vector<_Type, _Allocator>::size() noexcept
{
    return this->m_size;
}

template <class _Type, class _Allocator>
constexpr std::size_t nox::vector<_Type, _Allocator>::size() const noexcept
{
    return this->m_size;
}

template <class _Type, class _Allocator>
constexpr std::size_t nox::vector<_Type, _Allocator>::capacity() noexcept
{
    return this->m_capacity;
}

template <class _Type, class _Allocator>
constexpr std::size_t nox::vector<_Type, _Allocator>::capacity() const noexcept
{
    return this->m_capacity;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::reserve(std::size_t __new_capacity)
{
    if (__new_capacity <= this->m_capacity)
        return;

    _Allocator al;

    _Type *ptr = al.allocate(__new_capacity);

    for (std::size_t index=0; index<this->m_size; index++)
    {
        ptr[index] = std::move(this->m_elems[index]);
    }

    al.deallocate(this->m_elems);

    this->m_elems = ptr;
    this->m_capacity = __new_capacity;

    return;
}

// modifiers

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::clear() noexcept
{
    for (int index=0; index<this->m_size; index++)
    {
        nox::_destroy(&this->m_elems[index]);
    }

    this->m_size = 0;

    return;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::erase(_Type *__position)
{
    std::size_t index = __position - this->begin();

    if (index >= this->m_size)
        nox::__throw_out_of_range("nox::vector::erase()");
    
    nox::_destroy(&this->m_elems[index]);
    
    if (index < this->m_size)
    {
        for (std::size_t after_index=index; after_index<this->m_size-1; after_index++)
        {
            this->m_elems[after_index] = std::move(this->m_elems[after_index+1]);
        }
    }
    
    this->m_size--;

    return;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::erase(_Type *__first, _Type *__last)
{
    if (__first < this->begin() || __last > this->end())
        nox::__throw_out_of_range("nox::vector::erase()");
    
    if (__first > __last)
    {
        _Type *temp = __first;
        __first = __last;
        __last = temp;
    }

    std::size_t offset = __first - this->begin(); // offset from the beginning of the vector
    std::size_t length = __last - __first; // length of the range

    _Type *it = __first;

    while (it != __last)
    {
        nox::_destroy(it);
        it++;
    }

    for (std::size_t index=0; index<length; index++)
    {
        if (index + offset + length >= (std::size_t)this->end())
            break;
        
        this->m_elems[index+offset] = std::move(this->m_elems[index+offset+length]);
    }

    this->m_size -= length;

    return;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::insert(_Type *__position, const _Type &__element)
{
    std::size_t position_index = __position - this->begin();

    if (position_index >= this->m_size)
        nox::__throw_out_of_range("nox::vector::insert()");

    if (this->m_size + 1 > this->m_capacity)
    {
        _Allocator al;

        _Type *ptr = al.allocate(this->m_capacity * 2);
        this->m_capacity *= 2;

        for (std::size_t index=0; index<this->m_size; index++)
        {
            ptr[index] = this->m_elems[index];
        }

        al.deallocate(this->m_elems);

        this->m_elems = ptr;
    }

    for (std::size_t index=this->m_size; index>index; index--)
    {
        this->m_elems[index] = std::move(this->m_elems[index-1]);
    }

    this->m_elems[position_index] = __element;
    this->m_size++;

    return;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::push_back(const _Type &__element)
{
    if (this->m_size+1 > this->m_capacity)
    {
        _Allocator al;

        _Type *ptr = al.allocate(this->m_capacity * 2);
        this->m_capacity *= 2;

        for (std::size_t index=0; index<this->m_size; index++)
        {
            ptr[index] = this->m_elems[index];
        }

        al.deallocate(this->m_elems);

        this->m_elems = ptr;
    }

    this->m_elems[this->m_size] = __element;

    this->m_size++;

    return;
}

template <class _Type, class _Allocator>
template <class... _Args>
constexpr void nox::vector<_Type, _Allocator>::emplace(_Type *__position, _Args&&... __args)
{
    _Type element(__args...);

    if (__position == this->end())
        this->push_back(std::move(element));
    else
        this->insert(__position, std::move(element));

    return;
}

template <class _Type, class _Allocator>
template <class... _Args>
constexpr void nox::vector<_Type, _Allocator>::emplace_back(_Args&&... __args)
{
    _Type element(__args...);

    this->push_back(std::move(element));

    return;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::pop_back()
{
    this->erase(this->end()-1);
    return;
}

template <class _Type, class _Allocator>
constexpr void nox::vector<_Type, _Allocator>::swap(nox::vector<_Type, _Allocator> &__vector) noexcept
{
    std::size_t temp_capacity = __vector.m_capacity;
    std::size_t temp_size = __vector.m_size;
    _Type *temp_elems = __vector.m_elems;

    __vector.m_capacity = this->m_capacity;
    __vector.m_size = this->m_size;
    __vector.m_elems = this->m_elems;

    this->m_capacity = temp_capacity;
    this->m_size = temp_size;
    this->m_elems = temp_elems;

    return;
}

template <class _Type, class _Allocator>
constexpr nox::vector<_Type, _Allocator> nox::vector<_Type, _Allocator>::filter(bool (*__predicate)(const _Type &)) const
{
    nox::vector<_Type> vec;

    for (const _Type &element: *this)
    {
        if (__predicate(element))
            vec.push_back(element);
    }

    return vec;
}