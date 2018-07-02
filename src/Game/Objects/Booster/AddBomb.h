#ifndef BOMBERMAN_CADDBOMB_H
#define BOMBERMAN_CADDBOMB_H

#include "Booster.h"

/**
 * \brief This booster adds a bomb to the player.
 */
class AddBomb : public Booster
{
    public:
        AddBomb( void )
        {
            m_Mark = 'B';
        }

        virtual bool AddBooster( int &power, int &bombCnt, bool &confusion )
        {
            bombCnt++;

            return true;
        }
};


#endif //BOMBERMAN_CADDBOMB_H
