#include <iostream>
#include "BaseTask.hpp"
#include "Semaphore.hpp"

class Task : public BaseTask
{
    Semaphore& sem_;
    uint32_t id_;
    void Handler(void) override
    {
        for (uint32_t i = 0; i < 10; i++) {
            sem_.Wait();
            std::cout << "Task " << id_ << " : Semaphore acquired" << std::endl;
            WaitSec(1);
            sem_.Signal();
            WaitMsec(1);    // Waitを入れないと同じタスクが再度セマフォを獲得してしまう
        }
    }

public:
    Task(Semaphore& sem, uint32_t id) : sem_(sem), id_(id) {}
};

int main(int argc, char *argv[])
{
    Semaphore sem;
    Task t1(sem, 1);
    Task t2(sem, 2);
    t1.Start();
    t2.Start();
    t1.WaitUntilDone();
    t2.WaitUntilDone();
    return 0;
}