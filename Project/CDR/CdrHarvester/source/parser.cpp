#include <string>
#include <vector>
#include <sstream>

#include <iostream>// delete

#include "parser.hpp"

namespace cpp
{


void Parser::GetRecord(std::string a_line, std::vector<std::string> & a_vec) const
{
    a_vec.clear();
    std::stringstream newStr(a_line);
    std::string item;
    while(std::getline(newStr, item, m_delimiter))
    {
        a_vec.push_back(item);
    }
}


}/// end cpp namespace
