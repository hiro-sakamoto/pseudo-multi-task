#include <thread>
#include <cstdint>
#include <chrono>

class BaseTask
{
    std::thread * thread_;
    virtual void Handler(void) = 0;

protected:
    BaseTask(void) : thread_(nullptr)
    {
    }

public:
    // タスクを開始する
    void Start(void)
    {
        thread_ = new std::thread([&](BaseTask * task){
                            task->Handler();
                        }, this);
    }

    // タスクが終了するまで待つ
    void WaitUntilDone(void)
    {
        if (thread_ != nullptr) {
            thread_->join();
            delete thread_;
        }
    }

    // 秒単位の遅延を挿入
    void WaitSec(uint32_t sec)
    {
        std::chrono::seconds time(sec);
        std::this_thread::sleep_for(time);
    }

    // ミリ秒単位の遅延を挿入
    void WaitMsec(uint32_t msec)
    {
        std::chrono::milliseconds time(msec);
        std::this_thread::sleep_for(time);
    }

    // マイクロ秒単位の遅延を挿入
    void WaitUsec(uint32_t usec)
    {
        std::chrono::microseconds time(usec);
        std::this_thread::sleep_for(time);
    }
};