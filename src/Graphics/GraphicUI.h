#ifndef BOMBERMAN_GRAPHICUI_H
#define BOMBERMAN_GRAPHICUI_H

#include <iostream>
#include <vector>
#include "../Game/Map.h"

/**
 * \brief The interface for the graphic UI.
 */
class GraphicUI
{
    public:
        /**
         * \brief Creates the game window.
         */
        virtual void CreateGameWindow( const int &lines, const int &cols ) = 0;
        /**
         * \brief Display highscores.
         */
        virtual void ShowHighScores( const std::vector<std::pair<std::string, int>> &highScores ) = 0;
        /**
         * \bried Refresh the map window.
         */
        virtual void RefreshMap( std::shared_ptr<Map> map ) = 0;
        /**
         * \brief Display the menu and return the choice.
         */
        virtual int MenuDialog( const std::vector<std::string> &menuItems, const std::string &title ) = 0;
        /**
         * \brief Render score of the player.
         */
        virtual void RenderResult( const int &result, const int &playerID ) = 0;
        /**
         * \brief Get nickname from the winner.
         */
        virtual void GetNickname(std::string &nickname) = 0;
        /**
         * \brief Pauses the game.
         * @return true if player hits escape again, false otherwise.
         */
        virtual bool PauseGame(void) = 0;
};

#endif //BOMBERMAN_GRAPHICUI_H
