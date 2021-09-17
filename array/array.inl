#include <iostream>
#include "array.hpp"

template <typename T, std::size_t Length>
Array<T,Length>::Array()
{
    len = Length;
    array = new T[len];
}

template <typename T, std::size_t Length>
Array<T,Length>::~Array()
{
    delete array;
}

template <typename T, std::size_t Length>
Array<T,Length>::Array(const Array& other)
{
    len = other.size();
    array = new T[len];
    for(int i=0; i<len; i++)
    {
        array[i] = other.array[i];
    }
}

template <typename T, std::size_t Length>
std::size_t Array<T, Length>::size() const
{
    return Length;
}

template <typename T, std::size_t Length>
const T& Array<T,Length>::front() const
{
    return array[0];
}

template <typename T, std::size_t Length>
const T& Array<T,Length>::back() const
{
    return array[len-1];
}

template <typename T, std::size_t Length>
T&  Array<T, Length>::at(std::size_t index)
{
    if(index >= Length)
        throw std::out_of_range{"index out of range"};
    return array[index];
}
template <typename T, std::size_t Length>
const T& Array<T, Length>::at(std::size_t index) const
{
    if(index >= Length)
        throw std::out_of_range{"index out of range"};
    return array[index];
}