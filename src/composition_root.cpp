/*
  Manual test framework that accepts inputs from stdin; CM produces output to stdout.

 */
#include <iostream>
#include "cfg_mgr.h"
#include "cfg.h"
#include "client.h"
#include "operator.h"

cfg_mgr::Descriptor * get_base_descriptor();

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Name of config file is required.\n");
        return 1;
    }

    // Initialize the config manager with the base descriptor it is to manage.
    t_device * pCfg = nullptr;
    cfg_mgr::Config_manager cm(get_base_descriptor(), argv[1], printf, (uint8_t **)&pCfg);

    Client client(*pCfg);
    client.start();

    Operator op(cm);
    op.start();
    return 0;
}
