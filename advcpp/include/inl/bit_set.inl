#ifndef BIT_SET_INL
#define BIT_SET_INL

#include <algorithm> // std::generate , std::transform , std::find_if

namespace advcpp
{

template <size_t NBits, typename T>        
BitSet<NBits, T>::BitSet()
{
    ClearAll();
}   

template <size_t NBits, typename T>   
void BitSet<NBits, T>::Set(size_t a_index)
{
    auto [indexData, mask] = findDest(a_index);

    m_data[indexData] |= mask;
}

template <size_t NBits, typename T>  
void BitSet<NBits, T>::Clear(size_t a_index)
{
    auto [indexData, mask] = findDest(a_index);

    m_data[indexData] &= ~mask;    
}

template <size_t NBits, typename T>  
bool BitSet<NBits, T>::Get(size_t a_index) const
{
    auto [indexData, mask] = findDest(a_index);

    return m_data[indexData] & mask;
}

template <size_t NBits, typename T>  
bool BitSet<NBits, T>::operator[](size_t a_index) const
{
    return Get(a_index);
}

template <size_t NBits, typename T>  
BitSet<NBits, T>& BitSet<NBits, T>::operator &=(const BitSet& a_rhs)
{
    return bitWiseOperator<operation>(a_rhs, opeartionAND);
}

template <size_t NBits, typename T>  
BitSet<NBits, T>& BitSet<NBits, T>::operator |=(const BitSet& a_rhs)
{
    return bitWiseOperator<operation>(a_rhs, opeartionOR);
}

template <size_t NBits, typename T>  
BitSet<NBits, T>& BitSet<NBits, T>::operator ^=(const BitSet& a_rhs)
{
    return bitWiseOperator<operation>(a_rhs, opeartionXOR);
}

template <size_t NBits, typename T>  
BitSet<NBits, T>& BitSet<NBits, T>::operator <<=(size_t a_num)
{
    if(0 != a_num)
    {
        if(0 == a_num % std::numeric_limits<T>::digits)
        {
            fullShift(a_num);
        }
        else
        {
            partialShift(a_num);
        }   
    }
    return *this;
}

template <size_t NBits, typename T>  
BitSet<NBits, T>& BitSet<NBits, T>::operator ~()
{
    auto thisBegin = Begin();
    auto thisEnd = End();

    std::transform(thisBegin, thisEnd, thisBegin, [](T a_element){return ~a_element;});
                                                                         
    return *this;        
}

template <size_t NBits, typename T>  
size_t BitSet<NBits, T>::Count() const
{
    size_t count = 0;

    for(size_t i = 0; i < NBits; i++)
    {
        if(Get(i))
        {
            ++count;
        }
    }

    return count;
}

template <size_t NBits, typename T>  
bool BitSet<NBits, T>::Any() const
{
    auto begin = Begin();
    auto end = End();

    auto r = std::find_if(begin, end, [](auto a_element){return a_element;});

    if(r != end)
    {
        return true;
    }
    return false;
}

template <size_t NBits, typename T>  
bool BitSet<NBits, T>::All() const
{
    BitSet<NBits, T> tmp = *this;

    ~tmp;
    
    return !tmp.Any();
}

template <size_t NBits, typename T>  
bool BitSet<NBits, T>::None() const
{
    return !Any();
}

template <size_t NBits, typename T>    
void BitSet<NBits, T>::ClearAll()
{
    auto begin = Begin(); 
    auto end = End();

    std::generate(begin, end, [](){return 0;});
}

template <size_t NBits, typename T>  
auto BitSet<NBits, T>::Begin() const
{
    return std::begin(m_data);
}

template <size_t NBits, typename T>  
auto BitSet<NBits, T>::End() const
{
    return std::end(m_data);
}

template <size_t NBits, typename T>
auto BitSet<NBits, T>::Begin()
{
	return const_cast<T*>(static_cast<const BitSet&>(*this).Begin());    
}

template <size_t NBits, typename T>
auto BitSet<NBits, T>::End()
{
	return const_cast<T*>(static_cast<const BitSet&>(*this).End());    
} 

template <size_t NBits, typename T>  
std::pair<size_t, T> BitSet<NBits, T>::findDest(size_t a_index) const
{
    size_t indexData = a_index / TBits;

    T mask = 1;
                 
    mask <<= (a_index % TBits);

    return std::make_pair(indexData, mask);
                
}

template <size_t NBits, typename T>  
template <typename Operation>
BitSet<NBits, T>& BitSet<NBits, T>::bitWiseOperator(const BitSet& a_rhs, Operation a_opertaion)
{
    auto thisBegin = Begin();
    auto thisEnd = End();
    size_t i = 0;

    std::transform(thisBegin, thisEnd, thisBegin, [a_rhs, &i, a_opertaion](T a_element){T tmp = a_rhs.m_data[i];
                                                                           ++i;
                                                                           return a_opertaion(a_element, tmp);});

    return *this;    
}  

template <size_t NBits, typename T>  
void BitSet<NBits, T>::fullShift(size_t a_num)
{
    size_t numMove =  a_num / std::numeric_limits<T>::digits;

    std::fill(Begin(), Begin() + numMove, T{0});

    std::rotate(Begin(), Begin() + numMove, End());
}

template <size_t NBits, typename T>  
void BitSet<NBits, T>::partialShift(size_t a_num)
{
    fullShift(a_num);

    T mask{0};

    mask = ~mask;

    mask <<= a_num % std::numeric_limits<T>::digits;
    mask >>= a_num % std::numeric_limits<T>::digits;


}

template <typename T>
T opeartionAND(const T& a_first, const T& a_second)
{
    return a_first & a_second;
}

template <typename T>
T opeartionOR(const T& a_first, const T& a_second)
{
    return a_first | a_second;  
}

template <typename T>
T opeartionXOR(const T& a_first, const T& a_second)
{
    return a_first ^ a_second;    
}

} // namespace advcpp

#endif // BIT_SET_INL