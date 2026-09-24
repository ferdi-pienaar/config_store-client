/*
 */
#include "cfg.h" // Configuration data structures.
#include "client.h"
#include <chrono>

using namespace std::chrono;

void Client::start()
{
    m_thread = std::thread(&Client::thread_entry, this);
}

// Periodically, update some stats that can be displayed by cfg_mgr.
// NB: there's a race condition here! By the time we modify config
// it may not exist anymore.
void Client::thread_entry()
{
    for (;;)
    {
        std::this_thread::sleep_for(milliseconds(4500));

        if (m_device.userCnt > 0)
        {
            static unsigned short userIdx = 0;
            userIdx = (userIdx >= m_device.userCnt - 1) ? 0 : userIdx + 1;
            m_device.user[userIdx].elapsed++;
        }
    }
}
