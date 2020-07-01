#ifndef DEFAULT_HASHER_HPP
#define DEFAULT_HASHER_HPP

#include <cstddef>
#include <cmath>
#include <string>

namespace advcpp
{

size_t hash(int a_key);
size_t hash(size_t a_key);
size_t hash(const std::string& a_key);
template<typename T>
size_t hash(const T& a_key);

template<typename T>
struct DefaultHasher
{
    size_t operator()(T const& a_key) const
    {
        return hash(a_key);
    }
};

template<typename T>
size_t hash(const T& a_key)
{
    return a_key.hash();
}

}


#endif //DEFAULT_HASHER_HPP
