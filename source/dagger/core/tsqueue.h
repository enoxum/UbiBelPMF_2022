#include "core/core.h"
#include <mutex>
#include <deque>

namespace dagger {

    // This is a temporary naive implementation of a thread-safe queue
    template<typename T>
    class TSQueue
    {
    public:
        TSQueue() = default;
        TSQueue(const TSQueue<T>&) = delete;

        const T& front()
        {
            std::scoped_lock lock(mtx_);
            return queue_.front();
        }

        const T& back()
        {
            std::scoped_lock lock(mtx_);
            return queue_.back();
        }

        void push(const T& item) 
        {
            std::scoped_lock lock(mtx_);
            queue_.push_back(item);
        }

        bool empty() const
        {
            std::scoped_lock lock(mtx_);
            return queue_.empty();
        }

        size_t size() const
        {
            std::scoped_lock lock(mtx_);
            return queue_.size();
        }

        void clear()
        {
            std::scoped_lock lock(mtx_);
            queue_.clear();
        }

        T pop_front() 
        {
            std::scoped_lock lock(mtx_);
            auto item = std::move(queue_.front());
            queue_.pop_front();
            return item;
        }
    protected:
        std::mutex mtx_;
        std::deque<T> queue_;
    };
}