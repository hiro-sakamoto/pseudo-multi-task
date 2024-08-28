#include <condition_variable>
#include <mutex>

class Event
{
    std::mutex mutex_;
    std::condition_variable cond_;

public:
    void Signal(void)
    {
        cond_.notify_one();
    }
    void Wait(void)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock);
    }
};