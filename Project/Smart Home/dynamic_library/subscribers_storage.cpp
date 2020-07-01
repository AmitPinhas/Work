#include "subscribers_storage.hpp"

#include "subscribers_list.hpp"
#include <iostream>

namespace smarthome
{

size_t TopicHash(const Topic & a_topic)
{
    const int p = 31;
    const int m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;

    for (char c : a_topic.m_type.m_type) 
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    hash_value |= a_topic.m_location.m_room;
    hash_value ^= a_topic.m_location.m_floor;

    return hash_value;
}

SubscribersStorage::SubscribersStorage(size_t numOfTopics)
: m_subStorage(numOfTopics, TopicHash)
{
}

SharedPointer<ISubscribersList> SubscribersStorage::Find(Topic const& a_topic)
{
    SharedPointer<ISubscribersList> list;
    bool wasListFound = m_subStorage.Find(a_topic, list);
    if(!wasListFound)
    {
        SharedPointer<ISubscribersList> nullPtr(new SubscribersList);
        return nullPtr;
    }
    
    return list;
}

class UpdateList
{
public:
    explicit UpdateList(SharedPointer<ISubscriber>  a_iSubscriber);
    ~UpdateList() = default;

    void operator()(SharedPointer<ISubscribersList> a_list, SharedPointer<ISubscribersList> b_list);
private:
    SharedPointer<ISubscriber>  m_iSubscriber;
};

UpdateList::UpdateList(SharedPointer<ISubscriber>  a_iSubscriber)
: m_iSubscriber(a_iSubscriber)
{
}

void UpdateList::operator()(SharedPointer<ISubscribersList> a_list, SharedPointer<ISubscribersList> b_list)
{
    (void)b_list;
    a_list->Add(m_iSubscriber);
}

void SubscribersStorage::Subscribe(const Topic a_topic, SharedPointer<ISubscriber>  a_iSubscriber)
{
    SharedPointer<ISubscribersList> list(new SubscribersList);
    list->Add(a_iSubscriber);
    UpdateList updateList(a_iSubscriber);
    m_subStorage.Upsert(a_topic, list, updateList);
}

class EraseFromList
{
public:
    explicit EraseFromList(SharedPointer<ISubscriber>  a_iSubscriber, 
                           HashTableSafe<Topic, SharedPointer<ISubscribersList>, Tophas > & a_listIndex);
    ~EraseFromList() = default;

    void operator()(const Topic & a_topic);
private:
    SharedPointer<ISubscriber>  m_iSubscriber;
    HashTableSafe<Topic, SharedPointer<ISubscribersList>, Tophas > & m_listIndex;
};

EraseFromList::EraseFromList(SharedPointer<ISubscriber>  a_iSubscriber, 
                           HashTableSafe<Topic, SharedPointer<ISubscribersList>, Tophas > & a_listIndex)
: m_iSubscriber(a_iSubscriber)
, m_listIndex(a_listIndex)
{
}

void EraseFromList::operator()(const Topic & a_topic)
{
   SharedPointer<ISubscribersList> list(new SubscribersList);
    bool foundList = m_listIndex.Find(a_topic, list);
    if(foundList)
    {
        list->Remove(m_iSubscriber);
    }
}

void SubscribersStorage::UnSubscribe(const std::vector<Topic> & a_topics, SharedPointer<ISubscriber> a_iSubscriber)
{
    EraseFromList eraser(a_iSubscriber, m_subStorage);
    for_each(a_topics.begin(), a_topics.end(), eraser);
}

} // namespace smarthome
