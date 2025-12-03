#include "RPSMgr.h"

RPSMgr::RPSMgr (const char *pName) : NameObj(pName) {
    mPlayerChoice = NIL;
    mOpponentChoice = NIL;
}

RPSMgr::~RPSMgr () {

}

void RPSMgr::reportPlayer (RPSType input) {
    mPlayerChoice = (RPSType)input;
}

void RPSMgr::reportOpponent (RPSType input) {
    mOpponentChoice = (RPSType)input;
}

bool RPSMgr::isPlayerLoss () {
    return (mPlayerChoice == ROCK && mOpponentChoice == PAPER
        || mPlayerChoice == PAPER && mOpponentChoice == SCISSORS
        || mPlayerChoice == SCISSORS && mOpponentChoice == ROCK);
}

bool RPSMgr::isPlayerWin () {
    return (mPlayerChoice == ROCK && mOpponentChoice == SCISSORS
        || mPlayerChoice == PAPER && mOpponentChoice == ROCK
        || mPlayerChoice == SCISSORS && mOpponentChoice == PAPER);
}

NameObj *createRPSManager () {
    return new RPSMgr("RPSManager");
}

RPSMgr *getRPSManager () {
    return (RPSMgr *)MR::getSceneObjHolder()->getObj(SCENE_OBJ_RPS_MANAGER);
}