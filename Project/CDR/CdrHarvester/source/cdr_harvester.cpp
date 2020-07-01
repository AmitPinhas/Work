#include "cdr_harvester.hpp"
#include "watch_dog.hpp"
#include "common.hpp"
#include "file_handler.hpp"
#include "threads.hpp"


namespace advcpp
{
void CdrHarvester::Run()
{
    std::vector<std::string> files;
    
    while(true)
    {        
        size_t noFiles = m_watchDog.GetFiles(m_from, files);
        if (noFiles != 0)
        {
            std::cout << "file found :" << noFiles << "\n";
            HandleFiles(files);
        }
        else
        {
            std::cout << "Wait fro another batch of files\n" << noFiles << "\n";
        }        
        sleep(DirectoryCheckCycle);    
    }
}

void CdrHarvester::HandleFiles(std::vector<std::string>& a_files)
{
    std::vector<Thread*> treadPool;
    std::vector<IRunAble*> runPool;
    size_t noFiles = 0;
    while ( (noFiles = a_files.size()) != 0)
    {
        try
        {
            for (size_t i = 0; i < noFiles; ++i)
            {
                if(i >= m_noThreads)
                {
                    break;
                }
                CreateRunable(runPool, a_files);
                CreateThread(treadPool, runPool, i);
            }
            WeitThreads(treadPool);
        }
        catch(ClientNetExeption const& a_exeption)
        {
            std::cout << "connection to server failed\n";
        }

        catch(ConnectionLostExeption const& a_exeption)
        {
            std::cout << "connection lost\n";
        }

        catch(...)
        {
            std::cout << "file hendler failed\n";
        }
        CleanThreads(treadPool, runPool);
    }
}

}//namespace advcpp
