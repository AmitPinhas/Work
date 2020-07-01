#ifndef ATOMIC_VALUE_H
#define ATOMIC_VALUE_H

#include "common.hpp"

namespace advcpp
{

template <typename T = int>
class AtomicValue : private UnCopyable
{
public:
	explicit AtomicValue(T a_value = 0) NOEXCEPT;
	
	// ~AtomicValue() ; = default
	
	void Set(T a_value = 0) NOEXCEPT;
	T Get() const NOEXCEPT;
	T Value() const NOEXCEPT;
	
	
	void operator ++() NOEXCEPT;
	void operator --() NOEXCEPT;
	
	void operator +=(T a_add) NOEXCEPT;	
	void operator -=(T a_sub) NOEXCEPT;
	
private:
	T m_value;
};

template <>
class AtomicValue<bool>
{
public:
	explicit AtomicValue(bool a_value = false) NOEXCEPT;
	
	bool SetIf(bool a_old, bool a_new) NOEXCEPT;
	
	bool Acquire() NOEXCEPT;
	
	void Release() NOEXCEPT;

private:
	int m_flag;
};

typedef AtomicValue<bool> AtomicFlag;

} // namespace advcpp

#include "atomic_value.inl"

#endif // ATOMIC_VALUE_H
