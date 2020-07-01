#ifndef BIT_SET_H
#define BIT_SET_H

#include <cmath> // round
#include <utility> // std::pair

namespace advcpp
{
    
template <size_t NBits, typename T = size_t>    
class BitSet
{
public:
    using operation = T (*)(const T&, const T&);

    BitSet();

    ~BitSet() noexcept = default;
    BitSet(const BitSet& a_rhs) = default;
    BitSet& operator=(const BitSet& a_rhs) = default;

    void Set(size_t a_index);

    void Clear(size_t a_index);

    bool Get(size_t a_index) const;

    bool operator[](size_t a_index) const;

    BitSet& operator &=(const BitSet& a_rhs);
    BitSet& operator |=(const BitSet& a_rhs); 
    BitSet& operator ^=(const BitSet& a_rhs);  

    BitSet& operator >>=(size_t a_num); 
    BitSet& operator <<=(size_t a_num);

    BitSet& operator ~();      

    size_t Count() const;

    bool Any() const;   
    bool All() const;
    bool None() const;

private:
    static const size_t TBits = sizeof(T) * 8;
    void ClearAll();
    auto Begin() const;
    auto End() const;
    auto Begin();
    auto End();    
    std::pair<size_t, T> findDest(size_t a_index) const;
    template <typename Operation>
    BitSet& bitWiseOperator(const BitSet& a_rhs, Operation a_opertaion);   
    void fullShift(size_t a_num);
    void partialShift(size_t a_num);

private:
    T m_data[static_cast<size_t>(round(NBits / TBits))];

};

template <typename T>
T opeartionAND(const T& a_first, const T& a_second);

template <typename T>
T opeartionOR(const T& a_first, const T& a_second);

template <typename T>
T opeartionXOR(const T& a_first, const T& a_second);

} // namespace advcpp

#include "inl/bit_set.inl"

#endif // BIT_SET_H