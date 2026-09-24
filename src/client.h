#pragma once

#include <thread>

struct m_device;

class Client
{
public:
    Client(t_device &d) : m_device(d) {}

    void start();

private:
    void thread_entry();

    t_device &m_device;
    std::thread m_thread;
};
