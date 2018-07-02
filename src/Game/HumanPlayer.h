#ifndef BOMBERMAN_HUMANPLAYER_H
#define BOMBERMAN_HUMANPLAYER_H


#include "Player.h"

class HumanPlayer : public Player
{
    public:
        HumanPlayer( const std::shared_ptr<Map> &map, const std::pair<int, int> &pos, const int &id,
                     const int &up, const int &down, const int &left, const int &right, const int &bomb );

        virtual bool DoMove( const int &pressedKey, const int &timeDiff );
        virtual bool IsHuman( void ) const;
    private:
        int m_UpKey;
        int m_DownKey;
        int m_LeftKey;
        int m_RightKey;
        int m_BombKey;
};


#endif //BOMBERMAN_HUMANPLAYER_H
