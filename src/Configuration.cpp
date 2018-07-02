#include "Configuration.h"

int Configuration::GetUiChoice( void ) const
{
    return m_UiChoice;
}

std::string Configuration::GetHighScoresFilename( void ) const
{
    return HIGH_SCORES_FILENAME;
}

std::string Configuration::GetMapsDir( void ) const
{
    return MAPS_DIR;
}
