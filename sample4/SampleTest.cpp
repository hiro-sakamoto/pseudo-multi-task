#include <iostream>
#include "BaseTask.hpp"
#include "DataQueue.hpp"

class Task1 : public BaseTask
{
    DataQueue& dtq_;
    void Handler(void) override
    {
        for (uint32_t i = 0; i < 10; i++) {
            uintptr_t data;
            dtq_.Receive(&data);
            std::cout << "Received data : " << data << std::endl;
        }
    }

public:
    Task1(DataQueue& dtq) : dtq_(dtq) {}
};

class Task2 : public BaseTask
{
    DataQueue& dtq_;
    void Handler(void) override
    {
        for (uint32_t i = 0; i < 10; i++) {
            std::cout << "Send data : " << i << std::endl;
            dtq_.Send(i);
            WaitSec(1);
        }
    }

public:
    Task2(DataQueue& dtq) : dtq_(dtq) {}
};

int main(int argc, char *argv[])
{
    DataQueue dtq(4);
    Task1 t1(dtq);
    Task2 t2(dtq);
    t1.Start();
    t2.Start();
    t1.WaitUntilDone();
    t2.WaitUntilDone();
    return 0;
}