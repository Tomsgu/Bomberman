//
// Created by tomsgu on 5/19/17.
//

#ifndef BOMBERMAN_HIGHSCORESMANAGER_H
#define BOMBERMAN_HIGHSCORESMANAGER_H

#include <vector>
#include <fstream>
#include <sstream>
#include "../Configuration.h"

/**
 * \brief The class responsible for managing the highscores.
 */
class HighScoresManager
{
    public:
        /**
         * \brief Get highscores from the file specified in the config class.
         * @return Highscores
         */
        std::vector<std::pair<std::string, int>> GetHighScores(const std::string &level) const;

        void SaveHighScore(const int &score, const int &mode, const std::string &nickname, const std::string &level);
    private:
        Configuration m_Config;
};

#endif //BOMBERMAN_HIGHSCORESMANAGER_H
