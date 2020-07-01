#include <iostream>
#include <string>
#include <cstdio>

#include "Itransformer.hpp"

namespace cpp
{

ITransformer::~ITransformer()
{
}

void DeleteDoubleSpaces(std::string & a_string);

std::string& LowerCaseTransform::Transform(std::string& a_string)
{
    DeleteDoubleSpaces(a_string);

    std::string::iterator curr = a_string.begin();
    std::string::iterator end = a_string.end();
    
    while(curr != end)
    {
        *curr = tolower(*curr);
        ++curr;
    }

    return a_string;
}

std::string& UpperCaseTransform::Transform(std::string& a_string)
{
    DeleteDoubleSpaces(a_string);

    std::string::iterator curr = a_string.begin();
    std::string::iterator end = a_string.end();

    while(curr != end)
    {
        *curr = toupper(*curr);
        ++curr;
    }

    return a_string;
}

std::string& CapWordTransform::Transform(std::string& a_string)
{
    DeleteDoubleSpaces(a_string);

    std::string::iterator curr = a_string.begin();
    std::string::iterator end = a_string.end();

    if (*curr != ' ')
    {
        *curr = toupper(*curr);
        ++curr;
    }

    while (curr != end)
    {
        if (*curr == ' ')
        {
             *(curr + 1) = toupper(* (curr + 1) );
        }
        ++curr;
    }
    return a_string;
}

RemoveTransform::RemoveTransform(std::string const& a_string)
:   m_string(a_string)
{
}

std::string& RemoveTransform::Transform(std::string& a_string)
{
    DeleteDoubleSpaces(a_string);

    size_t position = 0;
    while(true)
    {
        if ( (position = a_string.find(m_string, position) )  == std::string::npos)
        {
            return a_string;
        }
        else
        {
            a_string.erase(position , m_string.length());
        }
    }
}

CensorTransform::CensorTransform(std::string const& a_string)
:   m_string(a_string)
{
}

std::string& CensorTransform::Transform(std::string& a_string)
{
    DeleteDoubleSpaces(a_string);

    size_t position = 0;
    std::string temp;

    for (unsigned int i = 0; i < m_string.length(); ++i)
    {
        temp.push_back('*');
    }

    while(true)
    {
        if ( (position = a_string.find(m_string, position) )  == std::string::npos)
        {
            return a_string;
        }
        else
        {
            a_string.replace (position,  m_string.length(),  temp);
        }
    }
}

std::string& NullTransform::Transform(std::string& a_string)
{
    return a_string;
}

void DeleteDoubleSpaces(std::string & a_string)
{
    bool flag = 0;
    std::string::iterator curr = a_string.begin();
    std::string::iterator end = a_string.end();
    while (curr != end)
    {
        if (*curr == ' ' && flag == 0)  
        {
            flag = 1;
        }
        else if(*curr == ' ' && flag == 1)
        {
            a_string.erase(curr);
            continue;
        }
        else
        {
            flag = 0;
        }
        ++curr;
    }

}



}