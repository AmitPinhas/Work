#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <string>
#include "parser.hpp"
#include "cdr.hpp"

namespace advcpp
{
class Encoder
{
public:
    Encoder();
    //~Encoder(); default

    bool MakeMsg(char* a_buffer, std::string const& a_line);

private:
    void MakeCdrCall(std::vector<std::string>const& a_parsed,  Cdr& a_cdr);
    void MakeCdrSms(std::vector<std::string>const& a_parsed, Cdr& a_cdr);
    void MakeCdrGprs(std::vector<std::string>const& a_parsed, Cdr& a_cdr);

private:
    static const size_t FirstChar = 48;
    static const size_t NoFields = 13;
    static const size_t ImsiLen = 15;
    static const size_t MsisdnLen = 15;
    static const size_t ImeiLen = 48;
    static const size_t MccLen = 3;
    static const size_t DateLen = 10;
    static const size_t TimeLen = 8;
    static const size_t DurotationLen = 4;
};

inline Encoder::Encoder()
{
}


}//advcpp namespace

#endif //ENCODER_HPP