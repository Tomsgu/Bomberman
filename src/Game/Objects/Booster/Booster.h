//
// Created by tomsgu on 5/18/17.
//

#ifndef BOMBERMAN_CBOOSTER_H
#define BOMBERMAN_CBOOSTER_H


#include "../Object.h"

/**
 * \Brief Game object that boosts a player, who has been picked it up.
 */
class Booster : public Object
{
    public:
        static const int SCORE = 70;

        Booster( void );
        virtual int Update( const int &timeDiff );
        virtual bool Destroy( int &power );
        virtual bool PickUp( int &power, int &bombCnt, bool &confusion );
        virtual bool AddBooster( int &power, int &bombCnt, bool &confusion ) = 0;
        virtual int GetScore( void ) const;
};


#endif //BOMBERMAN_CBOOSTER_H
