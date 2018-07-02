#include "Game.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"

using namespace std;

Game::Game( shared_ptr<GraphicUI> ui )
{
    m_Ui  = ui;
    m_Map = make_shared<Map>();
}

shared_ptr<Map> Game::GetMap( void ) const
{
    return m_Map;
}

void Game::AddPlayer( pair<int, int> position, const bool &isHuman )
{
    int playerCnt = (int) m_Players.size();

    if ( isHuman ) {
        if ( playerCnt == 0 ) {
            m_Players.push_back(unique_ptr<Player>(
                    new HumanPlayer(m_Map, position, playerCnt, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, ' ')));
        } else if ( playerCnt == 1 ) {
            m_Players.push_back(
                    unique_ptr<Player>(new HumanPlayer(m_Map, position, playerCnt, 'w', 's', 'a', 'd', '`')));
        } else {
            // At the moment multiplayer is only for 2 players so add an AI instead of.
            m_Players.push_back(unique_ptr<Player>(new AiPlayer(m_Map, position, playerCnt)));
        }
    } else {
        m_Players.push_back(unique_ptr<Player>(new AiPlayer(m_Map, position, playerCnt)));
    }
}

int Game::Play( int & playerID )
{
    clock_t time;
    double  res           = 1000.0 / CLOCKS_PER_SEC; // calculate clock resolution of a platform
    int     lastUpdate    = 0;
    int     timeDiff      = 0;
    int     aiPlayerTimer = 0;
    int     startTime;
    int     pressedKey;
    playerID = -1;

    m_Ui->CreateGameWindow(m_Map->Rows(), m_Map->Cols());
    startTime = (int) clock();
    while ( true ) {
        time     = clock();
        timeDiff = (int) ( time * res ) - lastUpdate;

        pressedKey = wgetch(stdscr);
        if ( pressedKey == 27) { // Escape key
            if ( m_Ui->PauseGame() ){
                return 0;
            }
        }
        DoMove(pressedKey, aiPlayerTimer);

        if ( aiPlayerTimer > 200 ) {
            aiPlayerTimer = 0;
        }

        if ( timeDiff > 16 ) { // It's 1/60 of a second more or less
            m_Map->Update(timeDiff);
            m_Map->DeleteDestroyedItems();
            if ( UpdatePlayers(timeDiff)) {
                break;
            }
            m_Ui->RefreshMap(m_Map);
            lastUpdate = (int) ( clock() * res );
            aiPlayerTimer += timeDiff;
        }
    }

    startTime = (int) (( clock() - startTime ) * res );
    sleep(3);
    for ( int i = 0; i < (int) m_Players.size(); ++i ) {
        if ( !m_Players[i]->IsDead() && m_Players[i]->IsHuman() ){
            playerID = m_Players[i]->GetId();
            break;
        }
    }
    m_Ui->RenderResult(startTime, playerID);

    return startTime;
}

void Game::DoMove( const int &pressedKey, const int &timeDiff )
{
    for ( int i = 0; i < (int) m_Players.size(); ++i ) {
        m_Players[i]->DoMove(pressedKey, timeDiff);
    }
}

bool Game::UpdatePlayers( int &timeDiff )
{
    int alivePlayers = (int) m_Players.size();
    int humanPlayersAlive = 0;

    for ( int i = 0; i < (int) m_Players.size(); ++i ) {
        m_Players[i]->Update(timeDiff);
        if ( m_Players[i]->IsDead()) {
            alivePlayers--;
        }else if ( m_Players[i]->IsHuman()){
            humanPlayersAlive ++;
        }
    }

    return alivePlayers <= 1 || humanPlayersAlive < 1;
}


