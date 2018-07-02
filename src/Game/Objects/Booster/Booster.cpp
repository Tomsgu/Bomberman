#include "Booster.h"

const int Booster::SCORE;

Booster::Booster( void ) : Object('*', 3, true, false, false)
{}

int Booster::Update( const int &timeDiff )
{
    return 0;
}

bool Booster::Destroy( int &power )
{
    m_Destroyed = true;

    return false;
}

bool Booster::PickUp( int &power, int &bombCnt, bool &confusion )
{
    AddBooster(power, bombCnt, confusion);
    m_Destroyed = true;

    return true;
}

int Booster::GetScore( void ) const
{
    return SCORE;
}

