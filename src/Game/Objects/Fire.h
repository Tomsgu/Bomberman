//
// Created by tomsgu on 5/16/17.
//

#ifndef BOMBERMAN_CFIRE_H
#define BOMBERMAN_CFIRE_H


#include "Object.h"

/**
 * \brief The game object representing a fire of the bomb.
 */
class Fire : public Object
{
    public:
        static const char MARK = 'x';
        static const int SCORE = -200;

        Fire( void );
        virtual int Update( const int &timeDiff );
        virtual bool Destroy( int &power );
        virtual bool InExplosion( void ) const;
        virtual int GetScore ( void ) const;
    private:
        static const int TIMEOUT = 1000;
        int              m_Timer;
};


#endif //BOMBERMAN_CFIRE_H
