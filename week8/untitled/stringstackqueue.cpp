#include "stringstackqueue.h"

StringStackQueue::StringStackQueue()
{}

std::string StringStackQueue::deqeue(){
    if (size() > 0){
        std::string temp = m_container.front();
        m_container.pop_front();
        return temp;
    }
    else{
        return "";
    }
}

std::string StringStackQueue::pop(){
    if (size() > 0){
        std::string temp = m_container.front();
        m_container.pop_front();
        return temp;
    }
    else{
        return "";
    }
}

StringStack& StringStackQueue::operator=(const StringStack &stack){}
StringQueue& StringStackQueue::operator=(const StringQueue &queue){}

