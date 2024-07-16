#ifndef JOB_H
#define JOB_H
#include "../interfaces/job_interface.hpp"
#include <iostream>
#include <functional>
#include <chrono>
#include <string>
#include "../helpers/date_parser.hpp"

class Job : public JobInterface
{
public:
    // Constructor for absolute time delay
    Job(const std::string &name, int priority, const DateParser &time, const std::function<void()> &task, bool periodic = false, const std::chrono::seconds &interval = std::chrono::seconds(0));
    // Constructor for relative time delay
    Job(const std::string &name, int priority, const std::chrono::system_clock::time_point &time, const std::function<void()> &task, bool periodic = false, const std::chrono::seconds &interval = std::chrono::seconds(0));
    // Constructor for seconds
    Job(const std::string &name, int priority, const std::chrono::seconds &time, const std::function<void()> &task, bool periodic = false, const std::chrono::seconds &interval = std::chrono::seconds(0));
    Job(const Job& other);
    
    std::string getName() const override;
    int getPriority() const override;
    const std::chrono::system_clock::time_point& getScheduledTime() const override;
    std::chrono::system_clock::time_point& getScheduledTime() override;
    std::function<void()> getTask() const override;
    bool IsPeriodic() const override;
    std::chrono::seconds getInterval() const override;
    void printScheduledTime() const override;
    ~Job() override {
        // std::cout << "\n " << name << " dtor\n";
    };
private:
    std::string name;
    int priority;
    std::chrono::system_clock::time_point scheduledTime;
    std::function<void()> task;
    bool isPeriodic;
    std::chrono::seconds interval;
};

#endif