#include "RPSPanel.h"

RPSPanel::RPSPanel (const char *pName) : LiveActor(pName) {
    mTimer = 0;
}

RPSPanel::~RPSPanel () {

}

void RPSPanel::init (const JMapInfoIter &rIter) {
    MR::initDefaultPos(this, rIter);
    MR::processInitFunction(this, rIter, false);
    MR::connectToSceneMapObj(this);
    MR::getJMapInfoArg0WithInit(rIter, (s32 *)&mType);
    MR::getJMapInfoArg1NoInit(rIter, &mTimer);
    initNerve(&NrvRPSPanel::NrvWait::sInstance, 0);
    MR::useStageSwitchSyncAppear(this, rIter);
    MR::useStageSwitchWriteA(this, rIter);
    initHitSensor(1);
    MR::addHitSensorMapObj(this, "Body", 1, 200.0f, TVec3f(0, 0, -250.0f));
}

void RPSPanel::appear () {
    LiveActor::appear();
    setNerve(&NrvRPSPanel::NrvWait::sInstance);
    switch (mType) {
        case ROCK:
            MR::startBtpAndSetFrameAndStop(this, "Texture", 1);
            break;
        case PAPER:
            MR::startBtpAndSetFrameAndStop(this, "Texture", 3);
            break;
        case SCISSORS:
            MR::startBtpAndSetFrameAndStop(this, "Texture", 5);
            break;
    }
}

void RPSPanel::attackSensor (HitSensor *pReceiver, HitSensor *pSender) {
    if (isNerve(&NrvRPSPanel::NrvWait::sInstance) && MR::isSensorPlayer(pSender) && MR::isOnGroundPlayer()) {
        setNerve(&NrvRPSPanel::NrvStepped::sInstance);
    }
}

void RPSPanel::exeWait () {
    
}

void RPSPanel::exeStepped () {
    if (MR::isFirstStep(this)) {
        MR::startSystemSE("SE_SY_LV_SNARE_ROLL_LV", -1, -1);
        switch (mType) {
            case ROCK:
                MR::startBtpAndSetFrameAndStop(this, "Texture", 0);
                break;
            case PAPER:
                MR::startBtpAndSetFrameAndStop(this, "Texture", 2);
                break;
            case SCISSORS:
                MR::startBtpAndSetFrameAndStop(this, "Texture", 4);
                break;
        }
    }
    MR::tryRumblePadVeryWeak(this, 0);
    if (MR::isStep(this, mTimer)) {
        MR::startSystemSE("SE_SY_SNARE_ROLL_END", -1, -1);
        MR::onSwitchA(this);
        getRPSManager()->reportPlayer(mType);
        setNerve(&NrvRPSPanel::NrvAfterStep::sInstance);
    }
}

namespace NrvRPSPanel {
    void NrvWait::execute (Spine *pSpine) const {
        RPSPanel *pExecutor = (RPSPanel *)pSpine->mExecutor;
        pExecutor->exeWait();
    }

    void NrvStepped::execute (Spine *pSpine) const {
        RPSPanel *pExecutor = (RPSPanel *)pSpine->mExecutor;
        pExecutor->exeStepped();
    }

    void NrvAfterStep::execute (Spine *pSpine) const {
        
    }

    NrvWait(NrvWait::sInstance);
    NrvStepped(NrvStepped::sInstance);
    NrvAfterStep(NrvAfterStep::sInstance);
}