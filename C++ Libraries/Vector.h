#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef>   // size_t
#include <stdexcept> // std::range_error

template <class T>
class Vector
{
public:
    class iterator;

private:
    T *array;
    size_t _capacity, _size;

    void grow()
    {
        if (_capacity == 0)
        {
            _capacity++;
        }
        else
        {
            _capacity = _capacity * 2;
        }

        T *tempArr = new T[_capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            tempArr[i] = std::move(array[i]);
        }
        delete[] array;
        array = tempArr;
    }

public:
    Vector() noexcept
    {
        _capacity = 0;
        _size = 0;
        array = nullptr;
    }

    Vector(size_t count, const T &value)
    {
        _size = count;
        _capacity = count;
        array = new T[count]{};
        for (size_t i = 0; i < count; i++)
        {
            array[i] = value;
        }
    }

    explicit Vector(size_t count)
    {
        _size = count;
        _capacity = count;
        array = new T[count]{};
    }

    Vector(const Vector &other)
    {
        _size = other.size();
        _capacity = other.capacity();
        array = new T[_capacity]{};
        for (size_t i = 0; i < _size; i++)
        {
            array[i] = other.at(i);
        }
    }

    Vector(Vector &&other) noexcept
    {
        array = other.array;
        _size = other.size();
        _capacity = other.capacity();

        other._capacity = 0;
        other._size = 0;
        other.array = nullptr;
    }

    ~Vector()
    {
        _size = 0;
        _capacity = 0;
        delete[] array;
    }

    Vector &operator=(const Vector &other)
    {
        if (other.array == this->array)
        {
            return *this;
        }
        _size = other.size();
        _capacity = other.capacity();

        delete[] array;
        array = new T[other._capacity]{};

        for (size_t i = 0; i < _size; ++i)
        {
            array[i] = other.array[i];
        }

        return *this;
    }
    Vector &operator=(Vector &&other) noexcept
    {
        if (other.array == this->array)
        {
            return *this;
        }

        delete[] array; 
         array = other.array;
        _size = other.size();
        _capacity = other.capacity();

        other._capacity = 0;
        other._size = 0;
        other.array = nullptr;

        other.clear();

        return *this;
    }

    iterator begin() noexcept
    {
        return iterator(array);
    }
    iterator end() noexcept
    {
        return iterator(array + _size);
    }

