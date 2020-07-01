#ifndef ROI_COMMON_H
#define ROI_COMMON_H

#include <string>
#include <stdexcept>
#include <sys/sysinfo.h> //nprocs

#define NOEXCEPT throw()
#define THROW1r(x) throw(x)
#define THROW2r(x,y) throw(x, y)
#define THROW3r(x, y, z) throw(x, y, z)

#define XINFO __FILE__, __FUNCTION__, __LINE__ 
#define THROWX(x) throw x(InfoException(__FILE__, __func__, __LINE__))




namespace advcpp
{


const size_t NT  = get_nprocs() - 1; 


class ExtendInfo
{

typedef std::string Str;

public:
    ExtendInfo(const char* a_file, const char* a_func, int a_line);    
    
    Str const& File() const;
    Str const& Func() const;
    int Line() const;        
    
private:
    const Str m_file;
    const Str m_func;
    const int m_line;
};

/////////////////////////////////////////////////////////////////////////////

class ExtendedException: public std::runtime_error
{
protected:
	explicit inline ExtendedException(const char* a_msg, ExtendInfo const& a_xInfo);
    virtual ~ExtendedException() NOEXCEPT = 0;
	    
    ExtendInfo const& XInfo();

private:
    ExtendInfo m_xInfo;
};

class Uncopyable
{
protected:
    Uncopyable() {}

private:
    Uncopyable(Uncopyable const&);
    Uncopyable& operator=(Uncopyable const&);
};

//TODO: meger both copiable
class UnCopiable {
protected:
    UnCopiable() {};
private: 
    UnCopiable(UnCopiable const& a_rhs);
    UnCopiable& operator = (UnCopiable const& a_rhs);
};

}//namespace advcpp

#include "inl/common.inl"

#endif //ROI_COMMON_H


