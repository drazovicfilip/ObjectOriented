#ifndef STRINGSTACKQUEUE_H
#define STRINGSTACKQUEUE_H

#include "stringqueue.h"
#include "stringstack.h"
#include <deque>
#include <iostream>


class StringStackQueue : public virtual StringQueue, public virtual StringStack
{
public:
    StringStackQueue();
    ~StringStackQueue(){}
    size_t size() const override{ return m_container.size(); }
    bool empty() const override{ return (m_container.size() == 0); }
    std::string deqeue() override;
    void enqueue(const std::string &string) override{ m_container.push_back(string); }
    const std::string& front() const override{ return m_container.front(); }
    void push(const std::string &string) override{ m_container.push_front(string); }
    std::string pop() override;
    const std::string& peek() const override{ return m_container.front(); }
    StringStack& operator=(const StringStack& stack) override;
    StringQueue& operator=(const StringQueue& queue) override;

private:
    std::deque<std::string> m_container;
};

#endif // STRINGSTACKQUEUE_H
