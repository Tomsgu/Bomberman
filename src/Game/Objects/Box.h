#ifndef BOMBERMAN_CBOX_H
#define BOMBERMAN_CBOX_H

#include "Object.h"

/**
 * \brief The game object representing a box.
 *
 * After the bomb hits this box, the box is destroyed
 * and the secret(booster) can appear on the map in the same position.
 */
class Box : public Object
{
    public:
        static const char MARK  = '+';
        static const int  SCORE = 10;

        Box( void );
        virtual int Update( const int &timeDiff );
        virtual bool Destroy( int &power );
        /**
         * \brief Get replacement in case there is a power up inside.
         * @return The booster object
         */
        virtual Object * GetReplacement() const;
        virtual int Color( void ) const;
        virtual int GetScore( void ) const;
    private:
        static const int TIMEOUT = 1000;
        int              m_Timer;

        /**
         * \brief Is the box in fire?
         * @return true if it is, false if not
         */
        bool InFire( void ) const;
};

#endif //BOMBERMAN_CBOX_H
