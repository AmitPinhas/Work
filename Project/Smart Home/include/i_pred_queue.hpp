#ifndef I_QUEUE_PRED_H
#define I_QUEUE_PRED_H

namespace advcpp
{

class IQueuePred
{
public:
    virtual ~IQueuePred() = 0;
    virtual bool operator()() const = 0;
};

inline IQueuePred::~IQueuePred()
{
}

} // namespace advcpp

#endif //  I_QUEUE_PRED_H