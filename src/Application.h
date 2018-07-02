//
// Created by tomsgu on 5/19/17.
//

#ifndef BOMBERMAN_APPLICATION_H
#define BOMBERMAN_APPLICATION_H
#include <cstdlib>
#include <ctime>
#include <memory>
#include "Exceptions/InvalidConfigurationException.h"
#include "Exceptions/InvalidArgumentException.h"
#include "Utils/LevelLoader.h"
#include "Utils/HighScoresManager.h"
#include "Graphics/GraphicUI.h"
#include "Graphics/NcursesUI.h"
#include "Configuration.h"

/**
 * \brief This class is responsible for displaying menu and run the game.
 */
class Application
{
    public:
        Application( void );
        /**
         * \brief Runs the app.
         */
        void Run( void );

        /**
         * \brief Write score to the file.
         */
        void WriteScore( const int &score, const int &mode, const int &playerID, const int &levelChoice );

    private:
        std::shared_ptr<GraphicUI> m_Ui;
        HighScoresManager          m_HighScoresManager;
        std::vector<std::string>   m_MenuItems;
        std::vector<std::string>   m_Levels;
        Configuration              m_Config;
        LevelLoader                m_LevelLoader;

        static const int MENU_PLAY_SINGLEPLAYER = 0;
        static const int MENU_PLAY_MULTIPLAYER  = 1;
        static const int MENU_HIGHSCORES        = 2;
        static const int MENU_QUIT              = 3;
};

#endif //BOMBERMAN_APPLICATION_H
