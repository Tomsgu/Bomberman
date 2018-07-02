#include "Box.h"
#include "Booster/AddBomb.h"
#include "Booster/IncreaseBombPower.h"
#include "Booster/Confuse.h"

const char Box::MARK;
const int  Box::SCORE;

Box::Box( void ) : Object(MARK, 8, false, false, false)
{
    m_Timer = TIMEOUT + 1;
}

int Box::Update( const int &timeDiff )
{
    if ( InFire()) { // It was hit by bomb.
        m_Timer -= timeDiff;
        if ( m_Timer <= 0 ) { // It is destroyed
            m_Destroyed = true;
        }
    }

    return 0;
}

bool Box::Destroy( int &power )
{
    m_Timer = TIMEOUT;
//    m_FiredAt = time;
    power   = 0;
    return false;
}

Object * Box::GetReplacement() const
{
    if (( rand() % 101 ) < 40 ) {
        switch ( rand() % 6 ) {
            case 1:
            case 2:
                return new AddBomb();
            case 3:
            case 4:
                return new IncreaseBombPower();
            case 5:
                return new Confuse();
        }
    }

    return nullptr;
}

int Box::Color( void ) const
{
    if ( InFire()) {
        return 2;
    } else {
        return m_Color;
    }
}

bool Box::InFire( void ) const
{
    return m_Timer <= TIMEOUT; // m_Timer is TIMEOUT+1 when the box wasn't hit.
}

int Box::GetScore( void ) const
{
    return SCORE;
}
