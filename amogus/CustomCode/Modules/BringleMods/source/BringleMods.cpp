#include "BringleMods.h"

// INFERNO MARIO (COSMIC CLONES)

InfernoMarioGenerator *pGenerator;
#ifdef INFERNO_BONUS
    bool isInfernoBonus = false;
#endif

#ifdef INFERNO_SPAWN_AUTOMATICALLY
    #define INFERNO_SPAWN_DELAY 120
    s32 infernoDelayTimer = 0;
#endif

void initInferno () {
    if (MR::isEqualStageName("SY24EntryGalaxy")
        || MR::isEqualStageName("WanwanBigFactoryGalaxy")
        || MR::isEqualStageName("DimensionSmallCastleGalaxy") && MR::getCurrentScenarioNo() == 1
        || MR::isEqualStageName("xandog_IslandFleetGalaxy") && MR::getCurrentScenarioNo() == 2
        || MR::isEqualStageName("xandog_IslandFleetGalaxy") && MR::getCurrentScenarioNo() == 3
        || MR::isEqualStageName("GhostlyMansionGalaxy")
        || MR::isEqualStageName("SandTwisterGalaxy")
        || MR::isEqualStageName("HubworldGalaxy")) 
        return;
    pGenerator = new InfernoMarioGenerator("InfernoMarioGenerator");
    
    //MR::initDefaultPos(pGenerator, rIter);
    MR::connectToSceneEnemyMovement(pGenerator);
    pGenerator->initEffectKeeper(0, "InfernoMario", 0);
    TVec3f v0 = TVec3f(0.0f);
    pGenerator->initSound(3, "InfernoMarioGenerator", false, v0);
    // Skip obj_arg reads
    pGenerator->mInfernoMarioGroup = new LiveActorGroup("インフェルノマリオ管理", pGenerator->mCount);
    for (s32 i = 0; i < pGenerator->mCount; i++) {
        InfernoMario *pInferno = new InfernoMario("インフェルノマリオ");
        if (i == 0) 
            pInferno->_128 = true;
        pInferno->_E0 = pGenerator->_9C;
        MR::setPosition(pInferno, pGenerator->mTranslation);
        pInferno->initWithoutIter();
        pGenerator->mInfernoMarioGroup->registerActor(pInferno);
    }
    pGenerator->initNerve(&NrvInfernoMarioGenerator::unk_807DA4E4::sInstance, 1);
    // Skip Actor State
    MR::invalidateClipping(pGenerator);
    // ??? _A8 = MR::setupAlreadyDoneFlag(&_A4, "繧､繝ｳ繝輔ぉ繝ｫ繝守匳蝣ｴ繝?繝｢蜀咲函貂医∩", rIter, 1);
    // if (!ActorStateThingy->_20) _A8 = 1;
    // No SW_APPEAR
    pGenerator->setNerve(&NrvInfernoMarioGenerator::unk_807DA4E4::sInstance);
    // No SW_B
}
kmBranch(0x803B7BAC, initInferno);

#ifdef INFERNO_BONUS
    void onInfernoBonus () {
        if (pGenerator && !MR::isDead(pGenerator)) 
            isInfernoBonus = true;
    }
    kmBranch(0x80452B60, onInfernoBonus);
    kmBranch(0x80452B90, onInfernoBonus);

    void startFlyingMusic () {
        MR::startSubBGM("BGM_FLYING_B", false);
    }
    kmCall(0x803CB938, startFlyingMusic);

    void exeInfernoBonus () {
        if (isInfernoBonus && !MR::isStageMarioFaceShip() && !MR::isStageWorldMap()) {
            MR::changePlayerModeFoo();
            isInfernoBonus = false;
        }
    }
    kmBranch(0x8005A4D0, exeInfernoBonus);
#endif

void updateInferno () {
    #ifdef INFERNO_SPAWN_AUTOMATICALLY
        if (infernoDelayTimer == 0 && pGenerator && MR::isDead(pGenerator) && !MR::isStageFileSelect() && !MR::isStageMarioFaceShip() && !MR::isStageWorldMap()) {
            infernoDelayTimer++;
        }
        if (infernoDelayTimer > 0 && pGenerator && MR::isDead(pGenerator)) {
            if (infernoDelayTimer++ == INFERNO_SPAWN_DELAY) {
                pGenerator->appear();
                infernoDelayTimer = 0;
            }
        }
    #endif
    if (MR::testCorePadTrigger2(0) && pGenerator) {
        if (MR::isDead(pGenerator)) {
            pGenerator->appear();
        } else {
            pGenerator->kill();
        }
    }
}


kmWrite32(0x80382084, 0x38800014); // 20 Cosmic Clones by default

kmWrite32(0x803801F0, 0x60000000); // Fix Shell animation crash

// FIX RAINBOW MARIO ANIMATION
// By Aurum
void invokeInvincibleMarioModelCalcAnim(ModelHolder *pModelHolder) {
    MR::onCalcAnim(pModelHolder);
    pModelHolder->calcAnim();
}
kmCall(0x803C4A0C, invokeInvincibleMarioModelCalcAnim);

// LIFE MUSHROOM

#ifdef NO_LIFE_MUSHROOM
    // Trust me Bringle, that fixes it :)
    void fixLifeMushroom (MarioActor *pMarioActor, s32 lifeNum) {
        MR::forceKillPlayerByGroundRace();
    }
    kmCall(0x803C1CBC, fixLifeMushroom);
#endif