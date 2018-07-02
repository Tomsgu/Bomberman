#include "WindowNcurses.h"

using namespace std;

WindowNcurses::WindowNcurses()
{
}

void WindowNcurses::CreateNewWindow( const int &lines, const int &cols, const int &startY, const int &startX )
{
    m_Window = newwin(lines, cols, startY, startX);
    box(m_Window, 0, 0); // Show borders
    wrefresh(m_Window);
}

WindowNcurses::~WindowNcurses()
{
    DestroyWindow();
}

void WindowNcurses::DestroyWindow( void )
{
    wborder(m_Window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(m_Window);
    delwin(m_Window);
}

void WindowNcurses::AddCenteredText( const string &text, const int &line )
{
    int textSize = (int) text.size();

    mvwaddstr(m_Window, line, ( COLS / 2 ) - ( textSize / 2 ), text.c_str());
}

void WindowNcurses::Refresh( void )
{
    wrefresh(m_Window);
}

void WindowNcurses::RenderMenu( const vector<string> &items, const int &option, const string &title )
{
    int    line = ( LINES / 2 ) - ((int) items.size() / 2 ); // In the center of the window.
    string text;

    Clear();
    AddCenteredText("Bomberman !!", 1);
    AddCenteredText(title, line - 2);
    for ( int i = 0; i < (int) items.size(); ++i ) {
        text = option == i ? ( "-> " + items[i] + " <-" ) : items[i];
        AddCenteredText(text, line++);
    }
    Refresh();
}

void WindowNcurses::RenderHighScores( const vector<pair<string, int>> highScores )
{
    int    line = ( LINES / 2 ) - ((int) highScores.size() / 2 ); // In the center of the window.
    string text;

    Clear();
    for ( int i = 0; i < (int) highScores.size(); ++i ) {
        text = highScores[i].first + " " + to_string(highScores[i].second);
        AddCenteredText(text, line++);
    }
    Refresh();
}

void WindowNcurses::PrintMark( const char &mark, const int &size, const int &row, const int &col )
{
    string border = "   ";

    if ( mark == '@' ) {
        border = "@ @";
    }
    if ( size == 3 ) {
        mvwprintw(m_Window, row, col, border.c_str());
        mvwprintw(m_Window, row + 1, col, " %c ", mark);
        mvwprintw(m_Window, row + 2, col, border.c_str());
    } else {
        mvwprintw(m_Window, row, col, "%c", mark);
    }
}

void WindowNcurses::ResizeWindow( const int &rows, const int &cols )
{
    int previousSize = m_Size;

    m_Size = ( LINES >= rows * 3 && COLS >= cols * 3 ) ? 3 : 1;
    if ( previousSize != m_Size ) {
        DestroyWindow();
        CreateNewWindow(rows * m_Size, cols * m_Size, ( LINES - rows * m_Size ) / 2, ( COLS - cols * m_Size ) / 2);
    }
}

void WindowNcurses::RenderMap( const shared_ptr<Map> &map )
{
    char mark;
    int  color;

    Clear();
    ResizeWindow(map->Rows(), map->Cols());
    for ( int i = 0, ii = 0; i < map->Rows(); ++i, ii += m_Size ) {
        string    line = "";
        for ( int j    = 0, jj = 0; j < map->Cols(); ++j, jj += m_Size ) {
            mark  = map->Mark(i, j);
            color = map->Color(i, j);
            wattron (m_Window, COLOR_PAIR(color));
            PrintMark(mark, m_Size, ii, jj);
            wattroff (m_Window, COLOR_PAIR(color));
        }
        AddCenteredText(line, i);
    }
    Refresh();
}

void WindowNcurses::RenderScore( const int &score, const int &playerID )
{
    string scoreMes = "Your score is " + to_string(score);

    wclear(m_Window);
    if ( playerID > -1) {
        AddCenteredText("Congratulations you've won!", LINES / 2);
        AddCenteredText(scoreMes.c_str(), LINES / 2 + 1);
        AddCenteredText("Press any key to continue.", LINES / 2 + 4);
    }else{
        AddCenteredText("Sorry... try another one!", LINES / 2);
        AddCenteredText("Press any key to continue.", LINES / 2 + 3);
    }

    Refresh();
}

void WindowNcurses::Clear( void )
{
    werase(m_Window);
    box(m_Window, 0, 0); // Show borders
}

