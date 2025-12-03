#pragma once

#include "syati.h"
#include "RPSMgr.h"

class RPSPanel : public LiveActor {
public:
    RPSPanel(const char *pName);
    ~RPSPanel();
    virtual void init(const JMapInfoIter &rIter);
    virtual void appear();
    virtual void attackSensor(HitSensor *pReceiver, HitSensor *pSender);
    void exeWait();
    void exeStepped();

    RPSType mType;  // _90
    s32 mTimer;     // _94
};

namespace NrvRPSPanel {
    NERVE(NrvWait);
    NERVE(NrvStepped);
    NERVE(NrvAfterStep);
}