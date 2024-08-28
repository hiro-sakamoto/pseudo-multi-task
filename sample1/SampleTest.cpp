#include <iostream>
#include "BaseTask.hpp"

class Task : public BaseTask
{
    const uint32_t id_;

    void Handler(void) override
    {
        for (uint32_t i = 0; i < 10; i++) {
            std::cout << "Task " << id_ << " : " << i << std::endl;
            uint32_t x = (i + id_) % 3;
            if (x == 0) {
                WaitUsec(500);
            } else if (x == 1) {
                WaitMsec(200);
            } else {
                WaitSec(1);
            }
        }
    }

public:
    Task(uint32_t id) : id_(id) {}
};

int main(int argc, char *argv[])
{
    Task t1(1), t2(2);
    t1.Start();
    t2.Start();
    t1.WaitUntilDone();
    t2.WaitUntilDone();
    return 0;
}