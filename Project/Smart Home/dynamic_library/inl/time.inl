namespace advcpp
{

inline Nano::operator size_t() const NOEXCEPTION
{
    return value;
}

inline Nano::operator timespec() const NOEXCEPTION
{
    timespec t_spec;
    t_spec.tv_sec = value / NANO;
    t_spec.tv_nsec = value % NANO;

    return t_spec;
}

inline Second::Second(size_t a_value) NOEXCEPTION
: value(a_value)
{
}

inline Second::operator size_t() const NOEXCEPTION
{
    return value;
}

inline Second::operator timespec() const NOEXCEPTION
{
    timespec t_spec;
    t_spec.tv_sec = value;
    t_spec.tv_nsec = 0;

    return t_spec;
}

inline Minute::Minute(size_t a_value) NOEXCEPTION
: value(a_value)
{
}

inline Minute::operator size_t() const NOEXCEPTION
{
    return value;
}

inline Minute::operator timespec() const NOEXCEPTION
{
    timespec t_spec;
    t_spec.tv_sec = value * SECONDS_IN_MINUTE;
    t_spec.tv_nsec = 0;

    return t_spec;
}

} // nameapsce advcpp
