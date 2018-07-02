#include "PlayerObject.h"

const char PlayerObject::MARK;
const int  PlayerObject::SCORE;

PlayerObject::PlayerObject( const int &id ) : Object(MARK, 8, true, true, true)
{
    m_ID    = id;
    m_Color = id + 4;
}

int PlayerObject::GetID( void ) const
{
    return m_ID;
}

int PlayerObject::Update( const int &timeDiff )
{
    return 0;
}

bool PlayerObject::Destroy( int &power )
{
    m_Destroyed = true;
    power       = 0;
    m_Mark      = ' ';
    return true;
}

int PlayerObject::GetScore( void ) const
{
    return SCORE;
}
