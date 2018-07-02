#include "Wall.h"

const char Wall::MARK;

Wall::Wall( void ) : Object(MARK, 64, false, false, false)
{
    m_Movable = false;
}


int Wall::Update( const int &timeDiff )
{
    return 0;
}

bool Wall::Destroy( int &power )
{
    power = 0;
    return false;
}

