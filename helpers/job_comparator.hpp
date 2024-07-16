#include "../interfaces/job_interface.hpp"
#include "memory"
struct JobComparator
{
    bool operator()(const JobInterface &lhs, const JobInterface &rhs) const;
    
};
