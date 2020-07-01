#ifndef CDR_HARVESTER_HPP
#define CDR_HARVESTER_HPP
#include <string>
#include <vector>
#include <unistd.h>

#include "watch_dog.hpp"
#include "common.hpp"
#include "file_handler.hpp"
#include "threads.hpp"


namespace advcpp
{

class CdrHarvester : private UnCopyAble
{
public:
    CdrHarvester(std::string a_filename);
    //~CdrHarvester(); default
    
    void Run();

private:
    void GetConfigurationData(std::string a_filename);
    void CreateRunable(std::vector<IRunAble*>& a_runPool, std::vector<std::string>& a_files);
    void CreateThread(std::vector<Thread*>& a_treadPool, std::vector<IRunAble*> const& a_runPool, size_t a_index);
    void WeitThreads(std::vector<Thread*>& a_treadPool);
    void CleanThreads(std::vector<Thread*>& a_treadPool, std::vector<IRunAble*>& a_runPool);
    void HandleFiles(std::vector<std::string>& a_files);

private:
    std::string m_from;
    std::string m_to;
    std::string m_ip;
    size_t m_noThreads;
    size_t m_port;
    WatchDog m_watchDog;

    static const int DirectoryCheckCycle = 10;
};



}//advcpp namespace
#include "inl/cdr_harvester.inl"
#endif // !CDR_HARVESTER_HPP