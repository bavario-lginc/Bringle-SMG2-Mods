#pragma once

#include "syati.h"

void initInferno();

#ifdef INFERNO_BONUS
    void onInfernoBonus();
    void startFlyingMusic();
    void exeInfernoBonus();
#endif

void updateInferno();
void invokeInvincibleMarioModelCalcAnim(ModelHolder *pModelHolder);

#ifdef NO_LIFE_MUSHROOM
    void fixLifeMushroom(MarioActor *pMarioActor, s32 lifeNum);
#endif