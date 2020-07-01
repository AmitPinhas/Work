
namespace advcpp
{

template <typename T>
AtomicValue<T>::AtomicValue(T a_arg) NOEXCEPTION
: m_value(a_arg)
{    
}

template <typename T>
void AtomicValue<T>::operator += (T a_arg) NOEXCEPTION
{
    __sync_fetch_and_add (&m_value, a_arg);
}

template <typename T>
void AtomicValue<T>::operator -= (T a_arg) NOEXCEPTION
{
    __sync_fetch_and_sub (&m_value, a_arg);
}

template <typename T>
void AtomicValue<T>::operator ++ () NOEXCEPTION
{
    __sync_fetch_and_add (&m_value, 1);
}

template <typename T>
void AtomicValue<T>::operator -- () NOEXCEPTION
{
    __sync_fetch_and_sub (&m_value, 1);
}

template <typename T>
void AtomicValue<T>::Set(T a_arg) NOEXCEPTION
{
    __sync_lock_test_and_set(&m_value, a_arg);
}

template <typename T>
T AtomicValue<T>::Get() const NOEXCEPTION
{
    return __sync_fetch_and_add(&m_value, T(0));
}

template <typename T>
T AtomicValue<T>::Value() const NOEXCEPTION
{
    return m_value;
}

inline AtomicValue<bool>::AtomicValue(bool a_value) NOEXCEPTION
: m_flag(a_value)
{
}

inline bool AtomicValue<bool>::SetIf(bool a, bool b) NOEXCEPTION
{
    return __sync_bool_compare_and_swap(&m_flag, a, b);
}

inline bool AtomicValue<bool>::Acquire() NOEXCEPTION
{
    return SetIf(false, true);
}

inline void AtomicValue<bool>::Release() NOEXCEPTION
{
    SetIf(true, false);
}


} // namespace advcpp
