#include <fstream>
#include <cstdlib>

namespace advcpp
{



inline CdrHarvester::CdrHarvester(std::string a_filename)
{
    GetConfigurationData(a_filename);
}


inline void CdrHarvester::GetConfigurationData(std::string a_filename)
{
    std::ifstream ifs(a_filename.c_str());
    char buffer[20];

    ifs.ignore (999, '=');
    ifs.getline(buffer, '\n');
    m_from = buffer;
    m_from += "/";

    ifs.ignore (999, '=');
    ifs.getline(buffer, '\n');
    m_to = buffer;
    m_to += "/";

    ifs.ignore (999, '=');
    ifs.getline(buffer, '\n');
    m_noThreads = atoi(buffer);

    ifs.ignore (999, '=');
    ifs.getline(buffer, '\n');
    m_ip = buffer;

    ifs.ignore (999, '=');
    ifs.getline(buffer, '\n');
    m_port = atoi(buffer);

    ifs.close();
}

inline void CdrHarvester::CreateRunable(std::vector<IRunAble*>& a_runPool, std::vector<std::string>& a_files)
{
    a_runPool.push_back(new FileHandler(m_ip.c_str(), m_port, a_files[a_files.size() - 1], m_from, m_to));
    a_files.pop_back();
}
inline void CdrHarvester::CreateThread(std::vector<Thread*>& a_treadPool, std::vector<IRunAble*> const& a_runPool, size_t a_index)
{
    a_treadPool.push_back(new Thread(a_runPool[a_index]));
}

inline void CdrHarvester::WeitThreads(std::vector<Thread*>& a_treadPool)
{
    size_t noThreads = a_treadPool.size();
    for(size_t i = 0; i < noThreads; ++i)
    {
        a_treadPool[i]->Join();
    }
}

inline void CdrHarvester::CleanThreads(std::vector<Thread*>& a_treadPool, std::vector<IRunAble*>& a_runPool)
{
    size_t noThreads = a_treadPool.size();
    for(size_t i = 0; i < noThreads; ++i)
    {
        delete a_treadPool[i];
        delete a_runPool[i];
    }
    a_treadPool.clear();
    a_runPool.clear();
}


}//advcpp namespace