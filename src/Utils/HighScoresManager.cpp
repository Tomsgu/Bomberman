#include <vector>
#include <fstream>
#include <sstream>

#include "HighScoresManager.h"

using namespace std;

vector<pair<string, int>> HighScoresManager::GetHighScores( const std::string &level ) const
{
    vector<pair<string, int>> highScores;
    string                    filename = m_Config.GetHighScoresFilename() + level;
    ifstream                  file(filename.c_str());
    string                    line;

    if ( file.fail()) {
        highScores.push_back(pair<string, int>("There is no record.", 0));
        return highScores;
        //TODO: Exception.
//        cerr << "Problem to open the file" << endl;
//        cout << m_Config.GetHighScoresFilename().c_str() << endl;
    }

    while ( std::getline(file, line)) {
        istringstream     iss(line);
        pair<string, int> score;
        // TODO: Exception when the file fail.
        // TODO: Exception when the file has bad format.
        iss >> score.second;
        iss >> score.first;
        highScores.push_back(score);
    }
    file.close();

    return highScores;
}

void HighScoresManager::SaveHighScore( const int &newScore, const int &mode, const std::string &nickname,
                                       const std::string &level )
{
    vector<pair<string, int>> scores;
    string                    filename = m_Config.GetHighScoresFilename() + level;
    ifstream                  infile(filename.c_str());
    ofstream                  outfile;
    string                    line;
    bool                      inserted = false;

    while ( std::getline(infile, line)) {
        istringstream     iss(line);
        pair<string, int> score;
        // TODO: Exception when the file fail.
        // TODO: Exception when the file has bad format.
        iss >> score.second;
        iss >> score.first;
        if ( score.second > newScore && !inserted ) {
            scores.push_back(pair<string, int>(nickname, newScore));
            inserted = true;
        }
        scores.push_back(score);
    }
    if ( !inserted ){
        scores.push_back(pair<string, int>(nickname, newScore));
    }
    infile.close();
    outfile.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);

    for ( int i = 0; i < (int)scores.size(); ++i ) {
        outfile <<  scores[i].second << " " << scores[i].first << '\n';
    }
}

