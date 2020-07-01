#include <iostream>
#include "watch_dog.hpp"

int main()
{
    advcpp::WatchDog dog(".");
    std::string currFile = dog.GetFileName();
    std::cout << "the file name is: " << currFile << "\n";
    return 1;
}