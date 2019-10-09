//#include <thread>
//#include "timer.h"
//#include "Log/log.h"
//#include <iostream>

//Timer::Timer()
//{

//}

//void Timer::add(std::chrono::milliseconds delay, std::map<Time, std::string>::iterator &it)
//{
//    std::thread thread(&Timer::callback, this, std::ref(it), delay);
//    thread.detach();
//}

//void Timer::callback(std::map<Time, std::string>::iterator &it, std::chrono::milliseconds delay)
//{
//    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
//    std::cout << &it<< std::endl;
//    std::clog << it->first.toString() << " " << it->second << std::endl;

//    add(delay, it);
//}
