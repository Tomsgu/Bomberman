#include "Application.h"

Application::Application( void )
{
    // initialize random seed */
    srand(time(NULL));

    //
    switch ( m_Config.GetUiChoice()) {
        case Configuration::UI_NCURSES:
            m_Ui = std::unique_ptr<GraphicUI>(new NcursesUI());
            break;
        case Configuration::UI_TERMINAL:
            // Terminal UI
            // m_Ui = unique_ptr<GraphicUI>(new TerminalUI());
            break;
        default:
            throw InvalidConfigurationException();
    }

    m_MenuItems = {
            "Play singleplayer",
            "Play multiplayer",
            "Highscores",
            "Quit"
    };

    m_Levels = m_LevelLoader.GetLevels();
}

void Application::Run( void )
{
    int option, choice, score, playerID;

    while ( true ) {
        Game game(m_Ui);

        option = m_Ui->MenuDialog(m_MenuItems, "Main menu");
        switch ( option ) {
            case MENU_PLAY_SINGLEPLAYER:
            case MENU_PLAY_MULTIPLAYER:
                choice = m_Ui->MenuDialog(m_Levels, "Choose level:");
                if ( choice == -1 ) {
                    break;
                }
                m_LevelLoader.LoadLevel(m_Levels[choice], game, option == MENU_PLAY_MULTIPLAYER);
                score = game.Play(playerID);
                if ( option == MENU_PLAY_SINGLEPLAYER ) {
                    WriteScore(score, option, playerID, choice);
                }
                break;
            case MENU_HIGHSCORES:
                choice = m_Ui->MenuDialog(m_Levels, "Choose level:");
                if ( choice == -1 ) {
                    break;
                }
                m_Ui->ShowHighScores(m_HighScoresManager.GetHighScores(m_Levels[choice]));
                break;
            case MENU_QUIT:
                return;
            case -1:
                return;
            default:
                throw InvalidArgumentException();
        }
    }
}

void Application::WriteScore( const int &score, const int &mode, const int &playerID, const int &levelChoice )
{
    std::string nickname;

    if ( playerID > -1 ) {
        m_Ui->GetNickname(nickname);
        m_HighScoresManager.SaveHighScore(score, mode, nickname, m_Levels[levelChoice]);
    }
}


