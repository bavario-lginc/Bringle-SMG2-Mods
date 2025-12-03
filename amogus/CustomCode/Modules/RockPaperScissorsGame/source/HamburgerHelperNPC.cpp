#include "HamburgerHelperNPC.h"

HamburgerHelperNPC::HamburgerHelperNPC (const char *pName) : NPCActor(pName) {
    mState = 0;
    MR::createSceneObj(SCENE_OBJ_RPS_MANAGER);
}

void HamburgerHelperNPC::init (const JMapInfoIter &rIter) {
    NPCActorCaps caps = NPCActorCaps("HamburgerHelperNPC");
    caps.setDefault();
    _EC = false;
    _ED = false;
    NPCActor::initialize(rIter, caps, 0, "HamburgerHelperNPC", 0);
    MR::registerBranchFunc(mTalkCtrl, TalkMessageFunc(this, &branchFunc));
    MR::registerKillFunc(mTalkCtrl, TalkMessageFunc(this, &killFunc));
}

bool HamburgerHelperNPC::branchFunc (u32 eventParam) {
    bool rpsChoice = MR::getRandom((s32)0, (s32)2);
    if (mState == 0) {
        if (rpsChoice) {
            getRPSManager()->reportOpponent(ROCK);
            mState = 2;
            return true;
        }
        mState = 1;
        return false;
    } else if (mState == 1) {
        mState = 2;
        if (rpsChoice) {
            getRPSManager()->reportOpponent(PAPER);
            return true;
        } else {
            getRPSManager()->reportOpponent(SCISSORS);
            return false;
        }
    } else if (mState == 2) {
        MR::stopSystemSE("SE_SY_LV_SNARE_ROLL_LV", 0);
        if (getRPSManager()->isPlayerWin()) {
            MR::startSystemSE("SE_SY_ITEM_DICE_FIXED_GOOD", -1, -1);
            return true;
        }
        mState = 3;
        return false;
    } else {
        if (getRPSManager()->isPlayerLoss()) {
            MR::startSystemSE("SE_SY_ITEM_DICE_FIXED_BAD", -1, -1);
            return false;
        }
        return true; // Tie
    }
}

bool HamburgerHelperNPC::killFunc (u32 eventParam) {
    if (getRPSManager()->isPlayerLoss()) {
        MR::forceKillPlayerByGroundRace();
    } else if (getRPSManager()->isPlayerWin()) {
        GameSequenceFunction::closeWipeCircleToPlayerHead();
        GameSequenceFunction::requestChangeScenarioSelect("RoshamboGalaxy");
    } else { // Tie
        LiveActor::kill();
    }
    return true;
}