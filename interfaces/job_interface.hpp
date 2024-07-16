#ifndef IJOB_HPP
#define IJOB_HPP
#include <chrono>
#include <functional>
#include <memory>

class JobInterface {
public:
    virtual ~JobInterface() = default;
    virtual std::string getName() const = 0;
    virtual int getPriority() const = 0;
    virtual const std::chrono::system_clock::time_point& getScheduledTime() const = 0;
    virtual std::chrono::system_clock::time_point& getScheduledTime() = 0;
    virtual std::function<void()> getTask() const = 0;
    virtual bool IsPeriodic() const = 0;
    virtual std::chrono::seconds getInterval() const = 0;
    virtual void printScheduledTime() const = 0;
};

#endif
