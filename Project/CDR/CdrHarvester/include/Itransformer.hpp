#ifndef I_TRANSFORMER_HPP
#define I_TRANSFORMER_HPP

#include <iostream>
#include <string>

namespace cpp
{

class ITransformer
{
public:
    virtual ~ITransformer() = 0;
    virtual std::string& Transform(std::string& a_string) = 0;
};

class LowerCaseTransform : public ITransformer
{
public:
    //explicit LowerCaseTransform(); no need 
    //LowerCaseTransform(LowerCaseTransform const& a_lower); no need 
    //~LowerCaseTransform(); no need 
    //LowerCaseTransform const& operator=(LowerCaseTransform const& a_lower) no need 


    virtual std::string& Transform(std::string& a_string);
};

class UpperCaseTransform : public ITransformer
{
public:
    //explicit UpperCaseTransform(); no need 
    //UpperCaseTransform(UpperCaseTransform const& a_lower); no need 
    //~UpperCaseTransform(); no need 
    //UpperCaseTransform const& operator=(UpperCaseTransform const& a_lower) no need

    virtual std::string& Transform(std::string& a_string);
};

class CapWordTransform : public ITransformer
{
public:
    //explicit CapWordTransform(); no need 
    //CapWordTransform(CapWordTransform const& a_lower); no need 
    //~CapWordTransform(); no need 
    //CapWordTransform const& operator=(CapWordTransform const& a_lower) no need

    virtual std::string& Transform(std::string& a_string);
};

class RemoveTransform : public ITransformer
{
public:
    //RemoveTransform(RemoveTransform const& a_lower); no need 
    //~RemoveTransform(); no need 
    //RemoveTransform const& operator=(RemoveTransform const& a_lower) no need


    explicit RemoveTransform(std::string const& a_string);

    virtual std::string& Transform(std::string& a_string);

private:
    std::string const& m_string;
};

class CensorTransform : public ITransformer
{
public:
    //CensorTransform(CensorTransform const& a_lower); no need 
    //~CensorTransform(); no need 
    //CensorTransform const& operator=(CensorTransform const& a_lower) no need

    explicit CensorTransform(std::string const& a_string);

    virtual std::string& Transform(std::string& a_string);

private:
    std::string const& m_string;
};

class NullTransform : public ITransformer
{
public:
    //NullTransform(); no need 
    //NullTransform(NullTransform const& a_lower); no need 
    //~NullTransform(); no need 
    //NullTransform const& operator=(NullTransform const& a_lower) no need

    virtual std::string& Transform(std::string& a_string);
};

}
#endif // I_TRANSFORMER_HPP