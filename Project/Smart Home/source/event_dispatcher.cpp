#include "event_dispatcher.hpp"

#include <iostream> // remove !!!

namespace smarthome
{

EventDispatcher::EventDispatcher(IEventStoragePop& a_eventStorage, ISubscribersListNotifier& a_broadcast, size_t a_numOfThreads)
: m_ptrEventDequeuer(new EventDequeuer(a_eventStorage, a_broadcast)) //m_threadPool(a_numOfThreads, a_numOfThreads)
, m_numThreads(a_numOfThreads)
, m_eventStorage(a_eventStorage)
{
   insertTasks(a_numOfThreads);
}

void EventDispatcher::Pause()
{
   m_ptrEventDequeuer->Pause();
}

void EventDispatcher::Resume()
{
   m_ptrEventDequeuer->Resume();   
}

void EventDispatcher::ShutDown()
{
   // m_ptrEventDequeuer->ShutDown();
   // m_threadPool.ShutDown();

   EventDispatcherShutDownRun runnableShutdown(m_eventStorage);

   Thread threadShutdown(&runnableShutdown);

   threadShutdown.Join();

   m_ptrEventDequeuer->ShutDown();
   while(m_numThreads-- > 0)
   {
      m_threads[m_numThreads]->Join();
   }   

   std::cout << "event storage size : " << m_eventStorage.Size() << std::endl;
}

void EventDispatcher::insertTasks(size_t a_numTasks)
{
   // while(a_numTasks-- > 0)
   // {
   //    m_threadPool.DispatchTask(m_ptrEventDequeuer);
   // }
   while(a_numTasks-- > 0)
   {
      SharedPointer<Thread> myThread(new Thread(&*m_ptrEventDequeuer));
      m_threads.push_back(myThread);
   }
}

EventDispatcherShutDownRun::EventDispatcherShutDownRun(IEventStoragePop& a_eventStorage)
: m_eventStorage(a_eventStorage)
{
}

void EventDispatcherShutDownRun::Run() NOEXCEPTION
{
   while(m_eventStorage.Size())
   {
   }   
}

} // namespace smarthome