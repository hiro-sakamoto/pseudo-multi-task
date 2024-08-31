#include <cstdint>
#include <mutex>
#include "Event.hpp"

class DataQueue
{
    uint32_t maxCount_;
    uint32_t count_;
    uint32_t head_;
    uint32_t tail_;
    uintptr_t *entries_;
    std::mutex mutex_;
    Event event_;

    bool SendData(uintptr_t data)
    {
        bool ret = false;
        mutex_.lock();
        if (count_ < maxCount_) {
            count_++;
            entries_[tail_++] = data;
            if (tail_ == maxCount_) {
                tail_ = 0;
            }
            ret = true;
        }
        mutex_.unlock();
        return ret;
    }

    bool ReceiveData(uintptr_t *data)
    {
        bool ret = false;
        mutex_.lock();
        if (count_ > 0) {
            count_--;
            *data = entries_[head_++];
            if (head_ == maxCount_) {
                head_ = 0;
            }
            ret = true;
        }
        mutex_.unlock();
        return ret;
    }

public:
    DataQueue(uint32_t maxCount) : maxCount_(maxCount), count_(0), head_(0), tail_(0)
    {
        entries_ = new uintptr_t[maxCount];
    }

    ~DataQueue(void)
    {
        delete [] entries_;
    }

    bool Send(uintptr_t data)
    {
        if (SendData(data)) {
            event_.Set();
            return true;
        }
        return false;
    }

    void Receive(uintptr_t *data)
    {
        while (ReceiveData(data) == false) {
            event_.Wait();
        }
    }
};