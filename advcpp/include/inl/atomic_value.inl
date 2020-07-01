#ifndef ATOMIC_VALUE_INL
#define ATOMIC_VALUE_INL

namespace advcpp
{

template <typename T>
AtomicValue<T>::AtomicValue(T a_value) NOEXCEPT
: m_value(a_value)
{
}

template <typename T>
void AtomicValue<T>::Set(T a_value) NOEXCEPT
{
	__sync_lock_test_and_set(&m_value, a_value);
}

template <typename T>
void AtomicValue<T>::operator ++() NOEXCEPT
{
	__sync_fetch_and_add(&m_value, 1);	
}

template <typename T>
void AtomicValue<T>::operator --() NOEXCEPT
{
	__sync_fetch_and_sub(&m_value, 1);	
}

template <typename T>
void AtomicValue<T>::operator +=(T a_add) NOEXCEPT
{
	__sync_fetch_and_add(&m_value, a_add);
}

template <typename T>
void AtomicValue<T>::operator -=(T a_sub) NOEXCEPT
{
	__sync_fetch_and_sub(&m_value, a_sub);
}

template <typename T>
T AtomicValue<T>::Get() const NOEXCEPT
{
	return m_value;
}

template <typename T>
T AtomicValue<T>::Value() const NOEXCEPT
{
	return m_value;	
}

inline AtomicValue<bool>::AtomicValue(bool a_value) NOEXCEPT
: m_flag(a_value)
{
}

inline bool AtomicValue<bool>::SetIf(bool a_old, bool a_new) NOEXCEPT
{
	return __sync_bool_compare_and_swap(&m_flag, a_old, a_new);
}

inline bool AtomicValue<bool>::Acquire() NOEXCEPT
{
	return SetIf(false, true);
}

inline void AtomicValue<bool>::Release() NOEXCEPT
{
	SetIf(true, false);
}

} // namespace advcpp

#endif // ATOMIC_VALUE_INL
