#include <mutex>

class Semaphore
{
    std::mutex mutex_;

public:
    // セマフォ資源を獲得する
    void Wait(void)
    {
        mutex_.lock();
    }

    // セマフォ資源を返却する
    void Signal(void)
    {
        mutex_.unlock();
    }
};