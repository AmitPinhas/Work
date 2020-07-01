#ifndef COMMON_H
#define COMMON_H

namespace advcpp
{

#define NOEXCEPT throw()
#define THROW1(x) 
#define THROW2(x, y) 
#define THROW3(x, y, z)
#define XINFO ExtendedExceptionInfo(__FILE__, __func__, __LINE__)

class UnCopyable
{
protected:
    UnCopyable() NOEXCEPT;

private:
    UnCopyable(const UnCopyable& a_unCopyable) NOEXCEPT; // = delete
    UnCopyable& operator =(const UnCopyable& a_unCopyable) NOEXCEPT; // = delete
};

} // namespace advcpp

#include "inl/common.inl"

#endif // COMMON_H
