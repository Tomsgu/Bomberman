#ifndef BOMBERMAN_AIPLAYER_H
#define BOMBERMAN_AIPLAYER_H

#include "Player.h"
#include "AiPlayerScore.h"
#include <queue>
#include <stack>
#include "Objects/Booster/Booster.h"

/**
 * \brief The ai player.
 */
class AiPlayer : public Player
{
    public:
        AiPlayer( const std::shared_ptr<Map> &map, const std::pair<int, int> &pos, const int &id );
        virtual bool DoMove( const int &pressedKey, const int &time );
    private:
        const int PLAYER_MOVE_TIMEOUT = 3000;

        /**
         * \brief Calculate score matrix for planing ai movements.
         * @param map
         */
        void CalculatePointScore( const std::vector<std::vector<Point>> &map );
        /**
         * \brief Find the next("best") movement.
         * @param nextMove The next move.
         */
        bool LookForScore( const std::vector<std::vector<Point>> &map, std::pair<int, int> &nextMove, const int &score,
                           int &foundScore );
        /**
         * \brief Get adjective nodes. It retuns them in random order.
         * @param row
         * @param col
         * @return The array of the adjective nodes.
         */
        std::vector<std::pair<int, int>> GetAdjNodes( const int &row, const int &col ) const;
        /**
         * Update the score in the given point.
         * @param pos Position of the node.
         */
        void UpdateScores( std::pair<int, int> pos );
        /**
         * Is the given score in the next point?
         * @param map
         * @param pos
         * @param score
         * @return true if it's near, false otherwise
         */
        bool IsNear( const std::vector<std::vector<Point>> &map, std::pair<int, int> pos, const int &score ) const;

        std::vector<std::vector<TScorePoint>> m_ScoreMap;

};

#endif //BOMBERMAN_AIPLAYER_H
