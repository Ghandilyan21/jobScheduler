#include "job.hpp"
#include "../helpers/date_parser.hpp"
Job::Job(const std::string &name, int priority, const DateParser &time, const std::function<void()> &task, bool periodic, const std::chrono::seconds &interval)
    : name{name}, priority{priority}, scheduledTime{time.parseDate()}, task{task}, isPeriodic{periodic}, interval{interval}
{
    if (isPeriodic && interval <= std::chrono::seconds(0))
    {
        throw std::invalid_argument("Interval must be positive for periodic jobs");
    }
}

Job::Job(const std::string &name, int priority, const std::chrono::system_clock::time_point &time, const std::function<void()> &task, bool periodic, const std::chrono::seconds &interval)
    : name{name}, priority{priority}, scheduledTime{time}, task{task}, isPeriodic{periodic}, interval{interval}
{
    if (isPeriodic && interval <= std::chrono::seconds(0))
    {
        throw std::invalid_argument("Interval must be positive for periodic jobs");
    }
}
Job::Job(const std::string &name, int priority, const std::chrono::seconds &time, const std::function<void()> &task, bool periodic, const std::chrono::seconds &interval)
    : name{name}, priority{priority}, scheduledTime{std::chrono::system_clock::now() + time}, task{task}, isPeriodic{periodic}, interval{interval}
{
    if (isPeriodic && interval <= std::chrono::seconds(0))
    {
        throw std::invalid_argument("Interval must be positive for periodic jobs");
    }
}
Job::Job(const Job &other)
    : name{other.getName()},
      priority{other.getPriority()},
      scheduledTime{other.getScheduledTime()},
      task{other.getTask()},
      isPeriodic{other.IsPeriodic()},
      interval{other.getInterval()}
{
}

std::string Job::getName() const
{
    return name;
}

int Job::getPriority() const
{
    return priority;
}

std::chrono::system_clock::time_point &Job::getScheduledTime()
{
    return scheduledTime;
}

const std::chrono::system_clock::time_point &Job::getScheduledTime() const
{
    return scheduledTime;
}

std::function<void()> Job::getTask() const
{
    return task;
}

bool Job::IsPeriodic() const
{
    return isPeriodic;
}

std::chrono::seconds Job::getInterval() const
{
    return interval;
}

void Job::printScheduledTime() const
{
    auto timeT = std::chrono::system_clock::to_time_t(scheduledTime);
    std::tm *tm = std::localtime(&timeT);
    std::cout << std::put_time(tm, "%d/%m/%Y %H:%M:%S") << " ";
}
