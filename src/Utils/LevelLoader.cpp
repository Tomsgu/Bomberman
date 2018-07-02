#include "LevelLoader.h"
using namespace std;
vector<string> LevelLoader::GetLevels( void ) const
{
    vector<string> levels;
    DIR           * dir;
    struct dirent * ent;

    if (( dir = opendir(m_Config.GetMapsDir().c_str())) != NULL ) {
        while (( ent = readdir(dir)) != NULL ) {
            if ( strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
                levels.push_back((string) ent->d_name);
            }
        }
        closedir(dir);
    } else {
        throw CannotOpenFileException();
    }

    return levels;
}


void LevelLoader::LoadLevel( string const &levelName, Game &game, const char &multiplayer ) const
{
    shared_ptr<Map> map     = game.GetMap();
    ifstream        file(( m_Config.GetMapsDir() + levelName ).c_str());
    string          line;
    int             lineCnt = 0;
    int             cols    = 0, rows = 0, playerCnt = 0;

    if ( file.fail()) {
        throw CannotOpenFileException();
    }

    while ( std::getline(file, line)) {
        if ( lineCnt == 0 ) {
            istringstream iss(line);
            iss >> rows;
            iss >> cols;
            map->InitMap(rows, cols);
            lineCnt++;
            continue;
        }

        for ( int i = 0; i < (int) line.size(); ++i ) {
            if ( line[i] == PlayerObject::MARK ) {
                if (!multiplayer && playerCnt == 0){
                    // The first player should be human. - singleplayer
                    game.AddPlayer(pair<int, int>(lineCnt, i + 1), true);
                } else {
                    game.AddPlayer(pair<int, int>(lineCnt, i + 1), multiplayer);
                }
                playerCnt++;
            }
            map->AddObject(line[i], lineCnt, i + 1, playerCnt - 1);
        }
        map->InitBombs(playerCnt);
        lineCnt++;
    }
}
