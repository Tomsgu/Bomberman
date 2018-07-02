#ifndef BOMBERMAN_CPLAYEROBJECT_H
#define BOMBERMAN_CPLAYEROBJECT_H

#include "Object.h"

/**
 * \brief The game object representing a player.
 */
class PlayerObject : public Object
{
    public:
        static const char MARK  = 'O';
        static const int  SCORE = 40;

        PlayerObject( const int &id );
        virtual int GetID( void ) const;
        virtual int Update( const int &timeDiff );
        virtual bool Destroy( int &power );
        virtual int GetScore( void ) const;
    private:
        int m_ID; //!< \brief The id of the player.
};

#endif //BOMBERMAN_CPLAYEROBJECT_H
