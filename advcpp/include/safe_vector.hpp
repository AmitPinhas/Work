#ifndef SAFE_VECTOR_HPP
#define SAFE_VECTOR_HPP

#include <vector>
#include "mutex.hpp"

namespace advcpp
{

template <typename T>
class SafeVector
{
public:
    // SafeVector() = default;
    // ~SafeVector() = default;
    // SafeVector(const SafeVector& a_rhs) = default;
    // SafeVector& operator =(const SafeVector& a_rhs) = default;

    void Reserve(size_t a_num);

    size_t Size() const;

    T& Back();
    const T& Back() const;

    void PopBack();

    void PushBack(const T& a_val);

private:
    std::vector<T> m_vector;
    mutable Mutex m_mutex;

};

} // namespace advcpp

#include "inl/safe_vector.inl"

#endif // SAFE_VECTOR_HPP