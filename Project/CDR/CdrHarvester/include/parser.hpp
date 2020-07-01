#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

namespace cpp
{


class Parser
{
public:
    Parser(char a_delimiter);
    void GetRecord(std::string a_line, std::vector<std::string> & a_vec) const;

private:
    char m_delimiter;
};

inline Parser::Parser(char a_delimiter)
:   m_delimiter(a_delimiter)
{
}



}/// end cpp namespace


#endif// PARSER_HPP