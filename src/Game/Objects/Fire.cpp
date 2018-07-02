#include "Fire.h"

const char Fire::MARK;
const int Fire::SCORE;

Fire::Fire( void ) : Object(MARK, 2, true, false, true)
{
    m_Timer   = TIMEOUT;
}

int Fire::Update( const int &timeDiff )
{
    m_Timer -= timeDiff;
    if ( m_Timer <= 0 ) {
        m_Destroyed = true;
    }

    return 0;
}

bool Fire::Destroy( int &power )
{
    power = 0;
    return true;
}

bool Fire::InExplosion( void ) const
{
    return true;
}

int Fire::GetScore( void ) const
{
    return SCORE;
}
