#ifndef BOMBERMAN_CWALL_H
#define BOMBERMAN_CWALL_H

#include "Object.h"

/**
 * \brief The game object representing a wall. It cannot be destroyed during the game.
 */
class Wall : public Object
{
    public:
        static const char MARK = '#';

        Wall( void );
        virtual int Update( const int &timeDiff );
        virtual bool Destroy( int &power );
};


#endif //BOMBERMAN_CWALL_H
