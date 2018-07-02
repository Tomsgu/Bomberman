#ifndef BOMBERMAN_POINT_H
#define BOMBERMAN_POINT_H

#include <iostream>
#include <memory>
#include <vector>
#include "Objects/Bomb.h"
#include "Objects/Wall.h"
#include "Objects/Box.h"
#include "Objects/PlayerObject.h"
#include "../Exceptions/InvalidObjectException.h"
#include "../Exceptions/ObjectAlreadyExistsException.h"
#include "../Exceptions/InvalidArgumentException.h"

/**
 * \brief The point of the map.
 *
 * Can consists of one or more game objects.
 */
class Point
{
    public:
        static const char GROUND = '_';

        static const int SCORE = 1;

        Point( void );
        Point( const char &symbol, const int &id );
        /**
         * \brief Add an object represented by character.
         * @param object The character representation of the object.
         * @param playerID Id of the player to whom the object belongs to.
         */
        void AddObject( const char &object, const int &playerID = 0 );
        /**
         * \brief Add the given object to the point.
         * @param object The object.
         */
        void AddObject( std::unique_ptr<Object> object );
        /**
         * \brief Remove the object.
         * @param id  Id of a player to whom the object belongs to.
         * @return The removed object.
         */
        std::unique_ptr<Object> RemoveObject( const int &id = -1 );
        /**
         * \brief Return the mark of the object.
         * @return The character representation of the object.
         */
        char Mark( void ) const;
        /**
         * \brief Decide if a moving object can enter to this point.
         * @return true if the moving object can enter to this point, false otherwise.
         */
        bool IsMovable( void ) const;
        /**
         * \brief Get information if some object is in this point.
         * @return true if the object is in this point, false otherwise.
         */
        bool HasObject( void ) const;
        /**
         * \brief Delete an object if it's destroyed.
         * @param playerID Id of the player to whom the destroyed object belongs to.
         * @return true if the object was successfully deleted false otherwise (there were no object)
         */
        bool DeleteIfDestroyed( int &playerID );
        /**
         * \brief Get the information about a player(alive, dead)
         * @param playerID The id of the player.
         * @return true if the player is dead, false otherwise.
         */
        bool IsPlayerDead( const int &playerID ) const;
        /**
         * \brief Get a color of the object.
         * @return The color of the object.
         */
        int Color( void ) const;
        /**
         * \brief Get the information about explosion on this point.
         * @return true if the point is in explosion, false otherwise.
         */
        bool InExplosion( void ) const;
        /**
         * \brief Pick up the object that can affect a player who has picked it up.
         * @param power The bomb power of the player.
         * @param bombCnt The bomb counter of the player.
         * @param confusion The indication if the player is confused,
         * @return true if the player picked up something, false if not.
         */
        bool PickUp( int &power, int &bombCnt, bool &confusion );

        /**
         * \brief Update objects in this point.
         * @return The bomb power.(If the bomb has exploded.)
         */
        int Update( const int &timeDiff );
        /**
         * \brief Destroy objects on this point. Mostly if the bomb hits it with the fire.
         * @param power The power of the bomb exploded in this point.
         * @return true if the fire can go through this point.
         */
        bool Destroy( int &power );

        /**
         * \brief Update mark indicates that the bomb is going to explode on this point.
         */
        void UpdateBombRangeMark ( const int & value );

        /**
         * \brief Is the point in bomb range.
         * @return  true if it is, false otherwise
         */
        bool InBombRange ( void ) const;

        /**
         * \brief Can the object propagate explosion behind it.
         * @return true if can propagate, false otherwise
         */
        bool CanPropagateExplosion() const;

        bool HasScore(const int &score) const;

        /**
         * \brief Get score for the ai player
         * @return .
         */
        std::vector<std::pair<int, int>> GetScore (void) const;
    protected:
        std::vector<std::unique_ptr<Object>> m_MergeableObjects; //!< Brief Objects that can be altogether in the same point
        std::unique_ptr<Object>         m_Object; //!< Brief The game object.
        char                       m_Mark; //!< Mark of the game object. (for displaying on the map)
        int                        m_bombMarks; //!< How many bombs are going to explode here.
};

#endif //BOMBERMAN_POINT_H
