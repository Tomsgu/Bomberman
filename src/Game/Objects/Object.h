//Box.o Wall.o
// Created by tomsgu on 5/13/17.
//

#ifndef BOMBERMAN_COBJECT_H
#define BOMBERMAN_COBJECT_H

#include <iostream>

/**
 * \brief The abstract class representing a game object.
 */
class Object
{
    public:
        static const int SCORE = 35;

        Object( const char &mark,
                const int &color,
                const bool &movable,
                const bool &mergeable,
                const bool &propagation
              );
        virtual ~Object();
        /**
         * \brief Return the mark of the object.
         * @return The character representation of the object.
         */
        virtual char Mark( void ) const;
        /**
         * \brief Decide if a moving object can enter to this point.
         * @return true if the moving object can enter to this point, false otherwise.
         */
        virtual bool IsMovable( void ) const;
        /**
         * \brief Decide if the object can be put to the point as well as another mergeable object.
         * @return true if it's mergeable, false if not.
         */
        virtual bool IsMergeable( void ) const;
        /**
         * \brief Gets if the object is destroyed.
         * @return true if the object is destroyed, false if not.
         */
        virtual bool IsDestroyed( void ) const;
        /**
         * \brief Get the id of the player to whom the object belongs to.
         * @return The id of player.
         */
        virtual int GetID( void ) const;
        /**
         * \brief Destroy this object. Mostly if the bomb hits it with the fire.
         * @param power The bomb power if this object is bomb.
         * @return true if the fire can go through this object.
         */
        virtual bool Destroy( int &power ) = 0;
        /**
         * \brief Update this object.
         * @return The bomb power if this object is a bomb.
         */
        virtual int Update( const int &timeDiff ) = 0;
        /**
         * \brief Get replacement of this object. (Used especially if there is a booster behind some object.
         * @return The replacement of this object.
         */
        virtual Object * GetReplacement() const;
        /**
         * \brief The color of this object.
         * @return  The color of this object.
         */
        virtual int Color( void ) const;
        /**
         * \brief Get the information about explosion in this object.
         * @return true if the object is exploading, false if not.
         */
        virtual bool InExplosion( void ) const;

        /**
         * \brief Pick up the object that can affect a player who has picked it up.
         * @param power The bomb power of the player.
         * @param bombCnt The bomb counter of the player.
         * @param confusion The indication if the player is confused.
         * @return true if the player picked up something, false if not.
         */
        virtual bool PickUp( int &power, int &bombCnt, bool &confusion );

        /**
         * \brief Can the object propagate explosion behind it.
         * @return true if can propagate, false otherwise
         */
        bool CanPropagateExplosion() const;

        /**
         * \brief Score is usefull when the ai wants to calculate his movements.
         * @return The score of this object.
         */
        virtual int GetScore( void ) const;

    protected:
        char m_Mark; //!< \brief The map mark.
        int  m_Color; //!< \brief The color of this object.
        bool m_Movable; //!< \brief Indicates if the player can move through this object.
        bool m_Mergeable; //!< \brief Indicates if the object can live with another object on the same point.
        bool m_Destroyed; //!< \brief Indicates if the object has been destroyed.
        bool m_Propagate; //!< \brief Can the object propagate explosion behind it.

};


#endif //BOMBERMAN_COBJECT_H
