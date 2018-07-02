#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include <ctime>
#include "Map.h"
#include <memory>

/**
 * \brief Class representing a player.
 */
class Player
{
    public:
        static const int DIRECTION_LEFT  = 0;
        static const int DIRECTION_DOWN  = 1;
        static const int DIRECTION_UP    = 2;
        static const int DIRECTION_RIGHT = 3;
        static const int TIMEOUT_CURSE   = 10000;

        Player( std::shared_ptr<Map> map,
                const std::pair<int, int> &pos,
                const int &id
              );
        /**
         * \brief Do move according a player needs.
         *  @return true if the move was done. false if not.
         */
        virtual bool DoMove( const int &pressedKey, const int &timeDiff ) = 0;
        /**
         * Move the player by one field.
         */
        bool Move( const int &direction );
        bool Move( const std::pair<int, int> position );
        /**
         * \brief Get direction depending on curses.
         * @param direction
         * @return The direction.
         */
        int GetDirection( const int &direction ) const;
        /**
         * \brief Plant a bomb
         * @return  false if there is already bomb on this point.
         */
        bool PlantBomb( void );
        /**
         * \brief Is player dead.
         * @return  true if it is, false otherwise.
         */
        bool IsDead( void ) const;
        /**
         * \brief Update a player.
         * @param timeDiff The time difference from the last update.
         */
        void Update( const int &timeDiff );
        /**
         * @return The id of a player.
         */
        int GetId( void ) const;
        virtual bool IsHuman( void ) const;
    protected:
        std::shared_ptr<Map> m_Map; //!< \brief  The game map.
        std::pair<int, int>  m_Position; //!< \brief The actual position.
        int                  m_BombPower;//!< \brief The bomb power.
        int                  m_AvailableBombs;//!< \brief Available bomb counter.
        bool                 m_Confusion;//!< \brief If the player is confused.
        int                  m_ID;//!< \brief The id of the player.
        int                  m_Cursed;//!< \brief How much ticks missing until curse dissepear.
};


#endif //BOMBERMAN_PLAYER_H
