#include "AiPlayer.h"

using namespace std;

AiPlayer::AiPlayer( const shared_ptr<Map> &map,
                    const pair<int, int> &pos,
                    const int &id ) : Player(map, pos, id)
{
    m_ScoreMap.resize((unsigned long) map->Rows());
    for ( int i = 0; i < map->Rows(); ++i ) {
        m_ScoreMap[i].resize((unsigned long) map->Cols());
    }
}

void AiPlayer::CalculatePointScore( const std::vector<std::vector<Point>> &map )
{
    vector<pair<int, int>> adj; //= GetAdjNodes(m_Position.first, m_Position.second);
    queue<pair<int, int>>  queue;
    pair<int, int>         pos;

    // Initialization
    for ( int i = 0; i < m_Map->Rows(); ++i ) {
        for ( int j = 0; j < m_Map->Cols(); ++j ) {
            m_ScoreMap.at(i).at(j).SetDefaults();
        }
    }

    queue.push(pair<int, int>(m_Position.first, m_Position.second));
    m_ScoreMap[m_Position.first][m_Position.second].m_State = m_ScoreMap[m_Position.first][m_Position.second].open;
    while ( !queue.empty()) {
        pos.first  = queue.front().first;
        pos.second = queue.front().second;
        adj = GetAdjNodes(pos.first, pos.second);

        // Calculate score
        for ( int i = 0; i < (int) adj.size(); ++i ) {
//            if ( m_Position.first != adj[i].first && m_Position.second != adj[i].second ) {
            m_ScoreMap[pos.first][pos.second].AddScores(map[adj[i].first][adj[i].second].GetScore());
//            }
        }

        for ( int i = 0; i < (int) adj.size(); ++i ) {
            if ( m_ScoreMap[adj[i].first][adj[i].second].m_State == m_ScoreMap[adj[i].first][adj[i].second].fresh &&
                 map[adj[i].first][adj[i].second].IsMovable() &&
                 !map[adj[i].first][adj[i].second].InExplosion() &&
                 ( !map[adj[i].first][adj[i].second].InBombRange() ||
                   map[m_Position.first][m_Position.second].InBombRange())
                    ) {
                m_ScoreMap[adj[i].first][adj[i].second].m_State               = m_ScoreMap[adj[i].first][adj[i].second].open;
                m_ScoreMap[adj[i].first][adj[i].second].m_PreviousNode.first  = pos.first;
                m_ScoreMap[adj[i].first][adj[i].second].m_PreviousNode.second = pos.second;
                queue.push(pair<int, int>(adj[i].first, adj[i].second));
            }
        }
        // Set updated scores to the previous point.
        UpdateScores(pos);

        queue.pop();
    }
}

bool AiPlayer::DoMove( const int &pressedKey, const int &timeDiff )
{
    const vector<vector<Point>> &map       = m_Map->GetMap();
    int                         foundScore = 0;
    pair<int, int>              nextMove(m_Position);

    if ( timeDiff < 200 || IsDead()) {
        return false;
    }

    CalculatePointScore(map);

    // Escape if is in bomb range.
    if ( map[m_Position.first][m_Position.second].InBombRange()) {
        if ( IsNear(map, m_Position, Point::SCORE)) { // Pick up the power up.
            vector<pair<int, int>> adj = GetAdjNodes(m_Position.first, m_Position.second);
            for ( int              i   = 0; i < (int) adj.size(); ++i ) {
                if ( map[adj[i].first][adj[i].second].HasScore(Point::SCORE)) {
                    Move(adj[i]);
                    return false;
                }
            }
        }
        if ( LookForScore(map, nextMove, Point::SCORE, foundScore)) {
            Move(nextMove);
            return false;
        }
    }

    if ( IsNear(map, m_Position, Booster::SCORE)) { // Pick up the power up.
        vector<pair<int, int>> adj = GetAdjNodes(m_Position.first, m_Position.second);
        for ( int              i   = 0; i < (int) adj.size(); ++i ) {
            if ( map[adj[i].first][adj[i].second].HasScore(Booster::SCORE)) {
                Move(adj[i]);
                return false;
            }
        }
    }
    if ( LookForScore(map, nextMove, Booster::SCORE, foundScore)) {
        if ( foundScore < 8 ) {
            Move(nextMove);
            return false;
        }
    }


    if ( m_AvailableBombs > 0 ) {//&& CanEscape(map)) {
        if ( LookForScore(map, nextMove, Box::SCORE, foundScore)) {
            if ( IsNear(map, m_Position, Box::SCORE)) {
                PlantBomb();
                return false;
            } else {
                Move(nextMove);
                return false;
            }
        }
        if ( LookForScore(map, nextMove, PlayerObject::SCORE, foundScore)) {
            if ( IsNear(map, m_Position, PlayerObject::SCORE)) {
                PlantBomb();
                return false;
            } else {
                Move(nextMove);
                return false;
            }
        }

    }

    return false;
}

bool
AiPlayer::LookForScore( const std::vector<std::vector<Point>> &map, std::pair<int, int> &nextMove,
                        const int &neededScore, int &foundScore )
{
    vector<pair<int, int>> pos   = GetAdjNodes(m_Position.first, m_Position.second);
    int                    score = 0;
    int                    adjScore;

    for ( int k = 0; k < (int) pos.size(); ++k ) {
        if ( map[pos[k].first][pos[k].second].IsMovable()) {
            adjScore = 0;
            for ( int i = 0; i < (int) m_ScoreMap[pos[k].first][pos[k].second].m_Score.size(); ++i ) {
                if ( m_ScoreMap[pos[k].first][pos[k].second].m_Score[i].first == neededScore ) {
                    adjScore = m_ScoreMap[pos[k].first][pos[k].second].m_Score[i].second;
                    break;
                }
            }

            if ( score == 0 || ( adjScore > 0 && adjScore < score )) {
                nextMove.first  = pos[k].first;
                nextMove.second = pos[k].second;
                score = adjScore;
            }
        }
    }

    foundScore = score;

    return score != 0;
}

std::vector<std::pair<int, int>> AiPlayer::GetAdjNodes( const int &row, const int &col ) const
{
    vector<pair<int, int>> adj     = {pair<int, int>(row - 1, col),
                                      pair<int, int>(row, col - 1),
                                      pair<int, int>(row + 1, col),
                                      pair<int, int>(row, col + 1)};
    vector<pair<int, int>> ret;
    int                    i       = 3;
    int                    randNum = 0;


    while ( i > 0 ) {
        randNum = rand() % i--;
        ret.push_back(adj[randNum]);
        adj.erase(adj.begin() + randNum);
    }
    ret.push_back(adj[0]);


    return ret;
}

void AiPlayer::UpdateScores( std::pair<int, int> pos )
{
    if ( pos.first == 0 && pos.second == 0 ) {
        return;
    }

    pair<int, int> prev = m_ScoreMap[pos.first][pos.second].m_PreviousNode;
    m_ScoreMap[prev.first][prev.second].UpdateScores(m_ScoreMap[pos.first][pos.second].m_Score);
    UpdateScores(prev);
}

bool AiPlayer::IsNear( const std::vector<std::vector<Point>> &map, std::pair<int, int> pos, const int &score ) const
{
    vector<pair<int, int>> adj = GetAdjNodes(pos.first, pos.second);

    for ( int i = 0; i < (int) adj.size(); ++i ) {
        if ( map[adj[i].first][adj[i].second].HasScore(score)) {
            return true;
        }
    }
    return false;
}
