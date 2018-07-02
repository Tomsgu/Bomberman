#ifndef BOMBERMAN_AIPLAYERSCORE_H
#define BOMBERMAN_AIPLAYERSCORE_H
#include <iostream>
#include <vector>

/**
 * This type is used for the ai player movement calculation when using BFS.
 */
struct TScorePoint
{
    enum State
    {
        fresh, open
    };
    State                             m_State; //!< \brief The state of the node.
    std::pair<int, int>               m_PreviousNode;//!< \brief The previous node.
    std::vector <std::pair<int, int>> m_Score;//!< \brief The score of the node.

    void SetDefaults( void )
    {
        m_PreviousNode.first  = 0;
        m_PreviousNode.second = 0;
        if ( m_Score.size() > 0 ) {
            m_Score.clear();
        }
        m_State = fresh;
    }

    void UpdateScores( std::vector <std::pair<int, int>> scores )
    {
        for ( int i = 0; i < (int) scores.size(); ++i ) {
            if ( scores[i].second > 0 ) {
                scores[i].second += 1;
            }
        }
        AddScores(scores);
    }

    void AddScores( std::vector <std::pair<int, int>> scores )
    {
        for ( int i = 0; i < (int) scores.size(); ++i ) {
            bool      found = false;
            for ( int k     = 0; k < (int) m_Score.size(); ++k ) {
                if ( m_Score[k].first == scores[i].first ) {
                    found = true;
                    if ( m_Score[k].second > 0 ) {
                        if ( scores[i].second > 0 && scores[i].second < m_Score[k].second ) {
                            m_Score[k].second = scores[i].second;
                        }
                    } else {
                        m_Score[k].second = scores[i].second;
                    }
                    break;
                }
            }
            if ( !found ) {
                m_Score.push_back(std::pair<int, int>(scores[i].first, scores[i].second));
            }
        }
    }
};

#endif //BOMBERMAN_AIPLAYERSCORE_H
