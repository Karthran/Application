#pragma once
#include <iostream>

#define VALUE_NOT_FOUND -1

#include "BadException.h"

template <typename T>
class Array
{
public:
    Array() = default;
    Array(int length);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    void erase();
    std::shared_ptr<T>& operator[](int index) const;
    void reallocate(int newLength);
    void resize(int newLength);
    void insertBefore(std::shared_ptr<T> value, int index);
    void remove(int index);
    void insertAtBeginning(std::shared_ptr<T> value);
    void insertAtEnd(std::shared_ptr<T> value);
    int findValue(T& value);
    int getArrayLength() const;

private:
    int _length{0};
    std::shared_ptr<std::shared_ptr<T>[]> _data;
    // T* _data{ nullptr };
};

template <typename T>
Array<T>::Array(int length) : _length(length), _data(new std::shared_ptr<T>[_length])
{
    if (_length <= 0) throw bad_length();
}

template <typename T>
Array<T>::Array(const Array<T>& other) : _length(other._length), _data(new std::shared_ptr<T>[_length])
{
    if (_length <= 0) throw bad_length();

    for (int i = 0; i < _length; ++i)
    {
        _data[i] = other._data[i];
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    if (this == &other) return *this;

    _length = other._length;
    if (_length <= 0) throw bad_length();

    std::shared_ptr<std::shared_ptr<T>[]> ptr(new std::shared_ptr<T>[_length]);

    _data = ptr;

    for (int i = 0; i < _length; ++i)
    {
        _data[i] = other._data[i];
    }
    return *this;
}

template <typename T>
Array<T>::~Array()
{
}

template <typename T>
void Array<T>::erase()
{
    _data = nullptr;
    _length = 0;
}

template <typename T>
std::shared_ptr<T>& Array<T>::operator[](int index) const
{
    if (index < 0 || index >= _length) throw bad_range();

    return _data[index];
}

template <typename T>
void Array<T>::reallocate(int newLength)
{
    if (newLength <= 0) throw bad_length();

    erase();
    _length = newLength;
    std::shared_ptr<std::shared_ptr<T>[]> ptr(new std::shared_ptr<T>[_length]);
    _data = ptr;
}

template <typename T>
void Array<T>::resize(int newLength)
{
    if (newLength <= 0) throw bad_length();
    if (_length == newLength) return;

    int totalLength = (_length > newLength) ? newLength : _length;

    std::shared_ptr<std::shared_ptr<T>[]> newPtr { new std::shared_ptr<T>[ newLength ] };

    for (int i{0}; i < totalLength; ++i)
    {
        newPtr[i] = _data[i];
    }
    _data = newPtr;
    _length = newLength;
}

template <typename T>
void Array<T>::insertBefore(std::shared_ptr<T> value, int index)
{
    if (index < 0 || index > _length) throw bad_range();

    std::shared_ptr<std::shared_ptr<T>[]> newPtr { new std::shared_ptr<T>[ _length + 1 ] };

    for (int i{0}; i < index; ++i)
        newPtr[i] = _data[i];

    newPtr[index] = value;

    for (int i{index}; i < _length; ++i)
        newPtr[i + 1] = _data[i];

    _data = newPtr;
    ++_length;
}

template <typename T>
void Array<T>::remove(int index)
{
    if (index < 0 || index >= _length) throw bad_range();

    if (_length == 1)
    {
        erase();
        return;
    }

    std::shared_ptr<std::shared_ptr<T>[]> newPtr { new std::shared_ptr<T>[ _length - 1 ] };

    for (int i{0}; i < index; ++i)
        newPtr[i] = _data[i];

    for (int i{index}; i < _length - 1; ++i)
        newPtr[i] = _data[i + 1];

    _data = newPtr;
    --_length;
}
template <typename T>
void Array<T>::insertAtBeginning(std::shared_ptr<T> value)
{
    insertBefore(value, 0);
}

template <typename T>
void Array<T>::insertAtEnd(std::shared_ptr<T> value)
{
    insertBefore(value, _length);
}

template <typename T>
int Array<T>::findValue(T& value)
{
    for (int i{0}; i < _length; ++i)
    {
        if (_data[i] != value) continue;
        return i;
    }
    return VALUE_NOT_FOUND;
}

template <typename T>
int Array<T>::getArrayLength() const
{
    return _length;
}
