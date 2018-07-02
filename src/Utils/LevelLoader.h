#ifndef BOMBERMAN_LEVELLOADER_H
#define BOMBERMAN_LEVELLOADER_H

#include <fstream>
#include <sstream>
#include <dirent.h>
#include <cstring>
#include "../Exceptions/CannotOpenFileException.h"
#include "../Game/Game.h"
#include "../Configuration.h"


/**
 * \brief Responsible for loading levels from the file.
 */
class LevelLoader
{
    public:
        /**
         * \brief Returns all levels found in level folder(specified in configuration file).
         */
        std::vector<std::string> GetLevels( void ) const;
        /**
         * \brief Load the level from file.
         */
        void LoadLevel( std::string const &levelName, Game &game, const char &multiplayer ) const;
    private:
        Configuration m_Config;
};

#endif //BOMBERMAN_LEVELLOADER_H
