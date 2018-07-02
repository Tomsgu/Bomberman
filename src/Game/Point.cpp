#include "Point.h"

using namespace std;
const int Point::SCORE;

Point::Point()
{
    m_Object    = nullptr;
    m_Mark      = ' ';
    m_bombMarks = 0;
}

void Point::AddObject( const char &symbol, const int &playerID /*= 0*/ )
{
    switch ( symbol ) {
        case Wall::MARK:
            AddObject(unique_ptr<Object>(new Wall()));
            break;
        case Box::MARK:
            AddObject(unique_ptr<Object>(new Box()));
            break;
        case PlayerObject::MARK:
            AddObject(unique_ptr<Object>(new PlayerObject(playerID)));
        case GROUND:
            break;
        default:
            throw InvalidObjectException();
    }
}


char Point::Mark( void ) const
{
    if ( m_Object == nullptr ) {
        if ( m_MergeableObjects.empty()) {

//            return to_string(m_bombMarks).c_str()[0];
            return m_Mark;
        } else {
            return m_MergeableObjects.back()->Mark();
        }
    }
    return m_Object->Mark();
}

void Point::AddObject( unique_ptr<Object> object )
{
    if ( m_Object != nullptr && !m_Object->IsMovable()) {
        throw ObjectAlreadyExistsException();
    }

    if ( object->IsMergeable()) {
        m_MergeableObjects.push_back(move(object));
    } else {
        m_Object = move(object);
    }
}

unique_ptr<Object> Point::RemoveObject( const int &id /* = -1*/ )
{
    if ( id == -1 ) {
        auto object = move(m_Object);
        return object;
    } else {
        for ( unsigned int i = 0; i < m_MergeableObjects.size(); ++i ) {
            if ( m_MergeableObjects[i]->GetID() == id ) {
                auto object = move(m_MergeableObjects[i]);
                m_MergeableObjects.erase(m_MergeableObjects.begin() + i);
                return object;
            }
        }
    }

    throw InvalidArgumentException();
}

bool Point::IsMovable( void ) const
{
    if ( m_Object == nullptr ) {
        return true;
    }
    return m_Object->IsMovable();
}

Point::Point( const char &symbol, const int &id )
{
    AddObject(symbol, id);
}

int Point::Update( const int &timeDiff )
{
    int power;
    if ( m_Object == nullptr ) {
        return 0;
    }
    power = m_Object->Update(timeDiff);

    return power;
}

bool Point::Destroy( int &power )
{
    power = 0;
    for ( int i = 0; i < (int) m_MergeableObjects.size(); ++i ) {
        m_MergeableObjects[i]->Destroy(power);
    }
    if ( m_Object == nullptr ) {
        return true;
    }
    return m_Object->Destroy(power);
}

bool Point::HasObject( void ) const
{
    if ( m_Object == nullptr && m_MergeableObjects.empty()) {
        return false;
    } else {
        return true;
    }
}

bool Point::DeleteIfDestroyed( int &playerID )
{
    if ( m_Object != nullptr && m_Object->IsDestroyed()) {
        playerID = m_Object->GetID();
        unique_ptr<Object> replacement(m_Object->GetReplacement());
        delete m_Object.release();
        if ( replacement != nullptr ) {
            AddObject(move(replacement));
        }
        return true;
    }

    return false;
}

bool Point::IsPlayerDead( const int &playerID ) const
{
    for ( int i = 0; i < (int) m_MergeableObjects.size(); ++i ) {
        if ( m_MergeableObjects[i]->GetID() == playerID ) {
            return m_MergeableObjects[i]->IsDestroyed();
        }
    }
    return false;
}

int Point::Color( void ) const
{
    if ( !m_MergeableObjects.empty()) {
        return m_MergeableObjects.at(0)->Color();
    }
    if ( m_Object == nullptr ) {
        return 8;
    } else {
        return m_Object->Color();
    }
}

bool Point::InExplosion() const
{
    if ( m_Object != nullptr && m_Object->InExplosion()) {
        return true;
    }
    for ( int i = 0; i < (int) m_MergeableObjects.size(); ++i ) {
        if ( m_MergeableObjects[i]->InExplosion()) {
            return true;
        }
    }
    return false;
}

bool Point::PickUp( int &power, int &bombCnt, bool &confusion )
{
    if ( m_Object != nullptr ) {
        return m_Object->PickUp(power, bombCnt, confusion);
    }

    return false;
}

void Point::UpdateBombRangeMark( const int &value )
{
    m_bombMarks += value;
    if (m_bombMarks < 0 ) m_bombMarks = 0;
}

bool Point::InBombRange( void ) const
{
    return m_bombMarks > 0 || (m_Object != nullptr && m_Object->Mark() == Bomb::MARK);
}

bool Point::CanPropagateExplosion() const
{
    if ( m_Object == nullptr ) {
        return true;
    }
    return m_Object->CanPropagateExplosion();
}

vector<pair<int,int>> Point::GetScore( void ) const
{
    vector<pair<int, int>> scores;

    if ( !InBombRange() && m_Object == nullptr){
        scores.push_back(pair<int, int>(Point::SCORE, 1));
    }
    for ( int j = 0; j < (int)m_MergeableObjects.size(); ++j ) {
        scores.push_back(pair<int, int>(m_MergeableObjects[j]->GetScore(), 1));
    }

    if ( m_Object != nullptr && m_Object->GetScore() != 0){
        scores.push_back(pair<int, int>(m_Object->GetScore(), 1));
    }

    return scores;
}

bool Point::HasScore( const int &score ) const
{
    if ( !InBombRange() && m_Object == nullptr){
        if ( score == Point::SCORE) return true;
    }
    for ( int j = 0; j < (int)m_MergeableObjects.size(); ++j ) {
        if ( score == m_MergeableObjects[j]->GetScore()) return true;
    }

    if ( m_Object != nullptr && m_Object->GetScore() != 0){
        if ( score == m_Object->GetScore()) return true;
    }

    return false;
}
