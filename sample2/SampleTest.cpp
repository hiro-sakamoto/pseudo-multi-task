#include <iostream>
#include "BaseTask.hpp"
#include "Event.hpp"

class Task1 : public BaseTask
{
    Event& evt_;
    void Handler(void) override
    {
        for (uint32_t i = 0; i < 10; i++) {
            std::cout << "Task 1 : Wait for event" << std::endl;
            evt_.Wait();
            std::cout << "Task 1 : Event received" << std::endl;
        }
    }

public:
    Task1(Event& evt) : evt_(evt) {}
};

class Task2 : public BaseTask
{
    Event& evt_;
    void Handler(void) override
    {
        for (uint32_t i = 0; i < 10; i++) {
            WaitSec(1);
            std::cout << "Task 2 : Signal event" << std::endl;
            evt_.Signal();
        }
    }

public:
    Task2(Event& evt) : evt_(evt) {}
};

int main(int argc, char *argv[])
{
    Event evt;
    Task1 t1(evt);
    Task2 t2(evt);
    t1.Start();
    t2.Start();
    t1.WaitUntilDone();
    t2.WaitUntilDone();
    return 0;
}