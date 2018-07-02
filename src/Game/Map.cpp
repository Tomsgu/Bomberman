#include "Map.h"
#include <csignal>
#include "Objects/Fire.h"

using namespace std;

Map::Map( void )
{
}

void Map::AddObject( const char &symbol, const int &row, const int &col, const int &playerID )
{
    m_Map.at(row).at(col).AddObject(symbol, playerID);
}

void Map::AddObject( unique_ptr<Object> object, const int &row, const int &col )
{
    m_Map.at(row).at(col).AddObject(move(object));
}

void Map::InitMap( const int &rows, const int &cols )
{
    m_Rows = rows + 2;
    m_Cols = cols + 2;
    m_Map.resize((unsigned long) ( m_Rows ));
    for ( int i = 0; i < m_Rows; i++ ) {
        for ( int j = 0; j < m_Cols; ++j ) {
            m_Map.at(i).push_back(Point());
            if ( i == 0 || i == m_Rows - 1 || j == 0 || j == m_Cols - 1 ) {
                m_Map.at(i).at(m_Map[i].size() - 1).AddObject(Wall::MARK);
            }
        }
    }
}

int Map::Rows( void ) const
{
    return m_Rows;
}

int Map::Cols( void ) const
{
    return m_Cols;
}

char Map::Mark( const int &row, const int &col ) const
{
    return m_Map.at((unsigned long) row).at((unsigned long) col).Mark();
}

bool Map::MoveTo( pair<int, int> pos, pair<int, int> nextPos, const int &id /*= -1*/ )
{
    if ( !m_Map[nextPos.first][nextPos.second].IsMovable())
        return false;
    auto object = m_Map[pos.first][pos.second].RemoveObject(id);

    if ( m_Map[nextPos.first][nextPos.second].InExplosion()) {
        int power = 0;
        object->Destroy(power);
    }
    m_Map[nextPos.first][nextPos.second].AddObject(move(object));

    return true;
}

void Map::InitBombs( const unsigned long &playerCnt )
{
    m_PlantedBombs.resize(playerCnt);
    for ( int i = 0; i < (int) playerCnt; i++ ) {
        m_PlantedBombs[i] = 0;
    }
}

int Map::GetBombCnt( const int &playerID ) const
{
    return m_PlantedBombs[playerID];
}

void Map::AddPlayerBomb( const int &playerID )
{
    m_PlantedBombs[playerID]++;
}

void Map::Update( const int &timeDiff )
{
    int explosionPower = 0;

    for ( int i = 0; i < (int) m_Map.size(); ++i ) {
        for ( int j = 0; j < (int) m_Map[i].size(); ++j ) {
            explosionPower = m_Map[i][j].Update(timeDiff);
            if ( explosionPower > 0 ) {
                for ( int k = 0; k < 4; ++k ) {
                    Explode(explosionPower, i, j, k);
                }
                UpdateBombRangeMark(pair<int, int>(i, j), explosionPower, -1);
                m_Map[i][j].Destroy(explosionPower);
            }
        }
    }

}

void Map::Explode( const int &power, const int &row, const int &col, const int &direction )
{
    pair<int, int> pos(row, col);
    int            newPower = 0;
    int            tmp      = 0;

    switch ( direction ) {
        case DIRECTION_DOWN:
            pos.first++;
            break;
        case DIRECTION_RIGHT:
            pos.second++;
            break;
        case DIRECTION_UP:
            pos.first--;
            break;
        case DIRECTION_LEFT:
            pos.second--;
            break;
        default:
            throw InvalidObjectException();
    }

    //
    if ( !m_Map.at(pos.first).at(pos.second).Destroy(newPower)) {
        return; // Explosion cannot be propagate throught a static object.
    }

    if ( !m_Map[pos.first][pos.second].HasObject()) {
        m_Map[pos.first][pos.second].AddObject(unique_ptr<Object>(new Fire()));
    }

    if ( newPower > 0 ) { // The bomb has been hit.
        for ( int i = 0; i < 4; ++i ) {
            if ( direction == i ) {
                tmp = newPower > power ? newPower : power;
            } else {
                tmp = newPower;
            }
            Explode(tmp, pos.first, pos.second, i);
        }
        UpdateBombRangeMark(pos, newPower, -1);
    } else if ( power > 1 ) { // Propagate explosion to the next point.
        Explode(power - 1, pos.first, pos.second, direction);
    }
}

void Map::DeleteDestroyedItems( void )
{
    int playerID = -1;

    for ( int i = 0; i < (int) m_Map.size(); ++i ) {
        for ( int j = 0; j < (int) m_Map[i].size(); ++j ) {
            if ( m_Map[i][j].DeleteIfDestroyed(playerID) && playerID > -1 ) {
                m_PlantedBombs[playerID]--;
            }
        }
    }
}

bool Map::IsPlayerDead( const pair<int, int> &pos, const int &playerID ) const
{
    return m_Map.at(pos.first).at(pos.second).IsPlayerDead(playerID);
}

int Map::Color( const int &row, const int &col ) const
{
    return m_Map.at(row).at(col).Color();
}

bool Map::PickUp( const pair<int, int> &pos, int &power, int &bombCnt, bool &confusion )
{
    return m_Map.at(pos.first).at(pos.second).PickUp(power, bombCnt, confusion);
}

const std::vector<std::vector<Point>> &Map::GetMap( void ) const
{
    return m_Map;
}

void Map::UpdateBombRangeMarkDir( int row, int col, const int &power, const int &direction, const int &value )
{
    switch ( direction ) {
        case 0:
            row -= 1;
            break;
        case 1:
            row += 1;
            break;
        case 2:
            col -= 1;
            break;
        case 3:
            col += 1;
            break;
    }

    if ( !m_Map[row][col].CanPropagateExplosion()) {
        return;
    } else {
        m_Map[row][col].UpdateBombRangeMark(value);
        if ( power == 0 ) {
            return;
        }
        UpdateBombRangeMarkDir(row, col, power - 1, direction, value);
    }
}

void Map::UpdateBombRangeMark( const std::pair<int, int> &pos, const int &power, const int &value )
{
    for ( int j = 0; j < 4; ++j ) {
        UpdateBombRangeMarkDir(pos.first, pos.second, power - 1, j, value);
    }
}

