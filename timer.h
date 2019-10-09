#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <mutex>

class Timer
{
public:
    Timer() : _stoped(true)
    {

    }

    template<class T, class TT>
    void start(void (*callback)(T&, TT&, std::chrono::milliseconds), T &test)
    {
        std::lock_guard<std::mutex> lock(m_changing_mutex);
        _stoped = false;

        std::thread thread(callback, std::ref(test), std::ref(*this), std::chrono::milliseconds(1000));
        thread.detach();
    }
    void stop()
    {
        std::lock_guard<std::mutex> lock(m_changing_mutex);
        _stoped = true;
    }

    bool _stoped;
    std::mutex m_changing_mutex;
};

#endif // TIMER_H
