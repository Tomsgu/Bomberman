#include "HumanPlayer.h"

HumanPlayer::HumanPlayer( const std::shared_ptr<Map> &map, const std::pair<int, int> &pos, const int &id, const int &up,
                          const int &down, const int &left, const int &right, const int &bomb ) : Player(map, pos, id)
{
    m_UpKey    = up;
    m_DownKey  = down;
    m_LeftKey  = left;
    m_RightKey = right;
    m_BombKey  = bomb;
}

bool HumanPlayer::DoMove( const int &pressedKey, const int &timeDiff )
{
    if ( IsDead()) {
        return false;
    }

    if ( pressedKey == m_UpKey ) {
        Move(DIRECTION_UP);
    } else if ( pressedKey == m_DownKey ) {
        Move(DIRECTION_DOWN);
    } else if ( pressedKey == m_LeftKey ) {
        Move(DIRECTION_LEFT);
    } else if ( pressedKey == m_RightKey ) {
        Move(DIRECTION_RIGHT);
    } else if ( pressedKey == m_BombKey ) {
        PlantBomb();
    } else {
        return false;
    }

    return true;
}

bool HumanPlayer::IsHuman( void ) const
{
    return true;
}
