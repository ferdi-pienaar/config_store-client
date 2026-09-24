/*
 */
#pragma once

namespace cfg_mgr
{
class Config_manager;
}

class Operator
{
public:
    Operator(cfg_mgr::Config_manager & cm) : m_cfg_mgr(cm) {}
    void start();

private:
    void handle_cmd();
    cfg_mgr::Config_manager &m_cfg_mgr;
};
