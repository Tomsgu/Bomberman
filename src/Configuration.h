#ifndef BOMBERMAN_CONFIGURATION_H
#define BOMBERMAN_CONFIGURATION_H

#include <iostream>

class Configuration
{
    public:
        std::string GetHighScoresFilename( void ) const;
        std::string GetMapsDir( void ) const;

        static const int UI_NCURSES  = 1;
        static const int UI_TERMINAL = 2;

        int GetUiChoice( void ) const;
    private:
        const std::string HIGH_SCORES_FILENAME = "./examples/HighScores";
        const std::string MAPS_DIR = "./examples/maps/";
        int               m_UiChoice = UI_NCURSES;
};

#endif //BOMBERMAN_CONFIGURATION_H