    [[nodiscard]] bool empty() const noexcept
    {
        if (iterator(array) == iterator(array + _size))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    size_t size() const noexcept
    {
        return _size;
    }
    size_t capacity() const noexcept
    {
        return _capacity;
    }

    T &at(size_t pos)
    {
        if (pos >= _capacity)
        {
            throw std::out_of_range("vector is out of range");
        }
        else
        {
            return array[pos];
        }
    }
    const T &at(size_t pos) const
    {
        if (pos >= _capacity)
        {
            throw std::out_of_range("vector is out of range");
        }
        else
        {
            return array[pos];
        }
    }

    T &operator[](size_t pos)
    { 
        return array[pos];
    }

    const T &operator[](size_t pos) const
    { 
        return array[pos];
    }

    T &front()
    { 
        return array[0];
    }

    const T &front() const
    { 
        return array[0];
    }

    T &back()
    { 
        return array[_size - 1];
    }

    const T &back() const
    { 
        return array[_size - 1];
    }

    void push_back(const T &value)
    { 
        if (_size >= _capacity)
        {
            grow();
        }
        array[_size] = value;
        ++_size;
    }

    void push_back(T &&value)
    { 
        if (_size >= _capacity)
        {
            grow();
        }
        array[_size] = std::move(value);
        _size++;
    }

    void pop_back()
    { 
        array[_size].~T();
        --_size;
    }

    iterator insert(iterator pos, const T &value)
    { 

        auto index = pos - begin();

        if (_size >= _capacity)
        {
            grow();
        }
        // inserting the element

        for (size_t i = _size; i > index; --i)
        {
            array[i] = std::move(array[i - 1]);
        }

        array[index] = value;
        ++_size;
        return begin() + index;
    }

    iterator insert(iterator pos, T &&value)
    { 
        auto index = pos - begin();

        if (_size >= _capacity)
        {
            grow();
        }
        // inserting the element

        for (size_t i = _size; i > index; --i)
        {
            array[i] = std::move(array[i - 1]);
        }

        array[index] = std::move(value);
        ++_size;
        return begin() + index;
    }

    iterator insert(iterator pos, size_t count, const T &value)
    { 
        auto index = pos - begin();
        size_t newSize = _size + count;

        while (newSize >= _capacity)
        {
            grow();
        }
        // inserting the element
        for (size_t i = _size; i > index; --i)
        {
            array[i + count - 1] = std::move(array[i - 1]);
        }
        
        for (size_t i = 0; i < count; ++i)
        {
            array[index + i] = value;
        }
        _size = _size + count; 
        return begin() + index;
    }

    iterator erase(iterator pos)
    { 
        auto index = pos - begin();

        for (auto i = index; i < _size - 1; i++)
        {
            array[i] = std::move(array[i + 1]);
        }

        --_size;
        return begin() + index;
    }

    iterator erase(iterator first, iterator last)
    {
        auto count = last - first;
        auto index = first - begin();
        _size = _size - count;
        for (auto i = index; i < _size; i++)
        {
            array[i] = std::move(array[i + count]);
        }

        return begin() + index;
    }

    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;

    private:
        pointer i_ptr;

    public:
        iterator(pointer ptr)
        {
            i_ptr = ptr;
        }

        iterator()
        {
            i_ptr = nullptr;
        }
        
        iterator &operator=(const iterator &) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept
        { 
            return *i_ptr;
        }
        [[nodiscard]] pointer operator->() const noexcept
        { 
            return i_ptr;
        }

        // Prefix Increment: ++a
        iterator &operator++() noexcept
        { 
            i_ptr++;
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept
        { 
            iterator copy_ptr = *this;
            ++(*this);
            return copy_ptr;
        }
        // Prefix Decrement: --a
        iterator &operator--() noexcept
        { 
            i_ptr--;
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept
        { 
            iterator copy_ptr = *this;
            --(*this);
            return copy_ptr;
        }

        iterator &operator+=(difference_type offset) noexcept
        { 
            i_ptr = i_ptr + offset;
            return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept
        { 
            iterator copy_ptr = *this;
            copy_ptr.i_ptr = copy_ptr.i_ptr + offset;
            return copy_ptr;
        }

        iterator &operator-=(difference_type offset) noexcept
        { 
            i_ptr = i_ptr - offset;
            return *this;
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept
        { 
            iterator copy_ptr = *this;
            copy_ptr.i_ptr = copy_ptr.i_ptr - offset;
            return copy_ptr;
        }
        [[nodiscard]] difference_type operator-(const iterator &rhs) const noexcept
        { 
            return (i_ptr - rhs.i_ptr);
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept
        { 
            return *(i_ptr + offset);
        }

        [[nodiscard]] bool operator==(const iterator &rhs) const noexcept
        { 
            return (i_ptr == rhs.i_ptr);
        }
        [[nodiscard]] bool operator!=(const iterator &rhs) const noexcept
        { 
            return (i_ptr != rhs.i_ptr);
        }
        [[nodiscard]] bool operator<(const iterator &rhs) const noexcept
        {
            return (i_ptr < rhs.i_ptr);
        }
        [[nodiscard]] bool operator>(const iterator &rhs) const noexcept
        { 
            return (i_ptr > rhs.i_ptr);
        }
        [[nodiscard]] bool operator<=(const iterator &rhs) const noexcept
        { 
            return (i_ptr <= rhs.i_ptr);
        }
        [[nodiscard]] bool operator>=(const iterator &rhs) const noexcept
        { 
            return (i_ptr >= rhs.i_ptr);
        }
    };

    void clear() noexcept
    { 
        _size = 0;
    }
};

template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept
{
    for (size_t i = 0; i < offset; i++)
    {
        ++iterator;
    }

    return iterator;
}

#endif
