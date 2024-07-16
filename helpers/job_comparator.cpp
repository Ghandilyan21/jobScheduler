#include "job_comparator.hpp"
bool JobComparator::operator()(const JobInterface &lhs,const JobInterface &rhs) const
{
    if (lhs.getScheduledTime() == rhs.getScheduledTime())
    {
        return lhs.getPriority() > rhs.getPriority();
    }
    return lhs.getScheduledTime() < rhs.getScheduledTime();
}
