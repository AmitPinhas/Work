#include <string>
#include <dirent.h>
#include <vector>

#include "watch_dog.hpp"

namespace advcpp
{
size_t WatchDog::GetFiles(std::string const& a_directory, std::vector<std::string>& a_results) 
{
    a_results.clear();
    size_t counter = 0;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (&(a_directory[0]))) != NULL) 
    {
        while ((ent = readdir (dir)) != NULL)
        {
            std::string currFile = ent->d_name;
            if (currFile == ".." || currFile == ".")
            {
                continue;
            }
            else
            {
                a_results.push_back(currFile);
                ++counter;
            }
        }
        closedir (dir);
    }
    return counter;
}

}//advcpp namespace
