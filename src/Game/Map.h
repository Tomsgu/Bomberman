#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include <ctime>
#include "Point.h"

/**
 * \brief The map class represents a game world.
 *
 * It consists of different objects that inherits form the Objecs/Object class.
 */
class Map
{
    public:
        static const int DIRECTION_LEFT  = 0;
        static const int DIRECTION_DOWN  = 1;
        static const int DIRECTION_UP    = 2;
        static const int DIRECTION_RIGHT = 3;

        Map( void );
        void InitMap( const int &rows, const int &cols );
        void InitBombs( const unsigned long &playerCnt );
        void AddObject( const char &symbol, const int &row, const int &col, const int &playerID );
        void AddObject( std::unique_ptr<Object> object, const int &row, const int &col );
        void UpdateBombRangeMark( const std::pair<int, int> &pos, const int &power, const int &value );
        bool PickUp( const std::pair<int, int> &pos, int &power, int &bombCnt, bool &confusion );
        bool MoveTo( std::pair<int, int> pos, std::pair<int, int> nextPos, const int &id = -1 );
        void AddPlayerBomb( const int &playerID );
        void Update( const int &time );

        void DeleteDestroyedItems( void );

        int GetBombCnt( const int &playerID ) const;
        int Rows( void ) const;
        int Cols( void ) const;
        char Mark( const int &row, const int &col ) const;
        int Color( const int &row, const int &col ) const;
        bool IsPlayerDead( const std::pair<int, int> &pos, const int &playerID ) const;
        const std::vector<std::vector<Point>> &GetMap( void ) const;

    private:
        std::vector<std::vector<Point>> m_Map;
        std::vector<int>                m_PlantedBombs;
        int                             m_Rows;
        int                             m_Cols;

        void Explode( const int &power, const int &row, const int &col, const int &direction );
        void UpdateBombRangeMarkDir( int row, int col, const int &power, const int &direction, const int &value );
};


#endif //BOMBERMAN_MAP_H
