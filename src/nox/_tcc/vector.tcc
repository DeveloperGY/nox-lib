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

template <class _Tp, class _Al>
constexpr std::size_t nox::vector<_Tp, _Al>::size() noexcept
{
    return this->_M_size;
}

template <class _Tp, class _Al>
constexpr std::size_t nox::vector<_Tp, _Al>::size() const noexcept
{
    return this->_M_size;
}

template <class _Tp, class _Al>
constexpr std::size_t nox::vector<_Tp, _Al>::capacity() noexcept
{
    return this->_M_capacity;
}

template <class _Tp, class _Al>
constexpr std::size_t nox::vector<_Tp, _Al>::capacity() const noexcept
{
    return this->_M_capacity;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::reserve(std::size_t __n)
{
    if (__n <= this->_M_capacity)
        return;

    _Al _al;

    _Tp *ptr = _al.allocate(__n);

    for (std::size_t i=0; i<this->_M_size; i++)
    {
        ptr[i] = std::move(this->_M_elems[i]);
    }

    _al.deallocate(this->_M_elems);

    this->_M_elems = ptr;
    this->_M_capacity = __n;

    return;
}

// modifiers

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::clear() noexcept
{
    for (int i=0; i<this->_M_size; i++)
    {
        nox::_destroy(&this->_M_elems[i]);
    }

    this->_M_size = 0;

    return;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::erase(_Tp *__position)
{
    std::size_t __n = __position - this->begin();

    if (__n >= this->_M_size)
        nox::__throw_out_of_range("nox::vector::erase()");
    
    nox::_destroy(&this->_M_elems[__n]);
    
    if (__n < this->_M_size)
    {
        for (std::size_t i=__n; i<this->_M_size-1; i++)
        {
            this->_M_elems[i] = std::move(this->_M_elems[i+1]);
        }
    }
    
    this->_M_size--;

    return;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::erase(_Tp *__first, _Tp *__last)
{
    if (__first < this->begin() || __last > this->end())
        nox::__throw_out_of_range("nox::vector::erase()");
    
    if (__first > __last)
    {
        _Tp *__temp = __first;
        __first = __last;
        __last = __temp;
    }

    std::size_t __offset = __first - this->begin();
    std::size_t __length = __last - __first;

    _Tp *__it = __first;

    while (__it != __last)
    {
        nox::_destroy(__it);
        __it++;
    }

    for (std::size_t i=0; i<__length; i++)
    {
        if (i + __offset + __length >= (std::size_t)this->end())
            break;
        
        this->_M_elems[i+__offset] = std::move(this->_M_elems[i+__offset+__length]);
    }

    this->_M_size -= __length;

    return;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::insert(_Tp *__position, const _Tp &__e)
{
    std::size_t __n = __position - this->begin();

    if (__n >= this->_M_size)
        nox::__throw_out_of_range("nox::vector::insert()");

    if (this->_M_size + 1 > this->_M_capacity)
    {
        _Al al;

        _Tp *ptr = al.allocate(this->_M_capacity * 2);
        this->_M_capacity *= 2;

        for (std::size_t i=0; i<this->_M_size; i++)
        {
            ptr[i] = this->_M_elems[i];
        }

        al.deallocate(this->_M_elems);

        this->_M_elems = ptr;
    }

    for (std::size_t i=this->_M_size; i>__n; i--)
    {
        this->_M_elems[i] = std::move(this->_M_elems[i-1]);
    }

    this->_M_elems[__n] = __e;
    this->_M_size++;

    return;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::push_back(const _Tp &__e)
{
    if (this->_M_size+1 > this->_M_capacity)
    {
        _Al al;

        _Tp *ptr = al.allocate(this->_M_capacity * 2);
        this->_M_capacity *= 2;

        for (std::size_t i=0; i<this->_M_size; i++)
        {
            ptr[i] = this->_M_elems[i];
        }

        al.deallocate(this->_M_elems);

        this->_M_elems = ptr;
    }

    this->_M_elems[this->_M_size] = __e;

    this->_M_size++;

    return;
}

template <class _Tp, class _Al>
template <class... Args>
constexpr void nox::vector<_Tp, _Al>::emplace(_Tp *__position, Args&&... args)
{
    _Tp __e(args...);

    if (__position == this->end())
        this->push_back(std::move(__e));
    else
        this->insert(__position, std::move(__e));

    return;
}

template <class _Tp, class _Al>
template <class... Args>
constexpr void nox::vector<_Tp, _Al>::emplace_back(Args&&... args)
{
    _Tp __e(args...);

    this->push_back(std::move(__e));

    return;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::pop_back()
{
    this->erase(this->end()-1);
    return;
}

template <class _Tp, class _Al>
constexpr void nox::vector<_Tp, _Al>::swap(nox::vector<_Tp, _Al> &__v) noexcept
{
    std::size_t __temp_capacity = __v._M_capacity;
    std::size_t __temp_size = __v._M_size;
    _Tp *__temp_elems = __v._M_elems;

    __v._M_capacity = this->_M_capacity;
    __v._M_size = this->_M_size;
    __v._M_elems = this->_M_elems;

    this->_M_capacity = __temp_capacity;
    this->_M_size = __temp_size;
    this->_M_elems = __temp_elems;

    return;
}

template <class _Tp, class _Al>
constexpr nox::vector<_Tp, _Al> nox::vector<_Tp, _Al>::filter(bool (*__pred)(const _Tp &)) const
{
    nox::vector<_Tp> __v;

    for (const _Tp &__e: *this)
    {
        if (__pred(__e))
            __v.push_back(__e);
    }

    return __v;
}