#include "Bomb.h"

const char Bomb::MARK;
const int  Bomb::SCORE;

Bomb::Bomb( const int &power,
            const std::pair<int, int> &position,
            const int &playerID ) : Object(MARK, 2, false, false, true)
{
    m_Exploded = false;
    m_Power    = power;
    m_PlayerID = playerID;
    m_Timer    = TIMEOUT;
}

int Bomb::Update( const int &timeDiff )
{
    m_Timer -= timeDiff;
    if ( m_Timer <= 0 ) {
        if ( !m_Exploded ) {
            m_Exploded = true;
            m_Timer    = TIMEOUT_AFTER_EXPLOSION;
            return m_Power; // Explode
        } else {
            m_Destroyed = true; // Explosion done.
        }
    }

    return 0;
}

bool Bomb::Destroy( int &power )
{
    if ( !m_Exploded ) {
        m_Exploded = true;
        m_Timer    = TIMEOUT_AFTER_EXPLOSION;
        power      = m_Power;
    }
    return true;
}

int Bomb::GetID( void ) const
{
    return m_PlayerID;
}

bool Bomb::InExplosion( void ) const
{
    return m_Exploded;
}

int Bomb::GetScore( void ) const
{
    return SCORE;
}

