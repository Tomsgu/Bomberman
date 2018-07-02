#ifndef BOMBERMAN_NCURSESWINDOW_H
#define BOMBERMAN_NCURSESWINDOW_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "../Exceptions/InvalidArgumentException.h"
#include "../Game/Map.h"

/**
 * \brief The wrapper for the ncurses window.
 */
class WindowNcurses
{
    public:
        WindowNcurses( void );
        ~WindowNcurses( void );
        /**
         * \brief Destroy this window.
         */
        void DestroyWindow( void );
        /**
         * \brief Creates new window.
         */
        void CreateNewWindow( const int &height, const int &width, const int &startY, const int &startX );
        /**
         * \brief Add the centered text to the window.
         * @param text The text.
         * @param line The row where the text should appear.
         */
        void AddCenteredText( const std::string &text, const int &line );
        /**
         * \brief Refresh this window.
         */
        void Refresh( void );
        /**
         * \brief Clear the window.
         */
        void Clear(void);
        /**
         * \brief Render a menu.
         * @param items The menu items.
         * @param option The selected option.
         * @param title The title for the menu.
         */
        void RenderMenu( const std::vector<std::string> &items, const int &option, const std::string &title );
        /**
         * \brief Display highscores on this window.
         * @param highScores
         */
        void RenderHighScores( const std::vector<std::pair<std::string, int>> highScores );
        /**
         * \brief Render the given map on this window.
         * @param map
         */
        void RenderMap( const std::shared_ptr<Map> &map );

        /**
         * \brief Render score of a winner.
         * @param score The score of a winner.
         */
        void RenderScore( const int &score, const int &playerID );

        /**
         * \brief Resize window if needed.
         */
        void ResizeWindow ( const int &rows, const int &cols );
    private:
        WINDOW * m_Window; //!< \brief The ncurses window.
        int      m_Size; //! \brief The size of the window.

        /**
         * \brief Prints the object mark to the specified position.
         */
        void PrintMark( const char &mark, const int &size, const int &row, const int &col );
};


#endif //BOMBERMAN_NCURSESWINDOW_H
