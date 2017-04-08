#include <curses.h>



WINDOW *actualize_window(WINDOW *old_win) {
	WINDOW	*win = newwin(50, COLS - 2 , (LINES - 50) / 2, 1);

	delwin(old_win);

	return win;
}


int		main(){
	bool	exit = false;

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	nodelay(stdscr, TRUE); /* Doesn't wait for user to press a key*/
	int ch;

	WINDOW	*win = newwin(50, COLS - 2 , (LINES - 50) / 2, 1);

	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	while(!exit) {
		ch = getch();

		if (ch == 4 || ch == 3 || ch == 27){
			exit = true;
		} else if (ch == 410) {// corresponds to the user changing the size of the screen
			win = actualize_window(win);
			wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
			wrefresh(win);
		} else if (ch != ERR){
			printw("%d\n", ch);

			box(win, 0 , 0);
		}
		wrefresh(win);
	}


	endwin();
}