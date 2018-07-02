#ifndef BOMBERMAN_CBOMB_H
#define BOMBERMAN_CBOMB_H

#include "Object.h"

/**
 * \brief The game object representing a bomb.
 */
class Bomb : public Object
{
    public:
        static const char MARK  = '@';
        static const int  SCORE = -100;

        Bomb( const int &power,
              const std::pair<int, int> &position,
              const int &playerID );
        virtual int GetID( void ) const;

        virtual bool Destroy( int &power );
        virtual int Update( const int &timeDiff );
        virtual bool InExplosion( void ) const;
        virtual int GetScore( void ) const;
    private:
        static const int TIMEOUT                 = 2000; // More or less 2 seconds
        static const int TIMEOUT_AFTER_EXPLOSION = 1000; //              1 second

        int  m_Power;    //!< \brief The power of the bomb.
        bool m_Exploded; //!< \brief Indicated if the bomb has exploded
        int  m_PlayerID; //!< \brief Player id who owns this bomb.
        int  m_Timer;    //!< \brief Holds ticks to next action(explosion, destroying)
};

#endif //BOMBERMAN_CBOMB_H
