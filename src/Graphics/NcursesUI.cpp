#include "NcursesUI.h"
#include "../Game/Game.h"

using namespace std;

void voidendwin()
{
    endwin();
}

NcursesUI::NcursesUI( void )
{
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    nonl();
    cbreak();
    noecho();
    curs_set(FALSE);
    atexit(voidendwin);

    /// Init all colors.
    for ( short background = 0, i = 1; background < 8; ++background ) {
        for ( short foreground = 0; foreground < 8; ++foreground, ++i ) {
            init_pair(i, foreground, background);
        }
    }
    refresh();
}

NcursesUI::~NcursesUI( void )
{
    endwin();
}

int NcursesUI::MenuDialog( const vector<string> &menuItems, const string &title )
{
    WindowNcurses window;
    int           choice = 0;
    int           pressedKey;

    window.CreateNewWindow(LINES, COLS, 0, 0);
    while ( true ) {
        window.RenderMenu(menuItems, choice, title);
        pressedKey = wgetch(stdscr);
        switch ( pressedKey ) {
            case KEY_DOWN:
            case 'j':
                choice++;
                break;
            case KEY_UP:
            case 'k':
                choice--;
                break;
            case 13:
            case ' ':
                return choice;
            case 'q':
            case 27: // Escape
                return -1;
            default:
                usleep(DELAY); // Shorter delay between movements
                break;
        }

        if ( choice >= (int) menuItems.size()) {
            choice--;
        } else if ( choice < 0 ) {
            choice++;
        }
    }
}

void NcursesUI::ShowHighScores( const vector<pair<string, int>> &highScores )
{
    WindowNcurses window;

    window.CreateNewWindow(LINES, COLS, 0, 0);
    window.RenderHighScores(highScores);
    while ( true ) {
        switch ( wgetch(stdscr)) {
            case 13:
            case ' ':
                return;
            default:
                usleep(DELAY);
                break;
        }
    }
}

void NcursesUI::CreateGameWindow( const int &lines, const int &cols )
{
    if ( LINES >= lines * 3 && COLS >= cols * 3 ) {
        m_GameWindow.CreateNewWindow(lines * 3, cols * 3, ( LINES - lines * 3 ) / 2, ( COLS - cols * 3 ) / 2);
    } else {
        m_GameWindow.CreateNewWindow(lines, cols, ( LINES - lines ) / 2, ( COLS - cols ) / 2);
    }
}

void NcursesUI::RefreshMap( shared_ptr<Map> map )
{
    m_GameWindow.RenderMap(map);
}

void NcursesUI::RenderResult( const int &result, const int &playerID )
{
    WindowNcurses window;

    window.CreateNewWindow(LINES, COLS, 0, 0);
    window.RenderScore(result, playerID);

    while ( true ) {
        if ( wgetch(stdscr) == ERR) {
            usleep(DELAY);
        } else {
            break;
        }
    }
}

void NcursesUI::GetNickname( std::string &nickname )
{
    WindowNcurses window;
    string        message = "Please enter your name:";


    window.CreateNewWindow(LINES, COLS, 0, 0);
    window.AddCenteredText(message, LINES / 2);
    window.Refresh();
    // let the terminal do the line editing

    int ch;
    nickname = "";
    echo();

    move(( LINES / 2 ), ( COLS / 2 ) + (int) message.size() / 2 + 2);

    timeout(-1);

    ch = getch();
    while ( ch != 13 ) {
        nickname.push_back((char) ch);
        ch = getch();
    }

    nodelay(stdscr, TRUE);
    noecho();

}

bool NcursesUI::PauseGame( void )
{
    WINDOW * subwindow = newwin(8, 40, LINES / 2, COLS / 2 - 20);
    int pressedKey;

    refresh();
    box(subwindow, 0, 0);
    mvwprintw(subwindow, 1, 1, "PAUSE");
    mvwprintw(subwindow, 3, 1, "Press any key to continue.");
    mvwprintw(subwindow, 4, 1, "Press q to return to the main menu.");
    refresh();
    wrefresh(subwindow);

    while ( true ) {
        timeout(-1);
        pressedKey = wgetch(stdscr);
        timeout(0);
        switch ( pressedKey ) {
            case 'q': // end game
                return true;
            case ERR:
                usleep(DELAY);
                break;
            default:
                return false;
        }
    }
}






