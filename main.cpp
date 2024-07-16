#include <iostream>
#include <cassert>
#include <thread>
#include "source/scheduler.hpp"
#include "source/job.hpp"

void basicFunctionalityTest()
{
    Scheduler scheduler;
    // Task definitions
    auto taskA = []()
    { std::cout << "Task A executed\n"; };
    auto taskB = []()
    { std::cout << "Task B executed\n"; };
    auto taskC = []()
    { std::cout << "Task C executed\n"; };
    auto taskD = []()
    { std::cout << "Task D executed\n"; };

    // Adding jobs
    Job jobA("Job A", 10, std::chrono::seconds(1), taskA);
    Job jobB("Job B", 50, DateParser("16/07/2024 15:25"), taskB);
    Job jobC("Job C", 5, std::chrono::seconds(0), taskC, true, std::chrono::seconds(30));
    Job jobD("Job D", 15, std::chrono::seconds(0), taskD);

    scheduler.addJob(jobA);
    scheduler.addJob(jobB);
    scheduler.addJob(jobC);
    scheduler.addJob(jobD);

    // Single step execution
    scheduler.singleStep(); // Should execute Job C (highest priority)
    scheduler.print();

    // Deleting a job
    scheduler.deleteJob("Job A");
    scheduler.print();

    // Start the scheduler
    scheduler.start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    scheduler.stop();
}

void edgeCaseTests()
{
    // Test invalid date format
    try
    {
        DateParser invalidDateParser("invalid date");
        Job invalidJob("Invalid Job", 10, invalidDateParser, []() {});
        assert(false && "Expected std::invalid_argument due to invalid date format");
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Caught expected invalid argument exception: " << e.what() << '\n';
    }

    // Test zero interval for periodic job
    try
    {
        Job zeroIntervalJob("Zero Interval Job", 10, std::chrono::seconds(0), []() {}, true, std::chrono::seconds(0));
        assert(false && "Expected std::invalid_argument due to zero interval");
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Caught expected invalid argument exception: " << e.what() << '\n';
    }

    // Test adding jobs within jobs
    Scheduler scheduler;

    auto taskE = [&scheduler]()
    {
        std::cout << "Task E executed\n";
        Job innerJob("Inner Job", 20, std::chrono::seconds(0), []()
                     { std::cout << "Inner job executed\n"; });
        scheduler.addJob(innerJob);
    };

    scheduler.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scheduler.stop();
}

void noJobsTest()
{
    Scheduler scheduler;
    // Start and stop scheduler with no jobs
    scheduler.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scheduler.stop();

    // Single step execution with no jobs
    scheduler.singleStep();
}

void stoppingWhileRunningTest()
{
    Scheduler scheduler;

    auto longTask = []()
    {
        std::cout << "Long task started\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Long task finished\n";
    };

    Job longJob("Long Job", 10, std::chrono::seconds(0), longTask);
    scheduler.addJob(longJob);

    scheduler.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    scheduler.stop();
}

int main()
{
    std::cout << "Running basic functionality test...\n";
    basicFunctionalityTest();
    std::cout << "Basic functionality test passed!\n\n";

    std::cout << "Running edge case tests...\n";
    edgeCaseTests();
    std::cout << "Edge case tests passed!\n\n";

    std::cout << "Running no jobs test...\n";
    noJobsTest();
    std::cout << "No jobs test passed!\n\n";

    std::cout << "Running stopping while running test...\n";
    stoppingWhileRunningTest();
    std::cout << "Stopping while running test passed!\n\n";

    std::cout << "All tests passed!\n";

    auto taskE = []()
    { std::cout << "Task E executed\n"; };

    return 0;
}
