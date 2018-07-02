#ifndef BOMBERMAN_NCURSESUI_H
#define BOMBERMAN_NCURSESUI_H

#include <memory>
#include <ncurses.h>
#include <cursesw.h>
#include "GraphicUI.h"
#include "WindowNcurses.h"

/**
 * \brief The ncurses user interface.
 */
class NcursesUI : public GraphicUI
{
    public:
        NcursesUI( void );
        ~NcursesUI( void );
        virtual int MenuDialog( const std::vector<std::string> &menuItems, const std::string &title );
        virtual void ShowHighScores( const std::vector<std::pair<std::string, int>> &highScores );
        virtual void CreateGameWindow( const int &lines, const int &cols );
        virtual void RefreshMap( std::shared_ptr<Map> map );
        virtual void RenderResult( const int &result, const int &playerID );
        virtual void GetNickname( std::string &nickname );
        virtual bool PauseGame( void );
    private:
        WindowNcurses m_GameWindow;
};

#endif //BOMBERMAN_NCURSESUI_H
