#include "default_hasher.hpp"

namespace advcpp
{

size_t hash(int a_key)
{
    const size_t num = 2654435761;
    return (static_cast<size_t>(a_key) * num) % static_cast<size_t>(pow(2, 32));
}

size_t hash(size_t a_key)
{
    const size_t num = 2654435761;
    return (a_key * num) % static_cast<size_t>(pow(2, 32));
}

size_t hash(const std::string& a_key)
{
    unsigned long hash = 5381;

    for(size_t i = 0; i < a_key.size(); ++i)
    {
            hash = ((hash << 5) + hash) + a_key[i];
    }
    
    return hash;
}

}