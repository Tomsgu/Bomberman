#include "Object.h"

const int Object::SCORE;

Object::Object( const char &mark,
                const int &color,
                const bool &movable,
                const bool &mergeable,
                const bool &propagation
              ) : m_Mark(mark),
                  m_Color(color),
                  m_Movable(movable),
                  m_Mergeable(mergeable),
                  m_Destroyed(false),
                  m_Propagate(propagation)
{
}

char Object::Mark( void ) const
{
    return m_Mark;
}

bool Object::IsMovable( void ) const
{
    return m_Movable;
}

bool Object::IsMergeable( void ) const
{
    return m_Mergeable;
}

int Object::GetID( void ) const
{
    return -1;
}

bool Object::IsDestroyed( void ) const
{
    return m_Destroyed;
}

Object * Object::GetReplacement() const
{
    return nullptr;
}

Object::~Object()
{

}

int Object::Color( void ) const
{
    return m_Color;
}

bool Object::InExplosion( void ) const
{
    return false;
}

bool Object::PickUp( int &power, int &bombCnt, bool &confusion )
{
    return false;
}

bool Object::CanPropagateExplosion() const
{
    return m_Propagate;
}

int Object::GetScore( void ) const
{
    return SCORE;
}

