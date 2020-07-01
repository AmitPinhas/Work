#ifndef SUBSCRIBERS_STORAGE_HPP
#define SUBSCRIBERS_STORAGE_HPP

#include <map>
#include "hash_table_safe.hpp"
#include "event_structs.hpp"
#include "i_subscribes_finder.hpp"
#include "i_subscriber.hpp"
#include "i_subscribers_updator.hpp"
#include "i_subscribers_list.hpp"

namespace smarthome
{

const size_t NUM_OF_TOPICS = 97; 

typedef size_t (*Tophas)(const Topic & ); // add func = ()

class SubscribersStorage : public ISubscriberUpdator, public ISubscribersFinder
{
public:
    typedef HashTableSafe<Topic, SharedPointer<ISubscribersList>, Tophas > SafeSub;
 
    SubscribersStorage(size_t numOfTopics = NUM_OF_TOPICS);
    ~SubscribersStorage() = default;
    SubscribersStorage(const SubscribersStorage & a_substorage) = default;
    SubscribersStorage & operator = (const SubscribersStorage & a_substorage) = default;

    virtual void Subscribe(const Topic a_topic, SharedPointer<ISubscriber>  a_iSubscriber);
    virtual void UnSubscribe(const std::vector<Topic> & a_topics, SharedPointer<ISubscriber> a_iSubscriber);

    SharedPointer<ISubscribersList> Find(Topic const& a_topic);

private:
    SafeSub     m_subStorage;
};

}
#endif // SUBSCRIBERS_STORAGE_HPP
