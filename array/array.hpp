#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

/**
 * Array of a fixed length.
 */
/**
 * std::size_t is a C++ alternative to the size_t type from C.
 * size_t is typically used when referring to anything that is a quantity
 * related to memory, such as the length of an array (which is in memory).
 * It is an unsigned integer type and is typically (but not always) a typedef
 * for something like unsigned or long unsigned.
 * (If you think this is complicated, then you should look up size_type.)
 */
template <typename T, std::size_t Length>
class Array
{
public:

    static_assert(Length != 0, "Length cannot be 0");


    Array();
    ~Array();
    Array(const Array& other);
    Array& operator=(const Array& other)
    {
        delete array;
        len = other.size();
        array = new T[len];
        for(int i=0; i<len; i++)
        {
            array[i] = other.array[i];
        }
        return *this;
    }


    std::size_t size() const;

    const T& front() const;
    const T& back() const;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    bool operator==(const Array& other) const
    {
        for(unsigned i=0; i<(unsigned)len; i++)
            if(array[i] != other.array[i])
                return false;
        return true;
    }

    bool operator!=(const Array& other) const
    {
        for(unsigned i=0; i<(unsigned)len; i++)
            if(array[i] != other.array[i])
                return true;
        return false;
    }

private:
    int len;
    T* array;
};

template <std::size_t Index, typename T, std::size_t Length>
T& get(Array<T, Length>& array)
{
    static_assert(Index < Length, "Index out of range");
    return array.at(Index);
}
template <std::size_t Index, typename T, std::size_t Length>
const T& get(const Array<T, Length>& array)
{
    static_assert(Index < Length, "Index out of range");
    return array.at(Index);
}

template <typename T, std::size_t Length>
std::ostream& operator<<(std::ostream& os, const Array<T, Length>& array)
{
    for(unsigned i=0; i<Length; i++)
    {
        os << array.at(i) << " ";
    }
    os << '\n';
    return os;
}


#include "array.inl"
#endif  // ARRAY_HPP
