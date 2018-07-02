#include "Player.h"

using namespace std;

const int Player::DIRECTION_LEFT;
const int Player::DIRECTION_DOWN;
const int Player::DIRECTION_UP;
const int Player::DIRECTION_RIGHT;

Player::Player( shared_ptr<Map> map,
                const pair<int, int> &pos,
                const int &id
              ) : m_Map(map),
                  m_BombPower(1),
                  m_AvailableBombs(1),
                  m_Confusion(false),
                  m_ID(id),
                  m_Cursed(TIMEOUT_CURSE)
{
    m_Position.first  = pos.first;
    m_Position.second = pos.second;
}

bool Player::Move( const std::pair<int, int> position )
{
    if ( m_Position.first < position.first ){
        return Move(DIRECTION_DOWN);
    }else if(m_Position.first > position.first){
        return Move(DIRECTION_UP);
    }else if( m_Position.second < position.second){
        return Move(DIRECTION_RIGHT);
    }else{
        return Move(DIRECTION_LEFT);
    }
}

bool Player::Move( const int &direction )
{
    pair<int, int> coors     = m_Position;
    bool           confusion = false;

    switch ( GetDirection(direction)) {
        case DIRECTION_LEFT:
            coors.second = m_Position.second - 1;
            break;
        case DIRECTION_RIGHT:
            coors.second = m_Position.second + 1;
            break;
        case DIRECTION_UP:
            coors.first = m_Position.first - 1;
            break;
        case DIRECTION_DOWN:
            coors.first = m_Position.first + 1;
            break;
        default:
            throw InvalidArgumentException();
    }
    if ( m_Map->MoveTo(m_Position, coors, m_ID)) {
        m_Position.first  = coors.first;
        m_Position.second = coors.second;
    }


    m_Map->PickUp(m_Position, m_BombPower, m_AvailableBombs, confusion);
    if ( confusion ) { // Player picked up a confusion. If he picked up again prolong his time.
        m_Confusion = true;
        m_Cursed    = TIMEOUT_CURSE;
    }

    return false;
}

bool Player::PlantBomb( void )
{
    if (( m_AvailableBombs - m_Map->GetBombCnt(m_ID)) > 0 ) {
        try {
            m_Map->AddObject(unique_ptr<Object>(new Bomb(m_BombPower, m_Position, m_ID)), m_Position.first,
                             m_Position.second);
            m_Map->AddPlayerBomb(m_ID);
            m_Map->UpdateBombRangeMark(m_Position, m_BombPower, 1);
        } catch ( ObjectAlreadyExistsException exc ) {
            return false; // The bomb is already there.
        }
        return true;
    } else {
        return false;
    }
}

bool Player::IsDead( void ) const
{
    return m_Map->IsPlayerDead(m_Position, m_ID);
}

int Player::GetDirection( const int &direction ) const
{
    if ( !m_Confusion || !IsHuman() ) {
        return direction;
    }
    switch ( direction ) {
        case DIRECTION_LEFT:
            return DIRECTION_RIGHT;
        case DIRECTION_RIGHT:
            return DIRECTION_LEFT;
        case DIRECTION_UP:
        case DIRECTION_DOWN:
            return direction;
        default:
            throw InvalidArgumentException();
    }
}

void Player::Update( const int &timeDiff )
{
    if ( m_Confusion ) {
        m_Cursed -= timeDiff;
        if ( m_Cursed <= 1 ) {
            m_Confusion = false;
        }
    }

}

int Player::GetId( void ) const
{
    return m_ID;
}

bool Player::IsHuman( void ) const
{
    return false;
}


