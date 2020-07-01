#ifndef WATCH_DOG_HPP
#define WATCH_DOG_HPP
#include <string>
#include <dirent.h>
#include <vector>

#include "common.hpp"

namespace advcpp
{
    
class WatchDog : private UnCopyAble
{
public:
    WatchDog();
    //~WatchDog(); default

    size_t GetFiles(std::string const& a_directory, std::vector<std::string>& a_results);
};

inline WatchDog::WatchDog()
{
}

}


#endif //WATCH_DOG_HPP