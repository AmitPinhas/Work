#include "cdr_harvester.hpp"

int main()
{
    advcpp::CdrHarvester myHarvester("config.ini");
    myHarvester.Run();
    return 1;
}