#ifndef IFINDER_HPP
#define IFINDER_HPP

#include "i_event.hpp"
#include "i_subscribers_list.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class ISubscribersFinder
{
public:
    virtual ~ISubscribersFinder() = default;
    virtual SharedPointer<ISubscribersList> Find(Topic const& a_topic) = 0;

protected:
    ISubscribersFinder() = default;
    ISubscribersFinder(ISubscribersFinder const& a_finder) = default;
    ISubscribersFinder & operator = (const ISubscribersFinder & a_finder) = default;

};

}


#endif //i_finder.hpp
