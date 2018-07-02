#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include <vector>
#include <memory>
#include "Map.h"
#include "../Graphics/GraphicUI.h"
#include "Player.h"
#include <ncurses.h>
#include <zconf.h>

#define DELAY 40000

/**
 * \brief The game class is responsible for running the game.
 */
class Game
{
    public:
        Game( std::shared_ptr<GraphicUI> ui );
        /**
         * \brief Gets a game world.
         * @return The map.
         */
        std::shared_ptr<Map> GetMap( void ) const;
        /**
         * \brief Add a player to the game.
         * @param position The beginning position of the player on the map.
         * @param isHuman Indicates if the player will be human or AI.
         */
        void AddPlayer( std::pair<int, int> position, const bool &isHuman );
        /**
         * \brief The main method responsible for starting and ending a game.
         */
        int Play( int &playerID );
        /**
         * \brief Do a player move.
         * @param pressedKey The keyboard key pressed by player.
         * @param time The time of the pressing.
         */
        void DoMove( const int &pressedKey, const int &timeDiff );

    private:
        std::vector<std::unique_ptr<Player>> m_Players; //!< \brief The players.
        std::shared_ptr<Map>                 m_Map;//!< \brief The map.
        std::shared_ptr<GraphicUI>           m_Ui;//!< \brief The graphic user interface.

        /**
         * \brief Update player objects by timeDiff.
         *
         * @param timeDiff The time difference from the last update.
         * @return true if the game is over (one or less player left) false otherwise
         */
        bool UpdatePlayers( int &timeDiff );
};

#endif //BOMBERMAN_GAME_H
