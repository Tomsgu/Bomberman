#ifndef BOMBERMAN_CINCREASEBOMBPOWER_H
#define BOMBERMAN_CINCREASEBOMBPOWER_H

#include "Booster.h"

/**
 * \brief This booster increases a power of the player's bombs.
 */
class IncreaseBombPower : public Booster
{
    public:
        IncreaseBombPower( void )
        {
            m_Mark = 'P';
        }

        virtual bool AddBooster( int &power, int &bombCnt, bool &confusion )
        {
            power++;

            return true;
        }
};

#endif //BOMBERMAN_CINCREASEBOMBPOWER_H
