#ifndef EXCEPTIONS_DEFINITIONS_H
#define EXCEPTIONS_DEFINITIONS_H

#include <exception>
#include <ios> // std::ios_base::failure
#include <string>

#ifdef __cplusplus11
        #define NOEXCEPT noexcept
#else
        #define NOEXCEPT throw()
#endif

#define THROW(X) throw(X)
#define THROW1(X) throw(X)
#define THROW2(X, Y) throw(X, Y)
#define THROW3(X, Y, Z) throw(X, Y, Z)
#define XINFO XtendedInformation(__FILE__, __LINE__, __func__)

namespace advcpp
{

class XtendedInformation
{      
public:
        XtendedInformation(const char* a_fileName, int a_line, 
                           const char* a_funcName) THROW(std::ios_base::failure);

        const std::string& Line() const NOEXCEPT;
        const std::string& Function() const NOEXCEPT;
        const std::string& FileName() const NOEXCEPT;
        std::string Location() const THROW(std::ios_base::failure);

        static std::string CreateStringFromLine(int a_line) THROW(std::ios_base::failure);       
private:
        const std::string m_fileName;
        const std::string m_funcName;
        const std::string m_line;
};

class EnrichedExeption: public std::logic_error
{
public:
        XtendedInformation const& Info() const NOEXCEPT;
        virtual ~EnrichedExeption()  NOEXCEPT;
protected:
        EnrichedExeption(const char* a_what_arg, XtendedInformation const& a_info) THROW(std::exception);
        EnrichedExeption(const std::string& a_what_arg, XtendedInformation const& a_info) THROW(std::exception);
private:
        XtendedInformation m_info;

};

} // namespace advcpp

#include"exceptions_definitions.inl"

#endif //EXCEPTION_DEFINITIONS_H
