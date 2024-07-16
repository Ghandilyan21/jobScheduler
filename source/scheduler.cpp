#include "scheduler.hpp"

Scheduler::Scheduler()
    : running(false) {}

void Scheduler::addJob(const Job &job)
{
    jobs.insert(job);
}

void Scheduler::addJob(Job *job)
{
    if (!job)
    {
        throw std::invalid_argument("Passed pointer is not allocated");
    }
    jobs.insert(*job);
}

void Scheduler::deleteJob(const std::string &name)
{
    for (auto it = jobs.begin(); it != jobs.end(); ++it)
    {
        if (it->getName() == name)
        {
            if (it != jobs.end())
            {
                jobs.erase(it);
                return;
            }
        }
    }
}

void Scheduler::execute()
{
    while (running && !jobs.empty())
    {
        auto now = std::chrono::system_clock::now();
        auto it = jobs.begin();
        if (it == jobs.end())
        {
            return;
        }
        if (it->getScheduledTime() > now)
        {
            std::this_thread::sleep_until(it->getScheduledTime());
        }
        (it->getTask())();
        if (it->IsPeriodic())
        {
            Job tmp = (*it);
            jobs.erase(it);
            tmp.getScheduledTime() += tmp.getInterval();
            addJob(tmp);
        }
        else
        {
            jobs.erase(it);
        }
    }
}

void Scheduler::start()
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        running = true;
    }
    schedulerThread = std::thread(&Scheduler::execute, this);
}

void Scheduler::stop()
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        running = false;
    }
    if (schedulerThread.joinable())
    {
        schedulerThread.join();
    }
}

void Scheduler::singleStep()
{
    if (!jobs.empty())
    {
        auto now = std::chrono::system_clock::now();
        auto it = jobs.begin();
        if (it->getScheduledTime() > now)
        {
            std::this_thread::sleep_until(it->getScheduledTime());
        }

        (it->getTask())();

        if (it->IsPeriodic())
        {
            Job tmp = (*it);
            jobs.erase(it);
            tmp.getScheduledTime() += tmp.getInterval();
            addJob(tmp);
        }
        else
        {
            jobs.erase(it);
        }
    }
}

void Scheduler::print()
{
    std::cout << "\nRemaining jobs in the scheduler:\n";
    std::cout << "---------------------------------------" << std::endl;
    for (auto &job : jobs)
    {
        std::cout << job.getName() << " ";
        job.printScheduledTime();
        std::cout << " " << job.getPriority() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
}

Scheduler::~Scheduler()
{
    if (schedulerThread.joinable())
    {
        schedulerThread.join();
    }
}
