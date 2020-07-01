#ifndef I_SUBSCRIBERS_GROUP_FINDER_H
#define I_SUBSCRIBERS_GROUP_FINDER_H

#include <vector>
#include "i_subscribers_group.hpp"
#include "event_structs.hpp" // Topic

namespace smarthome
{
    
class ISubscribersGroupFinder
{
public:
    virtual ~ISubscribersGroupFinder() = default;

    virtual std::vector<ISubscribersGroup> Find(const Topic& a_topic) const = 0;

protected:
    ISubscribersGroupFinder() = default;
    ISubscribersGroupFinder(const ISubscribersGroupFinder& a_rhs) = default;
    ISubscribersGroupFinder& operator = (const ISubscribersGroupFinder& a_rhs) = default;

};

} // namespace smarthome

#endif //  I_SUBSCRIBERS_GROUP_FINDER_H