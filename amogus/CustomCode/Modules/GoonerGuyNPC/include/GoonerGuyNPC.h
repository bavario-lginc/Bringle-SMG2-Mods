#pragma once

#include "syati.h"

class GoonerGuyNPC : public NPCActor {
public:
    GoonerGuyNPC(const char *pName);
    virtual void init(const JMapInfoIter &rIter);
};