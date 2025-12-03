#pragma once

#include "syati.h"

#define SCENE_OBJ_RPS_MANAGER 71

enum RPSType {
    NIL,
    ROCK,
    PAPER,
    SCISSORS
};

class RPSMgr : public NameObj {
public:
    RPSMgr(const char *pName);
    ~RPSMgr();
    void reportPlayer(RPSType input);
    void reportOpponent(RPSType input);
    bool isPlayerLoss();
    bool isPlayerWin();

    RPSType mPlayerChoice;      // _90
    RPSType mOpponentChoice;    // _94
};

NameObj *createRPSManager();
RPSMgr *getRPSManager();