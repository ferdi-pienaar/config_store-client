/*
 */
#include <iostream>
#include "cfg_mgr.h"
#include "operator.h"
#include "util/cfg_mgr_strtok.h" // strtok

#define WORD_DELIMITERS " \n"
#define BLOCK_DELIMITER "\""

void Operator::start()
{
    while (true)
    {
        handle_cmd();
    }
}

void Operator::handle_cmd()
{
    printf("%s> ", m_cfg_mgr.getPromptString());

    char cmd[120];
    if (fgets(cmd, sizeof(cmd), stdin) == nullptr)
    {
        return;
    }

    // Break commands into a list of tokens, as expected by config manager
    char * param[20];
    cfg_mgr::Strtok strtok(cmd);
    unsigned int wordCnt = 0;
    while ((param[wordCnt] = strtok(WORD_DELIMITERS, BLOCK_DELIMITER)))
    {
        wordCnt++;
    }
    m_cfg_mgr.handleCmd(wordCnt, param);
}
