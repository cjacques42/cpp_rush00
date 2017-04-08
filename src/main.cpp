#include "ft_retro.hpp"

int 	ft_min(int a, int b){
	return (a > b ? b : a);
}

int 	ft_max(int a, int b){
	return (a > b ? a : b);
}


WINDOW *actualize_window(WINDOW *old_win) {

	WINDOW	*win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);

	delwin(old_win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	return win;
}


int		main(){
	bool	exit = false;

	initscr();				/* Start curses mode 		*/
	raw();					/* Line buffering disabled	*/
	keypad(stdscr, TRUE);	/* We get F1, F2 etc..		*/
	noecho();				/* Don't echo() while we do getch */
	nodelay(stdscr, TRUE); 	/* Doesn't wait for user to press a key*/
	int ch;
	Player	p;

	WINDOW	*win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);

	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	while(!exit) {
		ch = getch();

		if (ch == 4 || ch == 3 || ch == 27){
			exit = true;
		} else if (ch == 410) {		// corresponds to the user changing the size of the screen
			win = actualize_window(win);
		} else if (ch != ERR){
			printw("%d\n", ch);
		}
		p.display(win);
		wrefresh(win);
	}


	endwin();
}