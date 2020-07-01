#ifndef COMMON_H
#define COMMON_H



namespace advcpp
{

// #define NOEXCEPTION throw() 
// #define THROW1(x) throw(x) 
// #define THROW2(x, y) throw(x, y)
// #define THROW3(x, y, z) throw(x, y, z)

#if __cplusplus == 201703L
        #define NOEXCEPTION noexcept
#else
        #define NOEXCEPTION throw()
#endif

#if __cplusplus == 201703L
        #define THROW1(X)
        #define THROW2(X, Y)
        #define THROW3(X, Y, Z)
#else
        #define THROW1(X) throw(X)
        #define THROW2(X, Y) throw(X, Y)
        #define THROW3(X, Y, Z) throw(X, Y, Z)
#endif

class UnCopyable
{
protected:
    UnCopyable() NOEXCEPTION;

private:
    UnCopyable(const UnCopyable & a_unCopyable); // = delete
    UnCopyable & operator= (const UnCopyable & a_unCopyable); // = delete
};

inline UnCopyable::UnCopyable() NOEXCEPTION
{
}

} // namespace advcpp

#endif //  COMMON_H
