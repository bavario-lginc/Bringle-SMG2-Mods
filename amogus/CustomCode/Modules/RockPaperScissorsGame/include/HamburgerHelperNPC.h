#pragma once

#include "syati.h"
#include "RPSMgr.h"

class HamburgerHelperNPC : public NPCActor {
public:
    HamburgerHelperNPC(const char *pName);
    virtual void init(const JMapInfoIter &rIter);
    bool branchFunc(u32 eventParam);
    bool killFunc(u32 eventParam);

    /* 0 = Wait
    *  1 = Paper or Scissors
    *  2 = Result
    *  3 = Tie or Loss
    */
    s32 mState;
};