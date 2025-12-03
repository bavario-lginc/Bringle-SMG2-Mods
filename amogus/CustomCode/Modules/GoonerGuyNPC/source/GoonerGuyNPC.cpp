#include "GoonerGuyNPC.h"

GoonerGuyNPC::GoonerGuyNPC (const char *pName) : NPCActor(pName) {

}

void GoonerGuyNPC::init (const JMapInfoIter &rIter) {
    NPCActorCaps caps = NPCActorCaps("GoonerGuyNPC");
    caps.setDefault();
    _EC = false;
    _ED = false;
    NPCActor::initialize(rIter, caps, 0, "GoonerGuyNPC", 0);
}

kmWrite32(0x80049424, 0x60000000); // Fix talking crash (problematic!)