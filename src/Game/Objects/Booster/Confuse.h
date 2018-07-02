#ifndef BOMBERMAN_CCONFUSE_H
#define BOMBERMAN_CCONFUSE_H

#include "Booster.h"

/**
 * \brief This booster infect the player with confusion (keyboard keys are in reverse).
 */
class Confuse : public Booster
{
    public:
        virtual bool AddBooster( int &power, int &bombCnt, bool &confusion )
        {
            confusion = true;

            return true;
        }
};

#endif //BOMBERMAN_CCONFUSE_H
