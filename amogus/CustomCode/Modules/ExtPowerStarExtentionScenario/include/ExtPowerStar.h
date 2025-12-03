

#include "syati.h"
class ExtPowerStar : public LiveActor {
public:
    ExtPowerStar(const char *pName);

    virtual void init(const JMapInfoIter &rIter);
    virtual void control();
};
namespace pt {

	s32 getPowerStarColor(const char *pStage, s32 scenarioId);
	s32 getPowerStarColorCurrentStage(s32 scenarioId);

	void TamakoroCustomPowerStarColorsParticles(LiveActor* pActor);
};